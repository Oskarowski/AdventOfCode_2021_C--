// --- Day 12: Passage Pathing ---
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct cave{
    string name;
    bool canBeVisited;

    vector<string> connections;
    
    cave(){
        canBeVisited=true;
    }
};

vector<cave> caves;

void importRoughMap(const string fileName){
    ifstream file;
    file.open(fileName);
    if (file.is_open())
    {
        cout<<endl<<"Filed opened";
        string line;
        while (getline(file, line))
        {
            string word;

        }
        



        file.close();
    }
    

}


int main(){
    const string fileName = "day12Test.txt";
    importRoughMap(fileName);


    return 0;
}