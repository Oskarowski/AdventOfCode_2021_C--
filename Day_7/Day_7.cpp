//Advent_of_Code_2021 Day 7: The Treachery of Whales
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

void inportNumbersFromFile(string &nameOfFile, vector<int> &crabsPosition);
void printCrabsPosition(vector<int> &crabs);
void sortCrabsPosition(vector<int> &crabs);
int calculateTheMostOptimalPosition(vector<int> crabs, int whichPart);
int calculateTotalFuelNeededToMoveToPosition(vector<int> &crabs, int &optimalPosition, int &whichPart);

// day_7_testInput day7_input

void startRolllingPartOne(){
    cout<<endl<<"    PART 1: ";
    //-----------------------------------------------------------------------------------------------
    string nameOfFileWithCrabsPosition="day7_input.txt";
    vector<int> crabsPosition;
    int fuelOptimalPosition, totalAmountOfFuelNeeded=0, whichPart=1;

    inportNumbersFromFile(nameOfFileWithCrabsPosition, crabsPosition);
    fuelOptimalPosition=calculateTheMostOptimalPosition(crabsPosition, whichPart);
    cout<<endl<<"fuelOptimalPosition: "<<fuelOptimalPosition;
    totalAmountOfFuelNeeded=calculateTotalFuelNeededToMoveToPosition(crabsPosition, fuelOptimalPosition, whichPart);
    
    cout<<endl<<"This costs a total of: "<<totalAmountOfFuelNeeded<<" fuel";
    
}

void startRolllingPartTwo(){
    cout<<endl<<"    PART 2: ";
    //-----------------------------------------------------------------------------------------------
    string nameOfFileWithCrabsPosition="day7_input.txt";
    vector<int> crabsPosition;
    int fuelOptimalPosition, whichPart=2;
    long long totalAmountOfFuelNeeded=0;

    inportNumbersFromFile(nameOfFileWithCrabsPosition, crabsPosition);
    fuelOptimalPosition=calculateTheMostOptimalPosition(crabsPosition, whichPart);
    cout<<endl<<"fuelOptimalPosition: "<<fuelOptimalPosition;
    totalAmountOfFuelNeeded=calculateTotalFuelNeededToMoveToPosition(crabsPosition, fuelOptimalPosition, whichPart);

    cout<<endl<<"This costs a total of: "<<totalAmountOfFuelNeeded<<" fuel";

}

void inportNumbersFromFile(string &nameOfFile, vector<int> &crabsPosition){
    ifstream crabsNumbers;
    crabsNumbers.open(nameOfFile);
    if(crabsNumbers.is_open()){
        string fromFile;
        while (getline(crabsNumbers, fromFile, ','))
        {
            int cotrolVar=stoi(fromFile);
            crabsPosition.push_back(cotrolVar);
        }    
        // cout<<endl<<"Imported crabs: ";
        // printCrabsPosition(crabsPosition);
        crabsNumbers.close();    
    }
    else{cout<<endl<<"Not able to open file";}
}

void printCrabsPosition(vector<int> &crabs){
    cout<<endl;
    for (int i = 0; i < crabs.size(); i++)
    {
        cout<<crabs[i]<<",";
    }
    
}

void sortCrabsPosition(vector<int> &crabs){
    for (int i = 0; i < crabs.size(); i++)
    {
        for (int j = 0; j < crabs.size()-i-1; j++)
        {
            if(crabs[j]>crabs[j+1]){
                int controlVar=crabs[j];
                crabs[j]=crabs[j+1];
                crabs[j+1]=controlVar;
            }
        }
    }
    // cout<<endl<<"Sorted crabs:";
    // printCrabsPosition(crabs);
}

int calculateTheMostOptimalPosition(vector<int> crabs, int whichPart){
    switch (whichPart)
    {
        case 1:
        {
            int optimalPosition=(crabs.size()/2);
            sortCrabsPosition(crabs);
            return crabs[optimalPosition];
        }
        case 2:
        {
            float sumOfAllPositions=0;
            for (int i = 0; i < crabs.size(); i++)
            {
                sumOfAllPositions += crabs[i];
            }
            int optimalPosition=floor((sumOfAllPositions/crabs.size()));
            return optimalPosition;
        }
    }
}

int calculateTotalFuelNeededToMoveToPosition(vector<int> &crabs, int &optimalPosition, int &whichPart){
    long long neededFuel=0;
    switch (whichPart)
    {
        case 1:
        {
            for(int i = 0; i < crabs.size(); i++){
                neededFuel += abs(crabs[i]-optimalPosition);
            }
            break;
        }
        case 2:
        {
            for(int i = 0; i < crabs.size(); i++){
                int distanceToPosition=abs(crabs[i]-optimalPosition);
                for (int k = 0; k <= distanceToPosition; k++)
                {
                    neededFuel += k;
                }
            }
            break;
        }
    }
    return neededFuel;

}

void startRollling(){
    cout<<endl<<"Day 7: The Treachery of Whales"<<endl;
    startRolllingPartOne();
    startRolllingPartTwo();
}

int main(){
    startRollling();

    return 0;
}