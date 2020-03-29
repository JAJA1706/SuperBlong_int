#include "Klasa.h"
#include <iostream>
#include <string>
#include <string.h>
#include "funkcje.h"

using namespace std;

void Number::dlugosc ( void ){
    cout<<leng;
}

void Number::wypisz( void ){
    if( sign == 0 ) cout<<"-";
    for( int i=leng-1; i>=0; --i ){
        cout<<(char)(tablicaDynamo[i] + '0');
    }
    cout<<endl;
}

Number::Number(){
    //cout<<"zwykly\n";
    leng = 0;
    sign = 1;
    tablicaDynamo = NULL;
    next = NULL;
}

Number::Number( const Number& numb ){
    //cout<<"kopiujacy\n";
    leng = numb.leng;
    sign = numb.sign;
    tablicaDynamo = new unsigned char[ leng + 1 ];

    for( int i=0; i < leng; ++i){
        tablicaDynamo[i] = numb.tablicaDynamo[i];
    }
}

Number::Number( string napis ){
    if( napis.front() == '-' ){
        sign = 0;
        napis.erase(0,1);
    }
    else{
        sign = 1;
    }
    leng = napis.length() ;
    tablicaDynamo = new unsigned char[ leng + 1 ];

    char zapas[leng + 1];
    strcpy( zapas, napis.c_str() );
    for( int i=0; i<leng; ++i ){
        tablicaDynamo[i] = zapas[leng-(i+1)] - '0';
    }
    tablicaDynamo = removeZero( leng, tablicaDynamo );
}

Number::Number( int* tab, size_t tabsize, bool symbol ){
    sign = symbol;
    leng = tabsize;
    tablicaDynamo = new unsigned char[ leng + 1 ];

    for( int i=0; i<leng; ++i ){
        tablicaDynamo[i] = tab[leng-(i+1)];
    }
    tablicaDynamo = removeZero( leng, tablicaDynamo );
}

Number::Number( long long number ){
    if( number < 0 ) sign = 0;
    else sign = 1;

    string zapas = to_string( number );
    if ( sign == 0 ) zapas.erase(0,1);
    leng = zapas.length();
    char zapas2[leng + 1];
    strcpy( zapas2, zapas.c_str() );


    tablicaDynamo = new unsigned char[ leng + 1 ];
    for( int i=0; i<leng; ++i ){
        tablicaDynamo[i] = zapas[leng-(i+1)] - '0';
    }
    tablicaDynamo = removeZero( leng, tablicaDynamo );
}

Number::~Number(){
    delete [] tablicaDynamo;
}

Number Number::operator+( const Number& numb ) const{
    int longer;
    int shorter;
    bool symbol = sign;
    if( numb.leng > leng )
    {
        longer = numb.leng;
        shorter = leng;
    }
    else
    {
        longer = leng;
        shorter = numb.leng;
    }

    int tab[ longer + 1 ] = {};
    if( (numb.leng >= leng) && (sign == numb.sign) ){
        suma( tab, numb.tablicaDynamo, tablicaDynamo, longer, shorter );
    }
    else if( (numb.leng < leng) && (sign == numb.sign) ) {
        suma( tab, tablicaDynamo, numb.tablicaDynamo, longer, shorter );
    }
    else if( numb.leng > leng ){
        roznica( tab, numb.tablicaDynamo, tablicaDynamo, longer, shorter );
        symbol = numb.sign;
    }

    else if( numb.leng == leng ){
        bool x = true;
        for( int i = (leng-1); x && (i>=0); --i){
            if( numb.tablicaDynamo[i] > tablicaDynamo[i] ){
                roznica( tab, numb.tablicaDynamo, tablicaDynamo, longer, shorter );
                symbol = numb.sign;
                x = false;
            }
            else if( numb.tablicaDynamo[i] < tablicaDynamo[i] ){
                roznica( tab, tablicaDynamo, numb.tablicaDynamo, longer, shorter );
                symbol = sign;
                x = false;
            }
        }
        if( x ){//przypadek gdy ciagi sa rowne
            symbol = 1;
        }
    }

    else{
        roznica( tab, tablicaDynamo, numb.tablicaDynamo, longer, shorter );
        symbol = sign;
    }

    return Number( tab, longer + 1, symbol );
}

