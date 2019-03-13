/*
Author: Hunter Morrison
Title: Individual project 2
Description: Write a C++ program to read in various types of test 
	questions (multiple choice and True/False) from a test bank 
	(text file), and load the questions into an array of questions.
Date modified: 2/27/2019	
 */
	
#include <iostream>
#include <string>
#include <fstream>
#include "examClass.cpp"
using namespace std;

// file reading
ifstream examfile;

int main()
{
	string questionType, questiontxt;
	string answertxt, optiontxt;
	int numQuestions, questionValue;
	
	examfile.open("testbank.txt");
	string line, theQuestion;
	if(examfile.is_open())
	{
		// read in test length
		getline(examfile,line);
		numQuestions = stoi(line);
		Question *myQuestions[numQuestions];
		
		// read in and set question type
		for(int count = 0; count < numQuestions; count++)
		{
			getline(examfile,line);
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
				getline(examfile,theQuestion);
				myQuestions[count] -> setQuestion(theQuestion,questionValue);
			}
			
			// Multiple choice question handling
			if(questionType == "MC")
			{
				myQuestions[count] = new QuestionMC;
				getline(examfile,theQuestion);
				myQuestions[count] -> setQuestion(theQuestion,questionValue);
			}
		}
		
		// print questions / answers and test length
		cout << "Test length: " << numQuestions << " questions\n" << endl;
	
		for(int count = 0; count < numQuestions; count++)
		{
			cout << "Question " << count+1 << ": " << endl;
			myQuestions[count] -> printOptions();
			cout << endl;
		}
	}else{
		cout << "File not found." << endl;
		terminate();
	}
	
	

	return 0;
};

