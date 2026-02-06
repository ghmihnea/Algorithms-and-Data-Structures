
#include <iostream>
using namespace std;

template<typename T>
/*creating a template such that we can use the following function for any 
variable type*/
int array_search(T arr[], int dim, T sf)

{
    for (int i = 0; i < dim; i ++)
        if (arr[i] == sf)
        /*when the searched for value is found we return its index*/
        {
            return i;
        }
    return -1;
}
class Complex {
    private:
    int real, imag;
    public :
    Complex (int r, int i) { real = r; imag = i;}
    /*parametherized constructor*/
    bool operator==(const Complex& other) const{
        return real == other.real && imag == other.imag;
    }
    /*overloading the == operator for complex numbers, allowing us
    to compare 2 complex numbers*/
    friend ostream &operator<<(ostream &out, const Complex &c) {
        out << c.real << " + " << c.imag << "i";
        return out;
    }
    /*overloading the << for complex numbers allowing us to print them on 
    escreen*/

};

int main() {
    int intarr[] = {2, 4, 6, 8};
    int intsf = 2;
    cout << "element found at index " << array_search(intarr, 4, intsf);
    cout << endl;

    double doublearr[] = {1.2, 1.4, 1.6, 1.8};
    double doublesf = 1.4;
    cout << "element found at index " << array_search(doublearr, 4, doublesf);
    cout << endl;

    Complex complexarr[] = {Complex(2,2), Complex(4,4)};
    Complex complexsf(4, 4);
    int complexind = array_search(complexarr, 2, complexsf);

    if(complexind != -1) {
        cout << complexsf << "found at index " << complexind << endl;
    }
    else {
        cout << "not found" << endl;
    }
    
    return 0;

}
