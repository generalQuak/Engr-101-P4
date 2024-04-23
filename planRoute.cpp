// Hoa Tran (hoatr)
// Brandon Nguyen (tiennguy)
// Lab 021 & 032
// April 22, 2024
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
    int ID;
    string name;
    string symbol;
    int row;
    int col;
    bool visited;
};





//-----HELPER FUNCTIONS-----

void filter(string &maintext){
/**
 * @brief Function used to filter out ("X") noise from strings
 * 
 * @param maintext - main text to be filtered
 * *filtering value is hard coded into function
*/

    // removes all instances of "XX"
    while(maintext.find("XX") != maintext.npos){ // loop through loop until there are no more instances
        int index = maintext.find("XX"); // set the index to the next instance
        maintext.erase(index,2); // remove the instance from the string
    }

    // removes all instances of "_"
    while(maintext.find("_") != maintext.npos){ // loop through loop until there are no more instances
        int index = maintext.find("_"); // set the index to the next instance
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
    string name; // temp string variables
    int ID;

    // feed ID and names into planets vector
    while(names >> ID >> name){
        temp.ID = ID; // changes ID attribute
        filter(name);
        temp.name = name; // changes name attribute
        planets.push_back(temp); // adds temp Planet to Planets vector
    }

    //cout << "finished ID & names" << endl; //names terminal log

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
    string symbol; // instantiate temp string variable
    
    while( locations >> row >> column >> symbol >> ID ){

        //checking if planet is within grid
        if( ( (0 < column) && (column <= gColumns) ) && ( (0 < row) && (row <= gRows) ) ){

            // find the right planet
            int i = 0;
            while(ID != planets.at(i).ID){
                i++;
            }

            // Update locations for the correct planet
            planets.at(i).row = row;
            planets.at(i).col = column;
            planets.at(i).symbol = symbol;

        } else {
            //not within grid
            cout << ID <<" out of range - ignoring" << endl;
        }
    }

    cout << "finished reading in planets" << endl; //planet terminal log
}



vector<vector<string>> createGrid(const vector<int> &data, const vector<Planet> &planets) {
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

    cout << "DONE WITH BASE GRID-----\n   looping through each planet \nplanets.size(): "<< planets.size() << endl;

    //-adding planets to grid-
    for(size_t i = 0; i < planets.size(); i ++) { // loops through each planet
        Planet planet = planets.at(i);

        cout << "starting with planet: " << planet.ID << ", index: " << i << endl;

        int row = (planet.row); //row
        int col = (planet.col); //col

        cout << "row: " << row << ", col: " << col << endl;

        string symbol = planet.symbol; //planet symbol

        grid.at(row - 1).at(col -1) = symbol; // change position to symbol on grid
    }    

    cout << "DONE WITH PLANETS" << endl;

    // adding start and end points
    grid.at(sRow -1).at(sCol - 1) = "S"; // marking starting point
    grid.at(eRow - 1).at(eCol - 1) = "E"; // marking ending point

    return grid;
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
     *
     * @returns the distance from reference point to potential point
    */
   double value = sqrt( pow(pCol - cCol, 2) + pow(pRow - cRow, 2) ); // distance formula

   return value; // value is distance between 2 points
}



double calcClosest(const vector<Planet> &planets, int sCurRow, int sCurCol) {
    /**
     * @brief Function will return the closest distance from reference planet to other planets
     * 
     * @param planets - Vector of planets 
     * // Might not be needed @param referenceI - A Reference planet or point 
     * 
     * @param sCurRow - The Current Row for reference.
     * @param sCurCol - The current column for refernece
     * @return Returns the distance from the reference planet to the closest stop (Planet/ End position)
    */

    double closestDist = -1.0; // value to be returned.

    for (size_t i = 0; i < planets.size(); i++) {    
        
        // potDist stores the potential distance between the reference planet and the next
        double potDist = calcDistance(sCurRow, sCurCol, planets.at(i).row, planets.at(i).col);

        // if else if statement 
        if (planets.at(i).visited == false) {
            if(closestDist == -1.0 ) {
            closestDist = potDist;
            }
            // maybe put something here... for when they're equal... maybe in calc Routedist
            else if (potDist < closestDist) {
            closestDist = potDist;
            }

        }
        
    }
    return closestDist;
}



void calcRoute(vector<Planet> &planets, const vector<int> &data, vector<Planet> &planetsTraveled) {
    /**
     * @brief Function will append a vector of Planets traveled per Nearest Neighbor algorithm
     * 
     * @param planets - vector of planets
     * @param data - vector of grid info
     * @param planetsTraveled - empty vector of planets
    */
    
    int sCurRow = data.at(2); //starting or current row position
    int sCurCol = data.at(3); //starting or current column position
    
    int eRow = data.at(4); // ending row position
    int eCol = data.at(5); // ending column position

    double closest = 0.0; // creates closest distance reference 
    
    int index; // Reference what was the cloest distnace.

    //Continues to Loop until route from start to end.
    while (sCurRow != eRow && sCurCol != eCol) {
        closest = -1.0; //set closest to a non valid value

        // checks if we have reached every planet yet
        if (planets.size() != planetsTraveled.size()) {

            // iterates through each potential planet
            for (size_t i = 0; i < planets.size(); ++i) {
                
                //storing the closest
                double potClosestDist = calcClosest(planets, sCurRow, sCurCol);
                if (closest == -1.0) {
                    closest = potClosestDist;
                    index = i;
                    }
                else if (closest == potClosestDist) {
                    if (planets.at(i).ID < planets.at(index).ID) {
                        closest = potClosestDist;
                        index = i;
                    }
                }
                else if (closest > potClosestDist) {
                    closest = potClosestDist;
                    index = i;
                }
            }
            sCurRow = planets.at(index).row;
            sCurCol = planets.at(index).col;
            planets.at(index).visited = true;
            planetsTraveled.push_back(planets.at(index));
        }     
    }
}



void writeFile(vector<Planet> &planetsTraveled, const vector<int> &data, vector<vector<string>> grid ) {
    /**
     * @brief Function will take information (vectors) and information and output it to an output stream
     *
     * @param planetsTraveled - vector which contains the list of planets to travel to in order
     * @param data - vector of driver data
     * @param grid - matrix of strings which represent individual positions on a map
     * 
    */

    //---WRITE MAP---
    ofstream summary("journey.txt");

    //loops through each row
    for(size_t row = 0; row < grid.size(); row++){
        //loops through each column
        for(size_t col = 0; col < grid.at(0).size(); col++){
            summary << grid[row][col];//prints element of index
        }
        summary << endl; // moves onto next row
   }
   
   //-- START POS -- 
   summary << "Start at " << data.at(2) << " " << data.at(3) << endl;
   
   //-- PLANET INFO --

   // loop through each planet and
   for(size_t i = 0; i < planetsTraveled.size(); i++){
    Planet planet = planetsTraveled.at(i);

    // print Planet info
    summary << "Go to " << planet.name << " at " << planet.row << " " << planet.col << endl;
   }
   
   //-- END POS ---
   summary << "End at " << data.at(4) << " " << data.at(5) << endl;
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

    // file check (if open)
    if(!locations.is_open() || !names.is_open()) {
        cout << "Input file could not be opened" << endl;
        return 1;
    }

    //Create planets and data vector and store information in it
    vector<Planet> planets;
    vector<int> data;

    readFiles(names, locations, planets, data); //feed names & locations into planets

    cout << "-----Files Read" << endl;

    names.close(); //close input streams
    locations.close();

    cout << "-----Input streams closed" << endl;

    //----- MAKE GRID-----
    vector< vector<string> > grid = createGrid(data, planets);

    cout << "-----Made grid" << endl;
    
    //----- CALCULATE ROUTE -----
    vector<Planet> planetsTraveled;
    calcRoute(planets, data, planetsTraveled);

    cout << "-----Calculated Route" << endl;

    //----- WRITE OUTPUT FILE ("journey.txt")-----
    writeFile(planetsTraveled, data, grid);

    cout << "-----Wrote journey.txt" << endl;

}