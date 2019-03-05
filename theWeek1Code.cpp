// Sample IP1 Program
// Created by Dr. Evans for CS215 - Intermediate C++
// Individual project 1
// Winter 2016

//#include "stdafx.h"
// #include "GreetingMessage.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[])
{
	// Variables
	int r = 3; //# of records to be generated
	string studentName[3];
	double GPA[3];
	string lName;
	string fName;

	// Set floating point values to two decimal places
	cout << setiosflags(ios::fixed);
	cout << setiosflags(ios::showpoint);
	cout << setprecision(2);


	// gather student names & GPAs
	for (int i = 0; i < r; i++)
	{
		if (i== 0){
	    cout << "Student " << + i+1 <<endl;
		          cout << "Enter Name (Last, First): ";
		          getline (cin, studentName[i]);
		          cout << "GPA: ";
		          cin >> GPA[i];
		} else
		{
			  cout << "Enter Name (Last, First): ";
					          cin.ignore();
					          getline (cin, studentName[i]);
					          cout << "GPA: ";
					          cin >> GPA[i];
		}

	}

	//print column names
	cout << setfill(' ') << setw(25) << left << "Student Name" << setw(5) << right << "GPA" << endl;

	// set letter case in studentNames array
	for (int i = 0; i < r; i++)
	{
		// separate first and last names
		string::size_type commaPos = studentName[i].find(",");  //find ","
		lName = studentName[i].substr(0, commaPos);	// select last name
		fName = studentName[i].substr(commaPos + 1);	// select first name
		if (fName[0] == ' ') fName.erase(0, 1);	// remove blank space between "," and first letter of first name

		// set all letters in first name to lower case, and then set first letter to upper case
		for (int x = 0; x < fName.length(); x++)
		{
			fName[x] = tolower(fName[x]);
		}
		fName[0] = toupper(fName[0]);

		// set all letters in last name to lower case, and then set first letter to upper case
		for (int x = 0; x < lName.length(); x++)
		{
			lName[x] = tolower(lName[x]);
		}
		lName[0] = toupper(lName[0]);

		// set original studentName variable to proper case formatting
		studentName[i] = lName + ", " + fName;

		// print student record
		cout << setfill(' ') << setw(25) << left << studentName[i] << setw(5) << right << GPA[i] << endl;

	}

	//system("pause");

	return 0;
}


 
