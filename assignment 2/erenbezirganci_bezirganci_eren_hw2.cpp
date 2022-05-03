//
//  main.cpp
//  notebook
//
//  Created by eren bezirgancı on 8.04.2022.
//

#include <iostream>
#include "bst.cpp"
#include "avl.cpp"
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include "strutils.h"


using namespace std;

// struct for title and its information
struct item_node{
    string title;
    string info;
    item_node(string s1, string s2):title(s1),info(s2){
    }
    
    
    /****************************************/
    // OPERATION OVERLOADS
    /***************************************/
    bool operator<(const item_node& rhs) const
    {
       return LowerString(this->title) < LowerString(rhs.title);
    }
    
    bool operator>(const item_node& rhs) const
    {
        return LowerString(this->title) > LowerString(rhs.title);
    }
    
    bool operator == (const item_node& rhs) const
    {
        return LowerString(this->title) == LowerString(rhs.title);
    }
    
};

// Overload for printing
ostream & operator << (ostream & os, item_node s)
{
    os << s.title;
    
    return os;
    
}

// struct for section and the avl tree that contains title_node(AVL)
struct avl_section_node{
    string section;
    AvlTree<item_node> avlInsideTree;
    avl_section_node(string s, AvlTree<item_node> t ):avlInsideTree(t){
        section = s;
        
    }
    
    /****************************************/
    // OPERATION OVERLOADS
    /***************************************/
    bool operator<(const avl_section_node& rhs) const
    {
       return LowerString(this->section) < LowerString(rhs.section);
    }
    
    bool operator>(const avl_section_node& rhs) const
    {
        return LowerString(this->section) > LowerString(rhs.section);
    }
    
    bool operator == (const avl_section_node& rhs) const
    {
        return LowerString(this->section) == LowerString(rhs.section);
    }
    
      
        
    };


// Overload for printing
ostream & operator << (ostream & os, avl_section_node s)
{
    os << s.section;
    
    return os;
    
}

// struct for section and the binary tree that contains title_node(BST
struct section_node{
    string section;
    BinarySearchTree<item_node> insideTree;
    section_node(string s, BinarySearchTree<item_node> t ):insideTree(t){
        section = s;
      
        
    };
    
    /****************************************/
    // OPERATION OVERLOADS
    /***************************************/
    bool operator<(const section_node& rhs) const
    {
       return LowerString(this->section) < LowerString(rhs.section);
    }
    
    bool operator>(const section_node& rhs) const
    {
        return LowerString(this->section) > LowerString(rhs.section);
    }
    
    bool operator == (const section_node& rhs) const
    {
        return LowerString(this->section) == LowerString(rhs.section);
    }
    
    

    
};


// Overload for printing
ostream & operator << (ostream & os, section_node s)
{
    os << s.section;
    
    return os;
    
}

// function for the break the item line into two separte pieces(title and information)
void arrange(const string line, string & title, string & info){
    long unsigned int found = line.rfind('-');
    long unsigned int lineLength = line.size();
    title = line.substr(1,found-1);
    info = line.substr(found+1,lineLength-found);
    
}

// function for displayin section menu

void displaySectionMenu(){
    
    cout << "MENU" << endl;
    cout << "Please enter an input between [1 - 6]:" << endl;
    cout << "1- Display the sections [AVL]"<< endl;
    cout << "2- Display the sections [BST]" << endl;
    cout << "3- Select a section" << endl;
    cout << "4- Add new section"<< endl;
    cout << "5- Delete a section" << endl;
    cout << "6- Exit" << endl;
}

void displayItemMenu(){
    cout << "Please enter an input between [1 - 7]:" << endl;
    cout << "1- Display the items [AVL]" << endl;
    cout << "2- Display the items [BST]" << endl;
    cout << "3- Display the information of a item" << endl;
    cout << "4- Add new item" << endl;
    cout << "5- Update the information of a item" << endl;
    cout << "6- Delete an item" << endl;
    cout << "7- Return to main menu" << endl;
}

