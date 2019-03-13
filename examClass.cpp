/* 
test handling header file
Inlcudess:
	Question class,
	Exam class
*/
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;



// question handling parent/super class
class  Question 
{
public:
		
		string getQuestion()
		{
			return question;
		}
		
		virtual int getValue()
		{
			return value;
		}
		
		virtual string questionType()
		{
			return questiontype;
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
		string questiontype;
};

// True/False class
class QuestionTF: public Question
{
public:
	void setQuestion(string theQuestion, int pointValue)
	{
		string theAnswer;
		questiontype = "TF";
		question = theQuestion;
		value = pointValue;
		options = "TRUE / FALSE";
		
		// read in answer from the text file
		getline(cin,theAnswer);
		answer = theAnswer;
	}
	
	int getValue()
	{
		return value;
	}
	
	string questionType()
	{
		return questiontype;
	}
	
	// print question and answer
	void printOptions()
	{
		cout << "Points: " << value << endl;
		cout << question << endl;
		cout << answer << endl;
	}
	
	string getAnswer()
	{
		return answer;
	}
	
private:
	string question, questiontype;
	string answer;
	int value;
	string options;
};

// Mutiple choice questions class
class QuestionMC: public Question
{
public:
	void setQuestion(string theQuestion, int pointValue)
	{
		string line;
		questiontype = "MC";
		
		// read in # of choices from file
		getline(cin,line);
		numberOfOptions = atoi(line.c_str());
		question = theQuestion;
		value = pointValue;
		
		// get each choice line and put into the array of options
		for(int count = 0; count < numberOfOptions; count++)
		{
			getline(cin,line);
			options[count] = line;
		}
		
		// get answer and set as answer variable
		getline(cin,line);
		answer = line;
	}
	
	int getValue()
	{
		return value;
	}
	
	string questionType()
	{
		return questiontype;
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
	string options[10], questiontype;
};



// exam handling parent/super class 
class Exam{
public:
	
	int loadExam(string file)
	{
		ifstream infile(file);
		streambuf *cinbuf = cin.rdbuf(); // save old buf
		cin.rdbuf(infile.rdbuf()); // redirect std::cin to infile
		
		string questiontype, line, theQuestion;
		int questionValue;
		
		// read in test length
		getline(cin,line);
		numQuestions = atoi(line.c_str());
		
		// read in and set question type
		for(int count = 0; count < numQuestions; count++)
		{
			getline(cin,line);
			int endpos = line.size();
			int prevpos = 0;
			int pos = 0;
			while(line[pos] != ' ')
			{
				pos++;
			}
			questiontype  = line.substr(prevpos, pos - prevpos);
			prevpos = pos++;
			questionValue = atoi(line.substr(prevpos, endpos - prevpos).c_str());
			
			// TRUE / FALSE question handling
			if(questiontype == "TF")
			{
				myQuestions[count] = new QuestionTF;
				getline(cin,theQuestion);
				myQuestions[count] -> setQuestion(theQuestion,questionValue);
			}
			
			// Multiple choice question handling
			if(questiontype == "MC")
			{
				myQuestions[count] = new QuestionMC;
				getline(cin,theQuestion);
				myQuestions[count] -> setQuestion(theQuestion,questionValue);
			}
		}
		cin.rdbuf(cinbuf); // restore cin to standard input
		return numQuestions;
	}
	
	void printExam(int numQuestions)
	{
		string qType;
		// print questions / answers and test length
		cout << "Test length: " << numQuestions << " questions\n" << endl;
	
		for(int count = 0; count < numQuestions; count++)
		{
			qType = myQuestions[count] -> questionType();
			cout << "Question " << count+1 << ": " << endl;
			cout << qType << " " << myQuestions[count] -> getValue() << endl;
			myQuestions[count] -> printOptions();
			cout << endl;
		}
	}
	
	private:
		Question *myQuestions[100];
		int numQuestions;
};

