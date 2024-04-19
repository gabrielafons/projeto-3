#define TOTAL 100

typedef struct {
char nome;
int telefone;
char email;
}Infos;

typedef enum {OK, MAX_TAREFA, SEM_TAREFAS, NAO_ENCONTRADO, ABRIR, FECHAR, ESCREVER, LER}ERROS ;

typedef ERROS (*funcao)(Infos[], int*);

ERROS add(Infos infos[], int *pos);

