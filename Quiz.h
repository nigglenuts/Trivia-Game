/*
Brendan My
April 2026
*/
// Base class for quizzes
#ifndef Quiz_h 
#define Quiz_h 
#include "Question.h" 
#include "TrueFalseQuestion.h"
#include "MultipleChoiceQuestion.h"
#include "GameExceptions.h"
#include <vector> 
#include <string> 

class Quiz {
    private:
    std::string quizName;
    std::vector<Question*> questions; // Stores pointers to Question objects in a vector so the user can dynamically add to the Quiz

    public:
    Quiz(const std::string& inputQuizName); // Parameterized constructor 
    Quiz(); // Default constructor
    ~Quiz(); // Destructor
    void addQuestion(Question* q); // Adds a question pointer to the vector
    void saveToFile(std::string filename) const; // Saves the quiz to a text file using ofstream
    void loadFromFile(std::string filename); // Loads the quiz from a text file using ifstream
    int play() const; // Plays quiz and returns the score


    // Setter
    void setQuizName(std::string inputQuizName); // Sets the quiz name

    // Getters
    std::string getQuizName() const; // Returns the quiz name
    int getQuestionCount() const; // Returns how many questions are in the quiz
};
#endif
    
