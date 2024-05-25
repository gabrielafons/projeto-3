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

  while(1){
        
        printf("Entre com seu email: ");
        scanf("%s", infos[*pos].email);
        clearBuffer();

        ERROS erro = validar_email(infos[*pos].email);
        if (erro == OK) {
            break;
        } else if (erro == EMAIL_INVALIDO) {
            printf("Email inválido! Digite novamente.\n");
        } else {
            return erro;
        }


    }
  

    *pos = *pos + 1;

    return OK;
}





ERROS validar_email(const char *email) {
    const char *arroba = strchr(email, '@');
    if (!arroba || arroba == email || arroba == email + strlen(email) - 1) {
        return EMAIL_INVALIDO;
    }
    const char *ponto = strchr(arroba + 1, '.');
    if (!ponto || ponto == arroba + 1 || ponto == email + strlen(email) - 1) {
        return EMAIL_INVALIDO;
    }
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

ERROS alterar(Infos infos[], int *pos) {
    int posicao_validada =0; // posição dos dados do usuarios, caso a validação seja correta
    if (*pos == 0) {
        return SEM_TAREFAS;  
    }

    char telefone[15];
       int encontrado =-1;
    
    printf("Entre com o número do contato a ser alterado: ");
    fgets(telefone, sizeof(telefone), stdin);
    telefone[strcspn(telefone, "\n")] = 0;

    normalizar_telefone(telefone);


    for (int i = 0; i < *pos; i++){
        char tel_comparacao[15];
        strcpy(tel_comparacao, infos[i].telefone);
        normalizar_telefone(tel_comparacao);

        if(strcmp(tel_comparacao, telefone) == 0){
            encontrado = 0; 
            posicao_validada =i;// defininido o contato como o indexador do array onde foi feita a comparação correta
            break;
        }
    }
    if(encontrado == -1){
        return NAO_ENCONTRADO;
    }

    if (encontrado == 0){
        char resp[15];
        printf("------------------\n");
        printf(" Ola %s\n",infos[posicao_validada].nome);
        printf("------------------\n");
        do{
        printf("Qual informação deseja mudar?\n");
        fgets(resp,sizeof(resp),stdin);
        resp[strcspn(resp, "\n")] = 0;
            
        
        
        if(strcmp(resp,"nome") == 0){
            printf("Entre com o novo nome: ");
            fgets(infos[posicao_validada].nome, sizeof(infos[posicao_validada].nome), stdin);
            infos[posicao_validada].nome[strcspn(infos[posicao_validada].nome, "\n")] = 0;
            break;
        } 
        else if(strcmp(resp,"telefone")==0){
            char novo_telefone[15];
            do{
            printf("Entre com o novo telefone: ");
                fgets(novo_telefone, sizeof(novo_telefone), stdin);
                novo_telefone[strcspn(novo_telefone, "\n")] = 0;
                normalizar_telefone(novo_telefone);

                if (strlen(novo_telefone) >= 11) {
                    ERROS erro = telefone_unico(infos, *pos, novo_telefone);
                    if (erro == OK) {
                         strcpy(infos[posicao_validada].telefone, novo_telefone);
                        printf("Telefone alterado com sucesso!\n");
                        
                        break;
                    } else if (erro == TELEFONE_DUPLICADO) {
                        printf("Telefone já cadastrado! Digite novamente.\n");
                    } else {
                        return erro;
                    }
                } else {
                    printf("Telefone inválido! Digite novamente.\n");
                }
                
            }while(1);
            break;
        }else if(strcmp(resp,"email")==0){
            char novo_email[50];
            do{
                printf("Entre com o novo e-mail:0");
                fgets(novo_email, sizeof(novo_email), stdin);
                novo_email[strcspn(novo_email, "\n")] = 0;
                ERROS erro = validar_email(novo_email);
                if (erro == OK){
                    strcpy(infos[posicao_validada].email, novo_email);
                    printf("Email alterado com sucesso!\n");
                    break;
                }else if (erro == EMAIL_INVALIDO) {
                    printf("Email inválido! Digite novamente.\n");
                } else {
                    return erro;
                }
                    
            }while(1);
            break;
        }else if(strcmp(resp,"todas")==0){
            char novo_telefone[15]; 
            char novo_email[50];

            printf("Entre com o novo nome: ");
            fgets(infos[posicao_validada].nome, sizeof(infos[posicao_validada].nome), stdin);
            infos[posicao_validada].nome[strcspn(infos[posicao_validada].nome, "\n")] = 0;
            
            do{
            printf("Entre com o novo telefone: ");
                fgets(novo_telefone, sizeof(novo_telefone), stdin);
                novo_telefone[strcspn(novo_telefone, "\n")] = 0;
                normalizar_telefone(novo_telefone);

                if (strlen(novo_telefone) >= 11) {
                    ERROS erro = telefone_unico(infos, *pos, novo_telefone);
                    if (erro == OK) {
                         strcpy(infos[posicao_validada].telefone, novo_telefone);
                        printf("Telefone alterado com sucesso!\n");

                        break;
                    } else if (erro == TELEFONE_DUPLICADO) {
                        printf("Telefone já cadastrado! Digite novamente.\n");
                    } else {
                        return erro;
                    }
                } else {
                    printf("Telefone inválido! Digite novamente.\n");
                }

            }while(1);
            do{
                printf("Entre com o novo e-mail:0");
                fgets(novo_email, sizeof(novo_email), stdin);
                novo_email[strcspn(novo_email, "\n")] = 0;
                ERROS erro = validar_email(novo_email);
                if (erro == OK){
                    strcpy(infos[posicao_validada].email, novo_email);
                    printf("Email alterado com sucesso!\n");
                    break;
                }else if (erro == EMAIL_INVALIDO) {
                    printf("Email inválido! Digite novamente.\n");
                } else {
                    return erro;
                }

            }while(1);
            break;
        }else if(strcmp(resp,"skate")==0){
            char eternochorao[2000] = "Di-sk8 eu vim\n"
              "Pra te mostrar que eu sou feliz\n"
              "Com ou sem você\n"
              "Di-sk8 eu vim\n"
              "Pra te mostrar que eu sou feliz\n"
              "Com ou sem você\n"
              "\n"
              "Sou diferente, sou rebelde\n"
              "Tenho o meu próprio estilo\n"
              "Não sigo as regras da sociedade\n"
              "Faço o que eu quero, quando eu quero\n"
              "\n"
              "Di-sk8 eu vim\n"
              "Pra te mostrar que eu sou feliz\n"
              "Com ou sem você\n"
              "Di-sk8 eu vim\n"
              "Pra te mostrar que eu sou feliz\n"
              "Com ou sem você\n"
              "\n"
              "Eu sou o dono da minha vida\n"
              "Ninguém me manda, ninguém me controla\n"
              "Faço o meu próprio caminho\n"
              "E vou aonde eu quero ir\n"
              "\n"
              "Di-sk8 eu vim\n"
              "Pra te mostrar que eu sou feliz\n"
              "Com ou sem você\n"
              "Di-sk8 eu vim\n"
              "Pra te mostrar que eu sou feliz\n"
              "Com ou sem você\n"
              "+ETERNO CHORÃO+\n";
            printf("%s\n",eternochorao);
        }else if(strcmp(resp,"voltar")==0){

            break;
        }
        else{
            printf("Campo invalido\n");
        }
            }while(1);
    }
    return OK;
}