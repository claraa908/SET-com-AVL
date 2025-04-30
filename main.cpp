#include <iostream>
#include "Set.hpp"
using namespace std;

int main(){
    Set teste;
    teste.add(1);
    teste.add(2);
    teste.add(3);
    teste.add(4);
    teste.add(5);
    teste.add(6);
    teste.add(7);
    
    teste.contains(7) ? cout << "True" << endl : cout << "False" << endl;
    teste.contains(9) ? cout << "True" << endl : cout << "False" << endl;

    teste.show();
}