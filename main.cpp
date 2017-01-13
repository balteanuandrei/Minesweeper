#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define MAX_LINII 24
#define MAX_COLOANE 30

struct casuta
{
    int val;
    bool buton;
    bool flag;
};

struct nod
{
    int i;
    int j;
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
            harta[i][j].val = 0;
            harta[i][j].buton=true;
            harta[i][j].flag=false;
            nod *a= new nod;
            a->i=i;
            a->j=j;
            a->urm = NULL;
            ultim->urm=a;
            ultim=ultim->urm;
        }
    int n = nr_linii * nr_coloane;
    while(nr_mine>0)
    {
        int index = rand()%n + 1;
        nod *it = lista;
        nod *it_old;
        while(index>0)
        {
            it_old = it;
            it = it->urm;
            index--;
        }
        harta[it->i][it->j].val = 9;
        if(it->i>0 && it->j>0 && harta[it->i-1][it->j-1].val != 9)
            harta[it->i-1][it->j-1].val++;
        if(it->i>0 && harta[it->i-1][it->j].val != 9)
            harta[it->i-1][it->j].val++;
        if(it->i>0 && it->j<nr_coloane-1 && harta[it->i-1][it->j+1].val != 9)
            harta[it->i-1][it->j+1].val++;
        if(it->j<nr_coloane-1 && harta[it->i][it->j+1].val != 9)
            harta[it->i][it->j+1].val++;
        if(it->i<nr_linii-1 && it->j<nr_coloane-1 && harta[it->i+1][it->j+1].val != 9)
            harta[it->i+1][it->j+1].val++;
        if(it->i<nr_linii-1 && harta[it->i+1][it->j].val != 9)
            harta[it->i+1][it->j].val++;
        if(it->i<nr_linii-1 && it->j>0 && harta[it->i+1][it->j-1].val != 9)
            harta[it->i+1][it->j-1].val++;
        if(it->j>0 && harta[it->i][it->j-1].val != 9)
            harta[it->i][it->j-1].val++;

        it_old->urm = it->urm;
        it->urm = NULL;
        delete it;
        n--;
        nr_mine--;
    }

}

void dezvaluieHarta(int nr_linii, int nr_coloane, casuta harta[MAX_LINII][MAX_COLOANE])
{
    for(int i=0;i<nr_linii;i++)
        for(int j=0;j<nr_coloane;j++)
            harta[i][j].buton = false;
}

void afisareHarta(int nr_linii, int nr_coloane, casuta harta[MAX_LINII][MAX_COLOANE])
{
    int k = 0;
	cout<<"      ";
	for (int j = 0; j < nr_coloane; j++)
	{
		if(j+1 > 9)
			cout<<" "<<j + 1<<" ";
		else
			cout<<" "<<j + 1<<"  ";
	}
	cout<<endl;

	for (int i = 0; i < nr_linii*2; i++)
	{
		if (i % 2 == 0)
		{
			cout<<"      ";
			cout<<"___";
			for (int j = 1; j < nr_coloane; j++)
				cout<<"____";
		}
		else
		{
		    cout<<"  ";
			if (k + 1 > 9)
				cout<<k + 1<<" |";
			else cout<<k + 1<< "  |";

			for (int j = 0; j < nr_coloane; j++)
			{
				if(!harta[k][j].buton)
				{
					if (harta[k][j].val == 9) cout<<" Q |";
					else if (harta[k][j].val == 0) cout<<"   |";
					else if (harta[k][j].val == -1) cout<<" + |";
					else cout<<" "<<harta[k][j].val<<" |";
				}
				else if(harta[k][j].flag)
				{
				    cout<<(char)176<<"F"<<(char)176<<"|";
				}
				else
				{
					cout<<(char)178<<(char)178<<(char)178<< "|";
				}
			}
			k++;
		}
		cout<<endl;
	}

	cout<<"      ";
	cout << "___";
	for (int j = 1; j < nr_coloane; j++)
		cout << "____";
	cout<<endl;
	cout<<endl;
}


