// Hoa Tran (hoatr)
// Brandon Nguyen (tiennguy)
// Lab 021
// April 14, 2024
//------------------------------------------------------
// AUTOGRADER INFO -- IGNORE BUT DO NOT REMOVE 
// test_cases: true
// feedback('all')
// 35b24e49-2842-4603-8ba7-0f656200c2d1
//------------------------------------------------------

/*
This file has 1 output, 

The gLyft driver needs two things before they start their route:

a “map” of their service range that includes symbols for the planets that they’re going to
a list of their stops in order: the starting location, each of the planets (as determined 
by the nearest neighbor algorithm), and the ending location

*/

// -----compile command: g++ -std=c++11 -Wall -pedantic planRoute.cpp -o planRoute

// libraries
#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>

using namespace std;
// struct declaration
struct Planet{
    string ID;
    string name;
    int row;
    int col;
    bool visited;
};

//-----HELPER FUNCTIONS-----

void filterOut(string maintext){
/**
 * @brief Function used to filter out ("X") noise from strings
 * 
 * @param maintext - main text to be filtered
 * *filtering value is hard coded into function
*/

    while(maintext.find("X") != maintext.npos){ // loop through loop until there are no more instances
        int index = maintext.find("X"); // set the index to the next instance
        maintext.erase(index,1); // remove the instance from the string
    }
}

void readfiles(istream &names, istream &locations, vector<Planet> &array){
    /**
     * @brief Function reads in Planet data into vector
     * 
     * @param names - names file input stream
     * @param locations - locations file input stream
     * @param array - vector to store information in
    */

    // 
    Planet temp; // temp Planet struct
    string ID, name; // temp string variables

    // feed ID and names into planets vector
    while(names >> ID >> name){
        temp.ID = ID; // changes ID attribute
        temp.name = name; // changes name attribute
        array.push_back(temp); // adds temp Planet to Planets vector
    }

    cout << "finished ID & names" << endl; //names terminal log

    //feed locations
    string line;
    int row = getline(locations, line);// header

}





//----- 1 TIME EXEC MAIN FUNCTION (DRIVER) -----
int main(){

    //-----USER PROMPT-----
    string locationsf;
    string namesf;

    //locations filename
    cout << "Enter Locations Filename:" << endl;
    cin >> locationsf;

    //names filename
    cout << "Enter Names Filename:" << endl;
    cin >> namesf;

    //-----OPENING FILES-----
    ifstream locations(locationsf);
    ifstream names(namesf);

    // file check if open
    if(!locations.is_open() || !names.is_open()) {
        cout << "Input file could not be opened" << endl;
        return 1;
    }

    //Create planets vector and store information in it
    vector<Planet> planets;

    readfiles(names,locations, planets);//feed names & locations into planets

    names.close(); //close input streams
    locations.close();

    // oki now wat
}