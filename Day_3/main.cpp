#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

vector<string> binaryInputVector; //vector przechowujący liczby pobrane z pliku
const int sizeOfTable=12;

struct binaryCuttedStruct
{
    int cuttedTable[sizeOfTable]={0}; //poszczególne bity liczby
    int amountOfZeros=0, amountOfOnes=0;

    void showYourself()
    {
        //cout<<endl;
        for (int i = 0; i < sizeOfTable; i++)
        {
            cout<<cuttedTable[i]<<" ";
        }
        
    }
    void lettersToIntInTable(int i)
    {
        string temporary = binaryInputVector[i]; //utworzenie zmiennej tymczasowej przechowującą całą binarną
        //cout<<endl<<"temporary = binaryInputVector: "<<temporary; //do debaggingu
        for (int k = 0; k < sizeOfTable; k++) 
        {
            char singleBinaryChar = temporary[k];
            // cout<<endl<<"singleBinaryChar: "<<singleBinaryChar;
            int fromConversion;
            fromConversion = (int)singleBinaryChar-48; //bo normalnie jest to liczba w tablicy asci
            cuttedTable[k] = fromConversion;
            if(fromConversion==1){amountOfOnes++;}
            else{amountOfZeros++;}
            //cout<<endl<<"cuttedTable[k]: "<<cuttedTable[k];
        }
    }
};
vector<binaryCuttedStruct> binaryCuttedVector;


void inportFromFile()
{
    ifstream binaryInputFile; //zmienna pliku
    binaryInputFile.open("binaryInput.txt"); //otwarcie pliku
    if(binaryInputFile.is_open()) //nie da się nic z pliku odczytać jeżeli się nie upewnimy że jest otwarty xD
    {
        cout<<endl<<"File was opened"; //do debuggingu
        string temporaryLine; //aby póniej pobrać całą linie z pliku
        int iteration={0}; //która to iteracja
        do
        {
            getline(binaryInputFile, temporaryLine); //pobranie całej linii z bliku z binarnymi STRING
            // cout<<endl<<"temporary: "<<temporaryLine; //debbuging
            binaryInputVector.push_back(temporaryLine); //dodanie do wektora string całej linii z pliku

            binaryCuttedVector.push_back(binaryCuttedStruct()); //dodanie obiektu który będzie miał już dostę do poszczególnych miejs liczby binarnej
            binaryCuttedVector[iteration].lettersToIntInTable(iteration); //odpalenie metody w każdym z obiektów struktury aby zmieniła ze stringa do inta i do tabeli
            
            iteration++; //kolejna iteracja pętli do while
        } 
        while (!binaryInputFile.eof()); //dopóki nie dojdzeimy do końca pliku

        binaryInputFile.close(); //zamknięcie pliku dobra praktyka
        std::cout<<endl<<"File was closed";
    }
}

int countingDominatingBit(int idOfOperation, int bitPosition, vector<binaryCuttedStruct> &binaryObjects)
{
    int amountOfZeros=0, amountOfOnes=0;
    bool isOneDominating;
    // cout<<endl<<"cDB: binaryObjects: "<<binaryObjects.size();
    for (int i = 0; i < binaryObjects.size(); i++)
    {
        if(binaryObjects[i].cuttedTable[bitPosition]==1){amountOfOnes++;}
        else{amountOfZeros++;}
    }
    switch (idOfOperation)
    {
    case 1: //for part 1
        if(amountOfOnes>amountOfZeros){return 1;}
        else if(amountOfOnes<amountOfZeros){return 0;}
        break;
    case 2: //for part 1
        if(amountOfOnes>amountOfZeros){return 0;}
        else if(amountOfOnes<amountOfZeros){return 1;}
        break;
    case 3: //for part 2 oxygen generator bit criteria
        if(amountOfOnes>amountOfZeros){return 1;}
        else if(amountOfOnes<amountOfZeros){return 0;}
        else if(amountOfOnes==amountOfZeros){return 1;}
        break;
    case 4: //for part 2 CO2 scrubber bit criteria
        if(amountOfOnes>amountOfZeros){return 1;}
        else if(amountOfOnes<amountOfZeros){return 0;}
        else if(amountOfOnes==amountOfZeros){return 0;}
        break;
    default:
        break;
    };
    return 96;
}

int toDecimal(int table[sizeOfTable]) //funkcja zamienia z binarnych na dziesiętne
{
    int power=11, decimal=0, temporary=0;
    for (int i = 0; i < sizeOfTable ; i++)
    {
        decimal += table[i]*pow(2,power);
        power--;
    }
    return decimal;
}

