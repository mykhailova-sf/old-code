//
//  main.cpp
//  Final_module_Mihailova_Sophia(IPS - 12)
//
//  Created by Sophia Mikhaylova on 03.06.2023.
//

#include <iostream>

using namespace std;

///TASK 1.10
struct Node
{
    int data;
    Node* next;
};


void showList(Node* head)
{
    Node* temp = head;
    while (temp)
    {
        cout << "(" << temp->data << ") -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

void appendToEnd(Node** head, int data)
{
    Node* temp = new Node;
    temp->data = data;
    temp->next = NULL;

    if (*head)
    {
        Node* current = *head;
        while(current->next)
        {
            current = current->next;
        }
        current->next = temp;
    }
    else
    {
        (*head) = temp;
    }
}
Node* combine(Node* bim, Node* bom)
{
    Node* combined = NULL;
    Node* current = NULL;

    while (bim && bom)
    {
        if (bim->data >= bom->data)
        {
            Node* tmp = new Node;
            tmp->data = bim->data;
            tmp->next = NULL;

            if (combined == NULL)
            {
                combined = tmp;
                current = tmp;
            }
            else
            {
                current->next = tmp;
                current = tmp;
            }
    
            bim = bim->next;
        }
        else
        {
            Node* tmp = new Node;
            tmp->data = bom->data;
            tmp->next = NULL;

            if (combined == NULL)
            {
                combined = tmp;
                current = tmp;
            }
            else
            {
                current->next = tmp;
                current = tmp;
            }

            bom = bom->next;
        }
    }

    while (bim)
    {
        Node* tmp = new Node;
        tmp->data = bim->data;
        tmp->next = NULL;

        current->next = tmp;
        current = tmp;

        bim = bim->next;
    }

    while (bom)
    {
        Node* tmp = new Node;
        tmp->data = bom->data;
        tmp->next = NULL;

        current->next = tmp;
        current = tmp;

        bom = bom->next;
    }

    return combined;
}
int main()
{
    ///TASK 1.10
    Node* bim = NULL;
    Node* bom = NULL;

    appendToEnd(&bim, 12);
    appendToEnd(&bim, 11);
    for(int i = 10; i > 0; i--)
    {
        if(i%2 == 0)
            appendToEnd(&bim, i);
        else
            appendToEnd(&bom, i);
    }

    Node* bim_bom = combine(bim, bom);

    showList(bim);
    showList(bom);
    showList(bim_bom);

    return 0;
}

