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