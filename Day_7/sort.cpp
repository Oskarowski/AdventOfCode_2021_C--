#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> toSort{16,1,2,0,4,2,7,1,2,14};

    for (int i = 0; i < toSort.size()-1; i++)
    {
        for (int k = 0; k < toSort.size(); k++)
        {
            if(toSort[k]>toSort[k+1]){
                int var=toSort[k];
                toSort[k]=toSort[k+1];
                toSort[k+1]=var;
            }
        }
        
    }
    
    cout<<endl<<"Sorted: "<<endl;
    for (int i = 0; i < toSort.size(); i++)
    {
        cout<<toSort[i]<<" ";
    }
    

    return 0;
}