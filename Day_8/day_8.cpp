//Advent_of_Code_2021 Day 8: Seven Segment Search
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct displayScreen
{
        vector<vector<string>> displayScreen{
        {".aaaa."},
        {"b....c"},
        {"b....c"},
        {".dddd."},
        {"e....f"},
        {"e....f"},
        {".gggg."}
    };

    void printDisplay(){
        cout<<endl;
        for (int i = 0; i < this->displayScreen.size(); i++)
        {
            for (int j = 0; j < this->displayScreen[i].size(); j++)
            {
                cout<<this->displayScreen[i][j];
            }
            cout<<endl;
        }
    }
};


struct encodedNumber{

    int afterDecryption, lengthOf;
    string beforeDecryption;

    void measureLength(){
        this->lengthOf = this->beforeDecryption.size();
    }
};

void inportEncodedNumbers(string &nameOfFile, vector<vector<encodedNumber>> &encodedNumberS)
{
    // cout<<endl<<"inportEncodedNumbers()"<<endl;
    ifstream fileWithEncodedNumbers;
    fileWithEncodedNumbers.open(nameOfFile);
    if(fileWithEncodedNumbers.is_open()){
        // cout<<endl<<"File opened"<<endl;
        string lineFromFile;
        int whichLine=0;
        while(getline(fileWithEncodedNumbers, lineFromFile))
        {
            stringstream lineS(lineFromFile);
            encodedNumberS.emplace_back();
            int whichWord=0;
            string individualWord;
            while (lineS>>individualWord)
            {
                if(individualWord=="|"){continue;}
                else{
                // cout<<endl<<individualWord;
                encodedNumberS[whichLine].push_back(encodedNumber());
                encodedNumberS[whichLine][whichWord].beforeDecryption=individualWord;
                encodedNumberS[whichLine][whichWord].measureLength();
                whichWord++;
                }
            }
            whichLine++;
        }
        // cout<<endl<<"File closed";
    }
    // else {cout<<"Not able to open file :(";};
}

void printEncodedNumbers(vector<vector<encodedNumber>> &encodedNumberS){
    cout<<endl<<"printEncodedNumbers()"<<endl;
    for (int i = 0; i < encodedNumberS.size(); i++)
    {
        for (int j = 0; j < encodedNumberS[i].size(); j++)
        {
            cout<<encodedNumberS[i][j].beforeDecryption<<" ";
        }
        cout<<endl;
    }
}

void countUniquePatternsInOutput(vector<vector<encodedNumber>> &encodedNumberS, int &uniquePatterns){
    cout<<endl<<"countUniquePatternsInOutput()"<<endl;
    vector<int> uniques{2,3,4,7};

    for(int i = 0; i < encodedNumberS.size(); i++){
        int amountOfWordsInLine = encodedNumberS[i].size()-1;
        // cout<<endl<<"amountOfWordsInLine-1: "<<amountOfWordsInLine;
        for(int j = amountOfWordsInLine; j > (amountOfWordsInLine-4); j--){
            for(int k = 0; k < 4; k++){
                if(encodedNumberS[i][j].lengthOf==uniques[k]){uniquePatterns++; break;}
            }
        }
    }
}

void letsssRollPart_1()
{
    cout<<endl<<"PART 1"<<endl;
    string nameOfFile="testinput.txt";
    vector<vector<encodedNumber>> encodedNumberS;
    int unuquePatternsCount=0;
    
    inportEncodedNumbers(nameOfFile, encodedNumberS);
    countUniquePatternsInOutput(encodedNumberS, unuquePatternsCount);
    cout<<endl<<endl<<"unuquePatternsCount: "<<unuquePatternsCount;
    cout<<endl;
}

void letsssRollPart_2(){
    cout<<endl<<"PART 2"<<endl;
    string nameOfFile="test2.txt";
    vector<vector<encodedNumber>> encodedNumberS;
    
    inportEncodedNumbers(nameOfFile, encodedNumberS);
    printEncodedNumbers(encodedNumberS);


}

int main(){
    cout<<endl<<"Advent_of_Code_2021 Day 8: Seven Segment Search";
    // letsssRollPart_1();
    letsssRollPart_2();

    return 0;
}