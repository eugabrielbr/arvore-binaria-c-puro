#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(){

    node *root = NULL, *result_seach = NULL;
    int cpf = 0,fone = 0,option = 0,remover = 0;
    char name[50], birth[20];

    do { 
        
        printf("==============================================================================\n");
        printf("O que deseja fazer?\n\n");
        printf("[1] - Cadastro\n[2] - Remocao\n[3] - Busca\n[4] - Sair\n");
        printf("==============================================================================\n");
        scanf("%d",&option);



        switch (option){

            case 1:
                
                printf("Insira o nome: ");
                scanf("%s", &name);
                printf("Insira o cpf: ");
                scanf("%d", &cpf);
                printf("Insira a data de nascimento: ");
                scanf("%s",&birth);
                printf("Insira o telefone: ");
                scanf("%d",&fone);
                root = insert_node(root,cpf,name,birth,fone);
                break;
            
            case 2:

                printf("Insira o cpf da pessoa que deseja remover: ");
                scanf("%d",&remover);
                
                result_seach = search(root,remover);

                if (result_seach){
                    
                    root = delete(root,remover);
                    printf("\nOperacao efetuada com sucesso!\n");
                
                }
                else{
                    printf("\nNenhum cadastro encontrado!\n");
                }
                
                break;
            
            case 3:

                printf("Insira o cpf da pessoa que deseja buscar: ");
                scanf("%d",&remover);
                result_seach = search(root,remover);

                if (result_seach){

                    printf("\nNome --> %s\n",result_seach->name);
                    printf("Cpf --> %d\n",result_seach->cpf);
                    printf("Data de nascimento --> %s\n",result_seach->date_of_birth);
                    printf("Telefone --> %d\n",result_seach->fone);
                }
                else{

                    printf("\nNada encontrado na busca\n");
                }
                break;

            case 4:
                
                option = 4;
                break;

            default:

                printf("Opcao invalida!\n");
                break;
        }

    } while (option != 4);
    

    //fuction_print(root);


    return 0;
    
}