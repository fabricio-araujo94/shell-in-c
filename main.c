#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define TRUE 1
#define COMMAND 20
#define PARAMETERS 20

void type_prompt();
void read_command( char *, char **);
char *alocar_char(int);
char **alocar_char_alt(int);

int main(void)
{
    char *binary_path = alocar_char(100);
    char *command = alocar_char(100);
    char **parameters = alocar_char_alt(20);
    int status;

    while(TRUE) {
        type_prompt();
        read_command(command, parameters);
   
        if(fork() != 0) {
            waitpid(-1, &status, 0);
        } else {
            strcpy(binary_path, "/bin/");
            strcat(binary_path, command);
            execve(binary_path, parameters, NULL);
        };
        
    };

	return 0;
}

char *alocar_char(int qtd) {
    char *array = (char *) malloc(qtd * sizeof(char));

    if(array == NULL) {
        puts("Não foi possível alocar na memória.");
        exit(1);
    }

    return array;
}

char **alocar_char_alt(int qtd) {
    char **array = (char **) malloc(qtd * sizeof(char));

    if(array == NULL) {
        puts("Não foi possível alocar na memória.");
        exit(1);
    }

    return array;
}

void type_prompt() {
    printf("> ");
}

void read_command( char command[],   char *parameters[]) {
    char *array[100], *palavras;
    int i = 0, j = 0;

    char *texto = (char *) malloc(1024 * sizeof(char));

    if(texto == NULL) { 
        puts("Sem memória!\n");
        exit(1);
    }
   
    scanf("%[^\n]%*c", texto);

    palavras = (char *) strtok(texto, " ");

    i = 0;
    while(palavras != NULL) {
        array[i++] = strdup(palavras);
        palavras = strtok(NULL, " ");
    }

    strcpy(command, array[0]);

    for(j = 0; j < i; j++) {
        parameters[j] = array[j];
    }
    parameters[i] = NULL;

    free(texto);

}
