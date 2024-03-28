//************************************************************************
// ASU CSE310 Assignment #6 Spring 2024
// Author: Nilay Kumar
// ASU ID: 
// Description: Red black tree implementation. See RedBlackTree.h
//              for the Red Black Tree definition
//************************************************************************

//include the relevant header file
//----
#include "RedBlackTree.h"

using namespace std;

int nodeSize = 0;       //counter to be able to tell how many nodes were deleted

//*******************************************************************
//constructor
RedBlackTree::RedBlackTree()
{
	//----
      //just need to declare a root node and set it to nullptr

      root = nullptr;

      
}

//*******************************************************************
//destructor
RedBlackTree::~RedBlackTree()
{
	//----
	//----
      //I want to use helper function to recursively go through and delete all of the nodes
      int nodeSize = deleteNode(root);          //want to start at the root and traverse down
      root = nullptr;

	cout << "The number of nodes deleted: " << nodeSize << endl;
}

//**************************************************************
//Accessor for the root of the red-black tree

//write your own code according to red-black tree definition
//----
Node* RedBlackTree::getRoot() {

      return root;       //just return the root
}


//*******************************************************************
//delete the sub-tree rooted at 'node' and return number of nodes deleted
//This should be defined as a recursive function

//write your own code according to red-black tree definition
//----
int RedBlackTree::deleteNode(Node *node) {
      

      //first lets set the base case for this recursive function
      if (node == nullptr) {
            return 0;
      }
      
      deleteNode(node->leftChild);           //delete everything on the left
      deleteNode(node->rightChild);          //delete everything on the right

      delete node;            //this will actually delete the current node
      nodeSize++;       //increment for node delete count when printing after calling destructor

      //return the nodeSize
      return nodeSize;
}


//****************************************************************
//This is the general BST insertion operation.
//It does not care about the color of the newly added node.

//write your own code according to red-black tree definition
//----

void RedBlackTree::insertNode(Node *node) {

      Node* y = nullptr;            //make some pointers to help traverse through the tree
      Node* x = root;

      //make the key
      string nodeKey = to_string(node->vin) + node->model + node->make;

      while (x != nullptr) {              //while root is not null, set main pointer equal to it
            y = x;
            if (compareNodes(x, nodeKey) > 0/*node->vin < x->vin*/) {           //if node vin is less than root's vin/x's vin (when not root also)
                  x = x->leftChild;             //move to the left child
            } else {
                  x = x->rightChild;            //means it's greater than, so move to the right
            }
      }

      //now we need to set a pointer for the new node's parent because now it's in the correct location
      node->parent = y;

      //lets determine whether the node needs to be on the left or right of parent node
      if (y == nullptr) {           //just to make sure if parent is null
            root = node;
      }else if (compareNodes(y, nodeKey) > 0/*node->vin < y->vin*/) {            //if new node's vin is less than parent vin, it becomes left child
            y->leftChild = node;
      } else {                                  //if new node's vin is greater than parent, then it becomes the right child
            y->rightChild = node;
      }

      node->color = "RED";          //since we just inserted a node, we need to set it as red
      

      //lastly we have to call fixup to make sure that there is no violations with the current tree
      fixUp(node);

      //lets increment nodeSize
      //nodeSize++;

}


//*******************************************************************
//At beginning, each newly added node will always be RED,
//this may violate the red-black tree property #4. fixUp()
//function will restore the property.

//write your own code according to red-black tree definition
//----

void RedBlackTree::fixUp(Node *node) {

      while (node != root && node->parent->color == "RED") {

            if (node->parent == node->parent->parent->leftChild) {      //if the parent is a left child

                  Node* uncle = node->parent->parent->rightChild;       //set the uncle to use later which has to be a right child

                  //lets start with doing case #1, where uncle is red
                  if (uncle != nullptr &&uncle->color == "RED") {
                        
                        node->parent->color = "BLACK";            //change parent to black
                        uncle->color = "BLACK";             //change uncle to black as well
                        node->parent->parent->color = "RED";           //change grandparent to red     
                        node = node->parent->parent;        //move the current node up to the grandparent, to then check for violations
                  } else {

                  //now we can do case #2, where uncle is black, and the current node is a left child of the parent
                       if (node == node->parent->rightChild) {

                        node = node->parent;          //move the current to the parent  node for the left rotation
                        leftRotate(node);             //perform the left rotation on the parent node
                        }

                  //now lets do the case #3, where uncle is black, and the current node is the right child
                 //since we are reaching this case no matter what if we perform case #2, since it's terminal, we dont need an outlying condition

                        node->parent->color = "BLACK";      //change color of parent to black
                        node->parent->parent->color = "RED";      //make grand parent change to red
                        rightRotate(node->parent->parent);        //right rotate on the grand parent
                  }


            } else {                //if the parent is a right child
                  //now we have to make all the symmetric cases to the ones we made above, aka left becomes right and right becomes left etc for rotates

                  Node* uncle = node->parent->parent->leftChild;

                  //lets start with Case #1 again, uncle is red:
                  if (uncle != nullptr && uncle->color == "RED") {

                        node->parent->color = "BLACK";                  //repeat same steps as above case #1
                        uncle->color = "BLACK";
                        node->parent->parent->color = "RED";
                        node = node->parent->parent;
                  } else {

                        //now we can do case #2, but differeently, just switch everything 
                        if (node == node->parent->leftChild) {

                              node = node->parent;                //move to parent and then right rotate to then later move to case 3
                              rightRotate(node);
                        }
                  
                        //now case 3
                        node->parent->color = "BLACK";            //set parent to black
                        node->parent->parent->color = "RED";                 //set grand parent to red
                        leftRotate(node->parent->parent);         //call left rotate to then have a full tree
                  }
            }
      }

      root->color = "BLACK";        //just to make sure that the root is always black after this fixup function
}


