//
//  main.cpp
//  homework 3
//
//  Created by eren bezirgancı on 10.05.2022.
//

#include <iostream>
#include "bst.cpp"
#include "hash.cpp"
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include "strutils.h"
#include <vector>
using namespace std;


struct DocumentItem {
    string documentName;
    int count;
    DocumentItem(string s, int i):documentName(s),count(i){
        
    }
};

vector<DocumentItem> tempDi;
struct WordItem {
    string word;
    vector<DocumentItem> vect;
    WordItem(){
        word="";
        
        
    }
    WordItem(string s, vector<DocumentItem> v):word(s), vect(v ){
        
    }
    
    /****************************************/
    // OPERATION OVERLOADS
    /***************************************/
    bool operator<(const WordItem& rhs) const
    {
       return LowerString(this->word) < LowerString(rhs.word);
    }
    
    bool operator>(const WordItem& rhs) const
    {
        return LowerString(this->word) > LowerString(rhs.word);
    }
    
    bool operator == (const WordItem& rhs) const
    {
        return LowerString(this->word) == LowerString(rhs.word);
        
    }
    
    bool operator != (const WordItem& rhs) const
    {
        return LowerString(this->word) != LowerString(rhs.word);
        
    }
    

   
};

// Overload for printing
ostream & operator << (ostream & os, WordItem s)
{
    os << s.word;
    
    return os;
    
}

int vectorFind(vector<WordItem> wi,string w){
    
    for (int i=0; i<wi.size(); i++) {
        if (wi[i].word == w) {
            return i;
        }
    }
    
    return -1;
}

void findAndIncrease(vector<DocumentItem> & di, string name){
    
    for (int i=0; i<di.size(); i++) {
        if (di[i].documentName == name) {
            di[i].count++;
        }
    }
    
    
    
}

    int vectorSearch(vector<string> v,string s){
        int count=0;
        for (int k=0; k< v.size(); k++) {
            if (v[k]==s) {
                count++;
              
            }
        }
        
        return count;
        
    }

