#include<iostream>
#include<string.h>

using namespace std;

int p=0;
struct mnode;

struct node{
node *previous;
node *next;
mnode* child;
int k;

};

struct mnode{
node * head;
node * tail;
node * current;
mnode * next;
bool is_leaf;
int total_ele;
bool root;
};

class stack{
mnode* a[100];int current;
public:
stack(){
current=0;
}

bool isempty(){
if(current==0)
return true;
else false;
}
void clrstk(){
current=0;
}
void push(mnode* ptr){
if(current==100)
cout<<"Stack overflow";

a[current]=ptr;
current++;
}

mnode* pop(){
if(--current<0)
cout<<"Stack is empty";
return a[current];
}

}stk;

class btree{

public:
struct mnode * ptr;
struct node * p;
btree(){


ptr->head=NULL;
ptr->tail=NULL;
ptr->current=NULL;
ptr->next=NULL;

p->child=NULL;
p->next=NULL;
p->previous=NULL;
}
};

void insert(int k,mnode* rootNode){
mnode* currentNode=rootNode;
currentNode->current=currentNode->head;
int q=0;
while( ! currentNode->is_leaf ){
stk.push(currentNode);
q=currentNode->total_ele;
if(k<=currentNode->head->k)
currentNode=currentNode->head->child;
else if(k>currentNode->tail->k)
{
currentNode=currentNode->tail->child;

}
else{
while(currentNode->current->next !=currentNode->tail){
currentNode->current=currentNode->current->next;
if((currentNode->current->previous->k < k) || ( k <= currentNode->current->k))
{currentNode=currentNode->current->child;
break;}
}

}

}
while(currentNode->current !=NULL){
if(currentNode->current->k == k){
cout<<"Record already in file cann't insert :"<<k;
return;
}
else
currentNode->current=currentNode->current->next;

}
currentNode->current=currentNode->head;
if(currentNode->total_ele < p) {   //check modification may need for root element check ,ie, wheter is initial element.
while(k < currentNode->current->k )
currentNode->current=currentNode->current->next;
node* temp=currentNode->current;
node* new_node;
new_node->k=k;
new_node->next=temp;
new_node->previous=currentNode->current->previous;
currentNode->current->previous->next=new_node;
}
else  //if leaf node is full
{mnode* tempe;

while(k < currentNode->current->k )
currentNode->current=currentNode->current->next;
node* temp=currentNode->current;

tempe=currentNode;

mnode* new_one;
new_one->next=currentNode->next;
int j=0;
if(currentNode->total_ele % 2)
{j=((j+1)/2)+1;}
else{j=(j+1)/2;}
int i=0;
currentNode->head=tempe->head;
currentNode->current=tempe->head;
currentNode->total_ele=j;
currentNode->is_leaf=true;
node* y;y=currentNode->head;
while(++i<j){
y=y->next;

}
k=y->k;
currentNode->tail=y;
currentNode->next=new_one;
new_one->head=y->next;
new_one->tail=tempe->tail;
new_one->current=new_one->head;
new_one->is_leaf=true;
new_one->total_ele=tempe->total_ele - j;
new_one->root=false;

// give new_one and new k value to parent node. How to do? (from 'finished <- false in text)
l:
if(stk.isempty()){ //rot node need to create
rootNode=new mnode;
rootNode->root=true;
rootNode->is_leaf=false;
rootNode->head->k=k;
rootNode->head->previous=NULL;
node* newnode;newnode->k=NULL;newnode->child=new_one;
rootNode->head->next=newnode;
rootNode->head->child=currentNode;
rootNode->tail=rootNode->head;
rootNode->current=rootNode->head;

}
else{ //not empty root
currentNode=stk.pop();
if(currentNode->total_ele < p){  //if parent node is not full 
currentNode->current=currentNode->head;
while(k < currentNode->current->k )
currentNode->current=currentNode->current->next;
node* temp=currentNode->current;
node* new_node;
new_node->k=k;
new_node->next=temp;
new_node->previous=currentNode->current->previous;
currentNode->current->previous->next=new_node;
}
else{  //if parent is full
mnode* tempe;
currentNode->current=currentNode->head;

while(k < currentNode->current->k )
currentNode->current=currentNode->current->next;
node* temp=currentNode->current;
tempe=currentNode;
tempe->tail=temp->previous;
node* pnode;
pnode->child=new_one;
pnode->k=k;
pnode->previous=tempe->tail;
pnode->next=temp;
tempe->tail->next=pnode;
tempe->tail=currentNode->tail;

// splitting parent node
int j=((p+1)/2);
int i=0;
currentNode->head=tempe->head;
currentNode->current=tempe->head;
currentNode->total_ele=j;
currentNode->is_leaf=true;
node* y;y=currentNode->head;
while(++i<j){
y=y->next;

}
k=y->k;mnode * new_one;
currentNode->tail=y;
currentNode->next=new_one;
new_one->head=y->next;
new_one->tail=tempe->tail;
new_one->current=new_one->head;
new_one->total_ele=tempe->total_ele - j;
goto l;
}

}

}


}

void display(mnode* currentNode){


}


int main(){
int n,k;
btree bt;
bt.ptr->root=true;
bt.ptr->is_leaf=true;
cout<<"Enter the maximum value of tree pointer\n";
cin>>p;
/*
while(true){
cout<<"\t Enter your choice\n";
cout<<"1. Insert\n"
<<"2. Display \n"
<<"3. Exit \n";
cin>>n;
switch(n){
case 1: 
cout<<"Enter value to insert\n";
cin>>k;
insert(k,bt.ptr);
break;
case 2: 
display(bt.ptr);
break;
default: return 0;
}} */

}
