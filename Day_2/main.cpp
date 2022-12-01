//Advent_of_Code 2021 Day 2: Dive!
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct submarineCommend //obiekt zawierający polecenie i jego wartość
{
    string commend; //komenda
    int units; //wartość polecenia
    int commendId={3};

    void commendToId()
    {
        if(commend=="forward")
        {
            commendId=1;
        }
        else if(commend=="down")
        {
            commendId=0;
        }
        else if(commend=="up")
        {
            commendId=2; 
        }
    }
};

//zmienne globalne
vector<submarineCommend> submarineCommendsVec; //vector zawierający obiekty z polecanimi i ich wartościami
int subHorizontalPosition={0}, subDepth={0}, subAim={0};


void downloadCommendsFromFile()
{
    ifstream commendsFileRead;
    commendsFileRead.open("commendsForSubmarine.txt");
    if(commendsFileRead.is_open())
    {
        // cout<<endl<<"FIle opened";
        string temporaryCommend;
        int temporaryUnit, iteration=0;
        do
        {
            commendsFileRead>>temporaryCommend;
            commendsFileRead>>temporaryUnit;

            submarineCommendsVec.push_back(submarineCommend());
            submarineCommendsVec[iteration].commend=temporaryCommend;
            submarineCommendsVec[iteration].units=temporaryUnit;

            cout<<endl<<"iteration: "<<iteration<<" temporaryCommend: "<<temporaryCommend<<" Id: "<<submarineCommendsVec[iteration].commendId<<"  temporaryUnit: "<<temporaryUnit;
            iteration++;
        } while (!commendsFileRead.eof());
        commendsFileRead.close();
    }
}

void subForward(int &i)
{
    // subHorizontalPosition += submarineCommendsVec[i].units;
    // cout<<endl<<"subHorizontalPosition++";
    subHorizontalPosition += submarineCommendsVec[i].units;
    subDepth += subAim * submarineCommendsVec[i].units;
    cout<<endl<<"subHorizontalPosition++";
}

void subDown(int &i)
{
    // subDepth += submarineCommendsVec[i].units;
    // cout<<endl<<"subDepth++";
    subAim += submarineCommendsVec[i].units;
    cout<<endl<<"subAim++";
}

void subUp(int &i)
{
    // subDepth -= submarineCommendsVec[i].units;
    // cout<<endl<<"subDepth--";
    subAim -= submarineCommendsVec[i].units;
    cout<<endl<<"subAim--";
}


int main()
{
    downloadCommendsFromFile();

    for(int i=0; i<submarineCommendsVec.size(); i++)
    {
        submarineCommendsVec[i].commendToId();

        switch (submarineCommendsVec[i].commendId)
        {
        case 0: //down
            subDown(i);
        break;

        case 1: //forward
            subForward(i);
        break;
        
        case 2: //up
            subUp(i);
        break;

        default:
            cout<<endl<<"Not able to do commend, captain";
            break;
        }
    }
    cout<<endl<<"horizontalPosition * depth = "<< subHorizontalPosition*subDepth;
    
    return 0;
}