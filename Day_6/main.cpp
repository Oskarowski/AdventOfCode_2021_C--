//Advent_of_Code_2021 Day 6: Lanternfish
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

string nameOfFile="inputFile.txt";
map<long long, long long> fishToDays;


void importFish(){
    cout<<endl<<"F importFish()";
    ifstream fishFile;
    fishFile.open(nameOfFile);
    if (fishFile.is_open())
    {
        cout<<endl<<"File: "<<nameOfFile<<" opened";
        string fishChar;
        while (getline(fishFile, fishChar, ','))
        {
            long int fishImported;
            fishImported = stoi(fishChar);
            fishToDays[fishImported]++;
        }
        fishFile.close();
        cout<<endl<<"File: "<<nameOfFile<<" closed";
    }
    else {cout<<endl<<"File not opened";}
}

void showFish(){
    // cout<<endl<<"F showFish"<<endl;
    for (int i = 0; i < 9; i++){
        cout<<"Amount of fish: ["<<fishToDays[i]<<"] in day: ["<<i<<"] of cycle"<<endl;
    }
    cout<<endl;
}

void passingDays(int &days){
    for (int d = 0; d < days; d++)
    {
        // cout<<endl<<"Day: "<<d+1;
        fishToDays[9]=fishToDays[0];
        fishToDays[7]+=fishToDays[0];
        fishToDays[0]=0;
        for(int i = 0; i<10; i++)
        {
            // cout<<endl<<"i: "<<i<<" "<<fishToDays[i]<<" i+1: "<<fishToDays[i+1];
            fishToDays[i]=fishToDays[i+1];
        }
        // showFish();
    }
}

int main()
{

    for (int i = 0; i < 11; i++)
    {
        fishToDays.insert(pair<long long,long long>(i,0));
    }

    importFish();

    int daysPassed=256;
    passingDays(daysPassed);

    long long amountOfFish=0;
    for (int i = 0; i < 9; i++)
    {
        amountOfFish+=fishToDays[i];
    }

    cout<<endl<<endl<<"Amount of fish after: "<<daysPassed<<" days: "<<amountOfFish;

    return 0;
}