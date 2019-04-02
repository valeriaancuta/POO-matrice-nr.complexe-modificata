#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

class complexi
{
    double real, imaginar;

public:
    complexi(double, double);
    complexi(const complexi&);
    ~complexi();
    friend ifstream& operator>>(ifstream&, complexi&);
    friend ostream& operator<<(ostream&,const complexi&);
    friend const complexi operator +(complexi&, complexi&);
    friend const complexi operator +(complexi&,const complexi&);
    friend const complexi operator -(const complexi&,const complexi&);
    friend const complexi operator *(const complexi&, const complexi&);
    friend bool operator==(const complexi&,const complexi&);
    double get_imaginar();
    double get_real();
    void set_imaginar(double);
    void set_real(double);
    bool is_null();
};
//constructor
complexi::complexi(double real=0, double imaginar=0)
{
    this->real=real;
    this->imaginar=imaginar;
}
//constructor copiere
complexi::complexi(const complexi &nr)
{
    real=nr.real;
    imaginar=nr.imaginar;
}
//destructor
complexi::~complexi()
{
    real=0;
    imaginar=0;
}
//adunare nr complexe
const complexi operator+( complexi &nr1, complexi &nr2)
{
    complexi suma;
    suma.real=nr1.real+nr2.real;
    suma.imaginar=nr1.imaginar+nr2.imaginar;
    return suma;
}
//adunare nr complexe
const complexi operator+( complexi &nr1,const  complexi &nr2)
{
    complexi suma;
    suma.real=nr1.real+nr2.real;
    suma.imaginar=nr1.imaginar+nr2.imaginar;
    return suma;
}
//scadere nr complexe
const complexi operator-(const complexi &nr1,const complexi &nr2)
{
    complexi dif;
    dif.real=nr1.real-nr2.real;
    dif.imaginar=nr1.imaginar-nr2.imaginar;
    return dif;
}
//inmultire nr complexe
const complexi operator*(const complexi &nr1, const complexi &nr2)
{
    complexi produs;
    produs.real=nr1.real*nr2.real-nr1.imaginar*nr2.imaginar;
    produs.imaginar=nr1.real*nr2.imaginar+ nr2.real*nr1.imaginar;
    return produs;
}
//comparatie nr complexe
bool operator==(const complexi &nr1, const complexi &nr2)
{
    return (nr1.real==nr2.real)&&(nr1.imaginar==nr2.imaginar);
}
//citire fisier
ifstream& operator>>(ifstream &fin, complexi &nr)
{
    fin>>nr.real>>nr.imaginar;
    return fin;
}
//afisare fisier
ostream& operator<<(ostream &fout, const complexi &nr)
{
    fout<<nr.real<<"."<<nr.imaginar;
    return fout;
}

double complexi::get_imaginar()
{
    return imaginar;
}

double complexi::get_real()
{
    return real;
}

void complexi::set_imaginar(double x)
{
    imaginar=x;
}

void complexi::set_real(double x)
{
    real=x;
}
bool complexi::is_null()
{
    if(get_real()==0 && get_imaginar()==0)
        return true;
    return false;
}
class matrice
{
    friend class complexi;
protected:
    struct nod
    {
        complexi valoare;
        nod* linie;
        nod* coloana;
        int indice;

    };
    nod *first, *p;
    int nr_linii, nr_coloane;
public:
    matrice();
    matrice(int,int);
    void adauga_linie();
    void adauga_coloana(int, complexi, int);
    matrice operator+(matrice &);
    matrice operator*(matrice &);
    matrice(matrice &);
    complexi determinant();
    complexi valoare_intre(int,int);
    bool operator ==(matrice &);

    friend ifstream &operator>>(ifstream&, matrice&);
    friend ostream &operator<<(ostream&, matrice&);

};
//constructor
matrice::matrice()
{
    nr_linii=0;
    nr_coloane=0;
    first=new nod;
    first->linie=NULL;
    first->coloana=NULL;
    p=NULL;
    first->valoare.set_imaginar(0);
    first->valoare.set_real(0);
}

