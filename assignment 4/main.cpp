//
//  main.cpp
//  hw4
//
//  Created by eren bezirganci on 9.06.2022.
//

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include "strutils.h"
#include <vector>
#include <chrono>



// SORTING ALGORITHMS

//********************//
// INSERTION SORT
//********************//
template <typename T>
void insertionSort(vector <T> & a) {
    int j;
    for (int p = 1;  p < a.size(); p++) {
        T tmp = a[p];
        for (j = p; j > 0 && tmp < a[j - 1]; j--)
            a[j] = a[j - 1];
        a[j] = tmp;
    }
}

//********************//
// MERGE SORT
//********************//
template <typename T>
void merge(vector<T> & arr, int leftStart, int center, int rightEnd) {
    int leftEnd = center + 1;

    if (arr[center] <= arr[leftEnd])
        return;

    while (leftStart <= center && leftEnd <= rightEnd) {
        if (arr[leftStart] <= arr[leftEnd])
            leftStart++;
        else {
            T value = arr[leftEnd];
            int index = leftEnd;
            while (index != leftStart) {
                arr[index] = arr[index - 1];
                index--;
            }
            arr[leftStart] = value;
            leftStart++; center++; leftEnd++;
        }
    }
}

template <typename T>
void mergeSort(vector<T> & arr, int left, int right) {
    if (left < right) {
        int center = left + (right - left) / 2;
        mergeSort(arr, left, center);
        mergeSort(arr, center + 1, right);
        merge(arr, left, center, right);
    }
}


//********************//
// QUICK SORT
//********************//
template <class Comparable>
void insertionSort( vector<Comparable> & a, int left, int right )
{
     for (int p = left + 1; p <= right; p++)
     {
          Comparable tmp = a[p];
          int j;

         for ( j = p; j > left && tmp < a[j - 1]; j-- ){
             a[j] = a[j - 1];
             
         }
          a[j] = tmp;
    }
}




template <class Comparable>
 void quicksort( vector<Comparable> & a )
 {
       quicksort( a, 0, a.size() - 1 );
 }

template <class Comparable>
    inline void swap2( Comparable & obj1,
                                Comparable & obj2 )
    {
          Comparable tmp = obj1;
          obj1 = obj2;
          obj2 = tmp;
    }


template <class Comparable>
const Comparable & median3( vector<Comparable> & a,
                                   int left, int right )
{
      int center = ( left + right ) / 2;
      if ( a[ center ] < a[ left ] )
        swap( a[ left ], a[ center ] );
      if ( a[ right ] < a[ left ] )
        swap( a[ left ], a[ right ] );
      if ( a[ right ] < a[ center ] )
        swap( a[ center ], a[ right ] );

      // Place pivot at position right - 1
      swap2( a[ center ], a[ right - 1 ] );
      return a[ right - 1 ];
}