//*****************************************************
//This function print the pre-order traversal of the
//subtree rooted at 'node'.It's a recursive function

//write your own code according to red-black tree definition
//----
void RedBlackTree::preOrderTraversal(Node *node) {

      //since this is supposed to be a recursive function, all we can do is keep calling the function with a new left/right child
      if (node != nullptr) {

            print(node);                              //starts at the node because it's pre order


            preOrderTraversal(node->leftChild);       //since it's pre order, we do the left child first

            preOrderTraversal(node->rightChild);      //and then right child is next to traverse the right subtrees
      }
}

//**************************************************
//This function print the in-order traversal of the
//subtree rooted at 'node'.It's a recursive function

//write your own code according to red-black tree definition
//----

void RedBlackTree::inorderTraversal(Node *node) {
      //all we change in this one compared to the pre order is the order in which you write the code, you do left side, then root, then right side

      if (node != nullptr) {

            inorderTraversal(node->leftChild);        //left side of the tree

            print(node);                              //used for the actual "root" node

            inorderTraversal(node->rightChild);       //right side of the tree
      }
}

//**************************************************
//This function print the post-order traversal of the
//subtree rooted at 'node'.It's a recursive function

//write your own code according to red-black tree definition
//----

void RedBlackTree::postOrderTraversal(Node *node) {
      //finally, change the order so that it's left, right, and then root
      if (node != nullptr) {
            
            postOrderTraversal(node->leftChild);            //left subtree

            postOrderTraversal(node->rightChild);           //right subtree

            print(node);                  //root
      }
}


//**************************************************************
//This function returns a pointer points to the minimum node from
//the current sub-tree rooted at 'node'. It should be designed as
//a recursive function

//write your own code according to red-black tree definition
//----

Node* RedBlackTree::findMinimumNode(Node *node) {
      //since it's a recursive function, all we have to do is keep calling the let child until we get to the smallest one

      while (node != nullptr && node->leftChild != nullptr) {
            node = node->leftChild;                   //keep moving to the left most node while it's not a nullptr
      }

      return node;            //return the last node you come across before the condition fails and the next pointer would be a nullptr
}

//**************************************************************
//This function returns a pointer points to the maximum node from
//the current sub-tree rooted at 'node'. It should be designed as
//a recursive function

//write your own code according to red-black tree definition
//----

Node* RedBlackTree::findMaximumNode(Node *node) {

      //same thing as above, except we keep moving to the right

      while (node != nullptr && node->rightChild != nullptr) {
            node = node->rightChild;                  //keep moving to the right most child for the highest number
      }

      return node;            //return last node I come across before condition fails
}


//**************************************************************
//This function search the tree for a given key of a Car
//Note: key is the combination of vin, model and make of the Car
//It returns a pointer points to the node if founded; otherwise it returns NULL

//write your own code according to red-black tree definition
//----

Node* RedBlackTree::treeSearch(int vin, string model, string make) {

      //lets start searching from the root as always
      Node* current = root;

      while (current != nullptr) {
            //now lets compare the data with the current's data
            if (current->vin == vin && current->model == model && current->make == make) {        //perfect case scenario where everything matches    
                  return current;

                  //this next if statement is for checking if any of the stats are less than that of the current node, in which case it'll take the left child
            } else if (vin < current->vin || (vin == current->vin && model < current->model) || (vin == current->vin && model == current->model && make < current->make)) {
                  
                  current = current->leftChild;

            } else {          //nothing else met so that means it has to move to the right child
                  
                  current = current->rightChild;
            }
      }
      //if it was not found in the above 3 cases then that means it doesn't exist
      return nullptr;
}

//****************************************************
//This function left-rotate the BST rooted at 'node'

//write your own code according to red-black tree definition
//----

