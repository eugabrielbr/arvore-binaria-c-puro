#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

typedef struct Node{

    int cpf;
    char name[50];
    char date_of_birth[20];
    int fone;
    
    struct Node *left,*right;
    int height;

} node;


//referências das funções

node *create_node();

node *insert_node(node *root, int cpf, char *name, char *birth, int fone);

node *delete(node *root, int cpf);

node *search(node *root, int cpf);

node *left_rotation(node *father);

node *right_rotation(node *father);

node *left_right_rotation(node *father);

node *right_left_rotation(node *father);

node *height(node *root,node *root2);

node *balancing(node *root);

int calculating_height(node *root);

int whitch_is_bigger(int a, int b);

int whitch_is_the_height(node *root);

int fb(node *root);

void fuction_print(node *root);


#endif
