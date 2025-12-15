// Chapter 7 Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int NUM_QUESTIONS = 20;

// Function prototypes
void createFiles();
void getAnswers(const string&, char[]);
int gradeExam(const char[], const char[], int[], char[][2]);
void writeReport(int, const int[], const char[][2]);

int main()
{
    char correct[NUM_QUESTIONS];
    char student[NUM_QUESTIONS];
    int missed[NUM_QUESTIONS];
    char wrongAnswers[NUM_QUESTIONS][2];

    // Create the text files inside the program
    createFiles();

    // Read answers from files
    getAnswers("CorrectAnswers.txt", correct);
    getAnswers("StudentAnswers.txt", student);

    int numMissed = gradeExam(correct, student, missed, wrongAnswers);

    writeReport(numMissed, missed, wrongAnswers);

    return 0;
}

/*
createFiles
Creates and writes the answer key and student answers files.
*/
void createFiles()
{
    ofstream correctFile("CorrectAnswers.txt");
    ofstream studentFile("StudentAnswers.txt");

    char correct[NUM_QUESTIONS] =
    { 'D','A','B','B','C','A','D','D','A','C',
     'B','D','C','A','A','B','A','C','D','C' };

    char student[NUM_QUESTIONS] =
    { 'D','A','C','D','C','A','B','D','B','C',
     'B','D','A','A','A','B','A','C','D','C' };

    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        correctFile << correct[i] << endl;
        studentFile << student[i] << endl;
    }

    correctFile.close();
    studentFile.close();
}

/*
getAnswers
Reads answers from a file into an array.
*/
void getAnswers(const string& fileName, char answers[])
{
    ifstream inputFile(fileName);

    if (!inputFile)
    {
        cout << "Error opening file: " << fileName << endl;
        exit(1);
    }

    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        inputFile >> answers[i];
    }

    inputFile.close();
}

/*
gradeExam
Compares correct answers and student answers.
Returns number of incorrect answers.
*/
int gradeExam(const char correct[], const char student[],
    int missed[], char wrongAnswers[][2])
{
    int count = 0;

    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        if (correct[i] != student[i])
        {
            missed[count] = i + 1;
            wrongAnswers[count][0] = student[i];
            wrongAnswers[count][1] = correct[i];
            count++;
        }
    }

    return count;
}

/*
writeReport
Displays exam results and pass/fail status.
*/
void writeReport(int numMissed, const int missed[],
    const char wrongAnswers[][2])
{
    int correctCount = NUM_QUESTIONS - numMissed;
    double percentage = (double)correctCount / NUM_QUESTIONS * 100;

    cout << fixed << setprecision(1);

    cout << "\nExam Results\n";
    cout << "-----------------------\n";

    if (numMissed > 0)
    {
        cout << "Question  Student  Correct\n";
        for (int i = 0; i < numMissed; i++)
        {
            cout << setw(5) << missed[i]
                << setw(9) << wrongAnswers[i][0]
                << setw(9) << wrongAnswers[i][1] << endl;
        }
    }
    else
    {
        cout << "No questions missed.\n";
    }

    cout << "\nTotal Missed: " << numMissed << endl;
    cout << "Percentage Correct: " << percentage << "%\n";

    if (percentage >= 70)
        cout << "Result: PASSED\n";
    else
        cout << "Result: FAILED\n";
}

