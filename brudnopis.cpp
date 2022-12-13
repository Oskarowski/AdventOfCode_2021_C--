#include <iostream>
#include <vector>
using namespace std;

int main(){

    vector<vector<char>> displays;
    displays.resize(10, vector<char>(7 , '0'));

    for (int i = 0; i < 10; i++)
    {
        cout<<endl;
        for (int j = 0; j < 7; j++)
        {
            cout<<" "<<displays[i][j];
        }
        
    }
    
    return 0;
}