matrice::matrice(int n,int m)
{
    nr_linii=n;
    nr_coloane=m;
    first=new nod;
    first->linie=NULL;
    first->coloana=NULL;
    p=NULL;
    first->valoare.set_imaginar(0);
    first->valoare.set_real(0);
    for(int i=1;i<n;i++)adauga_linie();
    complexi z;
    z.set_real(0);
    z.set_imaginar(0);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)adauga_coloana(i,z,j);
}
//constructor copiere
matrice::matrice(matrice &val)
{
    this->nr_linii=val.nr_linii;
    this->nr_coloane=val.nr_coloane;
    first=new nod;
    first->linie=NULL;
    first->coloana=NULL;
    p=NULL;
    first->valoare.set_imaginar(0);
    first->valoare.set_real(0);

    int i,j;

    for(i=0; i<nr_linii; i++)
    {
        adauga_linie();
    }

    for(i=0; i<nr_linii; i++)
        for(j=0; j<nr_coloane; j++)
        {
            if(val.valoare_intre(i,j).is_null()==false)
                adauga_coloana(i,val.valoare_intre(i,j),j);
        }
}

void matrice::adauga_linie()
{
    nod* q=new nod;
    for(p=first; p->linie; p=p->linie);
    q->linie=NULL;
    q->linie=NULL;
    q->coloana=NULL;
    q->indice=0;
    q->valoare.set_real(0);
    q->valoare.set_imaginar(0);
    p->linie=q;
}

void matrice::adauga_coloana(int nr_linie,complexi val, int nr_coloana)
{
    int i,n;
    p=first;
    for(i=0; i<nr_linie; i++)
        p=p->linie;
    if(p->coloana==NULL && p->valoare.get_real()==0 && p->valoare.get_imaginar()==0)
    {
        p->valoare=val;
        p->indice=nr_coloana;
        return;
    }

    for(; p->coloana; p=p->coloana);
    nod*q = new nod;
    p->coloana=q;
    p=p->coloana;
    q->linie=NULL;
    q->valoare=val;
    q->indice=nr_coloana;
    q->coloana=NULL;
}
//citire din fisier
ifstream &operator>>(ifstream &fin, matrice &val)
{
    complexi nr;
    int i,j;
    if(val.nr_linii || val.nr_coloane)
        while (val.first->linie && val.first->coloana)
        {
            for (val.p=val.first; val.p->linie; val.p=val.p->linie);
            for (val.p=val.first; val.p->coloana; val.p=val.p->coloana)
                delete val.p;
        }
    fin>>val.nr_linii;
    fin>>val.nr_coloane;

    if (val.nr_linii<1&&val.nr_coloane<1)
    {
        val.nr_linii=0;
        val.nr_coloane=0;
        return fin;
    }

    for (i=1; i<val.nr_linii; i++)
        val.adauga_linie();

    for (i=0; i<val.nr_linii; i++)
        for (j=0; j<val.nr_coloane; j++)
        {
            fin>>nr;
            if (nr.is_null()==false)
            val.adauga_coloana(i,nr,j);
        }
    return fin;
}
// operator afisare
ostream &operator << (ostream &fout,matrice &val)
{
    int i,j;
    for(i=0; i<val.nr_linii; i++)
    {
        for (j=0; j<val.nr_coloane; j++)
            fout<<val.valoare_intre(i,j)<<"  ";
        fout<<"\n";
    }
    return fout;
}

complexi matrice::valoare_intre(int x,int y)
{
    int i,j;
    p=first;
    for (i=0; i<x; i++)
        p=p->linie;

    for (j=0; j<y; j++)
    {
        if (p->indice==y)
            return p->valoare;
        else if (p->coloana)
            p=p->coloana;
    }
    if (p->indice==y)
        return p->valoare;
    complexi a;
    a.set_imaginar(0);
    a.set_real(0);
    return a;
}

matrice matrice::operator +(matrice &val)
{
    int i,j;
    matrice a;
    if (nr_coloane!=val.nr_coloane || nr_linii!=val.nr_linii)
        return a;
    a.nr_coloane=nr_coloane;
    a.nr_linii=nr_linii;
    for (i=1; i<nr_linii; i++)
        a.adauga_linie();
    for (i=0; i<nr_linii; i++)
        for (j=0; j<nr_coloane; j++)
        {
            complexi a1,b,c;
            a1=valoare_intre(i,j);
            b=val.valoare_intre(i,j);
            c=a1+b;
            if (c.is_null()==false)
                a.adauga_coloana(i,c,j);
        }
    return a;
}

