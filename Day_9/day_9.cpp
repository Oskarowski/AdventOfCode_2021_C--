//Advent_of_Code_2021 Day 9: Smoke Basin
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct haightmapNumber
{
    public:
    int number;
    bool ifchecked=false;

    haightmapNumber(int numberFromImport){
        this->number=numberFromImport;
    }
};

struct lowPoint{
    int xPos=0, yPos=0;

    lowPoint(int x, int y){
        this->xPos=x;
        this->yPos=y;
    }
};

vector<vector<haightmapNumber>> heightmap;
vector<int> theLowestPoint;
vector<lowPoint> lowPoints;

void importHeightmap(string &nameOfFile){
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
                    int number=(int)numberFromFile-48;
                    heightmap[positionVertically].push_back(number);  
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

void printHeightmap(){
    for (int i = 0; i < heightmap.size(); i++)
    {
        for (int j = 0; j < heightmap[i].size(); j++)
        {
            cout<<heightmap[i][j].number<<" ";
        }
        cout<<endl;
    }
}

void searchIfTheLowest(){
    cout<<endl;
    for (int i = 0; i < heightmap.size(); i++)
    {
        for (int j = 0; j < heightmap[i].size(); j++)
        {
            int localMin=heightmap[i][j].number;
            if (i==0) //upper border
            {
                //left and right upper corner
                if(j==0 && (localMin<heightmap[i][j+1].number && localMin<heightmap[i+1][j].number)) { 
                    theLowestPoint.push_back(localMin);
                    lowPoints.emplace_back(j,i);
                }
                if(j==heightmap[i].size()-1 && (localMin<heightmap[i][j-1].number && localMin<heightmap[i+1][j].number)) { 
                    theLowestPoint.push_back(localMin); 
                    lowPoints.emplace_back(j,i);
                }
                //anythink in line other then corners
                else
                {
                    if(localMin<heightmap[i][j-1].number && localMin<heightmap[i][j+1].number && localMin<heightmap[i+1][j].number) { 
                        theLowestPoint.push_back(localMin); 
                        lowPoints.emplace_back(j,i);
                    }
                }

            }
            else if (i==heightmap.size()-1) //bottom border
            {
                //left and right bottom corner
                if(j==0 && (localMin<heightmap[i][j+1].number && localMin<heightmap[i-1][j].number)) { 
                    theLowestPoint.push_back(localMin); 
                    lowPoints.emplace_back(j,i);
                }
                if(j==heightmap[i].size()-1 && (localMin<heightmap[i][j-1].number && localMin<heightmap[i-1][j].number)) { 
                    theLowestPoint.push_back(localMin); 
                    lowPoints.emplace_back(j,i);
                }
                //anythink in line other then corners
                else
                {
                    if(localMin<heightmap[i][j-1].number && localMin<heightmap[i][j+1].number && localMin<heightmap[i-1][j].number) { 
                        theLowestPoint.push_back(localMin);
                        lowPoints.emplace_back(j,i);
                    }
                }
            }
            else if (j==0) //left border without corners
            {
                if(localMin<heightmap[i-1][j].number && localMin<heightmap[i][j+1].number && localMin<heightmap[i+1][j].number) { 
                    theLowestPoint.push_back(localMin);
                    lowPoints.emplace_back(j,i);
                }
            }
            else if (j==heightmap[i].size()-1) //right border without corners
            {
                if(localMin<heightmap[i-1][j].number && localMin<heightmap[i][j-1].number && localMin<heightmap[i+1][j].number) { 
                    theLowestPoint.push_back(localMin);
                    lowPoints.emplace_back(j,i);
                }
            }
            else //anythink what is not a border
            {
                if(localMin<heightmap[i-1][j].number && localMin<heightmap[i][j+1].number && localMin<heightmap[i+1][j].number && localMin<heightmap[i][j-1].number) { 
                    theLowestPoint.push_back(localMin);
                    lowPoints.emplace_back(j,i);
                }
            }
        }
    }
}

void printLocalMin(){
    cout<<endl<<" printLocalMin: "<<endl;
    for (auto &&i : theLowestPoint)
    {
        cout<<" "<<i;
    }
}

void calculateTheRiskLevel(int &risk)
{
    // cout<<endl<<" calculateTheRiskLevel: ";
    for (auto &&i : theLowestPoint)
    {
        i++;
        risk+=i;
    }
}

void partOne(){
    cout<<endl<<"Part 1:";
    int riskLevel=0;

    // printHeightmap(heightmap);
    searchIfTheLowest();
    // printLocalMin(theLowestPoint);
    calculateTheRiskLevel(riskLevel);

    cout<<endl<<"The sum of the risk levels of all low points on your heightmap is: "<<riskLevel<<endl;
}


int whichIterationOfF=0, sizeOfBasin=0;
void checkHowBigIsBasin(int x, int y){
    whichIterationOfF++;
    int centralNumber=heightmap[y][x].number;
    if(centralNumber!=9)
    {
        // cout<<endl<<"centralNumber: "<<centralNumber<<" whichIterationOfF: "<<whichIterationOfF<<" sizeOfBasin: "<<sizeOfBasin;
        sizeOfBasin++;
        heightmap[y][x].ifchecked=true;
        if(centralNumber==8 && heightmap[y][x].ifchecked==false){
            // sizeOfBasin++;
            heightmap[y][x].ifchecked=true;
            }
        if(y-1>=0){
            if(heightmap[y-1][x].ifchecked==false && heightmap[y-1][x].number>centralNumber){
                heightmap[y-1][x].ifchecked=true;
                // cout<<" UP:"<<heightmap[y-1][x].number;
                checkHowBigIsBasin(x, y-1);
            }
        }
        if(x+1<heightmap[y].size()){
            if(heightmap[y][x+1].ifchecked==false && heightmap[y][x+1].number>centralNumber){
                heightmap[y][x+1].ifchecked=true;
                // cout<<" RIGHT:"<<heightmap[y][x+1].number;
                checkHowBigIsBasin(x+1, y);
            }
        }
        if(y+1<heightmap.size()){
            if(heightmap[y+1][x].ifchecked==false && heightmap[y+1][x].number>centralNumber){
                heightmap[y+1][x].ifchecked=true;
                // cout<<" DOWN"<<heightmap[y+1][x].number;
                checkHowBigIsBasin(x, y+1);
            }
        }
        if(x-1>=0){
            if(heightmap[y][x-1].ifchecked==false && heightmap[y][x-1].number>centralNumber){
                heightmap[y][x-1].ifchecked=true;
                // cout<<" LEFT"<<heightmap[y][x-1].number;
                checkHowBigIsBasin(x-1, y);
            }
        }
    }
}

void goViaLowestCords(vector<int> &basinsSize){
    for(int i = 0; i<lowPoints.size(); i++)
    {
        int x=lowPoints[i].xPos, y=lowPoints[i].yPos;
        checkHowBigIsBasin(x,y);
        basinsSize.push_back(sizeOfBasin);
        sizeOfBasin=0;
    }    
}

void sortBasins(vector<int> &basinsSize){
    for (int i = 0; i < basinsSize.size(); i++)
    {
        for (int j = 0; j < basinsSize.size(); j++)
        {
            if(basinsSize[j]<basinsSize[j+1]) {
                swap(basinsSize[j],basinsSize[j+1]);
            }
        }
    }
    
}

void printBasinsSize(vector<int> &basinsSize){
    cout<<endl;
    for (auto &&i : basinsSize)
    {
        cout<<" "<<i;
    }
    cout<<endl;
}

void partTwo(){
    cout<<endl<<"Part 2:";
    vector<int> basinsSize;
    
    goViaLowestCords(basinsSize);
    printBasinsSize(basinsSize);
    sortBasins(basinsSize);
    printBasinsSize(basinsSize);
    
    cout<<endl<<"If you multiply together the sizes of the three largest basins you get: "<<basinsSize[0]*basinsSize[1]*basinsSize[2];

}


void letsRolling(){

    cout<<endl<<"Advent_of_Code_2021 Day 9: Smoke Basin";
    string nameOfFile="day_9_input.txt";
    importHeightmap(nameOfFile);

    partOne(); //DONE
    partTwo(); //DONE
}


int main(){
    letsRolling();
    return 0;
}