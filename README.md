📚 Quiz System in C – README
1. Project Title

Dynamic Menu-Driven Quiz System with CSV Score Storage in C

2. Description

This project implements a dynamic, menu-driven quiz game in C.
The system supports:

1)Loading an unlimited number of questions from a text file.

2)Randomized question selection during the quiz.

3)Timed quizzes, with total time calculated based on the number of questions.

4)Input validation for safe user entries.

5)Score recording in a CSV file (score_history.csv) for up to 5 users.

6)Formatted score history display for clear, readable output.

7)Covers topics from UNIT I to UNIT V of the syllabus.

3. Features

Dynamic Question Loading

Supports any number of questions stored in a text file (questions.txt).

Uses pointers and dynamic memory allocation (malloc and realloc).

Menu-Driven Interface

Start Quiz

View Score History

Exit

Timed Quiz

Total time = Number of questions × 10 seconds (configurable via TIME_PER_QUESTION macro).

Quiz ends automatically if time expires.

Score Storage

Scores stored in CSV format (score_history.csv) for easy reading in Excel or Google Sheets.

Maximum of 5 users stored at a time.

CSV columns: Username,Score,TotalQuestions,TimeTaken.

Formatted Score Display

Displays scores in tabular format:

Username       Score     Time(sec)
-----------------------------------------
Manideep       5 / 10    42
Ravi           8 / 10    48


Input Validation

Handles invalid input (non-integer or out-of-range values).

Prevents crashes due to bad user input.

4. Files Included
File Name	Description
quiz.c	Main C program implementing the quiz system.
questions.txt	Sample questions for the quiz (text file).
score_history.csv	Automatically generated CSV file to store scores.
README.md	Project description and instructions.
5. questions.txt Format

Each question should follow this structure:

Question text
Option 1
Option 2
Option 3
Option 4
Correct option number (1-4)


Example:

Which bird lays the largest egg?
Owl
Ostrich
Kingfisher
Woodpecker
2


Notes:

No blank lines between questions.

Correct option number is 1-4.

6. How to Run

Make sure quiz.c and questions.txt are in the same folder.

Compile the program using GCC:

gcc quiz.c -o quiz


Run the program:

./quiz       # Linux / macOS
quiz.exe     # Windows


Follow the menu instructions to start the quiz or view score history.

7. How It Works

1)Loading Questions

2)The program dynamically loads all questions from questions.txt using malloc/realloc.

3)Starting the Quiz

4)Each question is randomly picked.

5)User answers using numbers 1–4.

6)Score is tracked and time is measured.

7)Storing Scores

8)After quiz completion, score and time taken are saved in score_history.csv.

9)CSV header is automatically created if file is empty.

10)Viewing Scores

11)Scores are displayed in a readable table.

8. Configuration
Macro	Description	Default
TIME_PER_QUESTION	Seconds per question	10
MAX_USERS	Maximum number of users stored in CSV	5
9. Sample Output
===== QUIZ MENU =====
1. Start Quiz
2. View Score History
3. Exit
Enter choice: 1

Enter username: Manideep
Quiz Started
Total Time Allowed: 50 seconds

Which bird lays the largest egg?
1. Owl
2. Ostrich
3. Kingfisher
4. Woodpecker
Enter your answer (1-4): 2

Quiz Completed!
Username: Manideep
Score: 5/10
Time Taken: 42 seconds
Score saved to score_history.csv

10. Advantages

1)Fully dynamic – can handle any number of questions.

2)CSV storage allows easy analytics and leaderboard creation.

3)Menu-driven interface is user-friendly.

4)Implements pointers, file handling, dynamic memory allocation, and input validation – great for exam demonstration.

11. Future Improvements

1)Unit-wise or difficulty-wise question selection.

2)Leaderboard sorting by score.

3)Option to reset or delete score history.

4)Support for binary file storage for secure scores.
