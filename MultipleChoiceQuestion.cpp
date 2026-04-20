/*
Brendan My
April 2026
*/
#include "MultipleChoiceQuestion.h" 

MultipleChoiceQuestion::MultipleChoiceQuestion(const std::string& inputQuestionText, std::vector<std::string> inputChoices, int inputCorrectIndex, int inputPoints) : Question(inputQuestionText, inputPoints) { // Parameterized constructor
    choices = inputChoices; // Sets number of choices
    correctAnswerIndex = inputCorrectIndex; // Sets which index in the array is the correct one
}
MultipleChoiceQuestion::MultipleChoiceQuestion() : Question() { // Default constructor
    correctAnswerIndex = 0;
}
void MultipleChoiceQuestion::display() const { // Displaying question and answer choices to user  
    std::cout << "\n" << questionText << "\n\n";
    for (int i = 0; i < choices.size(); i++) {
        std::cout << (i + 1) << ". " << choices[i] << "\n"; // To make things intuitive, 1 will be added to i since we don't want an answer choice number to be zero
    }
}
bool MultipleChoiceQuestion::checkAnswer(int userChoice) const {
    if ((userChoice - 1) == correctAnswerIndex) {
        return true;
    }
    return false;
}

void MultipleChoiceQuestion::saveToFile(std::ofstream &outFile) const { // Saving to the output file stream
    outFile << "MultipleChoice" << "\n"; // Writes/saves question category
    outFile << questionText << "\n"; // Writes/saves the question text on the next line
    outFile << choices.size() << "\n"; // Writes/saves how many choices there are
    for (int i = 0; i < choices.size(); i++) {
        outFile << choices[i] << "\n"; // Writing/saving each choice on its own line
    } // End of for loop
    outFile << correctAnswerIndex << "\n"; // Writing/saving correct answer via index
    outFile << points << "\n"; // Writing/saving question point value
}
std::string MultipleChoiceQuestion::getType() const {
    return "Multiple Choice";
}
int MultipleChoiceQuestion::getNumChoices() const {
    return choices.size();
}
std::vector<std::string> MultipleChoiceQuestion::getChoices() const { // Gets answer choices
    return choices;
}
int MultipleChoiceQuestion::getCorrectAnswerIndex() const { // Gets correct answer index
    return correctAnswerIndex;
}

