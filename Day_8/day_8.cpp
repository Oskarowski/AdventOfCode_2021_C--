//Advent_of_Code_2021 Day 8: Seven Segment Search
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

vector<vector<string>> encryptedTable;

void importData(){
    ifstream file;
    file.open("testInput.txt");
    if(file.is_open()){
        string line;
        int lineAt=0;;
        int elementAt=0;
        while(getline(file, line)){
            encryptedTable.emplace_back();
            string singular;
            stringstream lineStream(line);
            while (lineStream>>singular){
                if(singular != "|"){
                    encryptedTable[lineAt].push_back(singular);
                }            
            }
            lineAt++;
        }
        cout<<endl;
        file.close();
    }
}

vector<vector<char>> displays;

void decodePatterns(){
    int unique=0;
    displays.resize(encryptedTable.size(), vector<char>(7 , '0'));

    for (int i = 0; i < encryptedTable.size(); i++)
    {
        int lineSize = encryptedTable[i].size(); 
        // cout<<endl<<"lineSize[0]: "<<lineSize;
        for(int k = 0; k < lineSize; k++){
            int encryptionSize = encryptedTable[i][k].size();
            // cout<<endl<<"encryptedTable[i][k]: "<<encryptedTable[i][k];
            // cout<<endl<<"encryptionSize: "<<encryptionSize;
            string encryptedNumber = encryptedTable[i][k];
            // cout<<endl<<"encryptedNumber: "<<encryptedNumber;
            switch(encryptionSize){
                case 2:
                    displays[i][2]=encryptedNumber[0];
                    displays[i][5]=encryptedNumber[1];
                    break;
                case 3:
                    for (auto &&letter : encryptedNumber)
                    {
                        if( 
                            letter != displays[i][2] && 
                            letter != displays[i][5]) 
                            { displays[i][0] = letter; }
                    }
                    break;
                case 4:
                    for (auto &&letter : encryptedNumber)
                    {
                        if( 
                            letter != displays[i][2] && 
                            letter != displays[i][5] &&
                            letter != displays[i][0]) 
                            { displays[i][3] = letter; }
                    }
                    break;
                case 7:
                    for (auto &&letter : encryptedNumber)
                    {
                        if( 
                            letter != displays[i][2] &&
                            letter != displays[i][5] &&
                            letter != displays[i][0] &&
                            letter != displays[i][3]) 
                            { displays[i][1] = letter; }
                    }
                    for (auto &&letter : encryptedNumber)
                    {
                        if( 
                            letter != displays[i][2] && 
                            letter != displays[i][5] &&
                            letter != displays[i][0] &&
                            letter != displays[i][3] &&
                            letter != displays[i][1]) 
                            { displays[i][4] = letter; }
                    }
                    for (auto &&letter : encryptedNumber)
                    {
                        if(
                            letter != displays[i][2] &&  
                            letter != displays[i][5] &&
                            letter != displays[i][0] &&
                            letter != displays[i][3] &&
                            letter != displays[i][1] &&
                            letter != displays[i][4]) 
                            { displays[i][6] = letter; }
                    }
                    break;
            }
        }
    }
    cout<<endl;
    for (int i = 0; i < displays.size(); i++)
    {
        cout<<endl;
        for (size_t j = 0; j < 7; j++)
        {
            cout<<" "<<displays[i][j];
        }
    }
}



int main(){
    cout<<endl<<"Advent_of_Code_2021 Day 8: Seven Segment Search";
    importData();    
    decodePatterns();
    cout<<endl<<endl;
    return 0;
}




































/*
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


*/