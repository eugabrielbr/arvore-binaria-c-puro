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
    new_node->height = 0;

    
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

    }

    root = height(root,root); //atualiza a altura dos nós do lado da árvore que foi inserido
    root = balancing(root); //chamada da função para os casos de balanceamento
    root = height(root,root); //atualiza os ponteiros pós balanceamento

    return root; //como a alteração ocorre diretamente no endereço do ponteiro root, left ou right, pode ser retornado a raiz normalmente para a main cm os ponteiros atualizados

    //root->height = whitch_is_bigger(whitch_is_the_height(root->left),whitch_is_the_height(root->right)); //recalcula a altura da raiz ate o novo nó inserido

}

node *balancing(node *root){

    int fbb = fb(root); //pega o fator de banceamento do nó enviado para função

    if (fbb < -1 && fb(root->right) <= 0){ //analisa a condição do fator de balanceamento do pai e seu filho direito para a rotação para esquerda
        root = left_rotation(root); //chamada da função rotação para esquerda
    }
    else if(fbb > 1 && fb(root->left) >= 0){//analisa a condição do fator de balanceamento do pai e seu filho direito para a rotação para direita
        root = right_rotation(root); //chamada da função rotação para direita
    }
    else if(fbb > 1 && fb(root->left) < 0){//analisa a condição do fator de balanceamento do pai e seu filho direito para a rotação para rotação dupla esquerda-direita
        root = left_right_rotation(root); //chamada da função rotação dupla esquerda-direita
    }
    else if(fbb < -1 && fb(root->right) > 0){//analisa a condição do fator de balanceamento do pai e seu filho direito para a rotação dupla direita-esquerda
        root = right_left_rotation(root); //chamada da função rotação dupla direita-esquerda
    }

    return root;
}

int calculating_height(node *root){ //calcula a altura total da arvore

    if (root == NULL){

        return -1; //caso nao tenha nenhum elemento ou chegue ao final da arvore
    }
    else{ 

        int right = calculating_height(root->right); //faz chamada recursiva de ambos lados até chegar no caso base
        int left = calculating_height(root->left); 
        
        if (right > left){ 
            
            return right + 1;  //ex simples pra explicar a recursividade: caso a esquerda do root valer -1 (NULL) e a direita tb, logo ele cai no else retornando -1+1 = 0, ou seja, so tem a raiz (root) na arvore cm altura 0
        
        }
        else{
            
            return left + 1;
        
        }
    }   

}

node *height(node *root, node *root2){ //chamei o mesmo ponteiro duas vezes porque ao retornar root retornaria null, entao retorno o mesmo endereço (só para retornar algo) mas cm os dados atualizados

    
    if (root == NULL){ //caso a arvore esteja vazia, nao tem o que buscar

        return NULL;

    }

    else{

        root->height = calculating_height(root); //faz a chamada da função que calcula a altura do nó de acordo com seus filhos/subárvores
        return root2; //retorna o mesmo endereço que a função recebeu, somente para retornar algo, ja que as alterações ocorrem direto no endereço dos nós
    }


}


int whitch_is_bigger(int a, int b){ //verifica qual é o maior entre a altura do nó A e altura do nó B

    if (a > b){ //se a for maior, retorna a
        
        return a;
    }
    else{ //caso nao, retorna b

        return b;
    }
}

int whitch_is_the_height(node *root){ //retorna a altura do nó

    if (root == NULL){ //se o nó for igual a null, logo a altura é igual a -1
        return -1;
    }
    else{ //caso nao, ele retorna a altura do campo "height"
        return root->height;
    }
}

int fb(node *root){ //retorna qual é o fator de balanceamento do nó

    if (root){
        return (whitch_is_the_height(root->left) - whitch_is_the_height(root->right));  //retorna a subtração da altura do filho esquerdo e direito, que é o fator de balanceamento
    }
    else{
        
        return 0; //caso não exista o nó (NULL) o fator de balanceamento é igual a 0
    
    }
}


node *left_rotation(node *father){ //rotacao a esquerda

    node *son,*son2; //criando um ponteiro para o filho direito do nó e um para o filho esquerdo do filho

    son = father->right; //guarda o filho1 direito do pai
    son2 = son->left; //guarda o filho2 esquerdo do filho1

    son->left = father; // o filho esquerdo do filho1 se torna o seu antigo pai
    father->right = son2; // o filho2 agora é filho direito do antigo pai do nó (que agora é filho do filho1)

    son->height = whitch_is_bigger(whitch_is_the_height(son->left),whitch_is_the_height(son->right)) + 1; //atualiza a altura dos nós depois da rotação
    father->height = whitch_is_bigger(whitch_is_the_height(father->left),whitch_is_the_height(father->right)) + 1;

    return son;

}

node *right_rotation(node *father){ //rotacao a direita

    node *son, *son2; //crio um ponteiro para o filho do pai e para o filho do filho

    son = father->left;  //guarda o endereço do filho1 esquerdo do pai
    son2 = son->right; //guarda o filho2 direito do filho1

    son->right = father; //o pai se torna o filho direito do filho1
    father->left = son2; //o filho2 se torna o filho esquerdo do pai (que agora é filho do filho1) 

    son->height = whitch_is_bigger(whitch_is_the_height(son->left),whitch_is_the_height(son->right)) + 1; //atualiza a altura dos nós depois da rotação
    father->height = whitch_is_bigger(whitch_is_the_height(father->left),whitch_is_the_height(father->right)) + 1;

    return son;

}

node *left_right_rotation(node *father){

    father->left = (left_rotation(father->left)); //faz a rotação a esquerda
    father = right_rotation(father); //faz a rotação a direita
    return father; //retorna o endereço com dados atualizados

}

node *right_left_rotation(node *father){

    father->right = (right_rotation(father->right)); //faz rotação a direita 
    return left_rotation(father); //retorna o endereço com dados atualizados pós rotação a esquerda 
}


node *delete(node *root, int cpf){ //funcao responsavel por deletar um determinado nó

    

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
        //printf("%s  ",root->name);
        printf("%d  ",root->cpf);
        //printf("%s  ",root->date_of_birth);
        //printf("%d  ",root->fone);
        fuction_print(root->right);
    }
}

