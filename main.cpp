#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define MAX_LINII 24;
#define MAX_COLOANE 30;

struct casuta
{
    char val;
    bool buton;
    bool flag;
};

struct nod
{
    casuta *val;
    nod *urm;
};
void generareHarta(int nr_mine, int nr_linii, int nr_coloane, casuta harta[MAX_LINII][MAX_COLOANE])
{
    srand(time(NULL));   //rand() % nr
    nod *lista= new nod;
    nod *ultim = lista;
    for(int i=0;i<nr_linii;i++)
        for(int j=0;j<nr_coloane;j++)
        {
            harta[i][j].val='0';
            harta[i][j].buton=true;
            harta[i][j].flag=true;
            nod *a= new nod;
            a->val=&harta[i][j];
            a->urm = NULL;
            ultim->urm=a;
            ultim=ultim->urm;
        }
    int n = nr_linii * nr_coloane;
    //rand()%n + 1;


}

void incepeJoc(int nr_mine, int nr_linii, int nr_coloane)
{
    casuta harta[MAX_LINII][MAX_COLOANE];
    generareHarta(nr_mine,nr_linii,nr_coloane, harta)

}


void citesteCustom()
{
    int l,c,m;
    cout<<"Introduceti numarul de linii (9-"<<MAX_LINII<<"):\n";
    cin>>l;
    while(l<9 || l>MAX_LINII)
    {
        cout<<"Trebuie sa introduceti o valoare intre 9 si "<<MAX_LINII<<"!\n";
        cin>>l;
    }

    cout<<"Introduceti numarul de coloane (9-"<<MAX_COLOANE<<"):\n";
    cin>>c;
    while(c<9 || c>MAX_COLOANE)
    {
        cout<<"Trebuie sa introduceti o valoare intre 9 si "<<MAX_COLOANE<<"!\n";
        cin>>c;
    }

    cout<<"Introduceti numarul de mine (10-"<<(int)(l*c*0.7)<<"):\n";
    cin>>m;
    while(m<10 || m>l*c*0.7)
    {
        cout<<"Trebuie sa introduceti o valoare intre 10 si "<<(int)(l*c*0.7)<<"!\n";
        cin>>m;
    }
    incepeJoc(m,l,c);
}


void afisareMeniu()
{
    cout<<endl<<"MENIU\n";
    cout<<"(Alege cifra corespunzatoare din meniu)\n";
    cout<<" 1) Incepator (10 mine, 9x9 casute)\n";
    cout<<" 2) Intermediar (40 mine, 16x16 casute)\n";
    cout<<" 3) Avansat (99 mine, 16x30 casute)\n";
    cout<<" 4) Custom\n";
    cout<<" 5) Exit\n";
    cout<<endl;
}

int main()
{
    bool exit = false;
    while(!exit)
    {
        afisareMeniu();
        int c;
        cin>>c;
        switch(c)
        {
        case 1:
            incepeJoc(10,9,9);
            break;
        case 2:
            incepeJoc(40,16,16);
            break;
        case 3:
            incepeJoc(99,16,30);
            break;
        case 4:
            citesteCustom();
            break;
        case 5:
            exit = true;
            break;
        default:
            system("CLS");
            cout<<"Ati introdus o valoare invalida! Selectati un numar din meniu.\n";
        }

    }
    return 0;
}
