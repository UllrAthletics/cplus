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
#include <iomanip>
#include <utility>
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
		
		virtual int printOptions()
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
	int printOptions()
	{
		int points = 0;
		
		cout << "Points: " << value << endl;
		cout << question << endl;
		cout << "Enter T or F to answer the question: ";
		cin >> choice;
		cin.get();
		
		for (int x = 0; x < choice.length(); x++)
		{
			choice[x] = toupper(choice[x]);
		}
		
		if ((choice.at(0) == 'T' || choice.at(0) == 't') && answer == "TRUE")
		{
			cout << "\nCORRECT. The answer is: " << answer << endl;
			points = value;
		}else if ((choice.at(0) == 'F' || choice.at(0) == 'f') && answer == "FALSE"){
			cout << "\nCORRECT. The answer is: " << answer << endl;
			points = value;
		}else{
			cout << "\n" << choice << " is INCORRECT. The correct answer is: " << answer << endl;
		}
		return points;
	}
	
	string getAnswer()
	{
		return answer;
	}
	
private:
	string question, questiontype;
	string answer;
	int value;
	string choice;
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
	
	int printOptions()
	{
		int points = 0;
		char first = 'A';
		
		cout << "Points: " << value << endl;
		cout << question << endl;
		for(int count = 0; count < numberOfOptions; count++)
		{
			cout << first++ << ". " << options[count] << endl;
		}
		cout << "Enter a letter option from the list above: ";
		cin >> choice;
		cin.get();
		
		for (int x = 0; x < choice.length(); x++)
		{
			choice[x] = toupper(choice[x]);
		}
		
		if (choice == answer)
		{
			cout << "\nCORRECT. The answer is: " << answer << endl;
			points = value;
		}else{
			cout << "\n" << choice << " is INCORRECT. The correct answer is: " << answer << endl;
		}
		return points;
	}
	
	string getAnswer()
	{
		return answer;
	}

private:
	int value, numberOfOptions;
	string question, answer;
	string options[10], questiontype;
	string choice;
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
	
	int takeExam(int numQuestions)
	{
		string qType;
		int score = 0, maxScore = 0, points = 0;
		
		// print questions / answers and test length
		cout << "Test length: " << numQuestions << " questions\n" << endl;
	
		for(int count = 0; count < numQuestions; count++)
		{
			qType = myQuestions[count] -> questionType();
			cout << "Question " << count+1 << ": " << endl;
			value = myQuestions[count] -> getValue();
			cout << qType << " " << value << endl;
			maxScore += value;
			points = myQuestions[count] -> printOptions();
			cout << endl;
			score += points;
		}
		pointsEarned = score;
		totalPoints = maxScore;
	}
	
	void printResults(int numQuestions)
	{
		char letterGrade;
		double grade = 0;
		
		// Set floating point values to two decimal places
		cout << setiosflags(ios::fixed);
		cout << setiosflags(ios::showpoint);
		cout << setprecision(2);
		
		cout << "Points: " << pointsEarned << " out of " << totalPoints << endl;
		grade = ((static_cast<double>(pointsEarned) / static_cast<double>(totalPoints)) * 100);
		cout << "Grade Percentage: " << grade << "%" << endl;
		 
		if (grade >= 90)
		{
			letterGrade = 'A';
		}else if (grade < 90 && grade >= 80){
			letterGrade = 'B';
		}else if (grade < 80 && grade >= 70){
			letterGrade = 'C';
		}else if (grade < 70 && grade >= 60){
			letterGrade = 'D';
		}else{
			letterGrade = 'F';
		}
		
		switch(letterGrade)
		{
			case 'A': cout << "Well done! You passed with an A\n" << endl;
				break;
			case 'B': cout << "Good Job! You passed with a B\n" << endl;
				break;
			case 'C': cout << "You can do better. You passed with a C\n" << endl;
				break;
			case 'D': cout << "You barely made it. You passed with a D\n" << endl;
				break;
			default: cout << "You failed. You earned an F\n" << endl;
				break;
		}
	}
	
	private:
		Question *myQuestions[100];
		int numQuestions, value, totalPoints, pointsEarned;
		string qType;
};

