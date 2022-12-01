#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void inputFromFile(vector<int> &numbersInput)
{
    ifstream numbersFileRead;
    numbersFileRead.open("numbers.txt");
    if (numbersFileRead.is_open())
    {
        int iteration=0;
        int numberFromFile;

        while (numbersFileRead)
        {
        numbersFileRead>>numberFromFile;
        numbersInput.push_back(numberFromFile);
        // cout<<endl<<"Iteration: "<<iteration<<" numberFromFile: "<<numbersInput[iteration];
        iteration++;
        };
        numbersFileRead.close();
    }
}

void totalsOf(vector<int> &totals, vector<int> numbers)
{
    for (int i = 0; i < numbers.size()-3; i++)
    {
        int totalOfAAA=0;
        for (int k = 0; k < 3; k++)
        {
            totalOfAAA += numbers[i+k];
        }
        totals.push_back(totalOfAAA);
    }
}

int compereTwoNumbers(vector<int> &numbers)
{
    int increasesCount=0;
    for (int i = 0; i < numbers.size(); i++)
    {
        if(numbers[i+1]>numbers[i]) increasesCount++;
        // cout<<endl<<"increase";
    }
    return increasesCount;
}

int main() 
{
    vector<int> numbersInput;
    vector<int> totalsOf3Vec;

    inputFromFile(numbersInput);
    totalsOf(totalsOf3Vec, numbersInput);    

    cout<<endl<<"There were: "<<compereTwoNumbers(numbersInput)<<" amount of increases";
    cout<<endl<<"There were: "<<compereTwoNumbers(totalsOf3Vec)<<" amount of increases in noise";

    return 0;
}