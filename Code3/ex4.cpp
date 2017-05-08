//
// Created by Josefine on 2017-05-08.
//

#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>

#include "BinarySearchTree.h"

using namespace std;


//Test program: frequency table
int main( )
{
    BinarySearchTree<Row> Tab;
    ifstream file("C:\\Users\\HP\\Documents\\LiU\\TND004\\Code3\\other files\\words.txt");

    if (!file)
    {
        cout << "couldn't open file words.txt" << endl;
        return 1;
    }

    vector<string> V1 = { istream_iterator<string>{file}, istream_iterator<string>{} };
    file.close();

    for(auto j=0; j<V1.size(); j++)
    {
        Row newRow=Row(V1[j]);
        auto tmp = Tab.contains(newRow);
        if(tmp!=Tab.end()){
            tmp->add();
        }

        Tab.insert(newRow);
    }

    for(BinarySearchTree<Row>::BiIterator it = Tab.begin(); it != Tab.end(); ++it)
    {
        cout << *it << endl;
    }

    cout << endl;



    /**************************************/
    cout << "\nPHASE 1: FREQUENCY TABLE\n\n";
    /**************************************/


    cout << "\nFinished testing" << endl;

    return 0;
}