Number Number::operator-( const Number& numb ) const{
    int longer;
    int shorter;
    bool symbol;
    if( numb.leng > leng )
    {
        longer = numb.leng;
        shorter = leng;
    }
    else
    {
        longer = leng;
        shorter = numb.leng;
    }

    int tab[ longer + 1 ] = {};
    if( (numb.leng >= leng) && (sign != numb.sign) ){
        suma( tab, numb.tablicaDynamo, tablicaDynamo, longer, shorter );
        symbol = changeSymbol(numb.sign);
    }
    else if( (numb.leng < leng) && (sign != numb.sign) ) {
        suma( tab, tablicaDynamo, numb.tablicaDynamo, longer, shorter );
        symbol = sign;
    }
    else if( numb.leng > leng ){
        roznica( tab, numb.tablicaDynamo, tablicaDynamo, longer, shorter );
        symbol = changeSymbol(numb.sign);
    }

    else if( numb.leng == leng ){
        bool x = true;
        for( int i = (leng-1); x && (i>=0); --i){
            if( numb.tablicaDynamo[i] > tablicaDynamo[i] ){
                roznica( tab, numb.tablicaDynamo, tablicaDynamo, longer, shorter );
                symbol = changeSymbol( numb.sign );
                x = false;
            }
            else if( numb.tablicaDynamo[i] < tablicaDynamo[i] ){
                roznica( tab, tablicaDynamo, numb.tablicaDynamo, longer, shorter );
                symbol = sign;
                x = false;
            }
        }
        if( x ){//przypadek gdy ciagi sa rowne
            symbol = 1;
        }
    }

    else{
        roznica( tab, tablicaDynamo, numb.tablicaDynamo, longer, shorter );
        symbol = sign;
    }

    return Number( tab, longer + 1, symbol );
}

Number Number::operator*( const Number& numb ) const{
    bool symbol;
    if( sign == numb.sign ) symbol = 1;
    else symbol = 0;

    int tab[leng + numb.leng] = {};
    if( numb.leng > leng ){
        iloczyn( tab, numb.tablicaDynamo, tablicaDynamo, numb.leng, leng );
    }
    else{
        iloczyn( tab, tablicaDynamo, numb.tablicaDynamo, leng, numb.leng );
    }

    return Number( tab, leng + numb.leng, symbol );
}

bool Number::operator==( const Number& numb ) const{
    if( (leng != numb.leng) || (sign != numb.sign) ) return false;

    for( int i=0; i < leng; ++i ){
        if( tablicaDynamo[i] != numb.tablicaDynamo[i] ) return false;
    }
    return true;
}

bool Number::operator<( const Number& numb ) const{
    bool x = true;
    if( sign==1 && numb.sign==0 ) return false;
    if( sign==0 && numb.sign==1 ) return true;
    if( sign==0 && numb.sign==0 ) x = false;

    if( leng < numb.leng ) return x;
    else if( leng > numb.leng ) return !x;
    else{
        for( int i = (leng-1); i >= 0; --i ){
            if( tablicaDynamo[i] < numb.tablicaDynamo[i] ) return x;
        }
    }
    return !x;
}

bool Number::operator>( const Number& numb ) const{
    bool x = true;
    if( sign==1 && numb.sign==0 ) return true;
    if( sign==0 && numb.sign==1 ) return false;
    if( sign==0 && numb.sign==0 ) x = false;

    if( leng > numb.leng ) return x;
    else if( leng < numb.leng ) return !x;
    else{
        for( int i = (leng-1); i >= 0; --i ){
            if( tablicaDynamo[i] > numb.tablicaDynamo[i] ) return x;
        }
    }
    return !x;
}

ostream& operator<<( ostream& out, const Number& numb ){
    if( numb.sign == 0 ) out<<"-";
    for( int i=numb.leng-1; i>=0; --i ){
        out<<(char)(numb.tablicaDynamo[i] + '0');
    }
    return out;
}
