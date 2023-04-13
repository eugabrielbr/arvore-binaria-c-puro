#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

typedef struct Node{

    int cpf;
    char name[50];
    char date_of_birth[20];
    int fone;
    
    struct Node *left,*right;
    
} node;


//referências das funções

node *create_node();

node *insert_node(node *root, int cpf, char *name, char *birth, int fone);

void fuction_print(node *root);

node *delete(node *root, int cpf);

node *search(node *root, int cpf);

#endif