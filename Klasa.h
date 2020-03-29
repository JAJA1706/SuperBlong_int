#ifndef KLASA_H
#define KLASA_H
#include <string>

using namespace std;

class Number
{
    private:
    public:
        unsigned char* tablicaDynamo; //wsadzilem zmienne do public zeby moc uzywac listy edit:(luuuuuuuuuuuul)
        int leng;
        bool sign;
        Number* next;

        Number();
        Number( const Number& numb );
        Number( string );
        Number( int*, size_t, bool );
        Number( long long );
        ~Number();
        void dlugosc( void );
        void wypisz( void );

        Number operator+( const Number& numb ) const;
        Number operator-( const Number& numb ) const;
        Number operator*( const Number& numb ) const;
        bool operator==( const Number& numb ) const;
        bool operator>( const Number& numb ) const;
        bool operator<( const Number& numb ) const;

        friend
        ostream& operator<<( ostream& os, const Number& numb );
};


#endif
