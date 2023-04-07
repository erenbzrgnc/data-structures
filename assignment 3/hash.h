//
//  hash.h
//  homework 3
//
//  Created by eren bezirgancı on 10.05.2022.
//

#ifndef hash_h
#define hash_h
#include <vector>
#include <cmath>
using namespace std;


template <class HashedObj>
       class HashTable
       {
         public:
           explicit HashTable( const HashedObj & notFound, int size = 101 );
           HashTable( const HashTable & rhs )
                  : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
                    array( rhs.array ), currentSize( rhs.currentSize ) { }

           const HashedObj & find( const HashedObj & x ) const;

           void makeEmpty( );
           void insert( const HashedObj & x );
           void remove( const HashedObj & x );

           const HashTable & operator=( const HashTable & rhs );
           int wordCount();
           float loadRatio();

           enum EntryType { ACTIVE, EMPTY, DELETED };
        private:
           struct HashEntry
           {
                HashedObj element;
                EntryType info;

                HashEntry( const HashedObj & e = HashedObj( ),
                           EntryType i = EMPTY )
                         : element( e ), info( i ) { }
           };
                   
           vector<HashEntry> array;
           int currentSize;
           const HashedObj ITEM_NOT_FOUND;

           bool isActive( int currentPos ) const;
           int findPos( const HashedObj & x ) const;
           int hash(const HashedObj& x, int size) const;
           void rehash( );
           bool isPrime(int );
           int nextPrime(int );
        };



#endif /* hash_h */
