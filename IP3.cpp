#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cctype>
using namespace std;

// initaialize variables
int totalQuestions = 0;
string questionType;
int questionValue; 
int mcTotChoices = 0; 
string questionChoice[mcTotChoices];
string questionAnswer;
int y = 0; // variable for error handling
char correct = "n"; // variable for exception handling

// file handling operators
ifstream myfile;
ostream outfile;

// main

int main(){
	
	cout << "You will be prompted for information to create your testbank.\n"
			<< "Please read all prompts carfully before entering any information.";
			<< endl;
	
	outfile.open("customTestbank.txt");
	if (outfile.is_open){
		// input question information
		cout << "Enter the total number of questions you would like this test bank to hold:";
		getline(cin,totalQuestions);
		outfile << totalQuestions << endl;
		
		// for loop for question info input
		for (int count = 0; count < totalQuestions; count++){
			
			// questionType exception handling + input
			do{
				cout << "Question #" << count+1 << ":\nEnter (TF or MC):" << endl;
				getline(cin,questionType);
				for (int x = 0; x < questionType.length(); x++){ // set questionType to uppercase regardless of input case
					questionType[x] = toupper(questionType[x]);
				}
				if (isalpha(questionType) && (questionType == "TF" || questionType == "MC")){
					cout << questionType << endl;
					cout << "Is this correct? Y or N: " << endl;
					getline(cin,correct)
				}else{
					cout << "Invalid input. Please use only alphanumeric characters "
				}
			}while{correct != "y" || correct != "Y"}
			correct = "n" // initialize back to n
			outfile << questionType << endl;
				
			if (questionType == "TF"){ // T/F 
				
				do{	// T/F question eror/exception handling and question info
					cout << "Enter the Answer for question " << count+1 << " (T or F): " << endl;
					getline(cin,questionAnswer);
					
					if (questionAnswer == "t" || questionAnswer == "T"){
						questionAnswer = "TRUE";
						cout << "Is this answer correct? Y or N.\nAnswer: " << questionAnswer << endl;
						getline(cin,correct);
					}else if (questionAnswer == "f" || questionAnswer == "F"){
						questionAnswer = "FALSE";
						cout << "Is this answer correct? Y or N.\nAnswer: " << questionAnswer << endl;
						getline(cin,correct);
					}else{
						cout << "Invalid input. Please input T or F for the answer value. " << endl;
					}
				}while{correct != "y" || correct != "Y"}
				outfile << questionAnswer << endl;
				correct = "n"; // initialize back to n
				
			}else if (questionType == "MC"){ // M/C
				cout << "Enter the number of choices for question " << count+1 << ": " << endl;
				
				do{ // error/exception handling for M/C number of choices
					getline(cin,mcTotChoices);
					
					if (isdigit(mcTotChoices)){
						outfile << mcTotChoices << endl;
						y = 1;
					}else{
						cout << "Invalid input. \nPlease input a number using only digits: " << endl;
					}
				}while{y != 1}
				
				for (int choices = 0; choices < mcTotChoices; choices++){ // choices input 
					cout << "Enter choice number " << choices+1 << "(Do not precede staement with 'a.' or any other indicator): " << endl;
					getline(cin,questionChoice[choices]);
					
					outfile << questionChoice[choices] << endl;
				}
				
				char letter = "A"; // print options with letter indicators to prevent mistaken choice for answer
				for (int choices = 0; choices < mcTotChoices; choices++){
					cout << letter++ << ". " << questionChoice[choices] << endl;
				}
				
				cout << "Enter the answer based on the printed options above: " << endl;
				getline(cin,questionAnswer);
				
				for (int x = 0; x < questionAnswer.length(); x++){ // set questionAnswer to uppercase regardless of input case
				questionAnswer[x] = toupper(questionAnswer[x]);
				}
			}
		outfile.close()
		}
	}else{
		cout << "customTestbank.txt was not found or is unable to be opened." << endl;
		terminate();
	}
	return 0;	
}

