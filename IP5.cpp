/*
Author: Hunter Morrison
Title: Individual project 4
Description: Write a C++ program that is menu-driven that allows for the following menu choices:
			Load, Display, Quit
Date modified: 3/11/2019	
 */
	
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <utility>
#include "examClass.cpp"
using namespace std;

ifstream examFile;
int optionsMenu(); // function prototype

int main()
{
	Exam theExam;
	int numQuestions, choice, userScore;
	string file;
	int x = 0;
//	pair <int,int> scoring;
	
	while(x != 1)
	{
		cout << "Enter an exam file name to open: ";
		getline(cin,file);
		examFile.open(file);
		if (examFile.is_open())
		{
			cout << "\nFile found.\n" << endl;
			examFile.close();
			x = 1;
		}else{
			cout << "\nFile not found. Please try a different file name or";
			cout <<	"\ncheck the spelling of the name you entered.\n" << endl;
		}
	}
	
	while((choice=optionsMenu()) != 4)
		switch(choice)
		{
			case 1: numQuestions = theExam.loadExam(file);
				break;
			case 2: theExam.takeExam(numQuestions);
				break;
			case 3: theExam.printResults(numQuestions);
				break;
			default: cout << "Invalid choice. Try again.\n" << endl;
		}
	
	cout << "Thank You for using the Morrison Exam Handler.\n";
	cout << "It's a little more than MEH." << endl;	
		
	getchar();
	return 0;
};


int optionsMenu()
{
	int choice;
	
	cout << "Enter an option from the menu below." << endl;
	cout << "1. Load Exam" << endl;
	cout << "2. Take Exam" << endl;
	cout << "3. Display Results" << endl;
	cout << "4. Quit" << endl;
	cout << "Selection: ";
	cin >> choice;
	cout << endl;
	return choice;
};
