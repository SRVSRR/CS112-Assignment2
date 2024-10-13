#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

const int SIZE = 20;

struct Student{
	string id;
	double coursework;
	double finalExam;
	double totalMark;	
};

struct node {
    Student *studentdata;
    node *pNext;
    node *pPrev;
};

node *pHead = NULL;
node *pTail = NULL;

int validateInput(int lowerLimit, int upperLimit)
{
    int input;
    cin >> input;
    
    while(input < lowerLimit || input > upperLimit || cin.fail())
	{
        if (cin.fail())
		{
            cin.clear();
            string dummy;
            cin >> dummy;
            cout << "ERROR! Invalid option detected." << endl;
            cout << "Please enter a number." << endl;
        }
		else if (input < lowerLimit || input > upperLimit)
		{
            cin.clear();
            cout << "ERROR! Your choice is not in range." << endl;
            cout << "Please enter a number between " << lowerLimit << " and " << upperLimit << endl;
        }
        cin >> input;
    }
    return input;
}

void printWelcomeMessage()
{
    cout << "+-------------------------------------------------+\n";
    cout << "|      WELCOME TO THE STUDENT GRADES PROGRAM      |\n";
    cout << "+-------------------------------------------------+\n";
}

void endProgram(bool& continueExecuting)
{
    continueExecuting = false;

    cout << endl;
    cout << "+-------------------------------------+\n";
    cout << "|  Thank you for using this program!  |\n";
    cout << "+-------------------------------------+\n";
}

void displayMenu()
{
	cout << "Menu:" << endl;
	cout << "1. Print Entire List with Grades" << endl;
	cout << "2. Update Student's Marks" << endl;
	cout << "3. Print Average marks" << endl;
	cout << "4. Print Pass Rate" << endl;
	cout << "5. Print the Highest Scorer's Details" << endl;
	cout << "6. Exit Program" << endl;
	cout << "\nEnter the number corresponding to your choice" << endl;
}

void programStartQuit(bool& continueExecuting)
{
    string userDecision;
    cout << "Enter S to start or Q to quit" << endl;
    cin >> userDecision;
    
    while(userDecision != "S" && userDecision != "s" && userDecision != "Q" && userDecision != "q") {
        cin.clear();
        cout << "ERROR! Invalid input detected." << endl;
        cout << "Please enter either \"S\" or \"Q\" only." << endl;
        cin >> userDecision;
    }
    
    if (userDecision == "S" || userDecision == "s")
	{
		continueExecuting = true;
	}
	else if (userDecision == "Q" || userDecision == "q")
	{
		continueExecuting = false;
	}
}

void AppendNode(node *pNode) {
    if (pHead == NULL) {
        // List is empty
        pHead = pTail = pNode;
        pNode->pNext = pNode->pPrev = NULL;
    } else {
        // Append at the end
        pTail->pNext = pNode;
        pNode->pPrev = pTail;
        pNode->pNext = NULL;
        pTail = pNode;  // Correctly updating the tail
    }
}

void FreeList(node *pHead) {
    node *current = pHead;
    node *next;

    while (current != NULL) {
        next = current->pNext;
        delete current->studentdata;  // Free the Student object
        delete current;               // Free the node
        current = next;
    }
}

void fillArray(string fileName, int& rows, node*& pHead) {
    ifstream readFile(fileName.c_str());

    if (!readFile) {
        cout << "ERROR! File could not be found." << endl;
        exit(1); // Exiting as the file is not found
    } else {
        string id;
        double coursework, finalexam;

        // Read through the file and append to the linked list
        while (!readFile.eof()) {
			readFile >> id >> coursework >> finalexam;
            // Allocate and fill student object
            Student* student = new Student;
            student->id = id;
            student->coursework = coursework;
            student->finalExam = finalexam;

            // Print debug information
            cout << "Adding Student ID: " << student->id << ", Coursework: " 
                 << student->coursework << ", Final Exam: " << student->finalExam << endl;

            // Allocate new node
            node* pNode = new node;
            pNode->studentdata = student;

            // Append to linked list
            AppendNode(pNode);
        }
    }
}

string determineGrade(double totalMark)
{
	if (totalMark >= 85)
	{
		return "A+";
	}
	else if (totalMark >= 78)
	{
		return "A";
	}
	else if (totalMark >= 71)
	{
		return "B+";
	}
	else if (totalMark >= 64)
	{
		return "B";
	}
	else if (totalMark >= 57)
	{
		return "C+";
	}
	else if (totalMark >= 50)
	{
		return "C";
	}
	else if (totalMark >= 40)
	{
		return "D";
	}
	else 
	{
		return "E";
	}
}

