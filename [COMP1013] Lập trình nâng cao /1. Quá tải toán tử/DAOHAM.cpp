#include <iostream>
#include <cmath>
using namespace std;

struct DonThuc {
    int heSo;
    int soMu;

    DonThuc daoHam() {
        DonThuc res;
        res.heSo =  this->heSo * this->soMu;
        res.soMu = this->soMu - 1;
        return res;
    }
    
    friend ostream& operator << (ostream &out, DonThuc donThuc) {
        if (donThuc.heSo != 0) {
            if (donThuc.soMu != 0) {
                if (abs(donThuc.heSo) == 1) out << "x";
                else out << abs(donThuc.heSo) << "x";
                if (donThuc.soMu > 1) out << "^" << donThuc.soMu;
            } else out << abs(donThuc.heSo);
        }

        return out;
    }
};

struct DaThuc {
    int bac;
    DonThuc *giaTri;

    friend istream& operator >> (istream &in, DaThuc &daThuc) {
        in >> daThuc.bac;
        int size = daThuc.bac + 1;
        daThuc.giaTri = new DonThuc[size];

        for (int i = size-1; i >= 0; i--) {
            in >> daThuc.giaTri[i].heSo;
            daThuc.giaTri[i].soMu = i;
        }

        return in;
    }

    friend ostream& operator << (ostream &out, DaThuc daThuc) {
        int size = daThuc.bac;
        bool check = false;

        for (int i = size; i >= 0; i--) {
            int heSo = daThuc.giaTri[i].heSo;

            if (check && heSo > 0) cout << "+";
            if (heSo < 0) cout << "-";
            cout << daThuc.giaTri[i];

            if (heSo != 0) check = true;
        }

        return out;
    }

    DaThuc daoHamCapMot() {
        DaThuc res;
        res.bac = this->bac;
        res.giaTri = new DonThuc[res.bac];
        for (int i = res.bac; i >= 0; i--)  
            res.giaTri[i] = this->giaTri[i+1].daoHam();
        return res;
    }

    DaThuc daoHamCapHai() {
        DaThuc res1, res2;
        res1 = this->daoHamCapMot();
        res2 = res1.daoHamCapMot();
        return res2;
    }
};

int main() {
    DaThuc a; cin >> a;
    cout << a << endl;
    cout << a.daoHamCapMot() << endl;
    cout << a.daoHamCapHai() << endl;
    return 0;
}