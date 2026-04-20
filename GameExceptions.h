/*
Brendan My
April 2026
*/
#ifndef GameExceptions_h
#define GameExceptions_h
#include <string>

// Custom exception class for quiz errors
class QuizException {
    private:
    std::string message; // Saving error description
    public:
    QuizException(std::string inputMessage); // Constructor taking an error description
    std::string what(); 
};

// Is thrown when file can't successfully open a file
class FileNotFoundException : public QuizException {
    public:
    FileNotFoundException(std::string filename);
};

// Is thrown when the user inputs a number selection that isn't within the range of the option choices
class InvalidInputException : public QuizException {
    public:
    InvalidInputException(std::string detail);
};

// Is thrown when user plays a quiz that doesn't actually have any questions
class EmptyQuizException : public QuizException {
    public:
    EmptyQuizException(std::string quizName);
};

// Is thrown when there is bad data
class CorruptFileException : public QuizException {
    public:
    CorruptFileException(std::string filename);
};
#endif