int UpdateMark_Validation(int lowerLimit, int upperLimit)
{
    int input;
    cin >> input;
    
    while(input < lowerLimit || input > upperLimit || cin.fail())
	{
        if (cin.fail())
		{
            cin.clear();
            string dummy;
            cin >> dummy;
            cout << "ERROR! Invalid option detected." << endl;
            cout << "Please enter a number." << endl;
        }
		else if (input < lowerLimit || input > upperLimit)
		{
            cin.clear();
            cout << "ERROR! Your choice is not in range." << endl;
            cout << "Please enter a number between " << lowerLimit << " and " << upperLimit << endl;
        }
        cin >> input;
    }
    return input;
}

void printEntireList(node* pHead) {
    if (pHead == NULL) {
        cout << "The student list is empty." << endl;
        return;
    }

    cout << "\nThe Entire List of Students with Grades:" << endl;
    cout << left << setw(20) << "ID" << setw(20) << "Coursework" 
         << setw(20) << "Final Exam" << setw(20) << "Grade" << endl;
    cout << "-----------------------------------------------------------------" << endl;

    node* current = pHead;
    while (current != NULL) {
        Student* student = current->studentdata;
        student->totalMark = student->coursework + student->finalExam;
        string studentGrade = determineGrade(student->totalMark);
        
        cout << left << setw(20) << student->id << setw(20) << student->coursework 
             << setw(20) << student->finalExam << setw(20) << studentGrade << endl;
        cout << "-----------------------------------------------------------------" << endl;

        current = current->pNext;
    }
}

void updateMark(Student students[], int size)
{
	string searchId;
	bool found = false;
	
	cout << "Please enter the ID number you would like to search for. Example: S00005" << endl;
	cin >> searchId;
	while(cin.fail())
	{
		cin.clear();
		string dummy;
		cin >> dummy;
		cout << "ERROR! Invalid Input Detected." << endl;
		cout << "Please enter letter \"S\" in uppercase followed by numbers only." << endl;
		cin >> searchId;
	}
	
	for (int i = 0; i < size; i++)
	{
		if (students[i].id == searchId)
		{
			found = true;
			const int MIN_CHOICE = 1;
			const int MAX_CHOICE = 3;
			const int MARK_UPDATE_MAX = 50;
			const int MARK_UPDATE_MIN = 0;

			cout << "Which Mark Would You Like To Update?" << endl;
			cout << "1. Coursework Only" << endl;
			cout << "2. Final Exam Only" << endl;
			cout << "3. Course and Final Exam" << endl;		
			int choice;
			cin >> choice;
			while(choice < MIN_CHOICE || choice > MAX_CHOICE || cin.fail())
			{
				if (cin.fail())
				{
					cin.clear();
					string dummy;
					cin >> dummy;
					cout << "ERROR! Invalid option detected." << endl;
					cout << "Please enter a number." << endl;
				}
				else if (choice < MIN_CHOICE || choice > MAX_CHOICE)
				{
					cin.clear();
					cout << "ERROR! Your choice is not in range." << endl;
					cout << "Please enter a number between " << MIN_CHOICE << " and " << MAX_CHOICE << endl;
				}
				cin >> choice;
			}
			switch(choice){
				case 1: cout << "Enter the new coursework mark: ";
								cin >> students[i].coursework;								
								while(students[i].coursework < MARK_UPDATE_MIN || students[i].coursework > MARK_UPDATE_MAX || cin.fail())
									{
										if (cin.fail())
										{
											cin.clear();
											string dummy;
											cin >> dummy;
											cout << "ERROR! Invalid option detected." << endl;
											cout << "Please enter a number." << endl;
										}
										else if (students[i].coursework < MARK_UPDATE_MIN || students[i].coursework > MARK_UPDATE_MAX)
										{
											cin.clear();
											cout << "ERROR! Your choice is not in range." << endl;
											cout << "Please enter a number between " << MARK_UPDATE_MIN << " and " << MARK_UPDATE_MAX << endl;
										}
										cin >> students[i].coursework;
									}
								break;
				case 2: cout << "Enter the new final exam mark: ";
								cin >> students[i].finalExam;
								while(students[i].finalExam < MARK_UPDATE_MIN || students[i].finalExam > MARK_UPDATE_MAX || cin.fail())
									{
										if (cin.fail())
										{
											cin.clear();
											string dummy;
											cin >> dummy;
											cout << "ERROR! Invalid option detected." << endl;
											cout << "Please enter a number." << endl;
										}
										else if (students[i].finalExam < MARK_UPDATE_MIN || students[i].finalExam > MARK_UPDATE_MAX)
										{
											cin.clear();
											cout << "ERROR! Your choice is not in range." << endl;
											cout << "Please enter a number between " << MARK_UPDATE_MIN << " and " << MARK_UPDATE_MAX << endl;
										}
										cin >> students[i].finalExam;
									}
									break;
				case 3: cout << "Enter the new coursework mark: ";
								cin >> students[i].coursework;
								while(students[i].coursework < MARK_UPDATE_MIN || students[i].coursework > MARK_UPDATE_MAX || cin.fail())
									{
										if (cin.fail())
										{
											cin.clear();
											string dummy;
											cin >> dummy;
											cout << "ERROR! Invalid option detected." << endl;
											cout << "Please enter a number." << endl;
										}
										else if (students[i].coursework < MARK_UPDATE_MIN || students[i].coursework > MARK_UPDATE_MAX)
										{
											cin.clear();
											cout << "ERROR! Your choice is not in range." << endl;
											cout << "Please enter a number between " << MARK_UPDATE_MIN << " and " << MARK_UPDATE_MAX << endl;
										}
										cin >> students[i].coursework;
									}
						cout << "Enter the new final exam mark: ";
								cin >> students[i].finalExam;
								while(students[i].finalExam < MARK_UPDATE_MIN || students[i].finalExam > MARK_UPDATE_MAX || cin.fail())
									{
										if (cin.fail())
										{
											cin.clear();
											string dummy;
											cin >> dummy;
											cout << "ERROR! Invalid option detected." << endl;
											cout << "Please enter a number." << endl;
										}
										else if (students[i].finalExam < MARK_UPDATE_MIN || students[i].finalExam > MARK_UPDATE_MAX)
										{
											cin.clear();
											cout << "ERROR! Your choice is not in range." << endl;
											cout << "Please enter a number between " << MARK_UPDATE_MIN << " and " << MARK_UPDATE_MAX << endl;
										}
										cin >> students[i].finalExam;
									}
							break;
			}
			students[i].totalMark = students[i].coursework + students[i].finalExam;
			string studentGrade = determineGrade(students[i].totalMark);
			
			cout << "\nMarks Updated Successfully!" << endl;
			cout << "\n" << left << setw(20) << "ID" << setw(20) << "Coursework" << setw(20) << "Final Exam" << setw(20) << "Total" << setw(20) << "Grade" << endl;
			cout << left << setw(20) << students[i].id << setw(20) << students[i].coursework << setw(20) << students[i].finalExam << setw(20) << students[i].totalMark << setw(20) << studentGrade << endl;
		}
	}
	
	if (!found)
	{
		cout << "\nNo student was found with the ID# " << searchId << endl;
	}
}

