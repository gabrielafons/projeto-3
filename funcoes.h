#define TOTAL 255


typedef struct {
char nome[50];
char telefone[15];
char email[50];

}Infos;

typedef enum {OK, MAX_TAREFA, SEM_TAREFAS, NAO_ENCONTRADO, ABRIR, FECHAR, ESCREVER, LER}ERROS ;

typedef ERROS (*funcao)(Infos[], int*);

ERROS add(Infos infos[], int *pos);
ERROS listar(Infos infos[], int *pos);
ERROS deletar(Infos infos[], int *pos);
ERROS salvar(Infos infos[], int *pos);
ERROS carregar(Infos infos[], int *pos);

ERROS alterar(Infos infos[], int *pos);

void clearBuffer();