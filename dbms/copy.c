#include "helper.h"
int p;


int devide( int length ) {
	if (length % 2 == 0)
		return length/2;
	else
		return length/2 + 1;
}

node* insert(node* root,int key,int value){
node * leaf;
record * pr;
if(check(root,key,false) !=NULL )
return root;
pr=makerec(value);
if(root==NULL)
return create_tree(key,pr);
leaf = find_leaf(root, key, false);
if (leaf->num_keys < p - 1) {
leaf = insert_into_leaf(leaf, key, pr);
return root;
}
	
return split_and_insert(root, leaf, key, pr);	

}

node * adjust_root(node * root) {

node * new_root;

	
if (root->num_keys > 0)
return root;

	
if (!root->is_leaf) {
new_root = root->ttp[0];
new_root->parent = NULL;
}

	
else
new_root = NULL;


return new_root;
}

node * coalesce_nodes(node * root, node * n, node * neighbor, int neighbor_index, int k_prime) {

int i, j, neighbor_insertion_index, n_start, n_end, new_k_prime;
node * tmp;
bool split;
	
if (neighbor_index == -1) {
tmp = n;
n = neighbor;
neighbor = tmp;
}

	

neighbor_insertion_index = neighbor->num_keys;

	

split = false;

	

if (!n->is_leaf) {

		

neighbor->keys[neighbor_insertion_index] = k_prime;
neighbor->num_keys++;



n_end = n->num_keys;

n_start = 0; // Only used in this special case.
if (n->num_keys + neighbor->num_keys >= p) {
split = true;
n_end = devide(p) - 2;
}

for (i = neighbor_insertion_index + 1, j = 0; j < n_end; i++, j++) {
neighbor->keys[i] = n->keys[j];
neighbor->ttp[i] = n->ttp[j];
neighbor->num_keys++;
n->num_keys--;
n_start++;
}

		

neighbor->ttp[i] = n->ttp[j];

		
if (split) {
new_k_prime = n->keys[n_start];
for (i = 0, j = n_start + 1; i < n->num_keys; i++, j++) {
n->keys[i] = n->keys[j];
n->ttp[i] = n->ttp[j];
}
n->ttp[i] = n->ttp[j];
n->num_keys--;
}

		

for (i = 0; i < neighbor->num_keys + 1; i++) {
tmp = (node *)neighbor->ttp[i];
tmp->parent = neighbor;
}
}

	

else {
for (i = neighbor_insertion_index, j = 0; j < n->num_keys; i++, j++) {
neighbor->keys[i] = n->keys[j];
neighbor->ttp[i] = n->ttp[j];
neighbor->num_keys++;
}
neighbor->ttp[p - 1] = n->ttp[p - 1];
}

if (!split) {
root = delete_entry(root, n->parent, k_prime, n);



}
else
for (i = 0; i < n->parent->num_keys; i++)
if (n->parent->ttp[i + 1] == n) {
n->parent->keys[i] = new_k_prime;
break;
}

return root;

}


node * redistribute_nodes(node * root, node * n, node * neighbor, int neighbor_index, int k_prime_index, int k_prime) {  

int i;
node * tmp;

	

if (neighbor_index != -1) {
if (!n->is_leaf)
n->ttp[n->num_keys + 1] = n->ttp[n->num_keys];
for (i = n->num_keys; i > 0; i--) {
n->keys[i] = n->keys[i - 1];
n->ttp[i] = n->ttp[i - 1];
}
if (!n->is_leaf) {
n->ttp[0] = neighbor->ttp[neighbor->num_keys];
tmp = (node *)n->ttp[0];
tmp->parent = n;
neighbor->ttp[neighbor->num_keys] = NULL;
n->keys[0] = k_prime;
n->parent->keys[k_prime_index] = neighbor->keys[neighbor->num_keys - 1];
}
else {
n->ttp[0] = neighbor->ttp[neighbor->num_keys - 1];
neighbor->ttp[neighbor->num_keys - 1] = NULL;
n->keys[0] = neighbor->keys[neighbor->num_keys - 1];
n->parent->keys[k_prime_index] = n->keys[0];
}
}

	

else {  
if (n->is_leaf) {
n->keys[n->num_keys] = neighbor->keys[0];
n->ttp[n->num_keys] = neighbor->ttp[0];
n->parent->keys[k_prime_index] = neighbor->keys[1];
}
else {
n->keys[n->num_keys] = k_prime;
n->ttp[n->num_keys + 1] = neighbor->ttp[0];
tmp = (node *)n->ttp[n->num_keys + 1];
tmp->parent = n;
n->parent->keys[k_prime_index] = neighbor->keys[0];
}
for (i = 0; i < neighbor->num_keys; i++) {
neighbor->keys[i] = neighbor->keys[i + 1];
neighbor->ttp[i] = neighbor->ttp[i + 1];
}
if (!n->is_leaf)
neighbor->ttp[i] = neighbor->ttp[i + 1];
}


n->num_keys++;
neighbor->num_keys--;

return root;
}




