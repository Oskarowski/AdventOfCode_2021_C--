#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


struct octopusField{
    int energyLevel;
    bool canFlash = true, flashed = false;

    octopusField(int number){
        this->energyLevel=number;
    }
    void setStatusUsed(){
        if(this->canFlash==false){this->canFlash=true;}
    }
    void setStatusNotUsed(){
        if(this->canFlash==true){this->canFlash=false;}
    }
    void setStatusFlashed(){
        if(this->flashed==false){this->flashed=true;}
    }
    void setStatusNotFlashed(){
        if(this->flashed==false){this->flashed=true;}
    }
    

};

vector<vector<octopusField>> energyLevelMap;
int amountOFFlashes=0;

void printVector(){
    cout<<endl;
    for (int i = 0; i < energyLevelMap.size(); i++)
    {
        cout<<endl;
        for (int j = 0; j < energyLevelMap[i].size(); j++)
        {
            cout<<" "<<energyLevelMap[i][j].energyLevel;
        }
    }
}

void importEnergyLevelMap(string nameOfFile){
    ifstream file;
    file.open(nameOfFile);
    if(file.is_open()){
        int lineAt=0;
        string line;
        while (getline(file, line))
        {   
            energyLevelMap.emplace_back();
            for (auto &&i : line)
            {
                energyLevelMap[lineAt].push_back(i-48);
            }
            lineAt++;
        }
        // cout<<"After import: ";
        // printVector();
    }
}

void resetState(){
    for (int i = 0; i < energyLevelMap.size(); i++)
    {
        for (int j = 0; j < energyLevelMap[i].size(); j++)
        {
            energyLevelMap[i][j].canFlash=true;
        }   
    }
}

bool greaterThan(int &x, int &y){
    if( energyLevelMap[y][x].energyLevel > 9 ){ return true; }
    else return false;
}
bool canFlash(int &x, int &y){
    if( energyLevelMap[y][x].canFlash == true ){ return true; }
    else return false;
}

bool ifEveryoneFlashed(){
    int howManyFlashed=0;
    for (int y = 0; y < energyLevelMap.size(); y++)
    {
        for (int x = 0; x < energyLevelMap[y].size(); x++)
        {
            if(canFlash(x,y)==false){howManyFlashed++;}
        }
    }
    if(howManyFlashed==100){return true;}
    else return false;
}

void doFlash(int x, int y){
    amountOFFlashes++;
    energyLevelMap[y][x].canFlash=false;

    if(y==0 && x==0){
        // cout<<endl<<"Top left corner";
        energyLevelMap[y][x+1].energyLevel++;
        energyLevelMap[y+1][x+1].energyLevel++;
        energyLevelMap[y+1][x].energyLevel++;
    }
    else if(y==0 && x==energyLevelMap[y].size()-1){
        // cout<<endl<<"Top right corner";
        energyLevelMap[y][x-1].energyLevel++;
        energyLevelMap[y+1][x-1].energyLevel++;
        energyLevelMap[y+1][x].energyLevel++;
    }
    else if(y==energyLevelMap.size()-1 && x==0){
        // cout<<endl<<"Down left corner";
        energyLevelMap[y-1][x].energyLevel++;
        energyLevelMap[y-1][x+1].energyLevel++;
        energyLevelMap[y][x+1].energyLevel++;
    }
    else if(y==energyLevelMap.size()-1 && x==energyLevelMap[y].size()-1){
        // cout<<endl<<"Down right corner";
        energyLevelMap[y][x-1].energyLevel++;
        energyLevelMap[y-1][x-1].energyLevel++;
        energyLevelMap[y-1][x].energyLevel++;
    }
    else if( y==0 && x >= 0 && x < energyLevelMap[y].size()-1){
        // cout<<endl<<"Top line";
        energyLevelMap[y][x-1].energyLevel++;
        energyLevelMap[y+1][x-1].energyLevel++;
        energyLevelMap[y+1][x].energyLevel++;
        energyLevelMap[y+1][x+1].energyLevel++;
        energyLevelMap[y][x+1].energyLevel++;
    }
    else if(y==energyLevelMap[y].size()-1 && x>=1 && x<=energyLevelMap[y].size()-2){
        // cout<<endl<<"Bottom line";
        energyLevelMap[y][x-1].energyLevel++;
        energyLevelMap[y-1][x-1].energyLevel++;
        energyLevelMap[y-1][x].energyLevel++;
        energyLevelMap[y-1][x+1].energyLevel++;
        energyLevelMap[y][x+1].energyLevel++;
    }
    else if( x == 0 && y >= 1 && y <= energyLevelMap[y].size()-2){
        // cout<<endl<<"Left line";
        energyLevelMap[y-1][x].energyLevel++;
        energyLevelMap[y-1][x+1].energyLevel++;
        energyLevelMap[y][x+1].energyLevel++;
        energyLevelMap[y+1][x+1].energyLevel++;
        energyLevelMap[y+1][x].energyLevel++;
    }
    else if( x == energyLevelMap[y].size()-1 && y >= 1 && y <= energyLevelMap[y].size()-2){
        // cout<<endl<<"Right line";
        energyLevelMap[y-1][x].energyLevel++;
        energyLevelMap[y-1][x-1].energyLevel++;
        energyLevelMap[y][x-1].energyLevel++;
        energyLevelMap[y+1][x-1].energyLevel++;
        energyLevelMap[y+1][x].energyLevel++;
    }
    else{
        // cout<<endl<<"Middle";
        energyLevelMap[y-1][x].energyLevel++;
        energyLevelMap[y-1][x+1].energyLevel++;
        energyLevelMap[y][x+1].energyLevel++;
        energyLevelMap[y+1][x+1].energyLevel++;
        energyLevelMap[y+1][x].energyLevel++;
        energyLevelMap[y+1][x-1].energyLevel++;
        energyLevelMap[y][x-1].energyLevel++;
        energyLevelMap[y-1][x-1].energyLevel++;
    }
}