int main() {
    string number_file, fileName;
    string line;// for lines in txt files
    vector<string> vectFileName;// vector that keeps the file names that are entered by users
    vector<WordItem> vectWordItem;
 
    
    
    WordItem ITEM_NOT_FOUND("",tempDi);
    BinarySearchTree<WordItem> BST(ITEM_NOT_FOUND); //bst that keeps the  WordItem
    
    
    HashTable<WordItem> HT(ITEM_NOT_FOUND,101);//ht that keeps the  WordItem
    
    string word;

    
    int n_f;
    cout << "Enter the number of input files: ";
    getline(cin,number_file);
     n_f= atoi(number_file);
    int i=0;
    
    
     while (i<n_f) {
         cout << "Enter " << i+1 << ". file name: ";
         getline(cin, fileName);
    
         vectFileName.push_back(fileName);
         
         i++;
    }
    
    for (int n=0; n < vectFileName.size() ; n++) {
        ifstream txtFile;
        vectWordItem.clear();
        txtFile.open(vectFileName[n].c_str());
        if (txtFile.fail()) {
            perror( "Error occured while opening file");
            cout << "Error occured while opening file" << endl;
        }
        
        while (getline(txtFile,line)) {
            
            
            if(line!="\r" && line!=""){
                
                ToLower(line);
                for (int t=0;  t < line.size(); t++) {
                    if (char(line[t])< 'a' || char(line[t]) > 'z' ) {
                        line[t] = ' ';
                    }
                }
                
                istringstream ss(line);
                while (ss >> word) {
                    int index= vectorFind(vectWordItem,word);
                    if (index!=-1) {
                        findAndIncrease(vectWordItem[index].vect, vectFileName[n]);// increase the count of word that is encountered
                    }else{
                        DocumentItem di(vectFileName[n], 1);
                        tempDi.push_back(di);
                        WordItem wi(word,tempDi);
                        tempDi.pop_back();
                        vectWordItem.push_back(wi);
                        
                    }
                    
                }

            }
            
            
        }
        
        // adding word items to the bst and hash
        for (int k = 0; k < vectWordItem.size(); k++) {
            BST.insert(vectWordItem[k]);
            WordItem temp = vectWordItem[k];
            HT.insert(temp);

        }

    }
    cout << endl << "After preprocessing, the unique word count is " << HT.wordCount() << ". Current load ratio is " << (double)HT.loadRatio()<< endl;
    
    
    // SEARCH PART BEGINS
    string qword;
    vector<string> strVect;
    cout << "Enter queried words in one line: ";
    getline(cin, qword);
    
    ToLower(qword);
    for (int t=0;  t < qword.size(); t++) {
        if (char(qword[t])< 'a' || char(qword[t]) > 'z' ) {
            qword[t] = ' ';
        }
    }
    
    istringstream ss(qword);
    while (ss >> word) {
        strVect.push_back(word);
    }
    
    int timeBST=0;
    int timeHT=0;
    vector<int> countVect;
    vector<int> countVect2;
    vector<string> foundedFile;
    vector<string> foundedFile2;
    vector<string> fileN;
    vector<string> fileN2;
    for (int y=0; y < strVect.size(); y++) {
        WordItem tempw;
        tempw.word=strVect[y];
        bool isfoundHT= true;
        bool isfoundBST= true;

        
        
        int c = 100;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < c; i++)
        {
        // QueryDocuments(with BST);
            BST.find(tempw);
        }
        auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
        (std::chrono::high_resolution_clock::now() - start);
       
        
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < c; i++)
        {
        // QueryDocuments (with hashtable);
            HT.find(tempw);
        }
        auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
        (std::chrono::high_resolution_clock::now() - start);
       
        
        WordItem temp4 = BST.find(tempw);
        WordItem temp3 = HT.find(tempw);
        
        if ( temp4.word == "") {
            isfoundBST=false;
        }else{
            
           
            for (int k = 0; k<  temp4.vect.size(); k++) {
          
                if (vectorSearch(fileN, temp4.vect[k].documentName) == 0) {
                    fileN.push_back(temp4.vect[k].documentName);
                }
                foundedFile.push_back(temp4.vect[k].documentName);
                
       
                countVect.push_back(temp4.vect[k].count);

                
            }
        }
        
        
        
        
        if ( temp3.word == "") {
            isfoundHT=false;
        }else{
            for (int k = 0; k<  temp3.vect.size(); k++) {
                if (vectorSearch(fileN2, temp3.vect[k].documentName) == 0) {
                    fileN2.push_back(temp3.vect[k].documentName);
                }

               
                foundedFile2.push_back(temp3.vect[k].documentName);
                
                countVect2.push_back(temp3.vect[k].count);
       
                
            }
        }
        
        

        
     
        timeBST += (BSTTime.count() / c);
        timeHT += (HTTime.count() / c);
        
        
      

      
    }
    
   
    bool isfound=false;
    bool isfound2=false;
    for (int m=0; m< vectFileName.size(); m++) {
        int res = vectorSearch(foundedFile, vectFileName[m]);
        if ( res == strVect.size()) {
            isfound=true;
        }
       
    }
    
    for (int m=0; m< vectFileName.size(); m++) {
        int res = vectorSearch(foundedFile2, vectFileName[m]);
        if ( res == strVect.size()) {
            isfound2=true;
        }
       
    }


    
    if (!isfound) {
        cout << "No document contains the given query"  << endl;
    }else{
        for (int p=0; p<fileN.size(); p++) {
            cout << "in Document " << fileN[p];
            int d=p;
            int r=0;
            while(r<strVect.size()) {
                cout << ", " << strVect[r] << " found " << countVect[d]<< " times";
                d += fileN.size() ;
                r++;
            }
            cout <<"." << endl;
        }
        
    }
    
    
    if (!isfound2) {
        cout << "No document contains the given query"  << endl;
    }else{
        
        for (int p=0; p<fileN2.size(); p++) {
            cout << "in Document " << fileN2[p];
            int d=p;
            int r=0;
            while(r<strVect.size()) {
                cout << ", " << strVect[r] << " found " << countVect2[d]<< " times";
                d += fileN2.size() ;
                r++;
            }
            
            cout <<"." << endl;
        }
        
    }

    cout << "\nTime: " << timeBST << "\n";
    cout << "\nTime: " << timeHT<< "\n";
    cout << "Speed Up: " << float(timeBST)/float(timeHT) << endl;
    
    
    BST;
    HT;
    
    return 0;
}
