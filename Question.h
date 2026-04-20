/*
Brendan My
April 2026
*/
#ifndef Question_h
#define Question_h
#include <iostream>
#include <string>
#include <fstream>

// Base class for all questions
class Question {
protected: // Using protected for derived classes
    std::string questionText; // Question string
    int points; // Question point value
public:
    Question(const std::string& inputQuestionText, int inputPoints); // Constructor taking a question and point value
    Question(); // Default constructor 
    virtual ~Question(); // Destructor
    
    // Pure virtual functions 
    virtual void display() const = 0; // Pure virtual function for displaying questions
    virtual bool checkAnswer(int userChoice) const = 0; // Pure virtual function to check if user choice is the correct choice
    virtual void saveToFile(std::ofstream &outFile) const = 0; // Uses a parameter std::ofstream &outFile since questions will be added to files for organization
    virtual std::string getType() const = 0; 
    virtual int getNumChoices() const = 0; // Pure virtual function to get the number of choices for a multiple choice question to setup prompt for user

    // Getters
    std::string getQuestionText() const;
    int getPoints() const;

    // Setters
    void setQuestionText(std::string inputQuestionText); // Sets question
    void setPoints(int inputPoints); // Sets question point value
};
#endif


