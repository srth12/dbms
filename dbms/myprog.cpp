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
ptr->next=NULL;
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

if(stk->current==0){ //rot node need to create



}

}


}




int main(){
mnode *currentNode;
currentNode->root=true;
cout<<"Enter the maximum value of tree pointer\n";
cin>>p;

}
