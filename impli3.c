#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <readline/history.h>
#include <sys/wait.h>

int cd(char *path) {
    return chdir(path);
}
char **get_input(char *input) {
    char **command = malloc(16 * sizeof(char *));//mkaing a word of max 10 characters
    char *separator = " ";
    char *parsed;
    int index = 0;

    parsed = strtok(input, separator);//splittting into an array of char stirngs
    while (parsed != NULL) {
        command[index] = parsed;
        index++;

        parsed = strtok(NULL, separator);
    }

    command[index] = NULL;
    return command;
}


//fork the process
//child proces executes the commands
//parent waits for the child to be done with the commands
//take input form the user 
//cd
//text highlighting(probably wont do here)
int main(){
    while(1>0)
        {
    pid_t child, domer;
    int useless;
    char **command;
        char *input;
        char cwd[1024];
        //chdir("/path/to/change/directory/to");
        getcwd(cwd, sizeof(cwd));
        input = readline("");//add the shell name here 
        printf("Kilt %s ~$ ",cwd);
        command = get_input(input);
        if(!strcmp(command[0],"cd")){
            cd(command[1]);
        }
        
        child=fork();
        if(child==0){
            //child process
            execvp(command[0],command);
            printf("This is not going to get oprinted");
        }
        else if(child>0){
            waitpid(child,&useless,WUNTRACED);
            free(input);
            free(command);
        }
}
        return 0;


}
