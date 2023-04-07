//
//  hash.cpp
//  homework 3
//
//  Created by eren bezirgancı on 10.05.2022.
//

#include "hash.h"
#include <iostream>


template <class HashedObj>
float HashTable<HashedObj>::loadRatio( )
{
    float s = (float)array.size();
    float lr = float(currentSize)/s;
    return lr;
}

template <class HashedObj>
int HashTable<HashedObj>::wordCount( )
{
    return currentSize;
}

/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
template <class HashedObj>
bool HashTable<HashedObj>::isPrime( int n )
{
    if ( n == 2 || n == 3 )
        return true;

    if ( n == 1 || n % 2 == 0 )
        return false;

    for ( int i = 3; i * i <= n; i += 2 )
         if ( n % i == 0 )
             return false;

    return true;
}


/**
    * Internal method to return a prime number
   * at least as large as n.  Assumes n > 0.
    */
template <class HashedObj>
   int HashTable<HashedObj>::nextPrime( int n )
   {
         if ( n % 2 == 0 )
             n++;

         for ( ; !isPrime( n ); n += 2 )
              ;

         return n;
   }

/**
 * Construct the hash table.
 */
template <class HashedObj>
HashTable<HashedObj>::HashTable( const HashedObj & notFound,
                                      int size )
          : ITEM_NOT_FOUND( notFound ), array( nextPrime( size ) )
{
      
}

/**
 Hash Function
 */

template <class HashedObj>
int HashTable<HashedObj>::hash( const HashedObj & x, int size ) const
{
  
     int sum = 0;
    for (int i = 0; i < x.word.length(); i++) {
         sum = 31*sum + x.word[i];
    }

    sum = sum % size;

    if (sum < 0)
        sum = sum + size;

     return (sum);
}

/**
  * Method that performs quadratic probing resolution.
  * Return the position where the search for x terminates.
  */
 template <class HashedObj>
 int HashTable<HashedObj>::findPos( const HashedObj & x ) const
 {
        int collisionNum = 0;
        int currentPos = hash( x, array.size() );

        while ( array[ currentPos ].info != EMPTY &&
            array[ currentPos ].element != x )
        {
             currentPos += pow(++collisionNum, 2) ;  //add the difference
            if ( currentPos >= array.size( ) )   {           // perform the mod
                currentPos -= array.size(); // if necessary
             }
        }
        return currentPos;
 }

/**
  * Return true if currentPos exists and is active.
  */
 template <class HashedObj>
 bool HashTable<HashedObj>::isActive( int currentPos ) const
 {
       return array[ currentPos ].info == ACTIVE;
 }

/**
 * Make the hash table logically empty.
 */
template <class HashedObj>
void HashTable<HashedObj>::makeEmpty( )
{
    currentSize = 0;
    for( int i = 0; i < array.size( ); i++ )
        array[ i ].info = EMPTY;
}
/**
   * Remove item x from the hash table.
   *  x has to be in the table
   */
  template <class HashedObj>
  void HashTable<HashedObj>::remove( const HashedObj & x )
  {
        int currentPos = findPos( x );
        if ( isActive( currentPos ) )
            array[ currentPos ].info = DELETED;
  }

/**
     * Find item x in the hash table.
     * Return the matching item, or ITEM_NOT_FOUND, if not found.
     */
    template <class HashedObj>
    const HashedObj & HashTable<HashedObj>::find( const HashedObj & x )
                                                                                                         const
    {
         int currentPos = findPos( x );
         if (isActive( currentPos ))
              return array[ currentPos ].element;

         return   ITEM_NOT_FOUND;
    }

/**
   * Insert item x into the hash table. If the item is
   * already present, then do nothing.
   */
  template <class HashedObj>
  void HashTable<HashedObj>::insert( const HashedObj & x )
  {
       // Insert x as active
       int currentPos = findPos( x );
      if ( isActive( currentPos ) ){
          if (array[currentPos].element == x) {
   
            
              array[currentPos].element.vect.push_back(x.vect[0]);
          }

          return;
      }
      
      
     

          array[ currentPos ] = HashEntry( x, ACTIVE );
      


      
       // enlarge the hash table if necessary
      if ( ++currentSize >= (array.size()/1.5) ){
         cout << "rehashed..." << endl;
         cout << "previous table size: " << array.size();
          rehash( );
          cout << ", new table size: " << array.size() <<", current unique word count " << currentSize <<", current load factor: " << float(currentSize)/ array.size()<< endl;
      }
  }

/**
  * Expand the hash table.
  */
 template <class HashedObj>
 void HashTable<HashedObj>::rehash( )
 {
     vector<HashEntry> oldArray = array;

     // Create new double-sized, empty table
     array.resize( nextPrime( 2 * oldArray.size( ) ) );

     for ( int j = 0; j < array.size( ); j++ ){
          array[ j ].info = EMPTY;
     }

     // Copy table over
     currentSize = 0;
     for ( int i = 0; i < oldArray.size( ); i++ ){
         if ( oldArray[ i ].info == ACTIVE ){
              insert( oldArray[ i ].element );
         }
     }

 }


