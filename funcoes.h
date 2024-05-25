#define CONTATOS 255
#define TRABALHO 255



typedef struct {
char nome[50];
char telefone[15];
char email[50];

}Infos;

typedef enum {OK, MAX_TAREFA, SEM_TAREFAS, NAO_ENCONTRADO, ABRIR, FECHAR, ESCREVER, LER,EMAIL_INVALIDO, TELEFONE_DUPLICADO,}ERROS ;

typedef ERROS (*funcao)(Infos[], int*);

ERROS add(Infos infos[], int *pos);
ERROS listar(Infos infos[], int *pos);
ERROS deletar(Infos infos[], int *pos);
ERROS validar_email(const char *email);
ERROS telefone_unico(Infos infos[], int pos, const char *telefone);
ERROS alterar(Infos infos[], int *pos);

ERROS salvar(Infos infos[], int *pos);
ERROS carregar(Infos infos[], int *pos);
void normalizar_telefone(char *telefone);

void clearBuffer();