#include <stdio.h>

int main(){
int opcao;
do{
printf("Bem vindo! \n");
printf("0 - Sair\n");
printf("1 - Salvar Contatos\n");
printf("2 - Listar Contatos\n");
printf("3 - Deletar\n");
printf("4 - Salvar Agenda\n");
printf("5 - Carregar Agenda\n");
printf("Escolha uma Opção: ");
scanf("%d",&opcao);
if(opcao > 0 && opcao< 5){
//chamada da função
printf("parabens voce digitou um numero correto\n");
}
else{
printf("Opção Invalida");
}
}while(opcao >0);    
}