void stepTres(){
    for (int i = 0; i < energyLevelMap.size(); i++)
    {
        for (int j = 0; j < energyLevelMap[i].size(); j++)
        {
            if(energyLevelMap[i][j].canFlash==false){energyLevelMap[i][j].energyLevel=0;}
        }   
    }
}

void stepUno(){
    for (int i = 0; i < energyLevelMap.size(); i++)
    {
        for (int j = 0; j < energyLevelMap[i].size(); j++)
        {
            energyLevelMap[i][j].energyLevel++;
        }
    }
}

void stepDos(){
    bool aboveNueve=true;

    while(aboveNueve){
        aboveNueve = false;
        for (int y = 0; y < energyLevelMap.size(); y++)
        {
            for (int x = 0; x < energyLevelMap[y].size(); x++)
            {
                if(greaterThan(x,y) && canFlash(x,y)){
                    aboveNueve = true;
                    doFlash(x,y);
                }
            }
        }
    }
}




int main(){
    importEnergyLevelMap("day11Input.txt");
    
    int howManySteps=100, amountOfIterations=0;
    bool isAllFlashFound=false;
    do
    {
        stepUno();
        stepDos();
        stepTres();
        if(ifEveryoneFlashed()){
                isAllFlashFound=true;
                cout<<endl<<"All Flash! :"<<amountOfIterations;
            }
        resetState();
        amountOfIterations++;
    } while (!isAllFlashFound);
    cout<<endl<<"Total flashes: "<<amountOFFlashes<<" after: "<<amountOfIterations<<" steps";

    return 0;
}







