/********************************
Author: Karlis Kripens
Created: 02.06.2017
********************************/
/***********************************
A program, which allows to create and add to two binary files,
which creates arranged table from the words. In the first file there are words (not longer than 30 characters),
in the second file there are integers, which represent the numbers of the first file entries.
To arranged table can be (1) added a word, (2) printed out words in the order as they were entered,
(3) printed out words in the alphabetical order.
*************************************/
/*********************************
Input:                                 Output, alphabetical order:         Output, according to the input order:
Labdien                                 3 Karlis                            0 Labdien
Mani                                    0 Labdien                           1 Mani
Sauc                                    1 Mani                              2 Sauc
Karlis                                  2 Sauc                              3 Karlis


Adding a new word in input:          Output, alphabetical order:         Output, according to the input order:
Ada                                     4 Ada                                0 Labdien
                                        0 Labdien                            1 Mani
                                        1 Mani                               2 Sauc
                                        2 Sauc                               3 Karlis
                                        3 Karlis                             4 Ada







**********************************/
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int VALUE_SIZE = 30;

class Ieraksts
{
public:
char name[VALUE_SIZE+1]; // last '\0' symbol


public:
Ieraksts (const char *n = ""); // Ieraksts = Entry

void setName(const char *n);

/** method fillObject() fills Ieraksts (Entry) object field with values.
   Values are entered by the user from the keyboard.**/
void fillObject();
/** method write(fout) writes Ieraksts (Entry) object fields in the file,
   which is linked to the file object fout. **/
void write (ostream &fout);
/** method read(fin) reads Ieraksts (Entry) object fields from the file,
    which is linked to the file object fin, writes the read information in the Ieraksts object **/
bool read (istream &fin);
/** method print() prints Ieraksts (Entry) object fields **/
void print();
};
int main ()
{
ofstream fout1;
ofstream fout2; // file object variables
ifstream fin1, fin2;

Ieraksts s;


fin1.open("stud.bin", ios::in|ios::binary);
vector <string> vertibuMasivs; //creates vector, where words are read in
while (s.read(fin1)){
    vertibuMasivs.push_back(s.name);
}
fin1.close();
fin1.open("h2.bin", ios::in| ios::binary);
vector <int> integerMasivs; // creates vector, where numbers are read in
int temp;
while (fin1.read ((char*)&temp, sizeof(int))){
    integerMasivs.push_back(temp);
}
fin1.close();

fout1.open("stud.bin", ios::out | ios::app | ios::binary);
fout2.open("h2.bin", ios::out | ios::binary);
int garums= vertibuMasivs.size();


s.fillObject(); // gets first Ieraksts (Entry) word from the keyboard

while (!cin.eof()) //writes in from the keyboard
    {
    s.write(fout1);
    vertibuMasivs.push_back(s.name);
    integerMasivs.push_back(garums);
    garums++;
    s.fillObject();
    };
fout1.close ();

sort(vertibuMasivs.begin(),vertibuMasivs.end()); //sorts
fin1.open("stud.bin", ios::in|ios::binary);

if(vertibuMasivs.size() != integerMasivs.size()){
    cout << "nav vienadi masivi!!!!!!!!!!!!!!!";
    return 13;
}


int j;
for (int i=0; i < vertibuMasivs.size(); i++)
{
        j = 0;
          fin1.seekg(0);//puts the pointer to the beginning
        while (s.read(fin1)){   //reads while file has not ended
            if(vertibuMasivs[i] == s.name) //if the read word is the same as the word of array's element, then writes in it's key
            {

                fout2.write ((char*)&integerMasivs[j], sizeof(int));

                break;
            }
            j++;
        }

        fin1.clear();
}
fout2.close();
fin1.close();

fout1.open("stud.bin", ios::out | ios::binary);
for (int i=0; i < vertibuMasivs.size(); i++)
{
    s.setName(vertibuMasivs[i].c_str());//writes the word in the array's element file
   s.write(fout1);
}
fout1.close ();

fin1.open("stud.bin", ios::in | ios::binary );
fin2.open("h2.bin", ios::in | ios::binary );
while (s.read(fin1) && fin2.read ((char*)&temp, sizeof(int))){
    cout << temp << " ";   s.print();
}
fin1.close();
fin2.close();



cout << endl;


sort(integerMasivs.begin(),integerMasivs.end());

fin1.open("stud.bin", ios::in | ios::binary );
fin2.open("h2.bin", ios::in | ios::binary );


for (int i=0; i < integerMasivs.size(); i++)
{
    j = 0;
    while (fin2.read ((char*)&temp, sizeof(int))){      // prints out according to the input order
        if(temp == integerMasivs[i]){
            fin1.seekg(sizeof(Ieraksts)*j);
            if (s.read(fin1)){
                cout << " " << temp << " ";   s.print();
            }
            fin1.clear();
            break;
        }
        j++;
    }
    fin2.seekg(0);
    fin2.clear();

}

fin1.close();
fin2.close();




return 0;
};
Ieraksts::Ieraksts (const char *n)
{
setName(n);
};
void Ieraksts::setName(const char *n){
 strncpy (name, n, VALUE_SIZE);
 name[VALUE_SIZE]='\0';
};


void Ieraksts::fillObject()
{
char np[VALUE_SIZE+1];


    cout << "Enter a word: "<< endl;
    cout << "(CTRL+Z, to finish the work)" << endl;
    cin >> np; setName(np);
    cin.ignore(1); // To be able to finish the input before filling all the fields

}

void Ieraksts::write (ostream &fout)
{
fout.write ((char*)this, sizeof(Ieraksts)); // writing
};

bool Ieraksts::read (istream &fin)
{
fin.read ((char*)this, sizeof(Ieraksts)); // reading
return fin;
};

void Ieraksts::print(){
cout << name;
cout << endl;
};

