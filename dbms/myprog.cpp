#include<iostream>
#include<string.h>

using namespace std;

int p;

struct node{
node *child;
node *next;
node *parent;
int key_val;



};
struct mnode{
node * head;
node * tail;
bool is_leaf;
int total_ele;
bool root;
};

class stack{
node* a[100];int current;
public:
stack(){
current=0;
}

void push(node* ptr){
if(current==100)
cout<<"Stack overflow";

a[current]=ptr;
current++;
}

node* pop(){
if(--current<0)
cout<<"Stack is empty";
return a[current];
}

}stk;

class btree{

btree(){
struct mnode * ptr;
ptr->head=NULL;
ptr->tail=NULL;
}
};

void insert(){


}



int main(){
mnode *currentNode;
currentNode->root=true;
cout<<"Enter the maximum value of tree pointer\n";
cin>>p;

}
