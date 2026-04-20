/*
Brendan My
April 2026
*/
#include "TrueFalseQuestion.h"

// Contructor that uses the base constructor then sets correctAnswer
TrueFalseQuestion::TrueFalseQuestion(const std::string& inputQuestionText, bool inputCorrectAnswer, int inputPoints) : Question(inputQuestionText, inputPoints) {
    correctAnswer = inputCorrectAnswer; // Set to either true or false
}
// Default constructor
TrueFalseQuestion::TrueFalseQuestion() : Question() {
    correctAnswer = true; // Default to true
}
// Displaying question to user and prompts user with two choices: 1. True or 2. False
void TrueFalseQuestion::display() const {
    std::cout << "\n" << questionText << "\n\n"; 
    std::cout << "1. True\n" << "2. False\n";
}
// Checks whether the user answer selection is correct/matches the correct answer
bool TrueFalseQuestion::checkAnswer(int userChoice) const {
    if (userChoice == 1 && correctAnswer == true) {
        return true;
    } else if (userChoice == 2 && correctAnswer == false) {
        return true;
    } 
    return false;
}
// Saving a true or false question to a file (files wont actual)
void TrueFalseQuestion::saveToFile(std::ofstream &outFile) const { 
    outFile << "TrueOrFalse" << "\n"; // Writes/saves the category of this question
    outFile << questionText << "\n"; // Write/saves the question's question
    // Writing correct true or false answer
    if (correctAnswer == true) { 
        outFile << "true" << "\n";
    } else {
        outFile << "false" << "\n";
    }
    outFile << points << "\n"; // Writing quesiton point value
}

std::string TrueFalseQuestion::getType() const {
    return "True or False"; // Needed for setting up question prompt to user for better clearity
}
int TrueFalseQuestion::getNumChoices() const {
    return 2; // There could only be two options so this will always be 2
}
bool TrueFalseQuestion::getCorrectAnswer() const {
    return correctAnswer;
}