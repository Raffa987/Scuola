#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include "rettangolo.h"

using namespace std;

int main(){
    srand(time(NULL));
    rettangolo a;
    int i = 1;
    while(!a.isSquare()){
        


        a.set_h(((float)rand()/RAND_MAX) * 2.0f + 98.0f);
        a.set_b(((float)rand()/RAND_MAX) * 2.0f + 98.0f);

        cout << "--- Rettangolo " << i << " ---" << endl;
        cout << "Altezza:   " << a.get_h() << endl;
        cout << "Base:      " << a.get_b() << endl;
        cout << "Quadrato?  " << (a.isSquare() ? "Si" : "No") << endl;
        cout << "Diagonale: " << a.calc_d() << endl;
        cout << "Area:      " << a.calcA() << endl;
        cout << "Perimetro: " << a.calcP() << endl;
        cout << "---------------------\n" << endl;

        i++;
    }    
    return 0;
}