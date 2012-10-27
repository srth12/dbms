#include<iostream>
#include<stdio.h>
#include<fstream>
#include<stdlib.h>
#include<sstream>
#include<string.h>
#include<stdlib.h>
using namespace std;
//currently duing 21/9/12
struct list{
list *next;
list *prev;
char type;
int value;
}
class queue{
struct list *haed,*tail;
public:
queue(){
head=NULL;tail=NULL;
}
void enque(list *k)
{
		struct list *ptr;
		ptr=new list;
		ptr->value=k;
		ptr->next=NULL;
		if(head==NULL)
		head=ptr;
		else
		tail->next=ptr;
		tail=ptr;
}
list* deq()
	{
		if(head==NULL)
		return NULL;
		struct list *temp;
		temp=head;
		head=head->next;
		return temp->value->next;
		delete temp;
	}
};
void nonpreemtive(){
queue ioq,readyq;


}
void preemtive(){


}

int main(){
int x=0,i=0,j=0,b[10];
double m[10][100];
char junk;
int boolean=0;
 FILE *fp;
    char ch;
   fp = fopen("2.txt","r");
 if ( fp == NULL )
 {
        puts ( "Cannot open source file");
 }

    //count the number of lines
   int lines=0;
    char c;
    while((c = fgetc(fp)) != EOF)
    {   
        if(c == '\n')
        {    lines++;i++;boolean=0;j=0;continue;}
	if(c==' '){
		j++;boolean=0;b[i]=j;
	continue;}
	
	if(boolean){
	m[i][j]=m[i][j]*10+atoi(&c);	
	}
	else{
	m[i][j]=atoi(&c);boolean=1;	
	}
}	
    
lines+=1;
//cout<<i+1<<" "<<j<<" "<<b[0]+1;
cout<<"\n";
//displaying to check the output is expected
for(int i=0;i<lines;i++){
for(int j=0;j<=b[i];j++)
cout<<m[i][j]<<" ";
cout<<"\n";}
fclose(fp);
cout<<"Enter your choice\n"
<<"1.Pre-emptive\n"
<<"2.Non Pre-emptive\n";
int choice;
cin>>choice;
switch(choice){
case 1: preemtive();
break;
case 2: nonpreemtive();
break;
default: cout<<"Invalid Input\n";
break;
}
}