template <class Comparable>
void quicksort( vector<Comparable> & a, int left, int right )
{
    if ( left + 10 <= right )
    {
        
        Comparable pivot = median3( a, left, right );
        
        

        int i = left, j = right - 1;
        for ( ; ; )
        {
            while ( a[++i] < pivot ) { }

            while ( pivot < a[--j] ) { }

            if ( i < j ){
                swap2( a[i], a[j] );}
            else{
                break;}
        }
        swap2( a[i], a[right - 1] );   // Restore pivot

        quicksort( a, left, i - 1 );       // Sort small elements
        quicksort( a, i + 1, right );    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
    {  insertionSort( a, left, right );
    }
}


//********************//
// HEAP SORT
//********************//
inline int leftChild( int i ) {
    return 2*i+1;
}

template <typename T>
void percDown( vector<T> & a, int i, int n ) {
        int child;
        T tmp;

        for (tmp=a[i] ; leftChild(i) < n; i = child ) {
            child = leftChild(i);
            if ( child != n-1 && a[ child  ] < a[ child+1 ] )
                child++;
            if ( a[child ] > tmp )
                a[i] = a[ child ];
            else
                break;
        }
        a[ i ] = tmp;
}

template <typename T>
inline void Swap( T & obj1, T & obj2 )
{
    T tmp = obj1;
    obj1 = obj2;
    obj2 = tmp;
}

template <typename T>
void heapsort(vector<T> & a) {
    // buildHeap
    for (int i = a.size()/2; i >=0; i = i - 1)
        percDown(a, i, a.size());

    // sort
    int starter =  a.size() - 1;
    for (int j = starter; j > 0; j = j - 1) {
        Swap(a[0], a[j]);    // swap max to the last pos.
        percDown(a, 0, j); // re-form the heap
    }
}

//********************//
// SEARCH ALGORITHMS
//********************//

//********************//
// BINARY SEARCH
//********************//

template<typename T>
int binarySearch(vector<T> arr,int n,T x)
{
    int start = 0;
    int end = n-1;
    while(start<=end)
    {
        int mid = (start+end)/2;
        if(arr[mid]==x)
            return mid;
        else if(arr[mid]<x)
            start = mid + 1;
        else
            end = mid - 1;
    }
    return -1;
}


//********************//
// SEQUENTIAL SEARCH
//********************//
template <class Comparable>
int searchSeq(vector<Comparable> vec, int n, Comparable x)
{
    int i;
    for (i = 0; i < n; i++)
        if (vec[i] == x)
            return i;
    return -1;
}



 


//********************//
// STRUCT
//********************//

struct Item {
    string name;
    string surname;
    string phone;
    string city;
    
    Item(){
        name="";
        surname="";
        phone= "";
        city="";
        
        
    }

    Item(string n, string s, string p, string c):name(n), surname(s), phone(p), city(c){
        
        
    }
    
    /****************************************/
    // OPERATION OVERLOADS
    /***************************************/
    bool operator<(const Item& rhs) const
    {
        
        
        
        if (rhs.surname=="") {
            return LowerString(this->name) < LowerString(rhs.name);
        }else{
            
            if (this->name == rhs.name) {
                return LowerString(this->surname) < LowerString(rhs.surname);
            }
            return LowerString(this->name) < LowerString(rhs.name);
        }
        
      
    }
    
    bool operator<=(const Item& rhs) const
    {
        if (rhs.surname=="") {
            return LowerString(this->name) <= LowerString(rhs.name);
        }else{
            
            if (this->name == rhs.name) {
                return LowerString(this->surname) <= LowerString(rhs.surname);
            }
            return LowerString(this->name) <= LowerString(rhs.name);
        }
        
       
    }
    
    bool operator>(const Item& rhs) const
    {
        if (rhs.surname == "") {
            return LowerString(this->name) > LowerString(rhs.name);
        }else{
            if (this->name == rhs.name) {
                return LowerString(this->surname) > LowerString(rhs.surname);
            }
            return LowerString(this->name) > LowerString(rhs.name);
        }
      
    }
    
    
    
    
    bool operator>=(const Item& rhs) const
    {
        if (rhs.surname == "") {
            return LowerString(this->name) >= LowerString(rhs.name);
        }else{
            if (this->name == rhs.name) {
                return LowerString(this->surname) >= LowerString(rhs.surname);
            }
            return LowerString(this->name) >= LowerString(rhs.name);
        }

    }
    
    
    bool operator == (const Item& rhs) const
    {
        if (rhs.surname=="") {
            
            if (rhs.name.size() < this->name.size()) {
                
                for (int i=0; i < rhs.name.size(); i++) {
                    
                    
                    if (tolower(rhs.name[i]) != tolower(this->name[i])) {
                        return false;
                    }
                }
                return true;
            }
            
            
      
            
            
            return LowerString(this->name) == LowerString(rhs.name);
        }else{
            if (this->name == rhs.name) {
                return LowerString(this->surname) == LowerString(rhs.surname);
            }
            return LowerString(this->name) == LowerString(rhs.name);
            
            
        }
        
    }
    
    bool operator != (const Item& rhs) const
    {
        if (rhs.surname=="") {
            return LowerString(this->name) != LowerString(rhs.name);
        }else{
            if (this->name == rhs.name) {
                return LowerString(this->surname) != LowerString(rhs.surname);
            }
            
            return LowerString(this->name) != LowerString(rhs.name);
            
        }
  
    }
    

   
};

// Overload for printing
ostream & operator << (ostream & os, Item s)
{
    os << s.name;
    
    return os;
    
}

int findCh(string s, string searched){
    for (int i=0; i< s.size(); i++) {
        if (s[i]==searched[0]) {
            return i;
        }
    }
    return -1;
}

void splitStr(string s, string & first, string & second, int x){
    
    for (int i=0; i<x; i++) {
        first += s[i];
    }
    
    for (int i=x+1; i<s.size(); i++) {
        second += s[i];
    }
}



int main() {
    
    
    string fileName;
    ifstream txtFile;
    string line;
    string word;
    vector<string> eachLine;
    vector<Item> allItems;
    vector<Item> allItems2;
    vector<Item> allItems3;
    vector<Item> allItems4;
    Item item("","","","");
    cout << "Please enter the contact file name: "  <<endl;
    getline(cin, fileName);
    txtFile.open(fileName.c_str());
    if (txtFile.fail()) {
        perror( "Error occured while opening file");
        cout << "Error occured while opening file" << endl;
    }
    
    while (getline(txtFile,line)) {
        
        
        if(line!="\r" && line!=""){
            
            istringstream ss(line);
            while (ss >> word) {
                eachLine.push_back(word);
                
                
            }
            
            item.name=eachLine[0];
            item.surname = eachLine[1];
            item.phone = eachLine[2];
            item.city = eachLine[3];
            allItems.push_back(item);
            allItems2.push_back(item);
            allItems3.push_back(item);
            allItems4.push_back(item);

            eachLine.clear();
            
            
        }
    }
    
    string queryWord;
    string queryName;
    string querySurname;
    cout << "Please enter the word to be queried :" << endl;
    getline(cin, queryWord);
    
    if (findCh(queryWord, " ") != -1) {
        splitStr(queryWord, queryName, querySurname, findCh(queryWord, " "));
    }else{
        queryName = queryWord;
        querySurname="";
    }
   
    
    cout << endl <<"Sorting the vector copies" << endl;
    cout << "======================================"<<endl;
    
   
    int size = allItems.size();
    
    
    int N = 1000;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++)
    {
        quicksort(allItems);
    }
    auto Time1 = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
    int executionTime1 = Time1.count() / N;
    
    
    
    

    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++)
    {
        insertionSort(allItems2);
    }
    auto Time2 = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start2);
    int executionTime2 = Time2.count() / N;
    
    
    
    
    
    auto start3 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++)
    {
        mergeSort(allItems3,0, size-1);
    }
    auto Time3 = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start3);
    int executionTime3 = Time3.count() / N;
    
    
    
    
    auto start4 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++)
    {
        heapsort(allItems4);
    }
    auto Time4 = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start4);
    int executionTime4 = Time4.count() / N;


    cout << "Quick Sort Time: " << executionTime1 << " Nanoseconds " <<endl;
    cout << "Insertion Sort Time: " << executionTime2 << " Nanoseconds " <<endl;
    cout << "Merge Sort Time: " << executionTime3 << " Nanoseconds " <<endl;
    cout << "Heap Sort Time: " << executionTime4 << " Nanoseconds " <<endl <<endl;
    
    cout << "Searching for " << queryWord << endl;
    cout << "======================================"<< endl;
    
    
    Item temp(queryName,querySurname, "","");
   
    
    
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++)
    {
        binarySearch(allItems4, size, temp);
    }
    auto end = std::chrono::high_resolution_clock::now();
    int executionTimeSearch1 = chrono::duration_cast<chrono::nanoseconds>(end - start).count()/N;
    
    
    
    
    
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++)
    {
        searchSeq(allItems4, size, temp);
    }
    end = std::chrono::high_resolution_clock::now();
    int executionTimeSearch2 = chrono::duration_cast<chrono::nanoseconds>(end - start).count()/N;
    
    
    
    
    
    
    
    int index = binarySearch(allItems2, size, temp);
    int indexs = searchSeq(allItems, size, temp);
    
    int lastIndex=indexs;
    if (index != -1) {
        while (allItems[lastIndex] == temp) {
            lastIndex++;
        }
    }

    
    int startt = index;
    int endd = index;
    if (index != -1) {
        
        
        
        
        while (allItems[startt-1] == temp) {
            startt--;
        }
     
        
        
        while (allItems[endd+1] == temp) {
            endd++;
        }
     
        
        
        
        
        
    }else{
        
        cout << queryWord <<" does NOT exist in the dataset" << endl;
        cout << "Binary Search Time: "<< executionTimeSearch1 << " Nanoseconds" << endl<<endl;
        cout << "Search results for Sequential Search:" << endl;
        cout << queryWord <<" does NOT exist in the dataset" << endl <<endl;
        
        cout << "Sequential Search Time: "<< executionTimeSearch2 << " Nanoseconds" << endl<<endl;
    }

    if (index != -1) {
        
        for (int i=startt; i<= endd; i++) {
            cout << UpperString(allItems[i].name) << " " << UpperString(allItems[i].surname) <<  " "  << allItems[i].phone << " "<<allItems[i].city << endl;
        }
        cout << "Binary Search Time: "<< executionTimeSearch1 << " Nanoseconds" << endl<<endl;
    }
    
    
    
    
    
    
    if (indexs != -1) {
        cout << "Search results for Sequential Search:" << endl;

        for (int i=indexs; i<= lastIndex-1; i++) {
            cout << UpperString(allItems[i].name) << " " << UpperString(allItems[i].surname) <<  " "  << allItems[i].phone << " "<<allItems[i].city << endl;
        }
        cout << "Sequential Search Time: "<< executionTimeSearch2 << " Nanoseconds" << endl<<endl;
    
    }
    
    
    cout << "SpeedUp between Search Algorithms"<<endl;
    cout << "======================================" << endl;
    cout << "(Sequential Search/ Binary Search) SpeedUp = " << float(executionTimeSearch2)/float(executionTimeSearch1) <<endl <<endl;
    
    cout << "SpeedUps between Sorting Algorithms" <<endl;
    cout << "======================================" << endl;
    cout <<"(Insertion Sort/ Quick Sort) SpeedUp = " << float(executionTime2)/float(executionTime1)<<endl;
    cout <<"(Merge Sort / Quick Sort) SpeedUp = " << float(executionTime3)/float(executionTime1)<<endl;
    cout <<"(Heap Sort / Quick Sort) SpeedUp = " << float(executionTime4)/float(executionTime1)<<endl;

    
 

    
    return 0;
}
