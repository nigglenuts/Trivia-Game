/*
Brendan My
April 2026
*/
#ifndef TrueFalseQuestion_h 
#define TrueFalseQuestion_h 
#include "Question.h" 

class TrueFalseQuestion : public Question {
    private:
    bool correctAnswer; 

    public:
    TrueFalseQuestion(const std::string& inputQuestionText, bool inputCorrectAnswer, int inputPoints);
    TrueFalseQuestion();
    void display() const override;
    bool checkAnswer(int userChoice) const override;
    void saveToFile(std::ofstream &outFile) const override; // Uses a parameter std::ofstream &outFile to save to a file to save quiz
    std::string getType() const override; // Used for setting up prompt to user
    int getNumChoices() const override; // Used for setting up prompt to user
    bool getCorrectAnswer() const;
};
#endif