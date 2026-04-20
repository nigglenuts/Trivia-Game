/*
Brendan My
April 2026
*/
#include "GameExceptions.h"

// QuizException constructor (sets what the error message actually is)
QuizException::QuizException(std::string inputMessage) {
    message = inputMessage;
}
// Returning error message
std::string QuizException::what() {
    return message;
}

FileNotFoundException::FileNotFoundException(std::string filename) : QuizException("Error: " + filename + " not found.") {}
InvalidInputException::InvalidInputException(std::string detail) : QuizException("Error: " + detail + " is an invalid input.") {}
EmptyQuizException::EmptyQuizException(std::string quizName) : QuizException("Error: Quiz '" + quizName + "' has no questions.") {}
CorruptFileException::CorruptFileException(std::string filename) : QuizException("Error: " + filename + " is corrupted and could not be read.") {}


