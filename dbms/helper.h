#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<stdbool.h>

typedef struct node {
	void ** ttp;
	int * keys;
	struct node * parent;
	bool is_leaf;
	int num_keys;
	struct node * next;
} node;

typedef struct record {
	int value;
} record;
void printtree(node*);

node * make_node( void );
int path_to_root( node * root, node * child );
node * insert_into_node_after_splitting(node * root, node * old_node, int left_index, int key, node * right);
node * insert_into_parent(node * root, node * left, int key, node * right) ;
node * insert_into_node(node * root, node * n,int left_index, int key, node * right) ;
int get_left_index(node * parent, node * left) ;
node * remove_val(node * n, int key, node * pointer) ;
node* insert(node*,int,int);
node * redistribute_nodes(node * root, node * n, node * neighbor, int neighbor_index, int k_prime_index, int k_prime);
record * check( node * root, int key, bool verbose );
node * insert_into_leaf( node * , int , record *  );
int get_neighbor_index( node * n ) ;
node * coalesce_nodes(node * root, node * n, node * neighbor, int neighbor_index, int k_prime);
node * delete_entry( node * root, node * n, int key, void * pointer );
node * split_and_insert(node * , node * , int , record * );
record * find( node * root, int key, bool verbose );
record* makerec(int);
node * make_leaf( void );
node * adjust_root(node * root) ;
node * find_leaf( node * root, int key, bool verbose );
node * create_tree(int key, record * pointer);
node * queue = NULL;
bool vout = false;
