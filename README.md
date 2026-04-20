Trivia Game
A terminal-based trivia game built in C++ that allows users to create, play, view, and delete quizzes. Questions can be either True/False or Multiple Choice, and quiz sets are saved as text files within the project directory.
Features

- Create custom quizzes with True/False and Multiple Choice questions
- Play quizzes and receive a score at the end
- View and delete saved quizzes
- Quiz data persists between sessions via text files

Type the following to create an executable called "trivia":
  g++ -o trivia main.cpp Question.cpp TrueFalseQuestion.cpp MultipleChoiceQuestion.cpp Quiz.cpp GameExceptions.cpp

In order for quizzes to show up in the executable, they must be listed in the quiz_list.txt inside the quizzes folder in the project.