void printAverageMarks(Student students[], int size)
{
    double totalMarks = 0.0;

    for (int i = 0; i < size; i++)
    {
        students[i].totalMark = students[i].coursework + students[i].finalExam;
        totalMarks += students[i].totalMark;
    }

    double averageMarks = totalMarks / size;

    cout << "\nThe average mark for the class is: " << fixed << setprecision(2) << averageMarks << endl;
}

void printPassRate(Student students[], int size)
{
	double passRate = 0;
	double passedCounter = 0;
	
	for (int i = 0; i < size; i++)
	{
		students[i].totalMark = students[i].coursework + students[i].finalExam;
		
		if(students[i].totalMark >= 50)
		{
			passedCounter++;
		}
	}
	
	passRate = (passedCounter/size)*100;
	
	cout << "\nThe pass rate of the class is " << passRate << "%" << endl;	
}

void printHighestScorersDetails(Student students[], int size)
{
	int highestScorerIndex = 0;
	
	for (int i = 0; i < size; i++)
	{
		students[i].totalMark = students[i].coursework + students[i].finalExam;
		
		if(students[i].totalMark > students[highestScorerIndex].totalMark)
		{
			highestScorerIndex = i;
		}
	}
	
	string studentGrade = determineGrade(students[highestScorerIndex].totalMark);
	
	cout << "\nHighest Scorer's Full Details:" << endl;
	cout << "\n" << left << setw(20) << "ID" << setw(20) << "Coursework" << setw(20) << "Final Exam" << setw(20) << "Total" << setw(20) << "Grade" << endl;
	cout << left << setw(20) << students[highestScorerIndex].id << setw(20) << students[highestScorerIndex].coursework << setw(20) << students[highestScorerIndex].finalExam << setw(20) << students[highestScorerIndex].totalMark << setw(20) << studentGrade << endl;
}

int main()
{
    bool continueExecuting = true;
    
    cout << fixed << setprecision(2) << endl;
    printWelcomeMessage();
    
    programStartQuit(continueExecuting);
    
    if (continueExecuting) 
    {
        int rows = 0;
        fillArray("studentData.txt", rows, pHead);  // fill linked list once

        while (continueExecuting)
        {
            displayMenu();
            int choice = validateInput(1, 6);

            switch (choice)
            {
                case 1:
                    printEntireList(pHead);  // Print using linked list
                    break;
                case 2:
                    // updateMark(pHead);  // Update marks (requires linked list modification)
                    break;
                case 3:
                    // printAverageMarks(pHead);  // Calculate average marks
                    break;
                case 4:
                    // printPassRate(pHead);  // Calculate pass rate
                    break;
                case 5:
                    // printHighestScorerDetails(pHead);  // Find highest scorer
                    break;
                case 6:
                    endProgram(continueExecuting);
                    break;
            }
        }

        FreeList(pHead);  // Clean up memory
    }

    return 0;
}
