#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <readline/history.h>
#include <sys/wait.h>
char **get_input(char *);//for the get inpout file this is function declaration
int main(){
    while(1)
    {
    
    char **command;
    char *input;

    
        input = readline("RitwikGoel::> ");
    command = get_input(input);
    int stat_loc;//this is to make the parent wait for the child during its execution


    //basic flow imo==> intput==>fork==>exec the child==>make parent wait for the child to complete execution
    //pid_t child=fork(); //making a child by forking(should be done in parent class)
    pid_t child=fork();
    if(child==0){
        //we are in child process where we exec 
        execvp(command[0], command);
        printf("This is a test. this is not supposed to get printed!\n");
        }
    else if(child>0){
        //parent
        //wait for the child
        waitpid(child, &stat_loc, WUNTRACED);
    }
    else if(child<0){
        //something went wrong
        //this is when the forking goes wrong
    }

    free(input);
    free(command);
}
    return 0;


}

char **get_input(char *input) {
    char **command = malloc(10 * sizeof(char *));//mkaing a word of max 10 characters
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