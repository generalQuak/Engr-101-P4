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

/**
 * This file has 1 output, 
 * The gLyft driver needs two things before they start their route:
 *
 * a “map” of their service range that includes symbols for the planets that they’re going to
 * a list of their stops in order: the starting location, each of the planets (as determined 
 * by the nearest neighbor algorithm), and the ending location
*/

// -----compile command: g++ -std=c++11 -Wall -pedantic planRoute.cpp -o planRoute

// libraries
#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <cmath>

using namespace std;

// struct declaration
struct Planet{
    string ID;
    string name;
    string symbol;
    int row;
    int col;
    bool visited;
};





//-----HELPER FUNCTIONS-----

void filterOut(string &maintext){
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



void readFiles(istream &names, istream &locations, vector<Planet> &planets, vector<int> &data ){
    /**
     * @brief Function reads in Planet data into vector
     * 
     * @param names - names file input stream
     * @param locations - locations file input stream
     * @param planets - vector to store planet information in
     * @param data - vector to store grid information in
    */

    // 
    Planet temp; // temp Planet struct
    string ID, name; // temp string variables

    // feed ID and names into planets vector
    while(names >> ID >> name){
        temp.ID = ID; // changes ID attribute
        temp.name = name; // changes name attribute
        planets.push_back(temp); // adds temp Planet to Planets vector
    }

    cout << "finished ID & names" << endl; //names terminal log

    //feed locations
    int gRows, gColumns, sRow, sColumn, eRow, eColumn;
    locations >> gRows >> gColumns >> sRow >> sColumn >> eRow >> eColumn;// input data

    data.push_back(gRows); //Grid Row Size
    data.push_back(gColumns); //Grid Column Size

    data.push_back(sRow); //starting row
    data.push_back(sColumn); //starting column

    data.push_back(eRow); //end row
    data.push_back(eColumn); //end column
    
    int row, column;  // instantiate temp int variables
    string symbol, ID; // instantiate temp string variables
    
    while(locations >> row >> column >> symbol >> ID){

        // find the right planet
        int i = 0;
        while(ID != planets.at(i).ID){
            i++;
        }

        // Update locations for the correct planet
        planets.at(i).row = row;
        planets.at(i).col = column;
        planets.at(i).symbol = symbol;
    }
}



vector<vector<string>> createGrid(const vector<int> &data, const vector<Planet> planets) {
    /**
     * @brief Function reads in data and uses it to make a grid (matrix). Also adds planet
     * symbols onto grid.
     * 
     * @param data - data vector containing information needed 
     * @param planets - vector containing planets information
     * @return the matrix of strings initialized using data
    */

   // instantiate data variables from data vector
    int gRow = data.at(0); // number of rows
    int gCol = data.at(1); // number of columns in grid

    int sRow = data.at(2); // starting row
    int sCol = data.at(3); // starting column

    int eRow = data.at(4); // ending row
    int eCol = data.at(5); // ending column
    
    //instantiate vectors for making grid
    vector<string> row; 
    vector< vector<string> > grid; // grid at i is the column we want
    
    // creates a vector of vectors for how many rows there are
    for(int i = 0; i < gRow; ++i) {
        
        //  creates a vector of strings for how many for how many columns there are
        for (int k = 0; k < gCol; ++k){
            row.push_back("."); // appends each element to row
        }

        grid.push_back(row); // appends each row to the grid
    }

    //-adding planets to grid-
    for(size_t i = 0; i < planets.size(); i ++) { // loops through each planet
        int row = planets.at(i).row-1; //row
        int col = planets.at(i).col-1; //col
        string symbol = planets.at(i).symbol; //planet symbol

        grid.at(row).at(col) = symbol; // change position to symbol on grid
    }    

    // adding start and end points
    grid.at(sRow - 1).at(sCol - 1) = "S"; // marking starting point
    grid.at(eRow - 1).at(eCol - 1) = "E"; // marking ending point
}



double calcDistance(int cRow, int cCol, int pRow, int pCol) {
    /**
     * @brief Function returns a double which is the distance between 2 points
     * 
     * @param cRow - current row location
     * @param cCol - current column location
     * 
     * @param pRow - potential row location
     * @param pCol - potential Column location
    */
   double value = sqrt( pow(pCol - cCol, 2) + pow(pRow - cRow, 2) ); // distance formula

   return value; // value is distance between 2 points
}



double calcClosest(const vector<Planet> &planets, vector<int> data, Planet ref) {
    /**
     * @brief Function will return the closest distance from reference planet to other planets
     * 
     * @param planets - 
     * @param referenceI - 
    */
    int sCurRow = data.at(2); //starting row
    int sCurCol = data.at(3); //starting col
    
    int eRow = data.at(4); // ending row
    int eCol = data.at(5); // ending col 

    
    for (int i = 0; i < planets.size(); i++) {
        double closestDist = 0;
        

        // potDist stores the potential distance between the reference planet and the next
        double potDist = calcDistance(sCurRow, sCurCol, planets.at(i).row, planets.at(i).col);

        // if else if statement 
        if(closestDist == -1) {
            closestDist = potDist;
        }
        else if (potDist < closestDist) {
            closestDist = potDist;
        }
    }

    
}



double calcRouteDist(const vector<Planet> &planets, const vector<int> &data, vector<Planet> &planetsTraveled) {
    /**
     * @brief Function will return the total distance traveled per Nearest Neighbor algorithm
     * 
     * @param data - vector of grid info
     * @param planets - vector of planets
     * @return total distance traveled per route
    */
    //vector<string> planetsTraveled;
    
    int sCurRow = data.at(2); //starting row
    int sCurCol = data.at(3); //starting col
    
    int eRow = data.at(4); // ending row
    int eCol = data.at(5); // ending col 

    double closestDist = -1; // starts a -1, used to find closest distance
    double distTotal = 0.0; // stores the distance traveled
    
    int index; // Reference what was the cloest distnace.

    // loops through every planet (reference planet)
    for (int i = 0; i < planets.size(); i++) {

        // potDist stores the potential distance between the reference planet and the next
        double potDist = calcDistance(sCurRow, sCurCol, planets.at(i).row, planets.at(i).col);

        // if else if statement 
        if(closestDist == -1) {
            closestDist = potDist;
            index = i;
        }
        else if (potDist < closestDist) {
            closestDist = potDist;
            index = i;
        }
    }


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
    vector<int> data;

    readFiles(names, locations, planets, data);//feed names & locations into planets

    names.close(); //close input streams
    locations.close();

    //----- make grid now-----
    vector< vector<string> > grid = createGrid(data, planets);
    
}