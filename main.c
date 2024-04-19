#include <stdio.h>
#include "funcoes.h"

int main(){
int opcao;
do{
printf("Bem vindo! \n");
printf("------------------\n");
printf("0 - Sair\n");
printf("1 - Salvar Contatos\n");
printf("2 - Listar Contatos\n");
printf("3 - Deletar\n");
printf("4 - Salvar Agenda\n");
printf("5 - Carregar Agenda\n");
printf("------------------\n");
printf("Escolha uma Opção: ");
scanf("%d",&opcao);
if(opcao > 0 && opcao< 6){
//chamada da função
tarefas(opcao);
printf("------------------\n");
}
else{
printf("**Opção Invalida**\n");
printf("------------------\n");
}
}while(opcao >0);    
}