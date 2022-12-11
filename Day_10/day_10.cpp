//Advent_of_Code_2021 Day 10: Syntax Scoring
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
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

void findFaultyBrackets( vector<string> lines, map<char,int> &corruptedBrackets ){
    vector<char> endingBrackets{')','}',']','>'};
    vector<char> startBrackets{'(','{','[','<'};

    for(int lineAt = 0; lineAt < lines.size(); lineAt++){
        string singleLine = lines[lineAt];
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
                        // cout<<endl;
                        // for (auto &&w : singleLine)
                        // {
                        //     cout<<" "<<w;
                        // }
                        notSkip=false;
                        break;
                    }
                }
                signAt++;
            }
        }while(notSkip);
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

void partOne(){
    vector<string> lines;
    map<char,int> corruptedBrackets = { {')', 0}, {'}', 0}, {']', 0}, {'>', 0} };
    // day_10_puzzleInput  day_10_testInput
    string nameOfFile="day_10_puzzleInput.txt";
    importFromFile(nameOfFile, lines);
    findFaultyBrackets(lines, corruptedBrackets);
    int illegalPoints = calculateIllegalPoints(corruptedBrackets);
    cout<<endl<<"The total syntax error score for those errors is: "<<illegalPoints<<endl;
}

int main()
{
    partOne();
    return 0;
}