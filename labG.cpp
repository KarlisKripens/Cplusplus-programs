/******************************
Creates a programm in C++, which allows to create one direction linked list (using dynamic data structures),
which keeps certain type of values. It allows an option to add new elements (add element at the end of the list), print out the list, delete the list.
a) allows an option to input the elements of the list (create random list),
b) use written function on the list.
c) print out the list after the execution of the function.
d) at the end delete the list.
Function that deletes the lists n-th element and in its place puts that element, which number was held in the n-th element.


Plan of the Test
Input:
17 5 16 3 2 9 || changes 2nd element
Output:
17 2 16 3 9
Input: 0
Output: Mezglu nav iespejams aizvietot, saraksts ir tukðs. // Node cannot be replaced, the list is empty
Author: Kârlis Krîpens
Date: 26.04.2017
******************************/
#include <iostream>
using namespace std;

class Node {
public:
    int num;
    Node *next;
    Node (int n){num=n; next=NULL;};

};
class List {
protected:
    Node *first;
    Node *last;
public:
    Node *current;
    List(){
        first=last=current=NULL;
    };
    bool is_empty(){
        return (first==NULL);
    };
    void start(){
        current=first;
    };
    bool end(){
        return (current==NULL);
    };
    void next(){
        if(!end())current=current->next;
    };
    void add_element(int n){
            Node *p = new Node(n);
            if (first==NULL) first=last=p;
            else last=last->next=p;
            current = p;
    };
    void delete_element()//delete from the beginning
    {
            Node *p = first;
            if (!is_empty())
                {
                    if(current==first) current=first->next;
                    first=first->next;
                    delete p;
                    if(is_empty()) last=NULL;
                }
    };
    void iespraust_n (int n)
        {
            Node *help1;
            Node *help2;
            Node *help3;
            Node *help4;
            Node *help5;
            Node *help6;
            int z = 1; // keeps the element's number of order starting with 1
            int j; //keeps nth's element value, the one which needs to be replaced
            if (n<=1)
            {
                cout << "Mezglu aizvietot nav iespejams" << endl;
                return;
            }
            if (is_empty()) {
                cout << "Mezglu aizvietot nav iespejams, Saraksts ir tukð" << endl;
                return;
            }
            for (start();!end();next())
            {
                if (z==n-1) help1=current; //sets the pointer to n-1 element
                if (z==n)//starts new cycle if the element which needs to be changed is located before nth element
                    {
                        help2=current; //assigns the pointer to the nth element
                        j=current->num;//finds out what value is inside the nth element
                        help3=current->next;//assigns the pointer to n+1 element
                        if (z>j-1)
                            {
                                z=1;
                                for (start();!end();next())
                                    {
                                       if (z==j-1)// goes till the element which is located one before the element which needs to be changed
                                            {
                                                help4=current; //assigns the pointer to the element one before the element which needs to be changed
                                                help5=current->next; // assigns the pointer to the element which needs to be changed
                                                help6=current->next->next; // assigns the pointer to the element one after the element which needs to be changed
                                                break; //goes out of the cycle
                                            }
                                            z++;
                                    }
                            }
                    }
                if (z==j-1)// goes till the element which is located one before the element which needs to be changed
                    {
                       help4=current; //assigns the pointer to the element one before the element which needs to be changed
                       help5=current->next; // assigns the pointer to the element which needs to be changed
                       help6=current->next->next; //  assigns the pointer to the element one after the element which needs to be changed
                       break; //goes out of the cycle
                    }
                z++;
            }
            help1->next=help5;
            help5->next=help3;
            help3->next=help4;
            help4->next=help6;
            delete help2;

        };

};
int main()
{
    List l;
    int k;
    cout << "Ievadiet saraksta elementu, 0, lai beigtu" << endl;
    cin >> k;
    while (k!=0)
        {
            l.add_element(k);
            cout << "Ievadiet saraksta elementu, 0, lai beigtu" << endl;
            cin >> k;
        }
    int s;
    for (l.start();!l.end();l.next())
    {
        cout << l.current->num << endl;
    }
    cout << "Ievadiet elementa numuru, kuru velaties aizstat" << endl;
    cin >> s;
    l.iespraust_n(s);
    cout << "Jauna kartiba" << endl; //new order

    for (l.start();!l.end();l.next())
    {
        cout << l.current->num << endl;
    }
    while (!l.is_empty())
    {
        l.delete_element();
    }
    return 0;
}