node * insert_into_new_root(node * left, int key, node * right) {

node * root = make_node();
root->keys[0] = key;
root->ttp[0] = left;
root->ttp[1] = right;
root->num_keys++;
root->parent = NULL;
left->parent = root;
right->parent = root;
return root;
}

int get_neighbor_index( node * n ) {

int i;

	 
	
for (i = 0; i <= n->parent->num_keys; i++)
if (n->parent->ttp[i] == n)
return i - 1;

	// Error state.
printf("Search for nonexistent pointer to node in parent.\n");
printf("Node:  %#lx\n", (unsigned long)n);
exit(1);
}

node * insert_into_node(node * root, node * n,int left_index, int key, node * right) {
int i;

for (i = n->num_keys; i > left_index; i--) {
n->ttp[i + 1] = n->ttp[i];
n->keys[i] = n->keys[i - 1];
}
n->ttp[left_index + 1] = right;
n->keys[left_index] = key;
n->num_keys++;
return root;
}

int path_to_root( node * root, node * child ) {
int length = 0;
node * c = child;
while (c != root) {
c = c->parent;
length++;
}
return length;
}


void enqueue( node * new_node ) {
node * c;
if (queue == NULL) {
queue = new_node;
queue->next = NULL;
}
else {
c = queue;
while(c->next != NULL) {
c = c->next;
}
c->next = new_node;
new_node->next = NULL;
}
}

node * dequeue( void ) {
node * n = queue;
queue = queue->next;
n->next = NULL;
return n;
}

void printtree( node * root ) {

node * n = NULL;
int i = 0;
int rank = 0;
int new_rank = 0;
if (root == NULL) {
printf("Empty tree.\n");
return;
}
queue = NULL;
enqueue(root);
while( queue != NULL ) {
n = dequeue();
if (n->parent != NULL && n == n->parent->ttp[0]) {
new_rank = path_to_root( root, n );
if (new_rank != rank) {
rank = new_rank;
printf("\n");
}
}
if (vout) 
printf("(%lx)", (unsigned long)n);
for (i = 0; i < n->num_keys; i++) {
if (vout)
printf("%lx ", (unsigned long)n->ttp[i]);
printf("%d ", n->keys[i]);
}
if (!n->is_leaf)
for (i = 0; i <= n->num_keys; i++)
enqueue(n->ttp[i]);
if (vout) {
if (n->is_leaf) 
printf("%lx ", (unsigned long)n->ttp[p - 1]);
else
printf("%lx ", (unsigned long)n->ttp[n->num_keys]);
}
printf("- ");
}
printf("\n");
}

int get_left_index(node * parent, node * left) {

int left_index = 0;
while (left_index <= parent->num_keys && 
parent->ttp[left_index] != left)
left_index++;
return left_index;
}



node * insert_into_parent(node * root, node * left, int key, node * right) {

int left_index;
node * parent;
parent = left->parent;

if (parent == NULL)
return insert_into_new_root(left, key, right);

	
left_index = get_left_index(parent, left);


	

if (parent->num_keys < p - 1)
return insert_into_node(root, parent, left_index, key, right);

	
return insert_into_node_after_splitting(root, parent, left_index, key, right);
}

node * insert_into_node_after_splitting(node * root, node * old_node, int left_index, int key, node * right) {

int i, j, split, k_prime;
node * new_node, * child;
int * temp_keys;
node ** temp_ttp;



temp_ttp = malloc( (p + 1) * sizeof(node *) );
if (temp_ttp == NULL) {
perror("Temporary ttp array for splitting nodes.");
exit(1);
}
temp_keys = malloc( p * sizeof(int) );
if (temp_keys == NULL) {
perror("Temporary keys array for splitting nodes.");
exit(1);
}

for (i = 0, j = 0; i < old_node->num_keys + 1; i++, j++) {
if (j == left_index + 1) j++;
temp_ttp[j] = old_node->ttp[i];
}

for (i = 0, j = 0; i < old_node->num_keys; i++, j++) {
if (j == left_index) j++;
temp_keys[j] = old_node->keys[i];
}

temp_ttp[left_index + 1] = right;
temp_keys[left_index] = key;


split = devide(p);
new_node = make_node();
old_node->num_keys = 0;
for (i = 0; i < split - 1; i++) {
old_node->ttp[i] = temp_ttp[i];
old_node->keys[i] = temp_keys[i];
old_node->num_keys++;
}
old_node->ttp[i] = temp_ttp[i];
k_prime = temp_keys[split - 1];
for (++i, j = 0; i < p; i++, j++) {
new_node->ttp[j] = temp_ttp[i];
new_node->keys[j] = temp_keys[i];
new_node->num_keys++;
}
new_node->ttp[j] = temp_ttp[i];

new_node->parent = old_node->parent;
for (i = 0; i <= new_node->num_keys; i++) {
child = new_node->ttp[i];
child->parent = new_node;
}


return insert_into_parent(root, old_node, k_prime, new_node);
}


