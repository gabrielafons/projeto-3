#include <stdio.h>
#include "funcoes.h"

int main(){
     funcao fs[] = {add,listar,deletar,salvar,carregar,alterar};
     Infos pessoais[CONTATOS];
    Infos trabalho[TRABALHO];

    int posPessoais = 0;
    int posTrabalho = 0;
    int opcao, lista;

do{
printf("Bem vindo! \n");
printf("------------------\n");
printf("0 - Sair\n");
printf("1 - Salvar Contatos\n");
printf("2 - Listar Contatos\n");
printf("3 - Deletar\n");
printf("4 - Salvar Agenda\n");
printf("5 - Carregar Agenda\n");
printf("6 - Alterar Contato\n");
printf("------------------\n");
printf("Escolha uma Opção: ");
scanf("%d",&opcao);
   clearBuffer(); // Limpar buffer após scanf

    if (opcao > 0 && opcao < 7) {
        printf("Escolha a lista (1 - Pessoal, 2 - Trabalho): ");
        scanf("%d", &lista);
        clearBuffer();

        Infos *infos;
        int *pos;

        if (lista == 1) {
            infos = pessoais;
            pos = &posPessoais;
        } else if (lista == 2) {
            infos = trabalho;
            pos = &posTrabalho;
        } else {
            printf("**Lista Inválida**\n");
            continue;
        }
        

            ERROS erro = fs[opcao - 1](infos, pos);
            if (erro != OK) {
                printf("Erro: %d\n", erro);
            }
            printf("------------------\n");
        } else if (opcao == 0) {
            printf("Até mais =( \n");
        } else {
            printf("**Opção Inválida**\n");
            printf("------------------\n");
        }
    } while (opcao > 0);

    return 0;
}