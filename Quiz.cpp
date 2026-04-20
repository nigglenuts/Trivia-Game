/*
Brendan My
April 2026
*/
#include "Quiz.h" 

Quiz::Quiz(const std::string& inputQuizName) { // Parameterized constructor
    quizName = inputQuizName;
}

Quiz::Quiz() { // Default constructor
    quizName = "Untitled Quiz";
}

Quiz::~Quiz() { // Destructor
    for (int i = 0; i < questions.size(); i++) { // Iterating through all pointers to delete them
        delete questions[i];
    }
    questions.clear(); // Clears questions vector
}

void Quiz::addQuestion(Question* q) {
    questions.push_back(q); // Adding question to end of vector
}

void Quiz::saveToFile(std::string filename) const { // Saving to the output file using a file name parameter
    std::ofstream outFile(filename); // Opening/creating a file with the filename
    if (!outFile.is_open()) { // Checks to see if file was successfully opened
        throw FileNotFoundException(filename); // Throwing FileNotFoundException from GameExceptions
    }

    outFile << quizName << "\n"; // Writing/saving the quiz name on the first line
    outFile << questions.size() << "\n"; // Writing/saving the number of questions on the second line
    
    for (int i = 0; i < questions.size(); i++) { // Loop through each question pointer
        questions[i]->saveToFile(outFile); 
    } 
    outFile.close(); // Close the file to finish writing
    std::cout << "\nQuiz saved successfully\n"; 
}
void Quiz::loadFromFile(std::string filename) {
    std::ifstream inFile(filename); // Opening the file with the filename
    if (!inFile.is_open()) { // Checks to see if file was successfully opened
        throw FileNotFoundException(filename); // Throwing FileNotFoundException from GameExceptions
    }
    for (int i = 0; i < questions.size(); i++) { // Loop through existing question pointers
        delete questions[i]; // Free memory from questions vector from previous quiz
    } 
    questions.clear(); // Clear the vector after freeing memory
    std::getline(inFile, quizName); // Read the quiz name from the first line
    int questionCount; // Variable to store how many questions to read
    inFile >> questionCount; // Reads and sets the questionCount from the second line
    inFile.ignore(); // Clears buffer from reading previous two

    for (int i = 0; i < questionCount; i++) { // Iterating through each question in quiz
        std::string type; // Storing question type (True/False and Multiple choice questions are stored different. True or false text layout: Question -> Correct answer -> Question Point Value. Multiple Choice text layout: Question -> Number of answer choices -> Answer choices -> Corrent answer index.)
        std::getline(inFile, type); // Read what type the question is
        if (type == "TrueOrFalse") {
            std::string questionText; // String variable for storing question
            std::getline(inFile, questionText); // Reading and storing question
            std::string answerStr; // String variable for storing answer
            std::getline(inFile, answerStr); // Reading and storing answer in answerStr
            bool answer = (answerStr == "true"); // If answerStr equals to "true" then the answer will be set to true. If answerStr does not equal to "true" then the answer boolean will be set to false 
            int pts; // Variable for the point value
            inFile >> pts; // Using >> instead of getline since pts is an int, and >> automatically converts the text in the file to an integer. getline can only read into strings, not integers.
            inFile.ignore(); 
            questions.push_back(new TrueFalseQuestion(questionText, answer, pts)); // Creating a TrueFalseQuestion object and adding it to the questions vector
        }
        else if (type == "MultipleChoice") {
            std::string questionText;
            std::getline(inFile, questionText); // Reading question and saving it to questionText variable
            int numChoices; // Variable for how many choices this question has
            inFile >> numChoices; // Using >> instead of getline since pts is an int, and >> automatically converts the text in the file to an integer. getline can only read into strings, not integers.
            inFile.ignore(); // Clear the newline character left after >> usage
            std::vector<std::string> choices; // Vector for answer choices
            for (int j = 0; j < numChoices; j++) { // Iterating through each answer choice
                std::string choice; 
                std::getline(inFile, choice); // Reading and saving answer choice from file
                choices.push_back(choice); // Adding answer choice to choices vector
            }
            int correctIndex;
            inFile >> correctIndex; 
            inFile.ignore(); 
            int pts; 
            inFile >> pts; 
            inFile.ignore(); 
            questions.push_back(new MultipleChoiceQuestion(questionText, choices, correctIndex, pts)); // Adding multiple choice question to end of questions array
        }
        else { // If it wasn't either MultipleChoice nor TrueOrFalse...
            inFile.close();
            throw CorruptFileException(filename); // Throwing CorruptFileException
        }
    }
    inFile.close(); 
}

int Quiz::play() const {
    if (questions.empty()) {
        throw EmptyQuizException(quizName);
    }
    int score = 0;
    int totalPossible = 0;
    std::cout <<"\n";
    std::cout << "Quiz: " << quizName << "\n";
    std::cout << "Number of questions: " << questions.size() << "\n";
    for (int i = 0; i < questions.size(); i++) { // Iterating through each question
        totalPossible += questions[i]->getPoints();
        std::cout << "\nQuestion " << (i + 1) << " of " << questions.size();
        std::cout << " (" << questions[i]->getType() << " - " << questions[i]->getPoints() << " pts)\n"; // Printing question type
        questions[i]->display(); // Virtual function for displaying derived classes
        int maxChoice = questions[i]->getNumChoices();
        int userChoice = 0;
        bool validInput = false;
        while (!validInput) {
            std::cout << "\nYour answer (1-" << maxChoice << "): ";
            if (std::cin >> userChoice) {
                if (userChoice >= 1 && userChoice <= maxChoice) { // Check if the number is in the valid range
                    validInput = true;
                } else {
                    std::cout << "Please enter a number between 1 and " << maxChoice << ".\n"; 
                }
            }
            else {
                std::cin.clear(); // Clearing error flag
                std::cin.ignore(10000, '\n'); // Safe overkill number
                std::cout << "Please enter a valid number.\n";
            }
        }
        std::cin.ignore(10000, '\n'); // Clearing remaining characters

        if (questions[i]->checkAnswer(userChoice)) { // Using virtual function to check answers for derived questions
            std::cout << "\nCorrect. +" <<  questions[i]->getPoints() << " points\n";
            score += questions[i]->getPoints();
        }
        else { // If is a true or false question...
            std::cout << "\nIncorrect. The correct answer was: ";
            if (questions[i]->getType() == "True or False") {
                TrueFalseQuestion* tfq = (TrueFalseQuestion*)questions[i];
                if (tfq->getCorrectAnswer() == true) {
                    std::cout << "True\n";
                }
                else {
                    std::cout << "False\n";
                }
            }
            else { // If is a multiple choice question...
                MultipleChoiceQuestion* mcq = (MultipleChoiceQuestion*)questions[i];
                std::cout << mcq->getChoices()[mcq->getCorrectAnswerIndex()] << "\n";
            }
        }
    }
    std::cout << "\n";
    std::cout << "Quiz complete.\n";
    std::cout << "Score: " << score << " / " << totalPossible << "\n";
    int percentage = (score * 100) / totalPossible;
    std::cout << "Percentage: " << percentage << "%\n";
    return score; 
}
std::string Quiz::getQuizName() const {
    return quizName;
}
// Quiz size getter
int Quiz::getQuestionCount() const {
    return questions.size();
}
// Quiz name setter
void Quiz::setQuizName(std::string inputQuizName) {
    quizName = inputQuizName;
}
