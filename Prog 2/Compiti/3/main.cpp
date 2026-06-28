#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class Polinomio {
    private: 
        int poly[6];
    public:
        Polinomio(int coeff5 = 0, int coeff4 = 0, int coeff3 = 0, int coeff2 = 0, int coeff1 = 0, int coeff0 = 0) {
            poly[0] = coeff0;
            poly[1] = coeff1;
            poly[2] = coeff2;
            poly[3] = coeff3;
            poly[4] = coeff4;
            poly[5] = coeff5;
        }
        ~Polinomio() = default;

        void coeff_A_0() {
            for(int i = 0; i <= 5; i++) {
                poly[i] = 0;
            }
        }

        int grado() const {
            for (int i = 5; i >= 0; i--) {
                if(poly[i] != 0) {
                    return i;
                }
            }

            return 0;
        }

        bool operator>(const Polinomio& altro) const{
            return(this->grado() > altro.grado());
        }

        void print() const {
            bool hasPrinted = false;
            for(int i = 5; i > 1; i--){
                if(poly[i] != 0) {
                    hasPrinted = true;
                    if(poly[i] > 0) {
                        cout << "+";
                        if(poly[i] != 1){
                            cout << poly[i]; 
                        }
                        cout << "x^" << i;
                    } else {
                        if(poly[i] != -1){
                            cout << poly[i];
                        } else 
                            cout<< "-";
                        cout <<  "x^" << i;
                    }
                }
            }
            if(poly[1] != 0) {
                hasPrinted = true;
                if(poly[1] > 0) {
                    cout << "+";
                    if(poly[1] != 1){
                        cout << poly[1]; 
                    }
                    cout << "x";
                } else {
                    if(poly[1] != -1){
                            cout << poly[1];
                        } else 
                            cout << "-";
                        cout <<  "x";
                    } 
            }
            if(poly[0] != 0) {
                hasPrinted = true;
                if(poly[0] > 0) {
                    cout << "+" << poly[0];
                } else {
                    cout << poly[0];
                }
            }
            if(!hasPrinted){
                cout << "Polinomio Nullo";
            }
            cout << "\n";
            
        }

        void impostareCoefficiente(int exp, int n) {
            if(exp > 5 || exp < 0) {
                throw invalid_argument("exponent must be in range [0; 5]");
            } 
            poly[exp] = n;
        }

        Polinomio operator+(const Polinomio& altro) const{
            Polinomio sum;

            for(int i = 0; i <= 5; i++) {
                sum.poly[i] = this->poly[i] + altro.poly[i];
            }

            return sum;
        }
        
        Polinomio operator-(const Polinomio& altro) const{
            Polinomio diff;

            for(int i = 0; i <= 5; i++) {
                diff.poly[i] = this->poly[i] - altro.poly[i];
            }

            return diff;
        }


       
};

int maxGrade(Polinomio arr[], int l) {
    int max = 0;

    for(int i = 1; i < l; i++) {
        if(arr[i].grado() > arr[max].grado())
            max = i; 
    }

    return max;
}

int main() {
    Polinomio pol1(-2, 5, 2, 4, 12);
    Polinomio pol2(12, 3, 5, 1);
    Polinomio pol3(0, 7, -12, 0, 1);
    Polinomio pol4(1, 0, 0, 0, 0);
    Polinomio pol5(0, 0, 0, 0, 0);

    Polinomio polSum = pol1 + pol2;
    Polinomio polDiff = pol5 - pol3;

    pol5.print();
    polSum.print();
    polDiff.print();
    
    Polinomio arr[5] = {pol1, pol2, pol3, pol4, pol5};

    cout << "il polinomio di grado massimo è: \n";
    arr[maxGrade(arr, 5)].print();

    return 0;
}