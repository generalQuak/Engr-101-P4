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
};

// helper functions

// 1 time exc main function
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

    string ID, name;

    //instantiate temp planet & planets vector
    vector<Planet> planets;
    Planet temp;

    // feed ID and names into planets vector
    while(names >> ID >> name){
        temp.ID = ID;
        temp.name = name;
        planets.push_back(temp);
    }

}
