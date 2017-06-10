//Colin Legge
//calegge714
//Section 510
//calegge714@gmail.com

#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <regex>
#include "HashTable.h"

using namespace std;

int main(){
	HashTable hash; //declare hash from my class HashTable
	vector<int> UIN_vec; //declare vectors to call specific files to output to screen and 'results.csv'
	vector<int> grade_vec;
	vector<int> UIN_roster_vec;
	vector<string> roster_line;
	
	//Parts 1-3 on Homework
	cout << "Reading from input.csv..." << endl;
	ifstream input("input.csv"); //read from input.csv
	string name, data, line, UIN, grade;
	int UIN_int, grade_int;
	smatch keys; //regex smatch vector for UINs
	smatch grades; //regex smatch vector for grades
	while (input.good()){
		getline(input, name, ',');
		getline(input, data, ' ');
		line = name+","+data;
		regex UIN_pat("[0-9]{9}"); //regex pattern for UINs
		if(regex_search(line,keys,UIN_pat)){
			UIN = keys[0];
			UIN_int = stoi(UIN); //convert to int for insertion into hash table
			UIN_vec.push_back(UIN_int);
		}
		regex grade_pat("[0-9],[0-9]{2}"); //regex pattern for grades (will have two extra characters at front)
		if(regex_search(line,grades,grade_pat)){
			grade = grades[0];
			grade.erase(0,2); //delete the first two characters to obtain only the grade
			grade_int = stoi(grade); //convert to int for insertion into hash table
			grade_vec.push_back(grade_int); //store grades to insert into 'results.csv' later
		}
		cout << "Successfully inserted " << grade_int << " at key " << UIN_int << "!" << endl;
		hash.Insert(UIN_int,grade_int); //insert function defined in HashTable class: UIN_int is key and grade_int is valu
	}
	input.close();
	
	//Parts 4-6
	cout << endl;
	ifstream roster("roster.csv"); //read from 'roster.csv'
	string UIN_grade;
	int UIN_roster;
	smatch roster_grades; //regex smatch vector for grades
	while(roster.good()){
		getline(roster, line);
		line.pop_back(); //delete invisible endl character
		roster_line.push_back(line);
		regex UIN_pat("[0-9]{9}");
		if(regex_search(line,roster_grades,UIN_pat)){
			UIN_grade = roster_grades[0];
			UIN_roster = stoi(UIN_grade); //convert from strong to int to store in hash table
			UIN_roster_vec.push_back(UIN_roster);
		}
	}
	roster.close();
	
	//Part 7
	ofstream results;
	results.open("results.csv"); //read from 'results.csv'
	for (int i = 0; i<UIN_roster_vec.size(); i++){
		if(hash.Search(UIN_roster_vec[i])!=-1){ //if the key returns a value from the hash table
			cout << "The UIN " << UIN_roster_vec[i] << " scored a " << hash.Search(UIN_roster_vec[i]) << "!" << endl;
			results << roster_line[i] + to_string(hash.Search(UIN_roster_vec[i])) << endl; //write to 'results.csv'
		}
		else{
			results << roster_line[i] << endl; //default write to 'results.csv'
		}
	}
}