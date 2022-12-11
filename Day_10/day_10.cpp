//Advent_of_Code_2021 Day 10: Syntax Scoring
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <cmath>
using namespace std;

void importFromFile(string &nameOfFile, vector<string> &lines){
    ifstream file;
    file.open(nameOfFile);
    if(file.is_open()){
        string singleLine;
        while (getline(file, singleLine))
        {
            lines.push_back(singleLine);
        }
    }
}

vector<vector<char>> matchingBrackets;
void makeMatchingReflection(string line){
    static int lineAt=0;
    matchingBrackets.emplace_back();
    for( int i=line.size()-1; i>=0; i--){
        char whichBracket = line[i], matching;
        switch(whichBracket)
        {
            case '(':
                matching = ')';
                break;
            case '{':
                matching = '}';
                break;
            case '[':
                matching = ']';
                break;
            case '<':
                matching = '>';
                break;
        }
        matchingBrackets[lineAt].push_back(matching);
    }
    lineAt++;
}

void findFaultyBrackets( vector<string> &lines, map<char, int> &corruptedBrackets ){
    vector<char> endingBrackets{')','}',']','>'};
    vector<char> startBrackets{'(','{','[','<'};
    vector<bool> ifNotCorrupted;

    for(int lineAt = 0; lineAt < lines.size(); lineAt++){
        string singleLine = lines[lineAt];
        ifNotCorrupted.push_back(true);
        bool notSkip=false;
        do{
            int signAt=0, singleLineSize=singleLine.size();
            while(signAt<singleLineSize)
            {
                singleLineSize=singleLine.size();
                int endingBracketPosition=-1;
                for(auto &&bracket : endingBrackets){
                    if(singleLine[signAt]==bracket){
                        endingBracketPosition=signAt;
                        notSkip=true;
                        break;
                    }
                    else{
                        notSkip=false;
                    }
                }
                if(endingBracketPosition>0)
                {                
                    char endBracket;
                    endBracket = singleLine[endingBracketPosition];
                    char searchedBracket;
                    switch (endBracket)
                    {
                    case ')':
                        searchedBracket = '(';
                        break;
                    case '}':
                        searchedBracket = '{';
                        break;
                    case ']':
                        searchedBracket = '[';
                        break;
                    case '>':
                        searchedBracket = '<';
                        break;
                    }
                    if(singleLine[endingBracketPosition-1]==searchedBracket){
                        singleLine.erase(singleLine.begin()+endingBracketPosition);
                        singleLine.erase(singleLine.begin()+endingBracketPosition-1);
                        signAt=0;
                        notSkip=true;
                    }
                    else{
                        char firstFaultyBracket=singleLine[endingBracketPosition-1], secondFaultyBracket=singleLine[endingBracketPosition];
                        corruptedBrackets.find(secondFaultyBracket)->second++;
                        // cout<<endl<<lineAt+1<<"  Corupted line: "<<lines[lineAt]<<" faulty brackets: "<<firstFaultyBracket<<"  "<<secondFaultyBracket; 
                        ifNotCorrupted[lineAt]=false;
                        notSkip=false;
                        break;
                    }
                }
                signAt++;
            }
            
        }while(notSkip);

    if(ifNotCorrupted[lineAt]==true){ //for part 2 of puzzle
        makeMatchingReflection(singleLine); 
    }   
    }
}

int calculateIllegalPoints(map<char,int> &corruptedBrackets){
    int points=0;
    for(auto &&bracket: corruptedBrackets){
        switch(bracket.first){
            case ')':
                points+=bracket.second*3;
                break;
            case '}':
                points+=bracket.second*1197;
                break;
            case ']':
                points+=bracket.second*57;
                break;
            case '>':
                points+=bracket.second*25137;
                break;
        }
    }
    return points;
}

void calculateAutocomplatePoints(vector<long long> &points){
    for(int whichLine = 0; whichLine<matchingBrackets.size(); whichLine++){
        points.emplace_back(0);
        for(int positionInLine = 0; positionInLine < matchingBrackets[whichLine].size(); positionInLine++){
            points[whichLine] *= 5;
            char bracket = matchingBrackets[whichLine][positionInLine];
            int howManyPointsToAdd=0;
            switch (bracket)
            {
             case ')':
                howManyPointsToAdd = 1;
                break;
            case '}':
                howManyPointsToAdd = 3;
                break;
            case ']':
                howManyPointsToAdd = 2;
                break;
            case '>':
                howManyPointsToAdd = 4;
                break;
            }
            points[whichLine] += howManyPointsToAdd;
        }
    }
}

void sortPoints(vector<long long> &points){
    bool notSorted=true;
    do{
        notSorted=false;
        for (int j = 0; j < points.size()-1; j++)
        {
            if(points[j]>points[j+1]){
                swap(points[j], points[j+1]);
                notSorted=true;
            }
        }
    }while(notSorted);
}

long long getMiddleValue(vector<long long> &points){
    int middle = floor(points.size() / 2.0);
    // cout<<endl<<"middleI: "<<middleI<<" middleF: "<<middleF;
    return points[middle];
}

void executeTask(){
    vector<string> lines;
        // day_10_puzzleInput  day_10_testInput
    string nameOfFile="day_10_puzzleInput.txt";

    // Part 1:
    map<char,int> corruptedBrackets = { {')', 0}, {'}', 0}, {']', 0}, {'>', 0} };
    importFromFile(nameOfFile, lines);
    findFaultyBrackets(lines, corruptedBrackets);
    int illegalPoints = calculateIllegalPoints(corruptedBrackets);
    cout<<endl<<"The total syntax error score for those errors is: "<<illegalPoints;

    // Part 2:
    cout<<endl;
    vector<long long> machingBracketsPoints;
    calculateAutocomplatePoints(machingBracketsPoints);
    sortPoints(machingBracketsPoints);
    long long middleValue = getMiddleValue(machingBracketsPoints);
    cout<<endl<<"The middle score is: "<<middleValue<<endl;
}


int main()
{
    executeTask();
    return 0;
}