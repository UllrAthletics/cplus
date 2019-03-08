#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "IP2Class.cpp"
using namespace std;

// initaialize variables
int totalQuestions;
char choice;
string questionType;
string questionValue; 
int mcTotChoice; 
string answerChoice;
string questionAnswer;
string questionBody;
char correct = 'n'; // variable for exception/error handling

// file handling operators
fstream outfile;
ifstream myfile;

// main

int main(){
	
	cout << "You will be prompted for information to create your testbank.\n"
			<< "Please read all prompts carefully before entering any information.";
			cout << endl;
	
	outfile.open("customTestbank.txt", ios::in | ios::out);
	if (outfile.is_open()){
		
		// input question information

		do{
		startTotal:
			cout << "\nEnter the total number of questions you would like this test bank to hold: ";
			cin >> totalQuestions;
			cin.get();
			cout << endl;
			if (cin.fail()){
				cout << "Invalid input. Please use integers only.\n" << endl;
				goto startTotal;
			}
				
			cout << "You stated that there will be [" << totalQuestions << "] questions. Is this correct? Y or N: ";
			cin.get(correct);
			cin.get();
			cout << endl;
		}while(correct != 'Y' && correct != 'y');
		outfile << totalQuestions << endl;
		
		// for loop for question info input
		for (int count = 0; count < totalQuestions; count++){
			
			// questionType exception handling + input
			do{
			startType:
				cout << "\nQuestion #" << count+1 << " :\nEnter TF or MC to indicate question type: ";
				cin >> questionType;
				cin.get();
				for (int x = 0; x < questionType.length(); x++)
					questionType[x] = toupper(questionType[x]);
					
					if (questionType != "TF" && questionType != "MC"){
						cout << "Invalid input. Please input only TF or MC." << endl;
						goto startType;
					}
			
				cout << "You entered [" << questionType << "] for question type. Is this correct? Y or N: ";
				cin.get(correct);
				cin.get();
				cout << endl;
			}while(correct != 'Y' && correct != 'y');
			
			// question value
			do{
			startValue:
				cout << "\nEnter the question value as an integer: ";
				cin >> questionValue;
				cin.get();
				cout << endl;
				
				if (cin.fail()){
					cout << "Invalid input. Please enter only integers." << endl;
					goto startValue;
				}
				 
				cout << "You [" << questionValue << "] for the question value. Is this correct? Y or N: ";
				cin.get(correct);
				cin.get();
				cout << endl;
			}while(correct != 'Y' && correct != 'y');
			outfile << questionType << " " << questionValue << endl;
			
			// actual question
			do{
				cout << "Enter the question: ";
				getline(cin,questionBody);
				//cin.get();
				cout << endl;
				
				cout << "You entered: " << questionBody << "\nIs this correct? Y or N: ";
				cin.get(correct);
				cin.get();
				cout << endl;		
			}while(correct != 'Y' && correct != 'y');
			outfile << questionBody << endl;
			
			if (questionType == "TF"){ // T/F question eror/exception handling and question info
				
				do{	
				beginTF:
					cout << "Enter the Answer for question " << count+1 << " (T or F): ";
					cin >> questionAnswer;
					cin.get();
					cout << endl;
					
					if (questionAnswer == "t" || questionAnswer == "T"){
						questionAnswer = "TRUE";
						goto correctInput;
					}else if (questionAnswer == "f" || questionAnswer == "F"){
						questionAnswer = "FALSE";
						goto correctInput;
					}else{
						cout << "Invalid input. Please input T or F for the answer value. " << endl;
						goto beginTF;
					}
				correctInput:	
					cout << "You entered: "<< questionAnswer << "\nIs this answer correct? Y or N: ";
					cin.get(correct);
					cin.get();
					cout << endl;
				}while(correct != 'Y' && correct != 'y');
				outfile << questionAnswer << endl;
			}else{
				
				// MC error/exception handling
				do{ 
				mcChoice:
					cout << "\nEnter the number of answer choices for question " << count+1 << " using an integer: ";
					cin >> mcTotChoice;
					cin.get();
					cout << endl;
					
					if (cin.fail()){
						cout << "Invalid input. \nPlease input a number using only digits." << endl;
						goto mcChoice;
					}
					
					cout << "You stated that there are [" << mcTotChoice << "]. Is this correct? Y or N: ";
					cin.get(correct);
					cin.get();
					cout << endl;
				}while(correct != 'Y' && correct != 'y');
				outfile << mcTotChoice << endl;
				
				string options[mcTotChoice]; // choices to be printed for exception/error handling
				for (int x = 0; x < mcTotChoice; x++){  // answer choices input
					
					do{	
						cout << "\nEnter answer choice number " << x+1 << "(Do not precede statement with any indicator ex. 'a.'): ";
						getline(cin,answerChoice);
						
						cout << endl;
						
						cout << "You entered: " << answerChoice << "\nIs this correct? Y or N: ";
						cin.get(correct);
						cin.get();
						cout << endl;
							
					}while(correct != 'Y' && correct != 'y');
					outfile << answerChoice << endl;
					options[x] = answerChoice;
				}
				
				char letter = 'A'; // print options with letter indicators to prevent mistaken choice for answer
				for (int x = 0; x < mcTotChoice; x++){
					cout << letter++ << ". " << options[x] << endl;
				}
				do{
				startAnswer:	
					cout << "Enter the letter of the correct answer from the printed options above: ";
					cin.get(choice);
					cin.get();
					cout << endl;
				
					if (isalpha(choice)){
						goto acceptAnswer;
					}else if (cin.fail()){
						cout << "Invalid input. Enter a single letter." << endl;
						goto startAnswer;
					}
				acceptAnswer:	
					choice = toupper(choice);
					cout << "You entered [" << choice << "]. Is this correct? Y or N: ";
					cin.get(correct);
					cin.get();
					cout << endl;
				}while(correct != 'Y' && correct != 'y');
				outfile << choice << endl;
			}
		}
		outfile.close();
	}else{
		cout << "customTestbank.txt was not found or is unable to be opened." << endl;
		terminate();
	}
	
	// read and output all info from file that was written to it
	
	string questionType, questiontxt;
	string answertxt, optiontxt;
	int numQuestions, questionValue;
	
	myfile.open("customTestbank.txt");
	string line, theQuestion;
	if(myfile.is_open())
	{
		// read in test length
		getline(myfile,line);
		numQuestions = stoi(line);
		Question *myQuestions[numQuestions];
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
}