/*
if(y>0 && y<energyLevelMap.size()-1){
            if(x==0){
                if (energyLevelMap[y-1][x].canFlash==true){energyLevelMap[y-1][x].energyLevel++;}
                if (energyLevelMap[y-1][x+1].canFlash==true){energyLevelMap[y-1][x+1].energyLevel++;}
                if (energyLevelMap[y][x+1].canFlash==true){energyLevelMap[y][x+1].energyLevel++;}
                if (energyLevelMap[y+1][x+1].canFlash==true){energyLevelMap[y+1][x+1].energyLevel++;}
                if (energyLevelMap[y+1][x].canFlash==true){energyLevelMap[y+1][x].energyLevel++;}
            }
            if(x==energyLevelMap[y].size()-1){
                if (energyLevelMap[y-1][x].canFlash==true){energyLevelMap[y-1][x].energyLevel++;}
                if (energyLevelMap[y+1][x].canFlash==true){energyLevelMap[y+1][x].energyLevel++;}
                if (energyLevelMap[y+1][x-1].canFlash==true){energyLevelMap[y+1][x-1].energyLevel++;}
                if (energyLevelMap[y][x-1].canFlash==true){energyLevelMap[y][x-1].energyLevel++;}
                if (energyLevelMap[y-1][x-1].canFlash==true){energyLevelMap[y-1][x-1].energyLevel++;}
            }
            if(x>0 && x<energyLevelMap[y].size()-1){
                if (energyLevelMap[y-1][x].canFlash==true){energyLevelMap[y-1][x].energyLevel++;}
                if (energyLevelMap[y-1][x+1].canFlash==true){energyLevelMap[y-1][x+1].energyLevel++;}
                if (energyLevelMap[y][x+1].canFlash==true){energyLevelMap[y][x+1].energyLevel++;}
                if (energyLevelMap[y+1][x+1].canFlash==true){energyLevelMap[y+1][x+1].energyLevel++;}
                if (energyLevelMap[y+1][x].canFlash==true){energyLevelMap[y+1][x].energyLevel++;}
                if (energyLevelMap[y+1][x-1].canFlash==true){energyLevelMap[y+1][x-1].energyLevel++;}
                if (energyLevelMap[y][x-1].canFlash==true){energyLevelMap[y][x-1].energyLevel++;}
                if (energyLevelMap[y-1][x-1].canFlash==true){energyLevelMap[y-1][x-1].energyLevel++;}
            }
        }
        if(y==0){
            if(x==0){
                if (energyLevelMap[y][x+1].canFlash==true){energyLevelMap[y][x+1].energyLevel++;}
                if (energyLevelMap[y+1][x+1].canFlash==true){energyLevelMap[y+1][x+1].energyLevel++;}
                if (energyLevelMap[y+1][x].canFlash==true){energyLevelMap[y+1][x].energyLevel++;}
            }
            if(x==9){
                if (energyLevelMap[y+1][x].canFlash==true){energyLevelMap[y+1][x].energyLevel++;}
                if (energyLevelMap[y+1][x-1].canFlash==true){energyLevelMap[y+1][x-1].energyLevel++;}
                if (energyLevelMap[y][x-1].canFlash==true){energyLevelMap[y][x-1].energyLevel++;}
            }
            if(x>0 && x<energyLevelMap[y].size()-1){
                if (energyLevelMap[y][x+1].canFlash==true){energyLevelMap[y][x+1].energyLevel++;}
                if (energyLevelMap[y+1][x+1].canFlash==true){energyLevelMap[y+1][x+1].energyLevel++;}
                if (energyLevelMap[y+1][x].canFlash==true){energyLevelMap[y+1][x].energyLevel++;}
                if (energyLevelMap[y+1][x-1].canFlash==true){energyLevelMap[y+1][x-1].energyLevel++;}
                if (energyLevelMap[y][x-1].canFlash==true){energyLevelMap[y][x-1].energyLevel++;}
            }
        }
        if(y==energyLevelMap.size()-1){
            if(x==0){
                if (energyLevelMap[y-1][x].canFlash==true){energyLevelMap[y-1][x].energyLevel++;}
                if (energyLevelMap[y-1][x+1].canFlash==true){energyLevelMap[y-1][x+1].energyLevel++;}
                if (energyLevelMap[y][x+1].canFlash==true){energyLevelMap[y][x+1].energyLevel++;}
            }
            if(x==energyLevelMap[y].size()-1){
                if (energyLevelMap[y-1][x].canFlash==true){energyLevelMap[y-1][x].energyLevel++;}
                if (energyLevelMap[y][x-1].canFlash==true){energyLevelMap[y][x-1].energyLevel++;}
                if (energyLevelMap[y-1][x-1].canFlash==true){energyLevelMap[y-1][x-1].energyLevel++;}
            }
            if(x>0 && x<energyLevelMap[y].size()-1){
                if (energyLevelMap[y][x+1].canFlash==true){energyLevelMap[y][x+1].energyLevel++;}
                if (energyLevelMap[y][x-1].canFlash==true){energyLevelMap[y][x-1].energyLevel++;}
                if (energyLevelMap[y-1][x-1].canFlash==true){energyLevelMap[y-1][x-1].energyLevel++;}
                if (energyLevelMap[y-1][x].canFlash==true){energyLevelMap[y-1][x].energyLevel++;}
                if (energyLevelMap[y-1][x+1].canFlash==true){energyLevelMap[y-1][x+1].energyLevel++;}
            }
        }
*/
