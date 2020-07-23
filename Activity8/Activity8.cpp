// Activity8.cpp : This file contains the "main" function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>


using namespace std;

struct PersonalDetails
{
	
	string dob = "Empty";
	string surName = "Empty";
	string firstName = "Empty";
	string courseCode = "Empty";

	friend ostream& operator <<(ostream& os, PersonalDetails const& details)
	{
		return os 			
			<< "First Name: " << details.firstName << '\n'
			<< "Surname: " << details.surName << '\n'
			<< "D.O.B: " << details.dob << '\n'
			<< "Course Code: " << details.courseCode << '\n';
	}
};

PersonalDetails enterDetails(PersonalDetails newStudent) {
		

	cout << " Enter First Name : ";
	cin >> newStudent.firstName;
	cout << " Enter Surname : ";
	cin >> newStudent.surName;
	cout << " Enter D.O.B : ";	
	cin >> newStudent.dob;
	cout << " Enter Course Code : ";
	cin >> newStudent.courseCode;

	return newStudent;

}

int enterStudentID() {
	int input = 0;
	cout << " Enter Student ID : ";
	cin >> input;

	return input;
}


bool areYouSure() {

		string answer;
		cin >> answer;

		if (answer == "y" || answer == "Y" || answer == "Yes" || answer == "yes" || answer == "YES") {
		
			return true;
		}		
		else if (answer == "n" || answer == "N" || answer == "No" || answer == "no" || answer == "NO") {
			return false;
		}
		else {
			cout << answer;
			cout << "invalied input";
			areYouSure();
		}
}

void saveFile(map<int, PersonalDetails> &studentMap, int id, int fileID) {

	cout << "Save before Exiting? Y or N? ";
	{


		if (areYouSure()) {
			if (id > fileID) {
				ofstream file("studentCount.bin");
				file << id;

			}
			ofstream file("studentDetails.bin");
			for (map<int, PersonalDetails>::iterator it = studentMap.begin(); it != studentMap.end(); ++it)
				file << "\nStudent ID:" << it->first << '\n' << it->second;

			cout << "session updates saved";
		}
		else
		{
			cout << "session changes not saved";
		}
	}
}


int options(map<int, PersonalDetails>  &studentMap, int &id, int fileID) {

	PersonalDetails newStudent;

	int selection = 0;
	cout << "====================================\n 1. ADD NEW STUDENT TO THE CLASS\n 2. REMOVE A STUDENT FROM THE CLASS\n 3. PRINT ALL STUDENTS DETAILS\n 4. DISPLAY ONE STUDENTS DETAILS\n 5. DELETE ENTIRE CLASS LIST\n 6. EXIT\n====================================\n Enter Selection\n";

	cin >> selection;

	switch (selection)
	{
	case 1: cout << "1. ADD NEW STUDENT TO THE CLASS\n";
		studentMap[id += 1] = enterDetails(newStudent);
		break;
	case 2:  cout << "2. REMOVE A STUDENT FROM THE CLASS\n";
		studentMap.erase(enterStudentID());
		break;
	case 3:  cout << "3. PRINT ALL STUDENT DETAILS\n";
		for (map<int, PersonalDetails>::iterator it = studentMap.begin(); it != studentMap.end(); ++it)
			cout << "\nStudent ID:	" << it->first << '\n' << it->second << '\n';
		break;
	case 4:  cout << "5. DISPLAY ONE STUDENTS DETAILs\n";
		cout << studentMap[enterStudentID()];
		system("pause");
		break;
	case 5:  cout << "4. DELETE ENTIRE CLASS LIST\n";

		cout << "WARNING! DELETING ENTIRE CLASS LIST ALL DATA WILL BE LOST!\nAre You Sure? Y or N?\n";

		if (areYouSure()) {		//are they sure??
		//seems their sure..
		studentMap.clear();	
		}
		else {
			cout << "Phew that was tense...\n";
		}
		break;

	default:
		break;
	}

	if (selection != 6) {
		options(studentMap, id, fileID);
	}
	else {
		cout << "6. Exit Application\n";
		saveFile(studentMap, id, fileID);
	}
	return selection;
}


void getSavedData() {

	vector<string> words;

	int studentCount = 0;

	int temp = 0, id = 0;
	

	string word;


	string line;

	map<int, PersonalDetails>  studentMap;
	PersonalDetails newStudent;

	ifstream inFile("studentDetails.bin");
	ifstream inCountFile;


	while (getline(inFile, line))
	{

		word = line.substr(line.find_first_of(':') + 1);
		words.push_back(word);

		if (words.size() == 6) {


			newStudent.firstName = words[2];
			newStudent.surName = words[3];
			newStudent.dob = words[4];
			newStudent.courseCode = words[5];

			id = stoi(words[1]);
			studentMap[id] = newStudent;
			if (id > studentCount)
				studentCount = id;
			words.clear();

		}
	}

	inCountFile.open("studentCount.bin");
	while (getline(inCountFile, line))
	{
		word = line.substr(line.find_first_of("=") + 1);
		temp = stoi(word);
		break;
	}


	if (temp > studentCount)
		studentCount = temp;




	studentMap[studentCount] = newStudent; //DEBUG

	options(studentMap, studentCount, temp);



}

int main()
{

	getSavedData();
				
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
