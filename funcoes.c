#include <stdio.h>
#include "funcoes.h"

ERROS add(Infos infos[], int *pos) {
  printf("Entre com seu nome: ");
  fgets(infos[*pos].nome, sizeof(infos[*pos].nome), stdin); 
  infos[*pos].nome[strcspn(infos[*pos].nome, "\n")] = 0; 
 
  
  while (1) {
      printf("Entre com seu telefone (Ex: 11-123456789): ");
      fgets(infos[*pos].telefone, sizeof(infos[*pos].telefone), stdin);
      infos[*pos].telefone[strcspn(infos[*pos].telefone, "\n")] = 0;

      
      if (strlen(infos[*pos].telefone) >= 11) {
          break;  
      } else {
          printf("Telefone inválido! Digite novamente.\n");
      }
  }

  printf("Entre com seu email: ");
  
  scanf("%s", infos[*pos].email);
  clearBuffer(); 

    *pos = *pos + 1;

    return OK;
}



ERROS listar(Infos infos[], int *pos){
    if(*pos == 0)
        return SEM_TAREFAS;

    for(int i=0; i<*pos; i++){
                printf("nome: %s \ttelefone: %s \temail: %s \t\n", infos[i].nome, infos[i].telefone, infos[i].email);
    }

    return OK;
}



void normalizar_telefone(char *telefone) {
    int j = 0;
    for (int i = 0; telefone[i] != '\0'; i++) {
        if (isdigit(telefone[i])) {
            telefone[j++] = telefone[i];  
        }
    }
    telefone[j] = '\0';  
}

ERROS deletar(Infos infos[], int *pos) {
    if (*pos == 0) {
        return SEM_TAREFAS;  
    }

    char telefone_deletar[15];
    printf("Entre com o número do contato a ser deletado: ");
    fgets(telefone_deletar, sizeof(telefone_deletar), stdin);
    telefone_deletar[strcspn(telefone_deletar, "\n")] = 0;

   
    normalizar_telefone(telefone_deletar);

    int encontrado = -1;
    for (int i = 0; i < *pos; i++) {
        char telefone_comparacao[15];
        strcpy(telefone_comparacao, infos[i].telefone);
        normalizar_telefone(telefone_comparacao);

        if (strcmp(telefone_comparacao, telefone_deletar) == 0) {  
            encontrado = i;  
            break;
        }
    }

    if (encontrado == -1) {
        return NAO_ENCONTRADO;  
    }

    
    for (int i = encontrado; i < *pos - 1; i++) {
        infos[i] = infos[i + 1];  
    }

    (*pos)--;  

    ERROS erro_salvar = salvar(infos, pos); 
  if (erro_salvar != OK) {
    return erro_salvar;  
  }


    return OK;
}




ERROS salvar(Infos infos[], int *pos){
    FILE *f = fopen("info.bin", "wb");
    if(f == NULL)
        return ABRIR;

    int qtd = fwrite(infos, TOTAL, sizeof(Infos), f);
    if(qtd == 0)
        return ESCREVER;

    qtd = fwrite(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return ESCREVER;

    if(fclose(f))
        return FECHAR;

    return OK;
}




ERROS carregar(Infos infos[], int *pos){
    FILE *f = fopen("info.bin", "rb");
    if(f == NULL)
        return ABRIR;

    int qtd = fread(infos, TOTAL, sizeof(Infos), f);
    if(qtd == 0)
        return LER;

    qtd = fread(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return LER;

    if(fclose(f))
        return FECHAR;

    return OK;

}

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}