void getSectionTitle(string & s){

    cout << "Enter the title of the section: " ;
    getline(cin,s);
}

int main() {
    cout << "Welcome to the Notebook!" <<endl <<endl;

    
    item_node ITEM_NOT_FOUND("", "");
    BinarySearchTree<item_node> insideTree(ITEM_NOT_FOUND); //bst tree that keeps the item node (title, information)
    section_node ITEM_NOT_FOUND2("", insideTree);
    BinarySearchTree<section_node> outsideTree(ITEM_NOT_FOUND2); // bst tree that keeps section node(section name, title node)
    
    
    AvlTree<item_node> avlInsideTree(ITEM_NOT_FOUND); // avl tree that keeps the item node (title, information)
    avl_section_node ITEM_NOT_FOUND3("", avlInsideTree);
    AvlTree<avl_section_node> avlOutsideTree(ITEM_NOT_FOUND3); // avl tree that keeps section node(section name, title node)
    
    
    ifstream txtFile;
    string line, sectionName, itemTitle, itemInfo;
    bool inItem=false, inSection = false;
    
    string fileName = "data.txt";
    txtFile.open(fileName.c_str());
    section_node node_section("", insideTree);
    avl_section_node avl_node_section("", avlInsideTree);
    while (getline(txtFile,line)) {
        if(line!="\r" && line!=""){
            istringstream ss(line);
            if (line[0] != '-') {
                ss >> sectionName;
                if (inItem) {
                    // push the node_section into outside tree
                    
                    auto start = chrono::high_resolution_clock::now();
                    outsideTree.insert(node_section);
                    auto end = chrono::high_resolution_clock::now();
                    long long bstTimer = (end-start).count() / 1000.0;
                    
                    auto avlStart = chrono::high_resolution_clock::now();
                    avlOutsideTree.insert(avl_node_section);
                    auto avlEnd = chrono::high_resolution_clock::now();
                    long long avlTimer = (avlEnd-avlStart).count() / 1000.0;
                    
                    
                    cout << "Section "<< node_section.section << " has been inserted into the AVL notebook." << endl;
                    cout << "[AVL] Elapsed time: " << avlTimer <<  " microseconds" << endl;
                    
                    
                    cout << "Section "<< avl_node_section.section << " has been inserted into the BST notebook." << endl;
                    cout << "[BST] Elapsed time: " << bstTimer <<  " microseconds" << endl <<endl;
  
                }
                if (inSection) {
                    // push the node_section into outside tree
                    auto start = chrono::high_resolution_clock::now();
                    outsideTree.insert(node_section);
                    auto end = chrono::high_resolution_clock::now();
                    long long bstTimer = (end-start).count() / 1000.0;
                    
                    auto avlStart = chrono::high_resolution_clock::now();
                    avlOutsideTree.insert(avl_node_section);
                    auto avlEnd = chrono::high_resolution_clock::now();
                    long long avlTimer = (avlEnd-avlStart).count() / 1000.0;
                    
                    
                    cout << "Section "<< node_section.section << " has been inserted into the AVL notebook." << endl;
                    cout << "[AVL] Elapsed time: " << avlTimer <<  " microseconds" << endl;
                    
                    cout << "Section "<< avl_node_section.section << " has been inserted into the BST notebook." << endl;
                    cout << "[BST] Elapsed time: " << bstTimer <<  " microseconds" << endl << endl;

                }
                insideTree.makeEmpty();
                avlInsideTree.makeEmpty();
                
                node_section.section = sectionName;
                node_section.insideTree = insideTree;
                
                avl_node_section.section = sectionName;
                avl_node_section.avlInsideTree = avlInsideTree;
                
                inItem=false;
                inSection = true;
            }else{
                inItem = true;
                inSection = false;
                
                // 1)break itemLine into pieces
                arrange(line, itemTitle, itemInfo);
                // 2)create item_node
                item_node node_item(itemTitle,itemInfo);
                // 3) push the item_node into the insideTree of the section_node
                node_section.insideTree.insert(node_item);
                avl_node_section.avlInsideTree.insert(node_item);
            }
        
        }
        
    }
    
    auto start = chrono::high_resolution_clock::now();
    outsideTree.insert(node_section);
    auto end = chrono::high_resolution_clock::now();
    long long bstTimer = (end-start).count() / 1000.0;
    
    
    auto avlStart = chrono::high_resolution_clock::now();
    avlOutsideTree.insert(avl_node_section);
    auto avlEnd = chrono::high_resolution_clock::now();
    long long avlTimer = (avlEnd-avlStart).count() / 1000.0;
    
    
    cout << "Section "<< avl_node_section.section << " has been inserted into the AVL notebook." << endl;
    cout << "[AVL] Elapsed time: " << avlTimer <<  " microseconds" << endl;
    
    
    cout << "Section "<< node_section.section << " has been inserted into the BST notebook." << endl;
    cout << "[BST] Elapsed time: " << bstTimer <<  " microseconds" << endl<<endl;
    

    displaySectionMenu();
    
    string sectionInput, itemInput,sectionTitle, itemTitle2, itemInfo2;

    BinarySearchTree<item_node> insideTree2(ITEM_NOT_FOUND);
    section_node s_node("",insideTree2);
    
    
    AvlTree<item_node> insideTree3(ITEM_NOT_FOUND);
    avl_section_node avl_s_node("",insideTree3);
    
    item_node i_node("","");
    cout << "Input: ";
    getline(cin,sectionInput);
    
    
    while (sectionInput != "6") {
        if (sectionInput == "1") {
            // Display the section AVL
            cout << endl << "*****"<< endl;
             avlOutsideTree.printTree();
            cout << "*****"<< endl << endl;
        }else if(sectionInput == "2"){
            // Display the section BST
            cout << endl << "*****"<< endl;
             outsideTree.printTree();
            cout << "*****"<< endl << endl;
            
        }else if(sectionInput == "3"){
            // Select a section
            getSectionTitle(sectionTitle);
            s_node.section = sectionTitle;
            avl_s_node.section = sectionTitle;
            if(outsideTree.find(s_node).section == ""){
               
                cout << "Invalid title!" << endl << endl;
                
            }else{
                cout << endl <<"Seleceted section -> " << sectionTitle << endl;
                displayItemMenu();
                cout << "Input: ";
                getline(cin,itemInput);
       
               
                while (itemInput != "7") {
                    if (itemInput=="1") {
                        //Display the items [AVL]
                        
                        cout << endl << "*****" << endl;
                        avlOutsideTree.find(avl_s_node).avlInsideTree.printTree();
                        cout << "*****" << endl << endl;
                        
                    }else if(itemInput=="2"){
                        // Display the items [BST]
                        cout << endl <<"*****" << endl;
                        outsideTree.find(s_node).insideTree.printTree();
                        cout << "*****" << endl<<endl;
                    }else if(itemInput=="3"){
                        // Display the information of a item
                        cout << "Enter the title of the item: ";
                        getline(cin,itemTitle2);
           
                        i_node.title = itemTitle2;
                        
                        
                        auto start = chrono::high_resolution_clock::now();
                        outsideTree.find(s_node).insideTree.find(i_node);
                        auto end = chrono::high_resolution_clock::now();
                        long long bstTimer = (end-start).count() / 1000.0;
                        
                        
                        auto avlStart = chrono::high_resolution_clock::now();
                        avlOutsideTree.find(avl_s_node).avlInsideTree.find(i_node);
                        auto avlEnd = chrono::high_resolution_clock::now();
                        long long avlTimer = (avlEnd-avlStart).count() / 1000.0;
                        
                        cout << "[AVL] Elapsed time: " << avlTimer <<" microseconds" << endl;
                        cout << "[BST] Elapsed time: "<< bstTimer << " microseconds" << endl;
                        
                        
                        
                        if (outsideTree.find(s_node).insideTree.find(i_node).title == "") {
                            cout << "Invalid title." << endl<<endl;
                        }else{
                            cout << outsideTree.find(s_node).insideTree.find(i_node).info << endl<<endl;

                        }
                        
                        
                    }else if(itemInput=="4"){
                        // add new item
                        cout << "Enter the title of the item: ";
                        getline(cin,itemTitle2);
              

                        i_node.title = itemTitle2;
                        
                        
                        if (outsideTree.find(s_node).insideTree.find(i_node).title == "") {
                            //insert here BST
                            cout << "Enter a description for the item: ";
                            getline(cin,itemInfo2);
                            i_node.info = itemInfo2;
                            
                            insideTree = outsideTree.find(s_node).insideTree;
                            
                            auto start = chrono::high_resolution_clock::now();
                            insideTree.insert(i_node);
                            auto end = chrono::high_resolution_clock::now();
                            long long bstTimer = (end-start).count() / 1000.0;
                            
                            
                            outsideTree.remove(s_node);
                            s_node.section = sectionTitle;
                            s_node.insideTree = insideTree;
                            outsideTree.insert(s_node);
                            

                            
                            avlInsideTree = avlOutsideTree.find(avl_s_node).avlInsideTree;
                            
                            auto avlStart = chrono::high_resolution_clock::now();
                            avlInsideTree.insert(i_node);
                            auto avlEnd = chrono::high_resolution_clock::now();
                            long long avlTimer = (avlEnd-avlStart).count() / 1000.0;
                            
                            // insert here AVL
                            avlOutsideTree.remove(avl_s_node);
                            avl_s_node.section = sectionTitle;
                            avl_s_node.avlInsideTree = avlInsideTree;
                            avlOutsideTree.insert(avl_s_node);
                            
                            cout << "[AVL] Elapsed time: " << avlTimer <<" microseconds" << endl;
                            cout << "[BST] Elapsed time: "<< bstTimer << " microseconds" << endl;
                            
                            cout << "The new item " << itemTitle2 << " has been inserted." << endl<<endl;
                            
                           
                        
                            
                        }else{
                            // it is already exists
                            cout << "Item "<< itemTitle2 <<" already exists in the " << sectionTitle << "." << endl<<endl;
                        }
                         
                        
                    }else if(itemInput=="5"){
                        // Update the information of a item
                        
                        cout << "Enter the title of the item: ";
                        getline(cin,itemTitle2);
                        i_node.title = itemTitle2;
                        
                        auto start = chrono::high_resolution_clock::now();
                        outsideTree.find(s_node).insideTree.find(i_node);
                        auto end = chrono::high_resolution_clock::now();
                        long long bstTimer = (end-start).count() / 1000.0;
                    
                        
                        auto avlStart = chrono::high_resolution_clock::now();
                        avlOutsideTree.find(avl_s_node).avlInsideTree.find(i_node);
                        auto avlEnd = chrono::high_resolution_clock::now();
                        long long avlTimer = (avlEnd-avlStart).count() / 1000.0;
                        
                        cout << "[AVL] Elapsed time: " << avlTimer <<" microseconds" << endl;
                        cout << "[BST] Elapsed time: "<< bstTimer << " microseconds" << endl;
                      
                        if (outsideTree.find(s_node).insideTree.find(i_node).title == "") {
                            //cannot be updated because it doesnt exist
                            cout << "Item "<< itemTitle2 <<" does not exist in the " << sectionTitle << "." << endl<<endl;
                           
                        
                            
                        }else{
                            // update information of item

                            
                            cout << "Enter the new information: " ;
                            getline(cin,itemInfo2);
                            i_node.info = itemInfo2;
                            
                            
                            
                            insideTree = outsideTree.find(s_node).insideTree;
                            insideTree.remove(i_node);
                            insideTree.insert(i_node);
                            outsideTree.remove(s_node);
                            s_node.section = sectionTitle;
                            s_node.insideTree = insideTree;
                            outsideTree.insert(s_node);
                            
                            
                            avlInsideTree = avlOutsideTree.find(avl_s_node).avlInsideTree;
                            avlInsideTree.remove(i_node);
                            avlInsideTree.insert(i_node);
                            avlOutsideTree.remove(avl_s_node);
                            avl_s_node.section = sectionTitle;
                            avl_s_node.avlInsideTree = avlInsideTree;
                            avlOutsideTree.insert(avl_s_node);
                            
                            
                            
                            cout << "The content " << itemTitle2 << " has been updated." << endl<<endl;
                            
                            
                        }
                    }else if(itemInput == "6"){
                        //Delete an item
                        
                        cout << "Enter the title of the item:";
                        getline(cin,itemTitle2);
                        i_node.title = itemTitle2;
                      
                        if (outsideTree.find(s_node).insideTree.find(i_node).title == "") {
                            //cannot be updated because it doesnt exist
                            cout << "Item "<< itemTitle2 <<" does not exist in the " << sectionTitle << "." << endl<<endl;
                           
                        
                            
                        }else{

                            
                            
                            insideTree = outsideTree.find(s_node).insideTree;
                            
                            auto start = chrono::high_resolution_clock::now();
                        
                            insideTree.remove(i_node);
                            auto end = chrono::high_resolution_clock::now();
                            long long bstTimer = (end-start).count() / 1000.0;
                            
                            outsideTree.remove(s_node);
                            s_node.section = sectionTitle;
                            s_node.insideTree = insideTree;
                            outsideTree.insert(s_node);
                            
                            
                            
                            
                            avlInsideTree = avlOutsideTree.find(avl_s_node).avlInsideTree;
                            
                            auto avlStart = chrono::high_resolution_clock::now();
                          
                            avlInsideTree.remove(i_node);
                            auto avlEnd = chrono::high_resolution_clock::now();
                            long long avlTimer = (avlEnd-avlStart).count() / 1000.0;
                            
                            
                            
                    
                            avlOutsideTree.remove(avl_s_node);
                            avl_s_node.section = sectionTitle;
                            avl_s_node.avlInsideTree = avlInsideTree;
                            avlOutsideTree.insert(avl_s_node);
                            
                            
                            cout << "[AVL] Elapsed time: " << avlTimer <<" microseconds" << endl;
                            cout << "[BST] Elapsed time: "<< bstTimer << " microseconds" << endl;
                            cout << "The item " << itemTitle2 << " has been deleted." << endl<<endl;
                            
                            
                        }
                    }
                    
                    cout << "Input: ";
                    getline(cin,itemInput);
           
                }
                displaySectionMenu();
            }
            
            
        }else if(sectionInput == "4"){
            // insert new section
            getSectionTitle(sectionTitle);
            
            s_node.section = sectionTitle;
            avl_s_node.section = sectionTitle;
            s_node.insideTree.makeEmpty();
            avl_s_node.avlInsideTree.makeEmpty();
            
            if(outsideTree.find(s_node).section == ""){
               
                outsideTree.insert(s_node);
                
                avlOutsideTree.insert(avl_s_node);
                cout << "The new section " << sectionTitle << " has been inserted." << endl << endl;
                
            }else{
                cout << "Section " << sectionTitle << " already exists." << endl<<endl;
            }
            
            
        }else if(sectionInput == "5"){
            // Delete section
            getSectionTitle(sectionTitle);
            s_node.section = sectionTitle;
            avl_s_node.section = sectionTitle;
            if(outsideTree.find(s_node).section == ""){
                cout << "Section " << sectionTitle << " does not exist." << endl <<endl;
                
            }else{
                
                outsideTree.remove(s_node);
                avlOutsideTree.remove(avl_s_node);
                cout << "The section has been deleted." << endl;
            }
            
        }
        
        cout << "Input: " ;
        getline(cin,sectionInput);

    }
    
    
    

return 0;
}
