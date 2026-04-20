/*
Brendan My
April 2026
*/
#include "Question.h"
// Constructors
Question::Question(const std::string& inputQuestionText, int inputPoints) { // Regardless of the question being true/false or multiple choice, every question will have a text as the question and a point value for the question
    questionText = inputQuestionText;
    points = inputPoints;
}
Question::Question() { // Default constructor
    questionText = "";
    points = 0;
}
// Destructor
Question::~Question() {} // Virtual destructor 

// Getters
std::string Question::getQuestionText() const { // Question getter
    return questionText;
}
int Question::getPoints() const { // Question point value getter
    return points;
}

// Setters
void Question::setQuestionText(std::string inputQuestionText) { // Question setter
    questionText = inputQuestionText;
}
void Question::setPoints(int inputPoints) { // Question point value setter
    points = inputPoints;
}

