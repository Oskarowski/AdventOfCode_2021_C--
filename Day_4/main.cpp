//Advent of Code 2021 Day 4: Giant Squid
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

struct bingoNumber{
    int numberInBoard={0};
    bool isMarked=false;
};

string nameOfInportedFile="numbers.txt";
vector<int> chosenNumbersInput;
vector<int> isBoardWinning;
vector<vector<vector<bingoNumber>>> bingoBoard;
vector<vector<bingoNumber>> copyOfLastBingoBoard(5, vector<bingoNumber>(5));
int amountOfBingoBoards=0, winnigBoard, score, sumOfAllUnmarkedNumbers=0, sumOfAllMarkedNumbers, lastWinnigBoard, idOfCopiedBingoBoard;
bool isWinningBoardFound=false;

void getAmountOfBingoBoards(){
    ifstream bingoBoardsFile;
    bingoBoardsFile.open(nameOfInportedFile);
    if(bingoBoardsFile.is_open()){
        string line;
        float amountOfLines=0;
        do{
            getline(bingoBoardsFile, line);
            amountOfLines++;
        }while(!bingoBoardsFile.eof());
        amountOfLines -= 2;
        //cout<<endl<<"amountOfLines: "<<amountOfLines;
        amountOfBingoBoards=ceil((amountOfLines/6));
        cout<<endl<<"amountOfBingoBoards: "<<amountOfBingoBoards;
        bingoBoard.resize(amountOfBingoBoards, vector<vector<bingoNumber>>(5,vector<bingoNumber>(5)));
    }
    bingoBoardsFile.close();
    isBoardWinning.resize(amountOfBingoBoards, 0);
}

void copyFromVectorToVector(int whichBingoBoardToCopy){
    idOfCopiedBingoBoard=whichBingoBoardToCopy;
    for(int j=0;j<5;j++)
    {
        for (int k = 0; k < 5; k++)
        {
            copyOfLastBingoBoard[j][k].numberInBoard=bingoBoard[whichBingoBoardToCopy][j][k].numberInBoard;
            copyOfLastBingoBoard[j][k].isMarked=bingoBoard[whichBingoBoardToCopy][j][k].isMarked;

        }
    }
}

void importWinningChoosenNumbers(){
    ifstream importFile;
    importFile.open(nameOfInportedFile);
    if(importFile.is_open()){
        string wholeFirstline;
        getline(importFile, wholeFirstline);
        stringstream firstLineStream(wholeFirstline);
        int iteration=0;
        cout<<endl<<"importedChoosenWinningNumbers: ";
        while (firstLineStream.good())
        {
            string substr;
            getline(firstLineStream, substr, ',');
            int numberAfterConvert;
            numberAfterConvert=stoi(substr);
            cout<<numberAfterConvert<<" ";
            chosenNumbersInput.push_back(numberAfterConvert);
        }
        cout<<endl<<endl;
    }
    importFile.close();
}

void importGridFromFile(){
    ifstream gridFile;
    gridFile.open(nameOfInportedFile);
    if(gridFile.is_open()){
        string skipLine;
        getline(gridFile, skipLine);
        for(int i = 0; i < amountOfBingoBoards; i++)
        {
            for(int j=0;j<5;j++)
            {
                for (int k = 0; k < 5; k++)
                {
                    int number;              
                    gridFile>>number;
                    bingoBoard[i][j][k].numberInBoard=number;
                    bingoBoard[i][j][k].isMarked=false;
                    cout<<bingoBoard[i][j][k].numberInBoard<<",";
                }
                cout<<endl;
            }
            cout<<endl;
        }
    }
    gridFile.close();
    
}

void markingNumber(int winningNumber)
{
    for(int i = 0; i < bingoBoard.size(); i++)
    {
        for(int j = 0;j < 5; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                if(bingoBoard[i][j][k].numberInBoard==winningNumber){
                    bingoBoard[i][j][k].isMarked=true;
                }
            }
        }
    }
}

void showAllTheBingoBoards(){
    cout<<endl<<endl<<"showingTheBoards: "<<endl;
    for(int i = 0; i < bingoBoard.size(); i++)
    {
        for(int j=0;j<5;j++)
        {
            for (int k = 0; k < 5; k++)
            {
                cout<<bingoBoard[i][j][k].numberInBoard << ((bingoBoard[i][j][k].isMarked) ? "t, " : ",");
            }
            cout<<endl;
        }
        cout<<endl;
    }
}

void showSpecificBingoBoard(int whichOne){
    //cout<<endl<<"showingTheBingoBoard number "<<whichOne+1<<endl;
    for(int j=0;j<5;j++)
    {
        for (int k = 0; k < 5; k++)
        {
            cout<<bingoBoard[whichOne][j][k].numberInBoard<<",";
        }
        cout<<endl;
    }
    cout<<endl;
}

