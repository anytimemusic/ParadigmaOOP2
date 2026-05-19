#include <iostream>
using namespace std;

class orang {
public:
    int umur;
    orang(int pUmur) :
        umur(pUmur)
    {
        cout << "orang dibuat dengan umur " << umur << endl;
    }
};

class pekerja : virtual public orang {
public:
    pekerja(int pUmur) :
        orang(pUmur)
    {
        cout << "pekerja dibuat dengan umur " << umur << endl;
    }
};

class pelajar : virtual public orang {
public:
    pelajar(int pUmur) :
        orang(pUmur)
    {
        cout << "pelajar dibuat dengan umur " << umur << endl;
    }
};
class budi : public pekerja, public pelajar {
public:

    budi(int pUmur) :
        orang(pUmur),
        pekerja(pUmur),
        pelajar(pUmur) // hal ini dapat dilakukan jika menggunakan virtual
    {
        cout << "budi dibuat dengan umur " << umur << endl;
    }
};
