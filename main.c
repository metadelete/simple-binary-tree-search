#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef struct TREE_NODE {
  struct TREE_NODE* right;
  struct TREE_NODE* left;
  struct TREE_NODE* parent;
  int value;
} TREE_NODE;

int MAX_NODE = 100;
TREE_NODE *parent = NULL;
TREE_NODE *crawler = NULL;
TREE_NODE *trail = NULL;
int kontrol = 0;

void insert_node(TREE_NODE **node, int);
TREE_NODE* find_value(int search);
static int _rand(){return rand()%1000 + 1;}

void usage(char *program_name) {
 printf("Usage: %s <message> <# to find value>\n", program_name);
 exit(1);
}


int main(int argc, char *argv[])
{

	if(argc > 2 || argc <= 1) 
		usage(argv[0]);

	int search = atoi(argv[1]);
	

	int *array;
	array = (int*)malloc(sizeof(int) * MAX_NODE);

  	TREE_NODE* node = NULL;
  	int counter = 0;

  	while(counter < MAX_NODE) {
  		array[counter] = _rand();
  		printf("%d\n", array[counter]);
  		counter++;
  	}
	printf("\n\n\n");


	// Binary Tree Process Begin
  	counter = 0;
  	while(counter < MAX_NODE) {
  		node = (TREE_NODE*)malloc(sizeof(TREE_NODE));
  		insert_node(&node ,array[counter]);
  		crawler = trail = parent;
  		counter++;
  	}
  	// Binary Tree Process End


  	crawler = parent;
  	  	
  	printf("%s\n","Begin process of finding");

  	TREE_NODE *result = find_value(search);
  	if(result == NULL) {
  		printf("%s\n","No Result");	
  	} else {
  		printf("%s\n","Found");	
  		printf("%p\n", result);
  	}
  	printf("%s\n","End process of finding");

  	printf("%s\n", "the end");
}
TREE_NODE* find_value(int search)
{
	if(search > crawler->value) {
		if(crawler->right != NULL) {
			crawler = crawler->right;
			find_value(search);
		} else {
			return crawler->right;
		}
	} else if(search < crawler->value) {
		if(crawler->left != NULL) {
			crawler = crawler->left;
			find_value(search);
		} else {
			return crawler->left;
		}
	} else if(search == crawler->value){
		return crawler;
	}
}
void insert_node(TREE_NODE **node, int value)
{
	if(parent == NULL) {
		TREE_NODE *child = (TREE_NODE*)malloc(sizeof(TREE_NODE));
		child->value = value;
		child->left = NULL;
		child->right = NULL;
		parent = child;
		return;
	} else {
		if(crawler == NULL) {
			TREE_NODE *child = (TREE_NODE*)malloc(sizeof(TREE_NODE));
			child->value = value;
			child->left = NULL;
			child->right = NULL;
			*node = child;
			switch(kontrol){case 0:trail->left = crawler;break;case 1:trail->right = crawler;break;}
			return;
		} else {
			if(value <= crawler->value) {
				trail = crawler;
				crawler = crawler->left;
				kontrol = 0;
				insert_node(&(crawler), value);
			} else {
				trail = crawler;
				crawler = crawler->right;
				kontrol = 1;
				insert_node(&(crawler), value);
			}
		}		
	}
}
