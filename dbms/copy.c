#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
int p;
struct node {
	void ** pointers;
	int * keys;
	struct node * parent;
	bool is_leaf;
	int num_keys;
	struct node * next;
};
int main(int argc, char ** argv){
node * root;
root =NULL;
//vout=false;
int n;
if(argc<2){
fprintf(stderr," P  value not specified terminating...",0);
exit(1);
}
if(argc==2){
p=atoi(argv[1]);
}
else{printf("too many argument.. Terminating");exit(1);}

cout<<"\t Enter your choice\n";
cout<<"1. Insert\n"
<<"2. Display \n"
<<"3. Search \n"
<<"4. Delete \n";

while(scanf("%d",&n)){
switch(n){
case 1: printf("Enter the value to insert :");scanf("%d",&input);root=insert(root,input,input);break;
case 2:ptree(root);break;
case 3:printf("Enter value to search :");scanf("%d",&input);search(root,input);
case 4:root=del(root);break;
}


}

}