matrice matrice::operator *(matrice &val)
{
    int i,j,l;
    complexi z;
    matrice a;
    if (nr_coloane!=val.nr_linii)
        return a;

    a.nr_linii=nr_linii;
    a.nr_coloane=val.nr_coloane;

    for (i=1; i<a.nr_linii; i++)
        a.adauga_linie();

    for (i=0; i<a.nr_linii; i++)
        for (j=0; j<a.nr_coloane; j++)
        {
            for (l=0; l<val.nr_linii; l++)
            {
                complexi a1,b,c;
                a1=valoare_intre(i,j);
                b=val.valoare_intre(i,j);
                c=a1*b;
                z=z+c;
            }

            if (z.is_null()==false)
                a.adauga_coloana(i,z,j);
        }

    return a;
}

bool matrice:: operator==(matrice &matr)
{
    int i,j,ok=1;
    if(nr_linii!=matr.nr_linii || nr_coloane!=matr.nr_coloane)
        return false;
    else
    {
        for(i=0;i<nr_linii;i++)
            for(j=0;j<nr_coloane;j++)
        {
            complexi elem1, elem2;
            elem1=valoare_intre(i,j);
            elem2=matr.valoare_intre(i,j);
            if(elem1==elem2) ok=1;
                else ok=0;
        }
        if(ok)return true;
        else return false;
    }
}
complexi matrice::determinant()
{
    if(nr_linii == nr_coloane)
    {
        if(nr_linii==2)
        {
            return (first->valoare*first->linie->coloana->valoare)-(first->linie->valoare*first->coloana->valoare);
        }
        else
        {
            complexi det;
            matrice submatrice(nr_linii,nr_coloane);
            for(int i=0;i<nr_linii;i++)
            {
                int subi=0;
                for(int j=1;j<nr_linii;j++)
                {
                    int subj=0;
                    for(int x=0;x<nr_linii;x++)
                    {
                        if(i!=x)
                        {
                            submatrice.adauga_coloana(subi,valoare_intre(j,x),subj);
                            subj++;
                        }
                    }
                    subi++;
                }
                submatrice.nr_linii--;
                submatrice.nr_coloane--;
                det = det + (pow(-1,i)*valoare_intre(0,i)*submatrice.determinant());
            }
            return det;
        }
    }
    else fout<<"Matricea nu e patratica";
}
int main()
{
    matrice *v;//vector de obiecte de tip matrice de nr complexe
    int n,i=0,care,care1,op,ok=0;//nr de matrice
    fin>>n;
    v=new matrice[n];
    while(ok==0)
    {
        fin>>op;
        switch(op)
        {
            case 1: // Introduce o matrice
                {
                    fin>>v[i++];
                    break;
                }
            case 2: // Vizualizeaza o matrice
                {
                    fin>>care;
                    if(care>i)fout<<"Nu exista matricea";
                    else fout<<v[care-1];
                    break;
                }
            case 3: // Aduna 2 matrice
                {
                    fin>>care>>care1;
                    matrice aux;
                    aux=v[care-1]+v[care1-1];
                    fout<<aux;
                    break;
                }
            case 4: // Inmulteste 2 matrice
                {
                    fin>>care>>care1;
                    matrice aux1;
                    aux1=v[care-1]*v[care1-1];
                    fout<<aux1;
                    break;
                }
            case 5: // determinant
                {
                    fin>>care;
                    fout<<v[care-1].determinant()<<endl;
                    //fout<<aux2;
                }
            case 6://Compara 2 matrice
                {
                    fin>>care>>care1;
                    if(care==care1) fout<<"Matricele au aceleasi elemente";
                    else fout<<"Matricele nu au aceleasi elemente";

                }
            case 7:
                {
                    ok=1;
                    break;
                }
        }
    }
    return 0;
}
