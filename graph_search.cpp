//
//  main.cpp
//  graph search
//
//  Created by Sophia Mikhaylova on 24.05.2023.
//

#include <iostream>
using namespace std;

struct node{
    int num;
    node* next;
    
    node(){
        next = NULL;
    }
};

struct graph{
    node* arr[10];
    
//    graph(){
//        for (int i = 0; i < 10; i++)
//            arr[i] = NULL;
//        cout << "new Graph Struct Initialized"<<endl;
//    }
};

struct matrix{
    int mtr[10][10];
    
    matrix(){
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                mtr[i][j] = 0;
    }
};


graph matrixToStruct(int arr[10][10]){
    graph graph1;
    
    for (int i = 0; i < 10; i++)
            graph1.arr[i] = NULL;
    
    node* tempLast = NULL;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (arr[i][j] != 0)
            {
                node* tempNew = new node;
                tempNew->num = j+1;
                
                if (!graph1.arr[i])
                    graph1.arr[i] = tempNew;
                else
                    tempLast->next = tempNew;
                    
                tempLast = tempNew;
            }
    return graph1;
}

void showMatrix(int arr[10][10], int max){
    for (int i = 0; i < max; i++)
    {
        for (int j = 0; j < max; j++)
            cout << arr[i][j]<<";  ";
        cout << endl;
    }
}

void showGraph(graph graph1, int max){
    node* temp;
    for (int i = 0; i < max; i++)
    {
        cout << "node: " << i+1<< " -> ";
        temp = graph1.arr[i];
        while (temp)
        {
            cout << temp->num<<"; ";
            temp = temp->next;
        }
                   
        cout << endl;
    }
}


void depth_search(graph graph1, int active, bool check[10]){
    
    check[active-1] = true;
    node* temp = graph1.arr[active-1];
    
    while (temp)
    {
        if (!check[temp->num - 1])
        {
            depth_search(graph1, temp->num, check);
        }
        temp = temp->next;
    }
}

void depth_search_another(graph graph1, int active, int check[10]){
    
    node* temp = graph1.arr[active-1];
    
    while (temp)
    {
        if (check[temp->num - 1] == 0)
        {
            check[temp->num - 1] = check[active - 1] + 1;
            depth_search_another(graph1, temp->num, check);
        }
        temp = temp->next;
        
    }
}

bool checkEuler(graph graph1, int max){
    node* temp;
    bool check = true;
    int counter = 0;
    
    for (int i = 0; i < max; i++)
    {
        counter = 0;
        temp = graph1.arr[i] ;
        
        while(temp)
        {
            counter++;
            temp = temp->next;
        }
        cout << "counter: "<< counter<< endl;
        if (counter%2 != 0)
            check = false;
    }
    
    return check;
}

// wide search:

// queue:
struct que{
    int num;
    que* next;
};

void addQ(que** head, que** tail, int newNode){
    que* temp = new que;
    temp->num = newNode;
    temp->next = NULL;
    
    if (*tail)
        (*tail)->next = temp;
    else
        *head = temp;
    *tail = temp;
}

void delQ(que** head, que** tail){
    if (!(*head))
    {
        cout << "que is empty!"<<endl;
        return;
    }
    
//    cout << "del: " << (*head)->num<<endl;
    
    que* tempDel = *head;
    *head = (*head)->next;
    
    if (tempDel == *tail)
        *tail = NULL;
        
    delete tempDel;
}

void wideSearch(graph graph1, int path[10], int first){
    que* head = NULL, *tail = NULL;
    for (int i = 0; i < 10; i++)
        path[i] = -1;
        
    path[first-1] = 0;
    addQ(&head, &tail, first);
    
    while (head)
    {
        node* temp = graph1.arr[head->num - 1];
        while (temp)
        //for (; temp; temp = temp->next)
        {
            if (path[temp->num-1] == -1)
            {
                addQ(&head, &tail, temp->num);
                path[temp->num-1] = path[head->num -1]+1;
            }
            temp = temp->next;
        }
        delQ(&head, &tail);
    }
}



int main() {
    
    int mtr1[10][10] = {{0,1,1,0,1,0,0,0},
                        {1,0,0,0,1,0,0,0},
                        {1,0,0,1,0,0,1,0},
                        {0,0,1,0,0,0,0,0},
                        {1,1,0,0,0,1,1,0},
                        {0,0,0,0,1,0,0,0},
                        {0,0,1,0,1,0,0,1},
                        {0,0,0,0,0,0,1,0}};
    
    
    graph graph1 = matrixToStruct(mtr1);
    
    showMatrix(mtr1, 8);
    showGraph(graph1, 8);
    
    bool check[10];
    for (int i = 0; i < 10; i++)
        check[i] = 0;
        
    cout << "depth search:"<<endl;
    depth_search(graph1, 1, check);
    
    for (int i = 0; i < 10; i++)
        cout << i+1<<":  "<<check[i]<<endl;
    cout << "wide search:"<<endl;
    int path[10];
    
    wideSearch(graph1,path, 1);
    
    for (int i = 0; i < 10; i++)
        cout << i+1<<":  "<<path[i]<<endl;
    
    return 0;
}