void eliberareSpatii(int nr_linii, int nr_coloane, casuta harta[MAX_LINII][MAX_COLOANE], nod *coada, nod *ultim, int &clickuri)
{
    int x, y;
    x = coada->i;
    y = coada->j;
    if(coada!=NULL)
    {
        if(coada->i>0 && coada->j>0 && harta[coada->i-1][coada->j-1].buton)
        {
            if(harta[coada->i-1][coada->j-1].val == 0)
            {
                ultim->urm = new nod;
                ultim = ultim->urm;
                ultim->i = coada->i-1;
                ultim->j = coada->j-1;
                ultim->urm = NULL;
            }
            harta[coada->i-1][coada->j-1].buton = false;
            clickuri++;
        }
/*
        if(it->i>0 && harta[it->i-1][it->j].val != 9)
            harta[it->i-1][it->j].val++;
        if(it->i>0 && it->j<nr_coloane-1 && harta[it->i-1][it->j+1].val != 9)
            harta[it->i-1][it->j+1].val++;
        if(it->j<nr_coloane-1 && harta[it->i][it->j+1].val != 9)
            harta[it->i][it->j+1].val++;
        if(it->i<nr_linii-1 && it->j<nr_coloane-1 && harta[it->i+1][it->j+1].val != 9)
            harta[it->i+1][it->j+1].val++;
        if(it->i<nr_linii-1 && harta[it->i+1][it->j].val != 9)
            harta[it->i+1][it->j].val++;
        if(it->i<nr_linii-1 && it->j>0 && harta[it->i+1][it->j-1].val != 9)
            harta[it->i+1][it->j-1].val++;
        if(it->j>0 && harta[it->i][it->j-1].val != 9)
            harta[it->i][it->j-1].val++;
            */
        nod *gunoi = coada;
        coada = coada->urm;
        gunoi->urm = NULL;
        delete gunoi;
        eliberareSpatii(nr_linii,nr_coloane,harta,coada,ultim,clickuri);
    }
}

bool clickButon(int nr_linii, int nr_coloane, casuta harta[MAX_LINII][MAX_COLOANE], int &clickuri)
{
    int x, y;
    char c;
    cout<<endl;
    cout<<"Introduceti nr. liniei si coloanei unde doriti sa calcati sau sa puneti un steag\n";
    cin>>x>>y;
    bool coordGresite = true, flag;
    while(coordGresite)
    {
        x--;
        y--;
        coordGresite = false;
        flag = false;
        if(x<0 || x>nr_linii-1 || y<0 || y>nr_coloane-1)
        {
            cout<<"Ati introdus coordonate gresite, mai incercati!\n";
            cin>>x>>y;
            coordGresite = true;
            continue;
        }
        if(harta[x][y].flag)
        {
            flag = true;
            cout<<"Butonul nu poate fi apasat, deoarece are steag deasupra!\n";
            cout<<"Doriti sa inlaturati steagul de pe aceasta pozitie? (Y/N)\n";
            cin>>c;
            if(c=='y' || c=='Y')
                harta[x][y].flag = false;
            else
            {
                cout<<"Intoduceti alte coordonate atunci! \n";
                cin>>x>>y;
                coordGresite = true;
                continue;
            }
        }
        if(harta[x][y].buton == false)
        {
            cout<<"Butonul a fost deja apasat, incercati alte coordonate!\n";
            cin>>x>>y;
            coordGresite = true;
        }
    }
    if (!flag)
    {
        cout<<"Doriti sa puneti un steag pe aceasta pozitie? (Y/N)\n";
        cin>>c;
        if(c=='y' || c=='Y')
            harta[x][y].flag = true;
        else
        {
            harta[x][y].buton = false;
            clickuri++;
            if(harta[x][y].val == 9)
            {
                harta[x][y].val = -1;
                return true;
            }
            else if(harta[x][y].val == 0)
            {
                nod *coada = new nod;
                nod *ultim = coada;
                coada->i = x;
                coada->j = y;
                coada->urm = NULL;
                eliberareSpatii(nr_linii,nr_coloane,harta,coada,ultim,clickuri);

            }
        }
    }
    return false;
}

void incepeJoc(int nr_mine, int nr_linii, int nr_coloane)
{
    casuta harta[MAX_LINII][MAX_COLOANE];
    generareHarta(nr_mine,nr_linii,nr_coloane, harta);
    system("CLS");


    bool finish = false;
    int nr_casute_apasate = 0;

    while(!finish)
    {
        bool bomb;
        system("CLS");
        afisareHarta(nr_linii,nr_coloane, harta);
        bomb = clickButon(nr_linii, nr_coloane, harta, nr_casute_apasate);
        if(bomb)
        {
            system("CLS");
            dezvaluieHarta(nr_linii,nr_coloane, harta);
            afisareHarta(nr_linii,nr_coloane, harta);
            cout<<"BOOM!! Ai pierdut! \n";
            finish = true;
        }
        else
        {
            if(nr_casute_apasate == nr_linii*nr_coloane - nr_mine)
            {
                system("CLS");
                afisareHarta(nr_linii,nr_coloane, harta);
                cout<<"Ai castigat! \n";
                finish = true;
            }
        }
    }
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
