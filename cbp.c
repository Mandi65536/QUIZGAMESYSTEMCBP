#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERS 100
#define TIME_PER_QUESTION 10

typedef struct {
    char question[256];
    char options[4][64];
    int correct_option;
} Question;

/* ---------- Utility ---------- */

void clearInputBuffer() {
    while (getchar() != '\n');
}

void displayQuestion(Question q) {
    printf("\n%s\n", q.question);
    for (int i = 0; i < 4; i++)
        printf("%d. %s\n", i + 1, q.options[i]);
}

int checkAnswer(Question q, int ans) {
    return ans == q.correct_option;
}

/* ---------- Dynamic Question Loading ---------- */

Question* loadQuestions(const char *filename, int *total) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening questions file");
        return NULL;
    }

    Question *questions = NULL;
    int count = 0;

    while (1) {
        Question temp;

        if (!fgets(temp.question, 256, fp))
            break;

        temp.question[strcspn(temp.question, "\n")] = 0;

        for (int i = 0; i < 4; i++) {
            fgets(temp.options[i], 64, fp);
            temp.options[i][strcspn(temp.options[i], "\n")] = 0;
        }

        fscanf(fp, "%d\n", &temp.correct_option);

        questions = realloc(questions, (count + 1) * sizeof(Question));
        questions[count++] = temp;
    }

    fclose(fp);
    *total = count;
    return questions;
}

/* ---------- CSV Score Handling ---------- */

int countUsersCSV(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return 0;

    int lines = 0;
    char line[200];
    while (fgets(line, sizeof(line), fp))
        lines++;

    fclose(fp);
    return (lines > 0) ? lines - 1 : 0;
}

void saveScoreCSV(const char *filename, char username[],
                  int score, int total, int timeTaken) {

    int userCount = countUsersCSV(filename);
    if (userCount >= MAX_USERS) {
        printf("Score history full (max 5 users).\n");
        return;
    }

    FILE *fp = fopen(filename, "a");
    if (!fp) {
        printf("Error opening score file!\n");
        return;
    }

    if (userCount == 0)
        fprintf(fp, "Username,Score,TotalQuestions,TimeTaken\n");

    fprintf(fp, "%s,%d,%d,%d\n",
            username, score, total, timeTaken);

    fclose(fp);
}

void viewScoreHistoryCSV(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("\nNo score history available.\n");
        return;
    }

    char line[200], username[30];
    int score, total, timeTaken;

    fgets(line, sizeof(line), fp); // skip header

    printf("\n========== SCORE HISTORY ==========\n");
    printf("%-15s %-10s %-15s\n",
           "Username", "Score", "Time(sec)");
    printf("-----------------------------------------\n");

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^,],%d,%d,%d",
               username, &score, &total, &timeTaken);
        printf("%-15s %2d/%-6d %-15d\n",
               username, score, total, timeTaken);
    }

    fclose(fp);
}

/* ---------- Quiz ---------- */

void startQuiz() {
    char username[30];
    printf("\nEnter username: ");
    scanf("%29s", username);

    int total_questions;
    Question *questions = loadQuestions("questions.txt", &total_questions);

    if (!questions || total_questions == 0)
        return;

    int remaining = total_questions;
    int score = 0;
    int totalTime = total_questions * TIME_PER_QUESTION;

    printf("\nQuiz Started\n");
    printf("Total Time Allowed: %d seconds\n", totalTime);

    time_t startTime = time(NULL);

    while (remaining > 0) {
        if (difftime(time(NULL), startTime) >= totalTime) {
            printf("\nTime's up!\n");
            break;
        }

        int index = rand() % remaining;
        displayQuestion(questions[index]);

        int ans;
        printf("Enter your answer (1-4): ");
        if (scanf("%d", &ans) != 1 || ans < 1 || ans > 4) {
            printf("Invalid input!\n");
            clearInputBuffer();
            continue;
        }

        if (checkAnswer(questions[index], ans))
            score++;

        questions[index] = questions[remaining - 1];
        remaining--;
    }

    int timeTaken = (int)difftime(time(NULL), startTime);

    printf("\nQuiz Completed!\n");
    printf("Username: %s\n", username);
    printf("Score: %d/%d\n", score, total_questions);
    printf("Time Taken: %d seconds\n", timeTaken);

    saveScoreCSV("score_history.csv",
                 username, score, total_questions, timeTaken);

    free(questions);
}

/* ---------- Menu ---------- */

int main() {
    srand(time(NULL));
    int choice;

    do {
        printf("\n===== QUIZ MENU =====\n");
        printf("1. Start Quiz\n");
        printf("2. View Score History\n");
        printf("3. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            continue;
        }

        switch (choice) {
        case 1:
            startQuiz();
            break;
        case 2:
            viewScoreHistoryCSV("score_history.csv");
            break;
        case 3:
            printf("Thank you!\n");
            break;
        default:
            printf("Invalid choice!\n");
        }

    } while (choice != 3);

    return 0;
}
