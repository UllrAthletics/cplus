#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

// initaialize variables
int totalQuestions = 0;
string questionType;
int questionValue;
int mcTotChoices = 0; // get total number of options for multiple choice
string questionChoice;
string questionAnswer;

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
			cout << "Question #" << count+1 << ":\nType (TF or MC):" << endl;
			getline(cin,questionType);
			outfile << questionType << endl;
			
			for (int x = 0; x < questionType.length(); x++){
				questionType[x] = toupper(questionType[x]);
			}
			outfile << questionType << endl;
			
			if (questionType == "TF"){
				
			}
		}
		outfile.close()
	}else{
		cout << "customTestbank.txt was not found or is unable to be opened." << endl;
		terminate();
	}
	
}

