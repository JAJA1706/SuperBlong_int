#include <iostream>
#include <algorithm>
#include "Klasa.h"
#include "funkcje.h"
#include <string.h>

using namespace std;

Number* lista::wyczyscListe( Number* head ){
    Number* zapas;
    while( head->next != NULL ){
        zapas = head;
        head = head->next;
        delete zapas;
    }
    return head;
}

Number* lista::dodajObjekt( string napis, Number* head ){
    Number* nowa = new Number();

    if( napis.front() == '-' ){
        nowa->sign = 0;
        napis.erase(0,1);
    }
    else{
        nowa->sign = 1;
    }
    nowa->leng = napis.length() ;
    nowa->tablicaDynamo = new unsigned char[ nowa->leng + 1 ];

    char zapas[nowa->leng + 1];
    strcpy( zapas, napis.c_str() );
    for( int i=0; i<nowa->leng; ++i ){
        nowa->tablicaDynamo[i] = zapas[nowa->leng-(i+1)] - '0';
    }
    nowa->tablicaDynamo = removeZero( nowa->leng, nowa->tablicaDynamo );
    nowa->next = head;
    return nowa;

}

void suma( int* tab, unsigned char* tabLong, unsigned char* tabShort, int longer, int shorter ){
    for( int i=0; i < longer; ++i ){
        tab[i] = tabLong[i];
    }

    bool przeniesienie = 0;
    for( int i=0; i < shorter; ++i ){
        tab[i] = tab[i] + tabShort[i] + przeniesienie;
        przeniesienie = 0;
        if( tab[i] > 9 ){
            tab[i] -= 10;
            przeniesienie = 1;
        }
    }

    int j = shorter;
    while(( przeniesienie == 1 ) && ( j < longer )){
        ++tab[j];
        przeniesienie = 0;
        if( tab[j] > 9 ){
            tab[j] -= 10;
            przeniesienie = 1;
        }
        ++j;
    }
    if( przeniesienie ){
        ++tab[j];
    }

    reverse(tab, &tab[longer + 1]);//zeby pasowalo do konstruktora
}

void roznica( int* tab, unsigned char* tabLong, unsigned char* tabShort, int longer, int shorter ){
    for( int i=0; i < longer; ++i ){
        tab[i] = tabLong[i];
    }

    int tab2[longer] = {};
    for( int i=0; i < shorter; ++i ){
        tab2[i] = tabShort[i];
    }

    for( int i=0; i < longer; ++i ){
        if( tab[i] < tab2[i] ){
            --tab[i+1];
            tab[i] += 10;
            tab[i] -= tab2[i];
            tab2[i] = 0;
            --i;
        }
        else{
            tab[i] -= tab2[i];
        }
    }

    reverse( tab, &tab[longer + 1] );//zeby pasowalo do konstruktora
}

void iloczyn( int* tab, unsigned char* tabLong, unsigned char* tabShort, int longer, int shorter ){

    for( int j=0; j < shorter; ++j ){
        for( int i=0; i < longer; ++i ){
            tab[i+j] += tabShort[j] * tabLong[i];
        }
    }

    for( int i=0; i < (longer + shorter); ++i ){
        while( tab[i] > 9 ){
            tab[i] -= 10;
            ++tab[i+1];
        }
    }

   /* int*seeker; koncept
    bool x = true;
    for( int i = (longer+shorter-1); i>=0 && x; --i ){
        if( tab[i] != 0 ){
            seeker = &tab[i];
            x = false;
            reverse( tab, seeker+1);
        }
    }*/
    reverse(tab, &tab[shorter+longer]);
}

unsigned char* removeZero( int& leng, unsigned char* tab ){
    while( tab[leng-1] == 0 ){
        --leng;
    }

    if( leng == 0 ){
        ++leng;
        delete [] tab;
        unsigned char* newTab = new unsigned char[ leng + 1 ];
        newTab[0] = 0;
        return newTab;
    }
    else{
        unsigned char* newTab = new unsigned char[ leng + 1 ];
        for( int j=0; j < leng; ++j ){
            newTab[j] = tab[j];
        }
        delete [] tab;
        return newTab;
    }
}

bool changeSymbol( bool symbol ){
    if( symbol == 0) return 1;
    else return 0;
}

void shell( void ){
    bool x = true;
    short int y = 0;
    string napis;
    Number* head = new Number;

    while( x ){
        int switcher;
        cout<<"Co chcesz zrobic?"<<endl<<"1. Dodaj obiekt\n2. Suma 2 obiektow\n3. Roznica 2 obiektow\n4. Iloczyn 2 obiektow\n5. Wyczysc liste\n6. Wyjdz\n";
        cin>>switcher;
        switch ( switcher ){
            case 1:
                if( y < 2 ){
                    cin>>napis;
                    head = lista::dodajObjekt(napis, head);
                    cout<<"dodano obiekt\n";
                    ++y;
                }
                else cout<<"dodales juz 2 liczby\n";

            break;

            case 2:
                if( y < 2 ) cout<<"najpierw podaj 2 liczby\n";
                else{
                    cout<<( *head + *head->next )<<endl;
                }
            break;

            case 3:
                if( y < 2 ) cout<<"najpierw podaj 2 liczby\n";
                else{
                    cout<<( *head->next - *head )<<endl;
                }
            break;

            case 4:
                if( y < 2 ) cout<<"najpierw podaj 2 liczby\n";
                else{
                    cout<<( (*head) * (*head->next) )<<endl;
                }
            break;

            case 5:
               head = lista::wyczyscListe(head);
               y = 0;
            break;

            case 6:
                x = false;
                head = lista::wyczyscListe(head);
                delete head;
            break;

            default:
                cout<<"cos nie tak"<<endl;
            break;
        }
    }
}
