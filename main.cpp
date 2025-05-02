#include <iostream>
#include "Set.hpp"
using namespace std;

int main(){
    Set teste;
    teste.insert(1);
    teste.insert(2);
    teste.insert(3);
    teste.insert(4);
    teste.insert(5);
    teste.insert(6);
    teste.insert(7);

    Set t1;
    t1.insert(8);

    t1.swap(teste);
    
    //t1.empty() ? cout << "True" << endl : cout << "False" << endl;
    //teste.empty() ? cout << "True" << endl : cout << "False" << endl;
    //teste.contains(7) ? cout << "True" << endl : cout << "False" << endl;
    //teste.contains(9) ? cout << "True" << endl : cout << "False" << endl;
    //cout << teste.size() << endl;
    //cout << t1.size() << endl;

    //cout << teste.maximum() << endl;
    //cout << teste.minimum() << endl;
    //cout << teste.sucessor(5);
    teste.show();
    teste.clear();
}