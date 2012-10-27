#include<iostream>
#include<string.h>

using namespace std;

int p;
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

btree(){
struct mnode * ptr;
ptr->head=NULL;
ptr->tail=NULL;
ptr->current=NULL;
struct node * p;
p->child=NULL;
p->next=NULL;
p->previous=NULL;
}
};

void insert(int k,mnode* rootNode){
mnode* currentNode=rootNode;
currentNode->current=currentNode->head;
stack s;int q=0;
while( (! currentNode->is_leaf) && (currentNode->head !=NULL)){
s.push(currentNode);
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
if((currentNode->total_ele < p) && (currentNode->total_ele !=0) ){
while(k < currentNode->current->k )
currentNode->current=currentNode->current->next;
node* temp=currentNode->current;
node* new_node;
new_node->k=k;
new_node->next=temp;
new_node->previous=currentNode->current->previous;
currentNode->current->previous->next=new_node;
} 
if((currentNode->total_ele < p) && (currentNode->total_ele ==0) ){
while(k < currentNode->current->k )
currentNode->current=currentNode->current->next;
node* temp=currentNode->current;
node* new_node;
new_node->k=k;
new_node->next=temp;
new_node->previous=currentNode->current->previous;
currentNode->current->previous->next=new_node;
} 
}



int main(){
mnode *currentNode;
currentNode->root=true;
cout<<"Enter the maximum value of tree pointer\n";
cin>>p;

}