void RedBlackTree::leftRotate(Node *node) {

      //lets first make sure that since we are doing a leftRotate, the node should have a right child
      if (node == nullptr || node->rightChild == nullptr) {
            return;
      }

      //lets set the right child of node to rightChild of its right child
      Node* rightChild = node->rightChild;
      node->rightChild = rightChild->leftChild;

      //now lets update the parent pointer of rightChild->leftChild
      if (rightChild->leftChild != nullptr) {
            rightChild->leftChild->parent = node;
      }

      //lets update the parent pointer of the rightChild
      rightChild->parent = node->parent;

      //lets fix the scenario where node is the root of the entire tree
      if (node->parent == nullptr) {
            root = rightChild;
      //if node is left child, update left child of the parent
      }else {
            if (node == node->parent->leftChild) {
                  node->parent->leftChild = rightChild;
            //if node is the right child, update the right child of the parent
            } else {
                  node->parent->rightChild = rightChild;
            }
      }

      //node needs to be set as the leftChild of rightChild
      rightChild->leftChild = node;

      //update parent pointer for node
      node->parent = rightChild;

}


//***************************************************
//This function right-rotate the BST rooted at 'node'

//write your own code according to red-black tree definition
//----

void RedBlackTree::rightRotate(Node *node) {

      //lets do the same thing as leftRotate but switch all the rightChilds to LeftChilds and vice versa
      if (node == nullptr || node->leftChild == nullptr) {
            return;
      }

      //lets set the leftChild of node to leftChild of leftChild
      Node* leftChild = node->leftChild;
      node->leftChild = leftChild->rightChild;

      //update the parent pointer of leftChild->rightChild
      if (leftChild->rightChild != nullptr) {
            leftChild->rightChild->parent = node;
      }

      //update parent pointer of leftChild
      leftChild->parent = node->parent;

      //if the node is the root, update the root
      if (node->parent == nullptr) {
            root = leftChild;
      //if node is right child of parent, update right child of parent
      } else if (node == node->parent->rightChild) {
            node->parent->rightChild = leftChild;
      //if node is left child of parent, update left child of parent
      }else {
            node->parent->leftChild = leftChild;
      }

      //set node as right child of leftChild
      leftChild->rightChild = node;

      //update parent pointer of node
      node->parent = leftChild;
}


//**************************************************************
//This function finds the predecessor of the given 'node'
//it prints the relevant predecessor info. on screen and also
//return a pointer that points to the predecessor

//write your own code according to red-black tree definition
//----

Node* RedBlackTree::findPredecessorNode(Node *node) {

      if (node == nullptr) {        //just incase the node is nullptr
            return nullptr;
      }

      //lets check for if the leftSubtree of the node isn't nullptr, we can return the maximum node of the leftSubtree
      if (node->leftChild != nullptr) {
            return findMaximumNode(node->leftChild);
      }

      //now lets traverse up the tree until we find a node that is a right child or until we reach the root
      Node* parent = node->parent;
      while (parent != nullptr && node == parent->leftChild) {
            node = parent;
            parent = parent->parent;
      }

      //now parent will be the predecessor node so we will return that
      return parent;

}

//**************************************************************
//This function finds the successor of the given 'node'
//it prints the relevant successor info. on screen and also return
//a pointer that points to the successor node

//write your own code according to red-black tree definition
//----

Node* RedBlackTree::findSuccessorNode(Node *node) {
      
      //if the node is nullptr again, then just return nullptr
      if (node == nullptr) {
            return nullptr;
      }

      //if right subtree of the node is not  nullptr, then we can return the minimum
      if (node->rightChild != nullptr) {
            return findMinimumNode(node->rightChild);
      }

      //finally we can traverse up the tree to find a node that is a left child or until we reach the root
      Node* parent = node->parent;

      while (parent != nullptr && node == parent->rightChild) {
            node = parent;
            parent = parent->parent;            //update pointers
      }

      //parent should now be the sucessor, so we will just return that
      return parent;
}

//****************************************************************
//This function find the minimum node of the entire red-black tree
//It print out the minimum node info. on screen if tree is not empty
//or print Tree is empty. No Minimum. message on screen.

//write your own code according to red-black tree definition
//----

void RedBlackTree::treeMinimum() {

      //lets set a new node to be the value of the minimum to be a node

      Node* minNode = findMinimumNode(root);

      //now lets write the conditions and print statements based on the output of the findMinimumNode function that we called
      if (minNode != nullptr) {
            cout << "The MINIMUM is:" << endl;
            print(minNode);
      } else {
            cout << "Tree is empty. No Minimum." << endl;
      }
}

//**************************************************************
//This function find the maximum node of the entire red-black tree
//It print out the maximum node info. on screen if tree is not empty
//or print Tree is empty. No Maximum. message on screen.

