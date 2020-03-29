#ifndef FUNKCJE_H
#define FUNKCJE_H

struct lista{
    Number* first;
    static Number* dodajObjekt ( string, Number* );
    static Number* wyczyscListe( Number* );

    lista()
    {
        first = NULL;
    }
};

void suma(int* tab, unsigned char* tabLong, unsigned char* tabShort, int longer, int shorter );
void roznica(int* tab, unsigned char* tabLong, unsigned char* tabShort, int longer, int shorter );
void iloczyn( int* tab, unsigned char* tabLong, unsigned char* tabShort, int longer, int shorter );
unsigned char* removeZero( int& leng, unsigned char* tab );
bool changeSymbol( bool symbol );
void shell( void );

#endif
