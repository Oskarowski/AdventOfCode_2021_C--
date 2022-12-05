//Advent_of_Code_2021 Day 9: Smoke Basin
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void importHeightmap(vector<vector<int>> &heightmap, string &nameOfFile){
    cout<<endl<<" importHeightmap";
    ifstream mapFile;
    mapFile.open(nameOfFile);
    if (mapFile.is_open())
    {
        cout<<endl<<" File opened"<<endl;
        string line;
        int positionVertically=0;
        while (getline(mapFile, line))
        {
            heightmap.emplace_back();
            int positionHorizontally=0;
            for (auto &&numberFromFile : line)
            {
                try
                {
                    heightmap[positionVertically].push_back((int)numberFromFile-48);  
                    // cout<<" "<<heightmap[positionVertically][positionHorizontally];
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << "\n";
                }
                positionHorizontally++;
            }
            positionVertically++;
        }
        mapFile.close();
        cout<<endl<<" File closed"<<endl;
    }
}

void printHeightmap(vector<vector<int>> &heightmap){
    for (int i = 0; i < heightmap.size(); i++)
    {
        for (int j = 0; j < heightmap[i].size(); j++)
        {
            cout<<heightmap[i][j]<<" ";
        }
        cout<<endl;
    }
}

void searchIfTheLowest(vector<vector<int>> &heightmap, vector<int> &theLowestPoint){
    cout<<endl;
    for (int i = 0; i < heightmap.size(); i++)
    {
        for (int j = 0; j < heightmap[i].size(); j++)
        {
            int localMin=heightmap[i][j];
            if (i==0) //upper border
            {
                //left and right upper corner
                if(j==0 && (localMin<heightmap[i][j+1] && localMin<heightmap[i+1][j])) { theLowestPoint.push_back(localMin); }
                if(j==heightmap[i].size()-1 && (localMin<heightmap[i][j-1] && localMin<heightmap[i+1][j])) { theLowestPoint.push_back(localMin); }
                //anythink in line other then corners
                else
                {
                    if(localMin<heightmap[i][j-1] && localMin<heightmap[i][j+1] && localMin<heightmap[i+1][j]) { theLowestPoint.push_back(localMin); }
                }

            }
            else if (i==heightmap.size()-1) //bottom border
            {
                //left and right bottom corner
                if(j==0 && (localMin<heightmap[i][j+1] && localMin<heightmap[i-1][j])) { theLowestPoint.push_back(localMin); }
                if(j==heightmap[i].size()-1 && (localMin<heightmap[i][j-1] && localMin<heightmap[i-1][j])) { theLowestPoint.push_back(localMin); }
                //anythink in line other then corners
                else
                {
                    if(localMin<heightmap[i][j-1] && localMin<heightmap[i][j+1] && localMin<heightmap[i-1][j]) { theLowestPoint.push_back(localMin); }
                }
            }
            else if (j==0) //left border without corners
            {
                if(localMin<heightmap[i-1][j] && localMin<heightmap[i][j+1] && localMin<heightmap[i+1][j]) { theLowestPoint.push_back(localMin); }
            }
            else if (j==heightmap[i].size()-1) //right border without corners
            {
                if(localMin<heightmap[i-1][j] && localMin<heightmap[i][j-1] && localMin<heightmap[i+1][j]) { theLowestPoint.push_back(localMin); }
            }
            else //anythink what is not a border
            {
                if(localMin<heightmap[i-1][j] && localMin<heightmap[i][j+1] && localMin<heightmap[i+1][j] && localMin<heightmap[i][j-1]) { theLowestPoint.push_back(localMin); }
            }
        }
    }
}

void printLocalMin(vector<int> theLowestPoint){
    cout<<endl<<" printLocalMin: "<<endl;
    for (auto &&i : theLowestPoint)
    {
        cout<<" "<<i;
    }
    
}

void calculateTheRiskLevel(vector<int> lowestPoint, int &risk)
{
    cout<<endl<<" calculateTheRiskLevel: ";
    for (auto &&i : lowestPoint)
    {
        i++;
        risk+=i;
    }
}

void partOne(){
    cout<<endl<<"Part 1:";
    vector<vector<int>> heightmap;
    vector<int> theLowestPoint;
    int riskLevel=0;
    string nameOfFile="day_9_input.txt";

    importHeightmap(heightmap, nameOfFile);
    // printHeightmap(heightmap);
    searchIfTheLowest(heightmap, theLowestPoint);
    // printLocalMin(theLowestPoint);
    calculateTheRiskLevel(theLowestPoint, riskLevel);

    cout<<endl<<"The sum of the risk levels of all low points on your heightmap is: "<<riskLevel<<endl;
}

void letsRolling(){

    cout<<endl<<"Advent_of_Code_2021 Day 9: Smoke Basin";
    partOne(); //working
}


int main(){
    letsRolling();

    return 0;
}