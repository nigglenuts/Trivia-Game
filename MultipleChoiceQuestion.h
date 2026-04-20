/*
Brendan My
April 2026
*/
#ifndef MultipleChoiceQuestion_h
#define MultipleChoiceQuestion_h 
#include "Question.h" 
#include <vector> // Needed for std::vector to store answer choices

class MultipleChoiceQuestion : public Question {
    private:
    std::vector<std::string> choices; // Answer choices will be stored here
    int correctAnswerIndex;

    public:
    MultipleChoiceQuestion(const std::string& inputQuestionText, std::vector<std::string> inputChoices, int inputCorrectIndex, int inputPoints); // Parameterized constructor
    MultipleChoiceQuestion(); // Default constructor
    void display() const override;
    bool checkAnswer(int userChoice) const override;
    void saveToFile(std::ofstream &outFile) const override; // Saving to file function
    std::string getType() const override; // Used for setting up prompt to user
    int getNumChoices() const override; // Used for setting up prompt to user
    std::vector<std::string> getChoices() const; 
    int getCorrectAnswerIndex() const;
};
#endif
