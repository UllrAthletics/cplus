/* 
Author: Hunter Morrison
Purpose: class for handling test questions 
Date: 2/25/2019
*/

#include <string>
#include <fstream>
using namespace std;

// files reaading
extern ifstream examfile;

// parent/super class
class  Question 
{
public:
		
		string getQuestion()
		{
			return question;
		}
		
		int getValue()
		{
			return value;
		}
		
		virtual void setQuestion(string answer, int value)
		{
		}
		
		virtual void printOptions()
		{
		}
		
		virtual string getAnswer()
		{
			return answer;
		}
		
	private:
		string question, answer;
		int value;
};

// True/False class
class QuestionTF: public Question
{
public:
	void setQuestion(string theQuestion, int pointValue)
	{
		string theAnswer;
		question = theQuestion;
		points = pointValue;
		options = "TRUE / FALSE";
		
		// read in answer from the text file
		getline(examfile,theAnswer);
		answer = theAnswer;
	}
	
	// print question and answer
	void printOptions()
	{
		cout << "Points: " << points << endl;
		cout << question << endl;
		cout << answer << endl;
	}
	
	string getAnswer()
	{
		return answer;
	}
	
private:
	string question;
	string answer;
	int points;
	string options;
};

// Mutiple choice questions class
class QuestionMC: public Question
{
public:
	void setQuestion(string theQuestion, int pointValue)
	{
		string line;
		
		// read in # of choices from file
		getline(examfile,line);
		numberOfOptions = stoi(line);
		question = theQuestion;
		value = pointValue;
		
		// get each choice line and put into the array of options
		for(int count = 0; count < numberOfOptions; count++)
		{
			getline(examfile,line);
			options[count] = line;
		}
		
		// get answer and set as answer variable
		getline(examfile,line);
		answer = line;
	}
	
	void printOptions()
	{
		char first = 'A';
		cout << "Points: " << value << endl;
		cout << question << endl;
		for(int count = 0; count < numberOfOptions; count++)
		{
			cout << first++ << ". " << options[count] << endl;
		}
		cout << "Answer: " << answer << endl;
	}
	
	string getAnswer()
	{
		return answer;
	}

private:
	int value, numberOfOptions;
	string question, answer;
	string options[6];
};
