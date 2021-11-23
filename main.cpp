
#include <iostream>
#include <string>
#include <regex>
#include <sstream>
#include <time.h>
#include <queue>
#include <windows.h>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <stack>
using namespace std;


int ySequence(string input){

string output = std::regex_replace(
        input,
    regex("[^0-9]*([0-9]+).*"),
    string("$1")
        );
return stoi(output);
}
int xSequence(string input){

input.erase(input.begin(),input.end()-3);
string output = std::regex_replace(
        input,
    regex("[^0-9]*([0-9]+).*"),
    string("$1")
        );

return stoi(output);
}

int dfs(vector <string>& maze, int sizeCol, int sizeRow, int colourRole, char userPrize){

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // data stuctures to solve through the maze
    map <string,string> parentNode;
    queue<int> nextRow;
    queue<int> nextCol;
    int startCol=1; // base start case (1,1) (Y)
    int startRow=1; // base start case (1,1) (X)
    int solved=0;
    int currentCol;
    int currentRow;
    nextCol.push(startCol);
    nextRow.push(startRow);

    //searches maze until queue is empty
    while (!nextCol.empty()){

        currentCol=nextCol.front();
        currentRow=nextRow.front();
        nextCol.pop();
        nextRow.pop();

        //check if we are on the map
        if (currentCol<0||currentRow<0){
        }
        //check if we are on an already visited space
        else if(maze[currentCol][currentRow]=='.'){
            continue;
        //check if we're hitting a wall
        }else if(maze[currentCol][currentRow]=='X'){
            continue;
        //check to see if we've been to that cell
        }else if(maze[currentCol][currentRow]==' '){
        //mark empty spot as visited
            maze[currentCol][currentRow]='.';
        //add all locations around our current one
            nextCol.push(currentCol+1);
            nextRow.push(currentRow);
            nextCol.push(currentCol-1);
            nextRow.push(currentRow);
            nextCol.push(currentCol);
            nextRow.push(currentRow+1);
            nextCol.push(currentCol);
            nextRow.push(currentRow-1);

        //check each condition (up,down,left,right)

            //Right
            if (maze[currentCol+1][currentRow]==' '||maze[currentCol+1][currentRow]=='$'){
            parentNode["("+to_string(currentCol+1)+","+to_string(currentRow)+")"]="("+to_string(currentCol)+","+to_string(currentRow)+")";
            }else{
            }
            //Left
            if (maze[currentCol-1][currentRow]==' '||maze[currentCol-1][currentRow]=='$'){
            parentNode["("+to_string(currentCol-1)+","+to_string(currentRow)+")"]="("+to_string(currentCol)+","+to_string(currentRow)+")";
            }else{
            }
            //Down
            if (maze[currentCol][currentRow+1]==' '||maze[currentCol][currentRow+1]=='$'){
            parentNode["("+to_string(currentCol)+","+to_string(currentRow+1)+")"]="("+to_string(currentCol)+","+to_string(currentRow)+")";
            }else{
            }
            //Up
            if (maze[currentCol][currentRow-1]==' '||maze[currentCol][currentRow-1]=='$'){
            parentNode["("+to_string(currentCol)+","+to_string(currentRow-1)+")"]="("+to_string(currentCol)+","+to_string(currentRow)+")";
            }else{
            }
        }
    //check if we are on the end space
        else if(maze[currentCol][currentRow]=='$'){
                SetConsoleTextAttribute(hConsole, 2);
            cout<<"YOU HAVE SOLVED THE MAZE!"<<endl;
             SetConsoleTextAttribute(hConsole, 7);
            solved=1;
        //exit the loop because we have found the end
            break;
        } else{
            cout << "UNSOLVEABLE";
        }

    }

//initialize stack to become final currentPath
stack<string> currentPath;
string current;
//set the parentNode of our current location as current
current=parentNode["("+to_string(currentCol)+","+to_string(currentRow)+")"];
//add our current location (the end) to the stack
currentPath.push("("+to_string(currentCol)+","+to_string(currentRow)+")");

//add parentNode locations until we make it to the start
while(current!="("+to_string(startCol)+","+to_string(startRow)+")"){
    currentPath.push(current);
    current=parentNode[current];
}
currentPath.push(current);

//extract int from strings until the stack is empty and convert those locations to *'s
while(!currentPath.empty()){

    currentCol=ySequence(currentPath.top());
    currentRow=xSequence(currentPath.top());
    cout <<currentPath.top();
    maze[currentCol][currentRow]='*';
    currentPath.pop();

}

//output message for path
cout << " Is Your Final Path! " << endl;

//highlight and output the final currentPath of the maze


  for (int i=0;i<sizeCol;i++){
      cout<<endl;
    for(int j=0;j<sizeRow;j++){
        if(i == 6 && j == 8){
             cout << userPrize;

        }

        //the current location is a * make it the users choice;
        else if (maze[i][j]=='*'){
        SetConsoleTextAttribute(hConsole, colourRole);
        cout<<maze[i][j];
        SetConsoleTextAttribute(hConsole, 15);
        }
        else{
        cout<<maze[i][j];
        }
    }
    }
    return solved;


}
int main(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "Welcome Traveler to you will be traveling through the VERY difficult maze" << endl;
    cout << "Before we start, what would you like your pize to be? "<<endl;

    string userPrize, userColour;
    int userChoice;
     char prize;
     //ask user what kind of prize they'd like
    cout << "1. # - Harry's Number" << endl;
    cout << "2. & - Andre's Curly Hair" << endl;
    cout << "3. ! - Logan's Presidency" << endl;
    cout << "4. $ - Default" << endl;
         cin >> userPrize;
         //error message
     while (userPrize != "1" && userPrize != "2" && userPrize != "3" && userPrize != "4"){
        SetConsoleTextAttribute(hConsole, 4);
cout << "Invalid Input, Enter a valid number, enter a number from 1-4"<<endl;
        SetConsoleTextAttribute(hConsole, 7);
    cin >> userPrize;
     }

         if(userPrize == "1"){
            prize = '#';
         } else if (userPrize == "2"){
            prize = '&';
         } else if (userPrize == "3"){
            prize = '!';
         } else if (userPrize == "4"){
            prize = '$';
         }


        //ask user what colour path they'd like
    cout <<"What colour would you like your path to be?" << endl;
SetConsoleTextAttribute(hConsole,6);
    cout <<"1 - Yellow"<<endl;
SetConsoleTextAttribute(hConsole, 1);
    cout <<"2 - Blue"<<endl;
SetConsoleTextAttribute(hConsole, 2);
    cout <<"3 - Green"<<endl;
SetConsoleTextAttribute(hConsole, 4);
    cout <<"4 - Red"<<endl;
SetConsoleTextAttribute(hConsole, 5);
    cout <<"5 - Purple"<<endl;
SetConsoleTextAttribute(hConsole, 7);
    cin >> userColour;

    //error message
    while (userColour != "1" && userColour != "2" && userColour != "3" && userColour != "4" && userColour != "5"){
        SetConsoleTextAttribute(hConsole, 4);
cout << "Invalid Input, Enter a valid number, enter a number from 1-5"<<endl;
        SetConsoleTextAttribute(hConsole, 7);
    cin >> userColour;
}
        //determines which colour, then makes the setconsole attribute
        if(userColour == "1"){
            userChoice = 6;

        }else if (userColour == "2"){
            userChoice = 1;

        }else if (userColour == "3"){
            userChoice = 2;

        }else if (userColour == "4"){
            userChoice = 4;

        }if (userColour == "5"){
            userChoice = 5;}

//vector which stores the maze
vector<string> maze;
ifstream inFile("maze.txt");
string fileMaze;
int col;
int row;
//read in collum and row values from the txt file
inFile>>col;
inFile>>row;
//read in the whole maze from the txt file
getline (inFile,fileMaze);
while (getline (inFile,fileMaze))
{
    maze.push_back(fileMaze);
}
//close file
inFile.close();
//search the maze
cout<<dfs(maze,col,row,userChoice,prize);

return 0;
}



