// Day 5: Hydrothermal Venture
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

string nameOfInportedFile="inputFile.txt";
int sizeOfTheGrid=999, amountOfLines, howManyOverlap=0;

vector<vector<int>> grid(sizeOfTheGrid, vector<int>(sizeOfTheGrid, 0));

struct lineFromFile{
    int xStart=0, yStart=0;
    int xEnd=0, yEnd=0;
};

vector<lineFromFile> allLines;


void showTheGrid(){
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid.size(); j++)
        {
            if(grid[i][j]==0) cout<<'.'<<" ";
            else cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void importLinesFromFile(){
    ifstream whereLinesInFile;
    whereLinesInFile.open(nameOfInportedFile);
    if (whereLinesInFile.is_open()){
        cout<<endl<<"File Opened!"<<endl;
        int iteration=0;
        while (!whereLinesInFile.eof())
        {
            string controlVar="420";
            allLines.push_back(lineFromFile());
            // cout<<endl<<"    iteration: "<<iteration;
            for (int i = 0; i < 3; i++)
            {
                whereLinesInFile>>controlVar;
                stringstream lineStream(controlVar);
                string temporaryForConversionFromStringToInt="";
                switch (i)
                {
                case 0:
                    getline(lineStream, temporaryForConversionFromStringToInt, ',');
                    allLines[iteration].xStart=stoi(temporaryForConversionFromStringToInt);
                    getline(lineStream, temporaryForConversionFromStringToInt, ',');
                    allLines[iteration].yStart=stoi(temporaryForConversionFromStringToInt);
                    // cout<<endl<<"xStart: "<<allLines[iteration].xStart<<" yStart: "<<allLines[iteration].yStart;
                    break;
                case 2:
                    getline(lineStream, temporaryForConversionFromStringToInt, ',');
                    allLines[iteration].xEnd=stoi(temporaryForConversionFromStringToInt);
                    getline(lineStream, temporaryForConversionFromStringToInt, ',');
                    allLines[iteration].yEnd=stoi(temporaryForConversionFromStringToInt);
                    // cout<<endl<<"xEnd: "<<allLines[iteration].xEnd<<" yEnd: "<<allLines[iteration].yEnd;
                    break;
                
                default:
                    break;
                }
            }
            iteration++;
            // cout<<endl;
        }
        whereLinesInFile.close();
        cout<<endl<<"File Closed!"<<endl;
        cout<<endl;
    }
}

bool isXStartBigger(int i){
    if(allLines[i].xStart>=allLines[i].xEnd) {return true;}
    else {return false;}
}
bool isYStartBigger(int i){
    if(allLines[i].yStart>=allLines[i].yEnd) {return true;}
    else {return false;}
}
bool isXStartEqualXEnd(int i){
    if(allLines[i].xStart==allLines[i].xEnd) {return true;}
    else {return false;}
}
bool isYStartEqualYEnd(int i){
    if(allLines[i].yStart==allLines[i].yEnd) {return true;}
    else {return false;}
}
bool isYStartSmaller(int i){
    if(allLines[i].yStart<=allLines[i].yEnd) {return true;}
    else {return false;}
}
bool isXStartSmaller(int i){
    if(allLines[i].xStart<=allLines[i].xEnd) {return true;}
    else {return false;}
}
bool isThisDiagonalLine(int &i){
    int deltaX=0, deltaY=0;
    deltaX=abs(allLines[i].xEnd-allLines[i].xStart);
    deltaY=abs(allLines[i].yEnd-allLines[i].yStart);
    if (deltaX==deltaY) {return true;}
    else {return false;}
    
}

void drawHorizontalLine(int &i){
    // cout<<endl<<"Drawing horizontal line: "<<i+1<<endl;

    bool isYBiggerY=isYStartBigger(i);
    bool isYSmallerY=isYStartSmaller(i);

    if (isYBiggerY)
    {
        while (isYBiggerY)
        {
            grid[allLines[i].yStart][allLines[i].xStart]++;
            allLines[i].yStart--;
            isYBiggerY=isYStartBigger(i);
        }
    }
    else if(isYSmallerY)
    {
        while (isYSmallerY)
        {
            grid[allLines[i].yStart][allLines[i].xStart]++;
            allLines[i].yStart++;
            isYSmallerY=isYStartSmaller(i);
        }
    }
}

void drawVerticalLine(int &i){
    // cout<<endl<<"Drawing vertical line: "<<i+1<<endl;

    bool isXBiggerX=isXStartBigger(i);
    bool isXSmallerX=isXStartSmaller(i);

    if (isXBiggerX)
    {
        while (isXBiggerX){
            grid[allLines[i].yStart][allLines[i].xStart]++;
            allLines[i].xStart--;
            isXBiggerX=isXStartBigger(i);
        }
    }
    else if(isXSmallerX)
    {
        while (isXSmallerX){
            grid[allLines[i].yStart][allLines[i].xStart]++;
            allLines[i].xStart++;
            isXSmallerX=isXStartSmaller(i);
        }
    }
}

void drawDiagonalLine(int i){
    // cout<<endl<<"Drawing diagonal line: "<<i+1<<endl;

    bool isXBiggerX=isXStartBigger(i);
    bool isXSmallerX=isXStartSmaller(i);
    bool isYBiggerY=isYStartBigger(i);
    bool isYSmallerY=isYStartSmaller(i);

    if (isXBiggerX && isYBiggerY)
    {
        while (isXBiggerX && isYBiggerY){
            grid[allLines[i].yStart][allLines[i].xStart]++;
            allLines[i].xStart--;
            allLines[i].yStart--;
            isXBiggerX=isXStartBigger(i);
            isYBiggerY=isYStartBigger(i);
        }
    }
    else if (isXBiggerX && isYSmallerY)
    {
        while (isXBiggerX && isYSmallerY){
            grid[allLines[i].yStart][allLines[i].xStart]++;
            allLines[i].xStart--;
            allLines[i].yStart++;
            isXBiggerX=isXStartBigger(i);
            isYSmallerY=isYStartSmaller(i);
        }
    }
    else if (isXSmallerX && isYSmallerY)
    {
        while (isXSmallerX && isYSmallerY){
            grid[allLines[i].yStart][allLines[i].xStart]++;
            allLines[i].xStart++;
            allLines[i].yStart++;
            isXSmallerX=isXStartSmaller(i);
            isYSmallerY=isYStartSmaller(i);
        }
    }
    else if (isXSmallerX && isYBiggerY)
    {
        while (isXSmallerX && isYBiggerY){
            grid[allLines[i].yStart][allLines[i].xStart]++;
            allLines[i].xStart++;
            allLines[i].yStart--;
            isXSmallerX=isXStartSmaller(i);
            isYBiggerY=isYStartBigger(i);
        }
    }
}

void applyLinesOnGrid(){
    for (int i = 0; i < allLines.size(); i++)
    {
        // cout<<endl<<"F: applyLinesOnGrid"<<endl;

        if (isXStartEqualXEnd(i)) {drawHorizontalLine(i);}
        else if (isYStartEqualYEnd(i)) {drawVerticalLine(i);}
        else if (isThisDiagonalLine(i)) {drawDiagonalLine(i);}
    }
}

void countUpOverlapping(){
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid.size(); j++)
        {
            if(grid[i][j]>=2){howManyOverlap++;}
        }
        
    }
    cout<<endl<<"F: howManyOverlaps: "<<howManyOverlap<<endl;
}

int main(){
    cout<<endl<<"Day 5: Hydrothermal Venture"<<endl;
    
    importLinesFromFile();
    applyLinesOnGrid();
    countUpOverlapping();

    getchar();
    return 0;
}