#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

node *create_node(){ //funcao que cria um novo nó

    node *new_node = (node*)malloc(sizeof(node)); //alocando um espaço de memoria para um novo no
    return new_node; //retornando o endereço desse espaço alocado

}   

node *insert_node(node *root, int cpf, char *name, char *birth, int fone){ //funcao que insere uma nova folha/subarvore

    node *new_node = create_node();
    strcpy(new_node->name,name);
    strcpy(new_node->date_of_birth,birth); //inserindo informacoes da pessoa em um novo nó 
    new_node->cpf = cpf;
    new_node->fone = fone;
    new_node->left = NULL;
    new_node->right = NULL;

    
    if (root == NULL){

        return new_node; //caso a raiz/left/right seja NULL, é retornado o endereço do novo nó já com os dados
    }
    else{

        if (new_node->cpf < root->cpf){
            root->left = insert_node(root->left,cpf,name,birth,fone); //se por acaso o novo cpf for menor que o cpf da raiz, a funcao recursiva percorre o lado esquerdo da arvore até entrar no caso base
            
        }
        else if(new_node->cpf > root->cpf){
            root->right = insert_node(root->right,cpf,name,birth,fone); //se por acaso o novo cpf for maior que o cpf da raiz, a funcao recursiva percorre o lado direita da arvore até entrar no caso base
        }
        return root; //como a alteração ocorre diretamente no endereço do ponteiro root, left ou right, pode ser retornado a raiz normalmente para a main cm os ponteiros atualizados
    }

}

node *delete(node *root, int cpf){ //funcao responsavel por deletar um nó

    if (root == NULL){

        return NULL;// caso root seja igual null, a arvore esta vazia
    }
    else{

        if (root->cpf == cpf){ //se o cpf (key) for igual ao cpf que o nó esta guardando 
            
            if (root->left == NULL && root->right == NULL){ // caso seja golha, é dado free no nó e retornado NULL para o endereço que estava guardando o nó com o cpf (key)
            
                free(root); 
                return NULL;
            }
            else{
                
                if (root->left == NULL || root->right == NULL){ //se os dois não forem igual a null, mas left OU right for, significa que o nó atual é uma subarvore com UM filho
                    
                    node *aux; //neste caso, foi criado um aux para que guarde este filho, para assim poder dar free o pai sem problemas

                    if (root->left){ 
                        
                        aux = root->left; // guardando o filho left no aux

                    }
                    else{                                            

                        aux = root->right; // guardando o filho right no aux
                    
                    }

                    free(root); // da free no pai
                    return aux;  //retorna o endereço do filho para o endereço que o pai estava guardado
                }
                else{

                    node *aux = root->right;
                    
                    while (aux->left != NULL){
                        aux = aux->left;
                    }
                    
                    node *aux_p = root;
                    
                    if (aux->right){

                        aux->right->right = root->right;
                        (*root) = (*aux);
                    }
                    else{
                        
                        aux->right = aux_p->right;
                        aux->left = aux_p->left;
                        (*root) = (*aux);

                    }
                    return root;
            
                }
            }
        }
        else{

            if (cpf < root->cpf){ //caso o cpf (key) seja menor que o do nó atual, a recursao percorre o lado esquerdo da arvore até entrar em um dos casos bases
                
                root->left = delete(root->left,cpf);

            }
            else{

                root->right = delete(root->right,cpf); //caso o cpf (key) seja maior que o do nó atual, a recursao percorre o lado direito da arvore até entrar em um dos casos bases
            }
            return root; //como a alteração ocorre diretamente no endereço do ponteiro root, left ou right, pode ser retornado a raiz normalmente para a main cm os ponteiros atualizados
        }
    }

}


node *search(node *root, int cpf){ //função de buscar pessoas na arvore

    if (root == NULL){ //caso a arvore esteja vazia, nao tem o que buscar

        return NULL;

    }

    else{

        if(root->cpf == cpf){ //caso a raiz guarde o cpf procurado, reu endereço é retornado
            return root; //ao entrar no caso base, a funcao retorna o endereço do nó que guarda a chave de busca (cpf)
        }
        else{ //caso nao, a funcao recursiva recebe o endereço dos nós left e right até encontrar o cpf correspondente

            if (cpf < root->cpf){ //se o cpf (key) for menor que o cpf do nó atual, a busca ocorre pela esquerda

                return search(root->left,cpf);
            }
            else{ //se o cpf (key) for maior que o cpf do nó atual, a busca ocorre pela direita

                return search(root->right,cpf);
            }

        }
    }

}

void fuction_print(node *root){

    if (root){
        
        fuction_print(root->left);
        printf("%s  ",root->name);
        printf("%d  ",root->cpf);
        printf("%s  ",root->date_of_birth);
        printf("%d  ",root->fone);
        fuction_print(root->right);
    }
}