node * make_node( void ) {
node * new_node;
new_node = malloc(sizeof(node));
if (new_node == NULL) {
perror("Node creation.");
exit(1);
}
new_node->keys = malloc( (p - 1) * sizeof(int) );
if (new_node->keys == NULL) {
perror("New node keys array.");
exit(1);
}
new_node->ttp = malloc( p * sizeof(void *) );
if (new_node->ttp == NULL) {
perror("New node ttp array.");
exit(1);
}
new_node->is_leaf = false;
new_node->num_keys = 0;
new_node->parent = NULL;
new_node->next = NULL;
return new_node;
}


node * insert_into_leaf( node * leaf, int key, record * pointer ) {

int i, insertion_point;

insertion_point = 0;
while (insertion_point < leaf->num_keys && leaf->keys[insertion_point] < key)
insertion_point++;
	for (i = leaf->num_keys; i > insertion_point; i--) {
		leaf->keys[i] = leaf->keys[i - 1];
		leaf->ttp[i] = leaf->ttp[i - 1];
	}
	leaf->keys[insertion_point] = key;
	leaf->ttp[insertion_point] = pointer;
	leaf->num_keys++;
	return leaf;
}

node * make_leaf( void ) {
	node * leaf = make_node();
	leaf->is_leaf = true;
	return leaf;
}

void search(node * root, int key, bool verbose) {
	record * r = check(root, key, verbose);
	if (r == NULL)
		printf("Record not found under key %d.\n", key);
	else 
		printf("Record at %lx -- key %d, value %d.\n",
				(unsigned long)r, key, r->value);
}



node * remove_val(node * n, int key, node * pointer) {

	int i, num_ttp;

	// Remove the key and shift other keys accordingly.
	i = 0;
	while (n->keys[i] != key)
		i++;
	for (++i; i < n->num_keys; i++)
		n->keys[i - 1] = n->keys[i];

	// Remove the pointer and shift other ttp accordingly.
	// First determine number of ttp.
	num_ttp = n->is_leaf ? n->num_keys : n->num_keys + 1;
	i = 0;
	while (n->ttp[i] != pointer)
		i++;
	for (++i; i < num_ttp; i++)
		n->ttp[i - 1] = n->ttp[i];


	// One key fewer.
	n->num_keys--;

	// Set the other ttp to NULL for tidiness.
	// A leaf uses the last pointer to point to the next leaf.
	if (n->is_leaf)
		for (i = n->num_keys; i < p - 1; i++)
			n->ttp[i] = NULL;
	else
		for (i = n->num_keys + 1; i < p; i++)
			n->ttp[i] = NULL;

	return n;
}

node * delete_entry( node * root, node * n, int key, void * pointer ) {

	int min_keys;
	node * neighbor;
	int neighbor_index;
	int k_prime_index, k_prime;
	int capacity;

	n = remove_val(n, key, pointer);

	

	if (n == root) 
		return adjust_root(root);



	min_keys = n->is_leaf ? devide(p - 1) : devide(p) - 1;

	

	if (n->num_keys >= min_keys)
		return root;




	neighbor_index = get_neighbor_index( n );
	k_prime_index = neighbor_index == -1 ? 0 : neighbor_index;
	k_prime = n->parent->keys[k_prime_index];
	neighbor = neighbor_index == -1 ? n->parent->ttp[1] : 
		n->parent->ttp[neighbor_index];

	capacity = n->is_leaf ? p : p - 1;

	/* Coalescence. */

	if (neighbor->num_keys + n->num_keys < capacity)
		return coalesce_nodes(root, n, neighbor, neighbor_index, k_prime);

	/* Redistribution. */

	else
		return redistribute_nodes(root, n, neighbor, neighbor_index, k_prime_index, k_prime);
}