void checkForWinningBoards(){
    if(isWinningBoardFound==false){
        for( int i = 0; i < bingoBoard.size(); i++){ //pętla po planszach
            if (isBoardWinning[i]==0)
            {
                for(int row = 0; row < 5; row++){ //pętla po rzędach
                    int amountOfMarkedInRow=0;
                    for( int column = 0; column < 5; column++){
                        if(bingoBoard[i][row][column].isMarked){amountOfMarkedInRow++;}
                        if(amountOfMarkedInRow==5){
                            // cout<<endl<<"!!! Found winning BINGO BOARD horizontally !!!"<<endl;
                            //showSpecificBingoBoard(i);
                            winnigBoard=i;
                            isWinningBoardFound=true;
                            isBoardWinning[i]=1;
                            copyFromVectorToVector(i);
                            break;
                        }
                    }
                }
                for(int column = 0; column < 5; column++){ //pętla po kolumnach
                    int amountOfMarkedInColumn=0;
                    for( int row = 0; row < 5; row++){
                        if(bingoBoard[i][row][column].isMarked){amountOfMarkedInColumn++;}
                        if(amountOfMarkedInColumn==5){
                            // cout<<endl<<"!!! Found winning BINGO BOARD vertically !!!"<<endl;
                            //showSpecificBingoBoard(i);
                            winnigBoard=i;
                            isWinningBoardFound=true;
                            isBoardWinning[i]=1;
                            copyFromVectorToVector(i);
                            break;
                        }
                    }
                }
            }
        }
    }
}

void sumUnmarkedInBoard(int boardNumber){
    cout<<endl<<"sumUnmarkedInBoard:";
    showSpecificBingoBoard(boardNumber);
    cout<<endl;
    sumOfAllUnmarkedNumbers=0;
    sumOfAllMarkedNumbers=0;
    for (int i = 0; i < 5; i++)
    {
        for (int k = 0; k < 5; k++)
        {
            if(bingoBoard[boardNumber][i][k].isMarked==false){
                sumOfAllUnmarkedNumbers += bingoBoard[boardNumber][i][k].numberInBoard;
                //cout<<" "<<bingoBoard[boardNumber][i][k].numberInBoard;
            }
            if(bingoBoard[boardNumber][i][k].isMarked==true){
                sumOfAllMarkedNumbers += bingoBoard[boardNumber][i][k].numberInBoard;
            }
        }
    }
    //cout<<endl<<"sumOfAllUnmarkedNumbers: "<<sumOfAllUnmarkedNumbers;
}

bool isStillPossibleWinner(){
    bool isTrue=false;
    for (int i = 0; i < isBoardWinning.size(); i++)
    {
        if(isBoardWinning[i]==0){
            isTrue=true;
            return true;
        }
        else if(isBoardWinning[i]==1){isTrue=false;}
    }
    return isTrue;
}

int getTheLastWinningBoard(){
    importGridFromFile();
    isWinningBoardFound=false;
    int loseLastMarkedNumber, loseIteration={0};
    bool isPossible=true;
    
    while (isPossible)
    {
        isPossible=isStillPossibleWinner();
        if (loseIteration < chosenNumbersInput.size())
        {
            markingNumber(chosenNumbersInput[loseIteration]);
            checkForWinningBoards();
            if(isWinningBoardFound==true){
                bingoBoard.erase(bingoBoard.begin()+winnigBoard);
                isBoardWinning.erase(isBoardWinning.begin()+winnigBoard);
                isWinningBoardFound=false;
                loseLastMarkedNumber=chosenNumbersInput[loseIteration];
                lastWinnigBoard=winnigBoard;
            }
            loseIteration++;       
        }
    }
    int sumOfUnmmarked=0;
    cout<<endl<<"Last Winning Board: "<<endl;
    for(int j=0;j<5;j++)
    {
        for (int k = 0; k < 5; k++)
        {
            cout<<copyOfLastBingoBoard[j][k].numberInBoard<<",";
            if (copyOfLastBingoBoard[j][k].isMarked==false)
            {
                // cout<<" ["<<copyOfLastBingoBoard[j][k].numberInBoard<<"] ";
                sumOfUnmmarked+=copyOfLastBingoBoard[j][k].numberInBoard;
            }
        }
        cout<<endl;
    }
    cout<<endl<<endl;
    // cout<<endl<<"PART 2: sumOfUnmmarked: "<<sumOfUnmmarked;
    // cout<<endl<<"PART 2: lastMarkedNumber: "<<loseLastMarkedNumber;

    return sumOfUnmmarked*loseLastMarkedNumber;
}

int main(){
    cout<<endl<<"//Advent of Code 2021 Day 4: Giant Squid"<<endl;

    getAmountOfBingoBoards();
    importWinningChoosenNumbers();
    importGridFromFile();

    int lastMarkedNumber;
    for (int i = 0; i < chosenNumbersInput.size(); i++)
    {
        if(isWinningBoardFound==false){
            lastMarkedNumber=chosenNumbersInput[i];
            markingNumber(chosenNumbersInput[i]);
            checkForWinningBoards();
        }
        else if(isWinningBoardFound==true){break;}
    }
    //cout<<endl<<"lastMarkedNumber: "<<lastMarkedNumber;

    cout<<endl<<endl<<"! Winnig Bingo Board is: "<<winnigBoard+1<<endl;
    sumUnmarkedInBoard(winnigBoard);
    score=sumOfAllUnmarkedNumbers*lastMarkedNumber;
    int scorePart2=getTheLastWinningBoard();

    cout<<endl<<" PART 1: Score: "<<score;
    cout<<endl<<"======================="<<endl;
    cout<<" PART 2: Score: "<<scorePart2;

    return 0;
}