//write your own code according to red-black tree definition
//----

void RedBlackTree::treeMaximum() {

      //lets do the same thing and set a new node to be the value of the max node

      Node* maxNode = findMaximumNode(root);

      //now lets write the conditions again to print the info of this
      if (maxNode != nullptr) {
            cout << "The MAXIMUM is:" << endl;
            print(maxNode);
      } else {
            cout << "Tree is empty. No Maximum." << endl;
      }
}

//****************************************************************************
//This function print out the pre-order traversal of the entire red-black tree

//write your own code according to red-black tree definition
//----

void RedBlackTree::treePreorder() {

      
      preOrderTraversal(root);      //always start the traversal from the root
}

//***************************************************************************
//This function print out the in-order traversal of the entire red-black tree

//write your own code according to red-black tree definition
//----

void RedBlackTree::treeInorder() {
      //same as above

      inorderTraversal(root);       //again start at the root
}

//*****************************************************************************
//This function print out the post-order traversal of the entire red-black tree

//write your own code according to red-black tree definition
//----

void RedBlackTree::treePostorder() {

      //same as above
      postOrderTraversal(root);           //start at the root to encompass all the nodes
}

//******************************************************************
//Given a Car key, this function first check whether the
//Car is inside the tree or not, if it is inside, it will print
//its predecessor info. on screen, if not, it print an error message

//write your own code according to red-black tree definition
//----

void RedBlackTree::treePredecessor(int vin, string model, string make) {

      //lets first get the node using all the node details we are given

      Node* node = treeSearch(vin, model, make);

      //now lets make sure that it actually exists and isn't null
      if (node == nullptr) {
            cout << "ERROR: not found" << endl;
            return;
      }

      //now lets actually call the predecessor function we defined earlier   
      Node* predecessor = findPredecessorNode(node);


      //if it's found, print out the information
      if (predecessor != nullptr) {
            cout << "Its Predecessor is: " << endl;
            print(predecessor);
      }else {     //and if its not found, print statement accordingly
            cout << "Its Predecessor does NOT EXIST" << endl;
      }
}

//*****************************skil************************************
//Given a Car key, this function first check whether the
//Car is inside the tree or not, if it is inside, it will print
//its successor info. on screen, if not, it print an error message

//write your own code according to red-black tree definition
//----

void RedBlackTree::treeSuccessor(int vin, string model, string make) {

      //same format of code as above
      //make node with all details given
      Node* node = treeSearch(vin, model, make);

      //now lets make sure the node exists and isn't nullptr
      if (node == nullptr) {
            cout << "ERROR: not found" << endl;
            return;
      }

      //now lets call succesesor function
      Node* successor = findSuccessorNode(node);

      //if its found, print the information, and if not found, print that it's not found

      if (successor != nullptr) {
            cout << "Its Successor is: " << endl;
            print(successor);
      } else {
            cout << "Its Successor does NOT EXIST" << endl;

      }
}

//**************************************************************
//This function create a node from the given info., then insert
//the node inside the red-black tree. Note: at beginning, the newly
//added node should always be 'RED'

//write your own code according to red-black tree definition
//----

void RedBlackTree::treeInsert(int vin, string model, string make, double price) {
      //lets create a new node will all of this information

      Node* newNode = new Node;
      newNode->vin = vin;
      newNode->model = model;
      newNode->make = make;
      newNode->price = price;
      newNode->rightChild = nullptr;            //because we don't know what the child is going to be yet
      newNode->leftChild = nullptr;             //same as above
      newNode->color = "RED";       //new nodes always start out as red

      //now we can go ahead and call the function to insert the node into the tree
      insertNode(newNode);

      //violations will be fixed when insertNode calls fixUp function
      fixUp(newNode);
}

//******************************************************************
//Given a 'node', this function prints all the node information on screen
void RedBlackTree::print(Node *node)
{
      cout << left;
      cout << setw(8)  << node->vin
           << setw(12) << node->model
           << setw(12) << node->make
           << setw(10) << fixed << setprecision(2) << node->price;
      cout << right << setw(7) << node->color << endl;
}

//**************************************************************
//Given a Node 'node1', this function compares it with another
//node's key.
//key is a string combination of vin + model + make
//It returns a negative number if in alphabetical order, key2 is
//in front of 'node1'; otherwise it returns a positive number

//write your own code according to red-black tree definition
//----

int RedBlackTree::compareNodes(Node *node, string key) {

      //lets make the key to be able to compare
      string nodeKey = to_string(node->vin) + node->model + node->make;

      //simply compare the keys and it will return a:
      //positive number if key comes after the given key alphabetically
      //0 if they are the same/equal
      //negative number if node's key should come before given key alphabetically

      //in this scenario, node's key is nodeKey and given key is "key".
      return nodeKey.compare(key);

}