node * split_and_insert(node * root, node * leaf, int key, record * pointer) {

	node * new_leaf;
	int * temp_keys;
	void ** temp_ttp;
	int insertion_index, split, new_key, i, j;

	new_leaf = make_leaf();

	temp_keys = malloc( p * sizeof(int) );
	if (temp_keys == NULL) {
		perror("Temporary keys array.");
		exit(1);
	}

	temp_ttp = malloc( p * sizeof(void *) );
	if (temp_ttp == NULL) {
		perror("Temporary ttp array.");
		exit(1);
	}

	insertion_index = 0;
	while (insertion_index < p - 1 && leaf->keys[insertion_index] < key)
		insertion_index++;

	for (i = 0, j = 0; i < leaf->num_keys; i++, j++) {
		if (j == insertion_index) j++;
		temp_keys[j] = leaf->keys[i];
		temp_ttp[j] = leaf->ttp[i];
	}

	temp_keys[insertion_index] = key;
	temp_ttp[insertion_index] = pointer;

	leaf->num_keys = 0;

	split = devide(p - 1);

	for (i = 0; i < split; i++) {
		leaf->ttp[i] = temp_ttp[i];
		leaf->keys[i] = temp_keys[i];
		leaf->num_keys++;
	}

	for (i = split, j = 0; i < p; i++, j++) {
		new_leaf->ttp[j] = temp_ttp[i];
		new_leaf->keys[j] = temp_keys[i];
		new_leaf->num_keys++;
	}

	//free(temp_ttp);
	//free(temp_keys);

	new_leaf->ttp[p - 1] = leaf->ttp[p - 1];
	leaf->ttp[p - 1] = new_leaf;

	for (i = leaf->num_keys; i < p - 1; i++)
		leaf->ttp[i] = NULL;
	for (i = new_leaf->num_keys; i < p - 1; i++)
		new_leaf->ttp[i] = NULL;

	new_leaf->parent = leaf->parent;
	new_key = new_leaf->keys[0];

	return insert_into_parent(root, leaf, new_key, new_leaf);
}



record * check( node * root, int key, bool verbose ) {
	int i = 0;
	node * c = find_leaf( root, key, verbose );
	if (c == NULL) return NULL;
	for (i = 0; i < c->num_keys; i++)
		if (c->keys[i] == key) break;
	if (i == c->num_keys) 
		return NULL;
	else
		return (record *)c->ttp[i];
}

record * makerec(int value) {
	record * new_record = (record *)malloc(sizeof(record));
	if (new_record == NULL) {
		perror("Record creation.");
		exit(1);
	}
	else {
		new_record->value = value;
	}
	return new_record;
}

node * create_tree(int key, record * pointer) {

	node * root = make_leaf();
	root->keys[0] = key;
	root->ttp[0] = pointer;
	root->ttp[p - 1] = NULL;
	root->parent = NULL;
	root->num_keys++;
	return root;
}

node * find_leaf( node * root, int key, bool verbose ) {
int i = 0;
node * c = root;
if (c == NULL) {
if (verbose) 
printf("Empty tree.\n");
return c;
}
while (!c->is_leaf) {
if (verbose) {
printf("[");
for (i = 0; i < c->num_keys - 1; i++)
printf("%d ", c->keys[i]);
printf("%d] ", c->keys[i]);
}
i = 0;
while (i < c->num_keys) {
if (key >= c->keys[i]) i++;
else break;
}
if (verbose)
printf("%d ->\n", i);
c = (node *)c->ttp[i];
}
if (verbose) {
printf("Leaf [");
for (i = 0; i < c->num_keys - 1; i++)
printf("%d ", c->keys[i]);
printf("%d] ->\n", c->keys[i]);
}
return c;
}
node * del(node * root, int key) {

node * key_leaf;
record * key_record;

key_record = check(root, key, false);
key_leaf = find_leaf(root, key, false);
if (key_record != NULL && key_leaf != NULL) {
root = delete_entry(root, key_leaf, key, key_record);

}
return root;
}


int main(int argc, char ** argv){
node * root;
root =NULL;
//vout=false;
int n,input;
if(argc<2){
fprintf(stderr," P  value not specified terminating...",0);
exit(1);
}
if(argc==2){
p=atoi(argv[1]);
}
else{printf("too many argument.. Terminating");exit(1);}

printf("\t Enter your choice\n");
printf("1. Insert\n"
"2. Display \n"
"3. Search \n"
"4. Delete \n"
"5. Exit \n");

while(scanf("%d",&n)){

switch(n){
case 1: printf("Enter the value to insert :");scanf("%d",&input);root=insert(root,input,input);break;
case 2:printtree(root);break;
case 3:printf("Enter value to search :");scanf("%d",&input);search(root,input,false);break;
case 4:scanf("%d",&input);root=del(root,input);break;
case 5: exit(0);
default: printf("Invalid Input terminating...");exit(1);
}

printf("Enter your choice\n");
}

}
