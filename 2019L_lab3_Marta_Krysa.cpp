#include <cstdlib>
#include <iostream>

#include "2019L_lab3_Marta_Krysa.h"

using namespace std;

int main(int argc, char *argv[])
{
    AVLTree<string, int> dictionary, dictionary_copy;
    dictionary.insert("t", 1);
    dictionary.insert("h", 8);
    dictionary.insert("e", 1);
    dictionary.insert("r", 5);
    dictionary.insert("e", 1);
    dictionary.insert("i", 1);
    dictionary.insert("s", 8);
    dictionary.insert("n", 1);
    dictionary.insert("o", 1);
    dictionary.insert("t", 9);
    dictionary.insert("h", 1);
    dictionary.insert("i", 1);
    dictionary.insert("n", 5);
    dictionary.insert("g", 1);
    dictionary.insert("l", 1);
    dictionary.insert("i", 7);
    dictionary.insert("k", 2);
     dictionary.insert("e", 1);
    dictionary.insert("t", 1);
    dictionary.insert("r", 8);
    dictionary.insert("y", 1);
    dictionary.insert("i", 1);
    dictionary.insert("n", 9);
    dictionary.insert("g", 1);
    /***************REMOVAL******************/
    cout<<"\n*******Before removal of a "<<endl;
    dictionary.graph();
    cout<<"*******Removal of a "<<endl;
    dictionary.remove("a");
    dictionary.graph();
    cout<<"\n*******Removal of non-existing d "<<endl;
     dictionary.remove("d");
    dictionary.graph();
    /**************COPY*************************/
    cout<<"\nI am doing a copy of the origial Dictionary and I am checking if they are equal\n";
    dictionary_copy = dictionary;
    if (dictionary == dictionary_copy)
       cout<< "\n*******EQUAL DICTIONARIES\n";
    if (dictionary != dictionary_copy)
    cout<< "\n*******NOT EQUAL DICTIONARIES\n";
    dictionary.graph();
    cout << "\n\n\n\n*******COPY OF THE ORIGINAL:\n";
    dictionary_copy.graph();
    dictionary.clear();
    dictionary.graph();
    cout<<"Dictionary was destroyed, we are inserting \"x,2\" into non-exisitng dictionary\n";
    dictionary.insert("x", 2);
    dictionary.graph();
    cout<<"\nWe are looking for the element \"x\"\n";
    dictionary.search("x");
    cout<<"\nWe are looking for non-existing element \"b\"\n";
    dictionary.search("b");
    cout<<endl;

    return EXIT_SUCCESS;
}
