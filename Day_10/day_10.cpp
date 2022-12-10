#include <iostream>
#include <vector>
#include <fstream>
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

void printVector(vector<string> &lines){
    for (auto &&i : lines)
    {
        cout<<endl<<i;
    }
    cout<<endl;
}

void findFaultyBrackets(vector<string> lines){
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
                        cout<<endl<<lineAt+1<<"  Corupted line: "<<lines[lineAt]<<" faulty brackets: "<<firstFaultyBracket<<"  "<<secondFaultyBracket; 
                        cout<<endl;
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

void partOne(){
    vector<string> lines;
    string nameOfFile="day_10_testinput.txt";
    importFromFile(nameOfFile, lines);
    // printVector(lines);
    findFaultyBrackets(lines);
}

int main()
{
    partOne();
    return 0;
}