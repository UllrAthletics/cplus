/*
Author: Hunter Morrison
Title: Individual project 2
Description: Write a C++ program to read in various types of test 
	questions (multiple choice and True/False) from a test bank 
	(text file), and load the questions into an array of questions. */
	
#include <iostream>
#include <string>
#include <fstream>
#include "IP2Class.cpp"
using namespace std;

// file reading
ifstream myfile;

int main()
{
	Question *myQuestions[10];
	string questionType, questiontxt;
	string answertxt, optiontxt;
	int numQuestions, questionValue;
	
	myfile.open("testbank.txt");
	string line, theQuestion;
	if(myfile.is_open())
	{
		// read in test length
		getline(myfile,line);
		numQuestions = stoi(line);
		
		// read in and set question type
		for(int count = 0; count < numQuestions; count++)
		{
			getline(myfile,line);
			int endpos = line.size();
			int prevpos = 0;
			int pos = 0;
			while(line[pos] != ' ')
			{
				pos++;
			}
			questionType  = line.substr(prevpos, pos - prevpos);
			prevpos = pos++;
			questionValue = stoi(line.substr(prevpos, endpos - prevpos));
			
			// TRUE / FALSE question handling
			if(questionType == "TF")
			{
				myQuestions[count] = new QuestionTF;
				getline(myfile,theQuestion);
				myQuestions[count] -> setQuestion(theQuestion,questionValue);
			}
			
			// Multiple choice question handling
			if(questionType == "MC")
			{
				myQuestions[count] = new QuestionMC;
				getline(myfile,theQuestion);
				myQuestions[count] -> setQuestion(theQuestion,questionValue);
			}
		}
	}else{
		cout << "File not found." << endl;
		terminate();
	}
	
	// print questions / answers and test length
	cout << "Test length: " << numQuestions << " questions\n" << endl;
	
	for(int count = 0; count < numQuestions; count++)
	{
		cout << "Question " << count+1 << ": " << endl;
		myQuestions[count] -> printOptions();
		cout << endl;
	}

	return 0;
};

