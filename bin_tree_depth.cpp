//
//  main.cpp
//  2.10_BIN_TREE_DEPTH
//
//  Created by Sophia Mikhaylova on 03.06.2023.
//

#include <iostream>
using namespace std;

struct Node
{
    int num;
    Node* left;
    Node* right;
};

void addNode(Node* nod, int data)
{
    if (data < nod->num)
    {
        if (nod->left)
        {
            addNode(nod->left, data);
        }
        else
        {
            Node* newNode = new Node;
            newNode->num = data;
            newNode->left = newNode->right = NULL;
            nod->left = newNode;
        }
    }
    else
    {
        if (nod->right)
        {
            addNode(nod->right, data);
        }
        else
        {
            Node* newNode = new Node;
            newNode->num = data;
            newNode->left = newNode->right = NULL;
            nod->right = newNode;
        }
    }
}

void showBinary(Node* nod)
{
    if (!nod)
        return;
    
    showBinary(nod->left);
    cout << nod->num<<"; ";
    showBinary(nod->right);
}


int findDepth(Node* node, int target)
{
    if (node == NULL)
       {
           return -1;  // target not found at all
       }

       if (target == node->num)
       {
           return 1;  // target found
       }

       int depth;
    
       if (target < node->num)
       {
           depth = findDepth(node->left, target);
       }
       else
       {
           depth = findDepth(node->right, target);
       }
       
       return (depth != -1) ? depth + 1 : depth;
}

int main(){
    
    int arr[11] = {9,14,5,7,13,16,3,12,20,4,11};
    Node* root = new Node;
        root->num = arr[0];
        root->left = root->right = NULL; 

    for (int i = 1; i < 11; i++)
        addNode(root, arr[i]);
    
    showBinary(root);

    int U = 14;
    cout << "Depth: " << findDepth(root, U) << endl;

    return 0;
}

