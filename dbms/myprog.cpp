#include<iostream>
#include<string.h>

using namespace std;

int p;
struct mnode;
struct node{
node *next;
node *parent;
mnode* child;
int k;



};
struct mnode{
node * head;
node * tail;
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
struct node * p;
p->child=NULL;
p->next=NULL;
p->parent=NULL;
}
};

void insert(int k,mnode* rootNode){
mnode* currentNode=rootNode;
stack s;int q=0;
while(!currentNode->is_leaf && (currentNode->head!=NULL)){
s.push(currentNode);
q=currentNode->total_ele;
if(k<=currentNode->head->k)
currentNode=currentNode->head->child;
else if(k>currentNode->tail->k)
{
currentNode=currentNode->tail->child;

}

}

}



int main(){
mnode *currentNode;
currentNode->root=true;
cout<<"Enter the maximum value of tree pointer\n";
cin>>p;

}
