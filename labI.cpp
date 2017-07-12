/***********************
Author: Kârlis Krîpens
Date: 17/06/2017
**********************/
/***********************
Create C++ program, which allows the information about students to be written in binary file using hash function and linear probing.

h(surname, count of the students) = (surname_character_code_sum)mod(count of the students).


Allow to find information about the student using the surname.
************************/
/*************************
Plan of the test:
Input:         Output with hash index: Output with linear probing:
abc              92                     92
aad              92                     93
**************************/
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

const int VALUE_SIZE = 30;

int Hash(const char* key){ // hash function
        int hash = 0;
        int index;



        for (int i = 0; key[i]!='\0'; i++)
            {

                hash+=(int)key[i];
            }
            //cout << hash << endl;
        index = hash % 101; // with mod 101, because I chose that max count of the entries in the file will 101 (prime number)
        return index;
    }
class Uzvards{
public:
    char surname[30];

public:
    Uzvards(const char* n = ""){
        setName(n);
        };


    void fillObject()
    {
        char np[VALUE_SIZE+1];
        cout << "Ievadiet uzvardu: "<< endl;
        cin >> np; setName(np);
        cin.ignore(1); // To be able to quit the input before filling all the fields

    };
    void setName(const char *n)
    {
        strncpy (surname, n, VALUE_SIZE);
        surname[VALUE_SIZE]='\0';
    };
    char* getName (){
    return surname;
    }
    void write (ostream &fout)
    {
        fout.write ((char*)this, sizeof(Uzvards)); // writing all the value of the entry
    };
    bool read (istream &fin)
    {
        fin.read ((char*)this, sizeof(Uzvards)); // reading all the value of the entry
        return fin;
    };
/** method print() prints out all the Uzvards fields **/
    void print()
    {
    cout << surname;
    cout << endl;
    };
};



int main()
{
    fstream fout;
    int index;
    int ok;
    int index2;
    bool trueSearch = true; // if the surname is not found
    char meklejamais[30] = "";
    fout.open("uzv1.bin", ios::in | ios::out | ios::binary);
    if (fout){ cout << "Fails ir izveidots un atveries" << endl;}// creating and opening the file
    else {
            fout.open("uzv1.bin", ios::out | ios::binary);
            if (fout) {
                    fout.close();
                    fout.open("uzv1.bin", ios::in | ios::out | ios::binary);
                    }
        }
    Uzvards m; //object, which is written in
    Uzvards check; // object to check if the place where to write is empty
    Uzvards meklee; // object to compare the surname which is being searched
    for (int i = 0; i<101; i++)
    {
        fout.write(reinterpret_cast<char*>(&m), sizeof(Uzvards)); // writes 101 empty entries in the file
    }



   do
        {
            m.fillObject();
            index = Hash(m.surname);
            fout.seekg(index*sizeof(Uzvards), ios::beg); // puts reading cursor with hash function where it should be written
            fout.read(reinterpret_cast<char*>(&check), sizeof(Uzvards));//reads what is in that place
            while (strlen(check.getName())!=0) {// checks if the place is empty
                index=(index+1) % 101; // increases the index by 1
                int j = 0;
                j++;
                if (j==101) {
                    cout << "Fails ir pilns";// if checked 101 times then file is full and it goes out of the cycle
                    break;
                }
                fout.seekg(index*sizeof(Uzvards), ios::beg);//sets the cursor to the next position
                fout.read(reinterpret_cast<char*>(&check), sizeof(Uzvards));// reads what is located in that place
            }
            fout.seekp(index*sizeof(Uzvards), ios::beg); // sets to the found, empty place
            fout.write(reinterpret_cast<char*>(&m), sizeof(Uzvards)); // writes in the surname
            cout << "Lai turpinatu ievadi, nospieziet 1, lai beigtu 0" << endl;
            cin >> ok;
        } while (ok == 1);
    do
        {

            cout << "Ievadiet meklejamo uzvardu" << endl;
            cin >> meklejamais;
            index2 = Hash(meklejamais);
            fout.seekg(index2*sizeof(Uzvards), ios::beg); // sets to the position where should be the needed surname
            fout.read(reinterpret_cast<char*>(&meklee), sizeof(Uzvards));// reads what is located in that place
            char zoo[30] = "";
            strncpy(zoo, meklee.getName(), 30);
            int j = 0;

            while( strcmp(meklejamais, zoo) != 0 )// checks if the searched surname is equal to the read surname
            {

                index2++;
                index2 = index2 % 101; // increases the index by 1

                j++;
                if (j==100) {
                    trueSearch = false;
                    cout << "Uzvards nav atrasts" << endl; // if it went through 101 times and the surname not found, then goes out of the cycle and surname not found
                    break;
                }
                fout.seekg(index2*sizeof(Uzvards), ios::beg); // sets the reading cursor the found index
                fout.read(reinterpret_cast<char*>(&meklee), sizeof(Uzvards)); // reads what is inside there

                strncpy(zoo, meklee.getName(), 30); // the read surname is converted to so it can be compared



            }
            int mekleIndex = Hash(meklejamais);
            if(trueSearch)cout <<"Jus meklejat uzvardu: "<<meklejamais<<" orginali atrodas: "<< mekleIndex<<" ar linear probing: "<< index2 << endl;
            cout << "Lai turpinatu ievadi, nospieziet 1, lai beigtu 0" << endl;
            cin >> ok;
            cin.clear();
        }   while (ok == 1);

    fout.close();
    return 0;
}