int determineRating(vector<binaryCuttedStruct> binaryObjects, int idOfOperation)
{
    int dominatingBit, bitPosition=0, iteration=0;
    // cout<<endl<<"\t idOfOperation: "<<idOfOperation;
    // cout<<endl<<"\t binaryObjects size: "<<binaryObjects.size()<<endl;
    do
    {
        dominatingBit=countingDominatingBit(idOfOperation, bitPosition, binaryObjects);
        cout<<endl<<"bitPosition: "<<bitPosition;
        cout<<endl<<"binaryObjects.size(): "<<binaryObjects.size();
        // cout<<endl<<"dominatingBit: "<<dominatingBit;
        // cout<<endl<<"iteration: "<<iteration<<endl;
        for (int i = 0; i < binaryObjects.size(); i++)
        {
                //cout<<endl<<"binaryObjects.size(): "<<binaryObjects.size();

                // cout<<endl<<"i: "<<i;
                if(idOfOperation==3)
                {
                    if(dominatingBit==1)
                    {
                        if(binaryObjects[i].cuttedTable[bitPosition]==1)
                        {
                            //cout<<endl<<"Number stay: "; binaryObjects[i].showYourself();
                        }
                        else if(binaryObjects[i].cuttedTable[bitPosition]==0)
                        {
                            binaryObjects.erase(binaryObjects.begin()+i);
                            i = 0;
                        }
                    }
                    else if(dominatingBit==0)
                    {
                        if(binaryObjects[i].cuttedTable[bitPosition]==0)
                        {
                            //cout<<endl<<"Number stay: "; binaryObjects[i].showYourself();
                        }
                        else if(binaryObjects[i].cuttedTable[bitPosition]==1)
                        {
                            binaryObjects.erase(binaryObjects.begin()+i);
                            i = 0;
                        }
                    }
                }
                else if(idOfOperation==4)
                {
                    if(dominatingBit==1)
                    {
                        if(binaryObjects[i].cuttedTable[bitPosition]==0)
                        {
                            //cout<<endl<<"Number stay: "; binaryObjects[i].showYourself();
                        }
                        else if(binaryObjects[i].cuttedTable[bitPosition]==1)
                        {
                            binaryObjects.erase(binaryObjects.begin()+i);
                            i = 0;
                        }
                    }
                    else if(dominatingBit==0)
                    {
                        if(binaryObjects[i].cuttedTable[bitPosition]==1)
                        {
                            //cout<<endl<<"Number stay: "; binaryObjects[i].showYourself();
                        }
                        else if(binaryObjects[i].cuttedTable[bitPosition]==0)
                        {
                            binaryObjects.erase(binaryObjects.begin()+i);
                            i = 0;
                        }
                    }
                }
            if(binaryObjects.size() == 2)
            {
                cout<<endl<<"binaryObjects.size() == 2: "<<binaryObjects.size();
                cout<<endl<<"bitPosition: "<<bitPosition;

                if(idOfOperation==3)
                {
                    // cout<<endl<<"if size 2 id;3 obj 0:"; binaryObjects[0].showYourself();
                    // cout<<endl<<"if size 2 id;3 obj 1:"; binaryObjects[1].showYourself();

                    if(binaryObjects[0].cuttedTable[bitPosition+1]==1)
                    {
                        binaryObjects.erase(binaryObjects.begin()+1);
                    }
                    else if(binaryObjects[1].cuttedTable[bitPosition+1]==1)
                    {
                        binaryObjects.erase(binaryObjects.begin());
                    }
                }
                else if(idOfOperation==4)
                {
                    // cout<<endl<<"if size 2 id;4 obj 0:"; binaryObjects[0].showYourself();
                    // cout<<endl<<"if size 2 id;4 obj 1:"; binaryObjects[1].showYourself();
                    if(binaryObjects[0].cuttedTable[bitPosition+1]==0)
                    {
                        binaryObjects.erase(binaryObjects.begin()+1);
                    }
                    else if(binaryObjects[1].cuttedTable[bitPosition+1]==0)
                    {
                        binaryObjects.erase(binaryObjects.begin());
                    }
                }
            }
        }
        bitPosition++;
        iteration++;
    } while (binaryObjects.size() > 2);

    

    int lastStandingTable[sizeOfTable]={0};
    // cout<<endl<<endl<<"binaryObjects.size(): "<<binaryObjects.size();
    // cout<<endl<<"binaryCuttedVector.size(): "<<binaryCuttedVector.size();
    // cout<<endl<<"lastStanding: ";
    // cout<<endl<<endl;
    for(int i=0; i<sizeOfTable; i++)
    {
        // cout<<"lastStandingTable: "<<binaryObjects[0].cuttedTable[i];
        lastStandingTable[i]=binaryObjects[0].cuttedTable[i];
    }
    cout<<endl;
    int afterConvertedToDecimal;
    afterConvertedToDecimal=toDecimal(binaryObjects[0].cuttedTable);
    return afterConvertedToDecimal;
}

int main()
{
    inportFromFile(); //zaimportowanie liczb w systemie binarnym ++

    int gammaRate[sizeOfTable], epsilonRate[sizeOfTable], gammaRateDecimal, epsilonRateDecimal, powerConsumption;
    
    for (int i = 0; i < sizeOfTable; i++)
    {
        gammaRate[i]=countingDominatingBit(1, i, binaryCuttedVector);
        epsilonRate[i]=countingDominatingBit(2, i, binaryCuttedVector);
    }
    
    gammaRateDecimal=toDecimal(gammaRate);
    epsilonRateDecimal=toDecimal(epsilonRate);

    cout<<endl<<"gammaRateDecimal: "<<gammaRateDecimal;
    cout<<endl<<"epsilonRateDecimal: "<<epsilonRateDecimal;
    powerConsumption=gammaRateDecimal*epsilonRateDecimal;
    cout<<endl<<"powerConsumption: "<<powerConsumption;

    //Part Two
    cout<<endl;
    int lifeSupportRating, oxygenGeneratorRatingDecimal, co2ScrubberRatingDecimal;
    
    oxygenGeneratorRatingDecimal=determineRating(binaryCuttedVector, 3); //id==3 determine the oxygen generator rating
    co2ScrubberRatingDecimal=determineRating(binaryCuttedVector, 4); //id==4 determine the co2 scrubber rating
    lifeSupportRating=oxygenGeneratorRatingDecimal*co2ScrubberRatingDecimal;
    cout<<endl<<"oxygenGeneratorRatingDecimal: "<<oxygenGeneratorRatingDecimal;
    cout<<endl<<"co2ScrubberRatingDecimal: "<<co2ScrubberRatingDecimal;
    cout<<endl<<"lifeSupportRating: "<<lifeSupportRating;
    
    cout<<endl<<"Tutto Finito";
    return 0;
}
