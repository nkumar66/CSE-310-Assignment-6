//************************************************************************
// ASU CSE310 Assignment #6 Spring 2024
// Author: Nilay Kumar
// ASU ID: 1225127891
// Description: this is the main program that reads input from keyboard,
// it then execute various red-black tree operations which is given in the input.
//**************************************************************************

#include "RedBlackTree.h"

using namespace std;

//This function used to get the key of a Car which is the combination of vin, model & make
void getCarKey(string oneLine, int& vin, string& model, string& make);

//This function used to get all info. of a Car
void getCarInfo(string oneLine, int& vin, string& model, string& make, double& price);

int main()
{

   int vin;
   string model, make;
   double price;
   string command, oneLine, token;
   string delimiter = ",";

   int pos = 0;

   //Create a RedBlackTree object here, use it throughout the program
   //----
   //----
   RedBlackTree RBT;

   do
   {
      getline(cin, oneLine);
      pos = oneLine.find(delimiter);
      token = oneLine.substr(0, pos);
      command = token;
      oneLine.erase(0, pos + delimiter.length());

      if(command.compare("quit")==0)
      {
         cout << "\nCommand: quit" << endl;
         //call the relevant function on the red black tree
         //----
         RBT.~RedBlackTree();    //lets just call the destructor


         break;
      }
      else if(command.compare("tree_preorder")==0)
      {
         cout << "\nCommand: tree_preorder" << endl;

         //call the relevant function on the red black tree
         //----
         RBT.treePreorder();     //just need to call the function
      }
      else if(command.compare("tree_inorder")==0)
      {
         cout << "\nCommand: tree_inorder" << endl;

         //call the relevant function on the red black tree
         //----
         RBT.treeInorder();   //just need to call the function
      }
      else if(command.compare("tree_postorder")==0)
      {
         cout << "\nCommand: tree_postorder" << endl;

         //call the relevant function on the red black tree
         //----
         RBT.treePostorder();    //just need to call the function
      }
      else if(command.compare("tree_minimum")==0)
      {
         cout << "\nCommand: tree_minimum" << endl;

         //call the relevant function on the red black tree
         //----
         RBT.treeMinimum();     //just need to call the function
      }
      else if(command.compare("tree_maximum")==0)
      {
         cout << "\nCommand: tree_maximum" << endl;

         //call the relevant function on the red black tree
         //----
         RBT.treeMaximum();   //just need to call function
      }
      else if(command.compare("tree_predecessor")==0)
      {
         //call the getCarKey function to get the Car key first
         //----

         getCarKey(oneLine, vin, model, make);     //just call the function

         cout << "\nCommand: tree_predecessor" << endl;

         //call the relevant function on the red black tree
         //----
         
         RBT.treePredecessor(vin, model, make);       //call predecessor function

      }
      else if(command.compare("tree_successor")==0)
      {
         //call the getCarKey function to get the Car key first
         //----

         getCarKey(oneLine, vin, model, make);        //call function

         cout << "\nCommand: tree_successor" << endl;
         //call the relevant function on the red black tree
         //----
         RBT.treeSuccessor(vin, model, make);         //successor function called
      }
      else if(command.compare("tree_search")==0)
      {
         //call the getCarKey function to get the Car key first
         //----
         getCarKey(oneLine, vin, model, make);        //get car key function
         cout << "\nCommand: tree_search" << endl;
         //call the relevant function on the red black tree
         //----
         RBT.treeSearch(vin, model, make);         //find the node using treeSearch
      }
      else if(command.compare("tree_insert")==0)
      {
         //call the getCarInfo function to get the Car key first
         //----
         getCarInfo(oneLine, vin, model, make, price);      //simply call getCarInfo

         cout << "\nCommand: tree_insert" << endl;
         cout << left;
         cout << setw(8)  << vin
              << setw(12) << model
              << setw(12) << make
              << setw(10) << fixed << setprecision(2) << price << endl;

        //call the relevant function to insert the Car
         //----
         RBT.treeInsert(vin, model, make, price);     //just call function with parameters


        }
   } while(true);  //continue until 'quit'
   return 0;
}

//*********************************************************************************
//This function from one line, extracts the vin, model, make of a Car.
//You should already know how to extract tokens from Assignment5.cpp file
void getCarKey(string oneLine, int& vin, string& model, string& make)
{
   //Design your own code here
   //----

   //we are going to do the same thing as in Assignment5.cpp

   string delimiter = ",";          //comma is delimiter
   int position = line.find(delimiter);      //find the position of delimiter
   line.erase(0, position+delimiter.length());     //delete first phrase because we need the info that comes after it

   position = line.find(delimiter);             //this block is for the vin
   token = line.substr(0, position);
   vin = token;
   line.erase(0, position+delimiter.length());

   position = line.find(delimiter);          //this block is for the model
   token = line.substr(0, position);
   model = token;
   line.erase(0, position+delimiter.length());

   position = line.find(delimiter);       //this block is for the make
   token = line.substr(0, position);
   make = token;
   line.erase(0, position+delimiter.length());

   //now lets make the key
   string nodeKey = to_string(node->vin) + node->model + node->make;
   
}

//************************************************************************************************
//This function from one line, extract tokens and get all info. of a Car
void getCarInfo(string oneLine, int& vin, string& model, string& make, double& price)
{
   //Design your own code here
   //----

   string delimiter = ",";          //comma is delimiter
   int position = line.find(delimiter);      //find the position of delimiter
   line.erase(0, position+delimiter.length());     //delete first phrase because we need the info that comes after it

   position = line.find(delimiter);             //this block is for the vin
   token = line.substr(0, position);
   vin = token;
   line.erase(0, position+delimiter.length());

   position = line.find(delimiter);          //this block is for the model
   token = line.substr(0, position);
   model = token;
   line.erase(0, position+delimiter.length());

   position = line.find(delimiter);       //this block is for the make
   token = line.substr(0, position);
   make = token;
   line.erase(0, position+delimiter.length());

   position = line.find(delimiter);       //this block is for the price
   token = line.substr(0, position);
   price = token;
   line.erase(0, position+delimiter.length());


}

