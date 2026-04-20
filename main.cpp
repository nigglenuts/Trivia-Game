/*
Brendan My
April 2026
*/
#include "Quiz.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio> // For deleting files

std::string quizDirectory = "quizzes/"; // Quizzes are located inside a folder named quizzes
std::string quizListFile = "quizzes/quiz_list.txt"; // The quiz list file is inside the quizzes folder name as quiz_list.txt

// Reads quiz_list.txt and returns a vector of quiz filenames
std::vector<std::string> getQuizFiles();
// Writes quiz filenames to quiz_list.txt
void saveQuizList(std::vector<std::string> files);
// Gets valid number input from user within a range
int getValidInput(int minVal, int maxVal);
// Displays available quizzes and returns filenames
std::vector<std::string> displayQuizList();
// Lets the user pick and play a quiz
void playQuiz();
// Walks the user through creating a new quiz
void createQuiz();
// Shows all saved quizzes
void viewQuizzes();
// Lets the user pick and delete a quiz
void deleteQuiz();

int main() {
    std::cout << "\nWelcome to the Trivia Game!\n\n";

    bool exitProgram = false;

    while (!exitProgram) {
        int choice;
        std::cout << "Select an option:\n";
        std::cout << "1. Play a Quiz\n";
        std::cout << "2. Create a Quiz\n";
        std::cout << "3. View All Quizzes\n";
        std::cout << "4. Delete a Quiz\n";
        std::cout << "5. Quit Program\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch(choice) {
            case 1:
                playQuiz();
                break;
            case 2:
                createQuiz();
                break;
            case 3:
                viewQuizzes();
                break;
            case 4:
                deleteQuiz();
                break;
            case 5:
                exitProgram = true;
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
    std::cout << "Goodbye!\n";
    return 0;
}

std::vector<std::string> getQuizFiles() { // Reads quiz_list.txt and returns a vector of quiz filenames
    std::vector<std::string> files;
    std::ifstream inFile(quizListFile);

    if (inFile.is_open()) {
        std::string filename;
        while (std::getline(inFile, filename)) {
            if (filename.size() > 0) {
                files.push_back(filename);
            }
        }
        inFile.close();
    }
    return files;
}

// Writes quiz filenames to quiz_list.txt
void saveQuizList(std::vector<std::string> files) {
    std::ofstream outFile(quizListFile);

    if (outFile.is_open()) {
        for (int i = 0; i < files.size(); i++) {
            outFile << files[i] << "\n";
        }
        outFile.close();
    }
}

// Gets valid number input from user within a range
int getValidInput(int minVal, int maxVal) {
    int choice;

    while (true) {
        std::cout << "Enter your choice (" << minVal << "-" << maxVal << "): ";
        if (std::cin >> choice) {
            if (choice >= minVal && choice <= maxVal) {
                std::cin.ignore(10000, '\n');
                return choice;
            } else {
                std::cout << "Invalid choice. Please try again.\n";
            }
        } else {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number.\n";
        }
    }
}

// Displays available quizzes and returns filenames
std::vector<std::string> displayQuizList() {
    std::vector<std::string> files = getQuizFiles();

    if (files.empty()) {
        std::cout << "\nNo quizzes available. Create one first!\n\n";
        return files;
    }

    std::cout << "\nAvailable Quizzes:\n";
    for (int i = 0; i < files.size(); i++) {
        try {
            Quiz tempQuiz;
            tempQuiz.loadFromFile(quizDirectory + files[i]);
            std::cout << (i + 1) << ". " << tempQuiz.getQuizName() << " (" << tempQuiz.getQuestionCount() << " questions)\n";
        } catch (QuizException &e) {
            std::cout << (i + 1) << ". " << files[i] << " [corrupted]\n";
        }
    }
    std::cout << (files.size() + 1) << ". Back to Main Menu\n\n";

    return files;
}

// Lets the user pick and play a quiz
void playQuiz() {
    std::vector<std::string> files = displayQuizList();

    if (files.empty()) {
        return;
    }

    int selection = getValidInput(1, files.size() + 1);

    if (selection == (int)files.size() + 1) {
        return;
    }

    try {
        Quiz quiz;
        quiz.loadFromFile(quizDirectory + files[selection - 1]);
        quiz.play();
    } catch (QuizException &e) {
        std::cout << e.what() << "\n";
    }
}

// Walks the user through creating a new quiz
void createQuiz() {
    Quiz* newQuiz = new Quiz();
    int questionNum = 0;

    std::cout << "\nCreate a New Quiz\n";
    std::cout << "Add questions to your quiz. Select save when done.\n\n";

    bool doneCreating = false;

    while (!doneCreating) {
        std::cout << "Questions added so far: " << questionNum << "\n";
        std::cout << "1. Create a True or False Question\n";
        std::cout << "2. Create a Multiple Choice Question\n";
        std::cout << "3. Save Quiz and Return to Main Menu\n";

        int choice = getValidInput(1, 3);

        if (choice == 1) {
            std::string questionText;
            int answer;
            int ptsChoice;
            int pointValues[] = {5, 10, 15, 20};

            std::cout << "\nEnter the True or False question:\n> ";
            std::getline(std::cin, questionText);

            std::cout << "\nWhat is the correct answer?\n";
            std::cout << "1. True\n";
            std::cout << "2. False\n";
            answer = getValidInput(1, 2);

            std::cout << "\nHow many points is this question worth?\n";
            std::cout << "1. 5 pts\n";
            std::cout << "2. 10 pts\n";
            std::cout << "3. 15 pts\n";
            std::cout << "4. 20 pts\n";
            ptsChoice = getValidInput(1, 4);

            bool correctAnswer = (answer == 1);
            newQuiz->addQuestion(new TrueFalseQuestion(questionText, correctAnswer, pointValues[ptsChoice - 1]));
            questionNum++;
            std::cout << "\nQuestion added.\n\n";

        } else if (choice == 2) {
            std::string questionText;
            int numChoices;
            int correctChoice;
            int ptsChoice;
            int pointValues[] = {5, 10, 15, 20};
            std::vector<std::string> choices;

            std::cout << "\nEnter the Multiple Choice question:\n> ";
            std::getline(std::cin, questionText);

            std::cout << "\nHow many answer choices? (2-6)\n";
            numChoices = getValidInput(2, 6);

            for (int i = 0; i < numChoices; i++) {
                std::string choiceText;
                std::cout << "Enter choice " << (i + 1) << ":\n> ";
                std::getline(std::cin, choiceText);
                choices.push_back(choiceText);
            }

            std::cout << "\nWhich choice is the correct answer? (1-" << numChoices << ")\n";
            correctChoice = getValidInput(1, numChoices);

            std::cout << "\nHow many points is this question worth?\n";
            std::cout << "1. 5 pts\n";
            std::cout << "2. 10 pts\n";
            std::cout << "3. 15 pts\n";
            std::cout << "4. 20 pts\n";
            ptsChoice = getValidInput(1, 4);

            int correctIndex = correctChoice - 1; // Converting to 0-based
            newQuiz->addQuestion(new MultipleChoiceQuestion(questionText, choices, correctIndex, pointValues[ptsChoice - 1]));
            questionNum++;
            std::cout << "\nQuestion added.\n\n";

        } else if (choice == 3) {
            if (questionNum == 0) {
                std::cout << "\nNo questions added yet.\n";
                std::cout << "1. Keep adding questions\n";
                std::cout << "2. Discard and go back\n";

                int discardChoice = getValidInput(1, 2);
                if (discardChoice == 1) {
                    continue;
                } else {
                    delete newQuiz;
                    std::cout << "\nQuiz discarded.\n\n";
                    return;
                }
            }

            std::string quizName;
            std::cout << "\nEnter a name for your quiz:\n> ";
            std::getline(std::cin, quizName);
            newQuiz->setQuizName(quizName);

            // Making filename from quiz name by replacing spaces with underscores
            std::string filename = quizName;
            for (int i = 0; i < filename.size(); i++) {
                if (filename[i] == ' ') {
                    filename[i] = '_';
                }
            }
            filename = filename + ".txt";

            try {
                newQuiz->saveToFile(quizDirectory + filename);
                // Adding filename to quiz list
                std::vector<std::string> files = getQuizFiles();
                files.push_back(filename);
                saveQuizList(files);
            } catch (FileNotFoundException &e) {
                std::cout << e.what() << "\n";
            }
            doneCreating = true;
        }
    }
    delete newQuiz; // Memory cleanup
}

// Shows all saved quizzes
void viewQuizzes() {
    std::vector<std::string> files = getQuizFiles();

    if (files.empty()) {
        std::cout << "\nNo quizzes available. Create one first!\n\n";
        return;
    }

    std::cout << "\nAll Available Quizzes:\n";
    for (int i = 0; i < files.size(); i++) {
        try {
            Quiz tempQuiz;
            tempQuiz.loadFromFile(quizDirectory + files[i]);
            std::cout << (i + 1) << ". " << tempQuiz.getQuizName() << " (" << tempQuiz.getQuestionCount() << " questions)\n";
        } catch (QuizException &e) {
            std::cout << (i + 1) << ". " << files[i] << " [corrupted]\n";
        }
    }
    std::cout << "\nPress Enter to go back...";
    std::cin.ignore(10000, '\n');
    std::cout << "\n";
}

// Lets the user pick and delete a quiz
void deleteQuiz() {
    std::vector<std::string> files = displayQuizList();

    if (files.empty()) {
        return;
    }

    int selection = getValidInput(1, files.size() + 1);

    if (selection == (int)files.size() + 1) {
        return;
    }

    std::string filepath = quizDirectory + files[selection - 1];

    // Showing quiz name for confirmation
    try {
        Quiz tempQuiz;
        tempQuiz.loadFromFile(filepath);
        std::cout << "\nAre you sure you want to delete \"" << tempQuiz.getQuizName() << "\"?\n";
    } catch (QuizException &e) {
        std::cout << "\nAre you sure you want to delete \"" << files[selection - 1] << "\"?\n";
    }

    std::cout << "1. Yes\n";
    std::cout << "2. No\n";

    int confirm = getValidInput(1, 2);

    if (confirm == 1) {
        remove(filepath.c_str()); // Deleting file from disk
        // Removing filename from quiz list
        std::vector<std::string> updatedFiles;
        for (int i = 0; i < files.size(); i++) {
            if (i != (selection - 1)) {
                updatedFiles.push_back(files[i]);
            }
        }
        saveQuizList(updatedFiles);
        std::cout << "\nQuiz deleted.\n\n";
    } else {
        std::cout << "\nCancelled.\n\n";
    }
}
