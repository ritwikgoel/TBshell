#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <readline/history.h>
#include <sys/wait.h>
//ctrl+z to quit
char **get_input(char *);

int cd(char *path);

void welcome();

int cd(char *path);
//functions definitions 

int cd(char *path) 
{
    return chdir(path);
}

char **get_input(char *input) 
{
    char **command = malloc(16 * sizeof(char *));//mkaing a word of max 16 characters using malloc 
    char *separator = " ";
    char *parsed;
    int index = 0;

    parsed = strtok(input, separator);//splittting into an array of char stirngs
    while (parsed != NULL) 
    {
        command[index] = parsed;
        index++;
        parsed = strtok(NULL, separator);
    }

    command[index] = NULL;
    return command;
}

void welcome()
{
    system("./cowsayer.sh");
    printf("Made for my OS project \n ");
}

void sendmail(){
    system("./sendmail.sh");
}

int main()
{
    welcome();
    int ctr=0;
    FILE *fp;
    //fp=fopen("/home/tangobeer/Desktop/shell-workspace/final/log.txt", "a");
    while(1){
        fp=fopen("/home/tangobeer/Desktop/shell-workspace/final/log.txt", "a");
        signal(SIGINT, SIG_IGN);//what this does is basically ignores the ctrl c
        pid_t child,domer;
        int stat_loc;
       //ask for the input first
        char **command;
        char *input;
        char cwd[1024];
        //chdir("/path/to/change/directory/to");
        getcwd(cwd, sizeof(cwd));
        
        while(ctr!=1)
        {
            getcwd(cwd, sizeof(cwd));
            printf("\033[1;36m");
            printf("Kilt@%s:~$ ",cwd);
            printf("\033[0;m");
            ctr++;
            
        }
        input = readline("");//add the shell name here 
        
        command = get_input(input);
        //if the command is empty
            if (command[0]==NULL) 
            {      /* Handle empty commands */
            free(input);
            free(command);
            printf("\n");
            getcwd(cwd, sizeof(cwd));
            printf("\033[1;36m");
            printf("Kilt@%s:~$ ",cwd);
            printf("\033[0;m");
            continue;
        }
        if(strcmp(command[0], "cd") == 0)
        {
            cd(command[1]);
            getcwd(cwd, sizeof(cwd));
            printf("\033[1;36m");
            printf("Kilt@%s:~$ ",cwd);
            printf("\033[0;m");
            continue;
        }
        if(strcmp(command[0], "sendmail") == 0){
            sendmail();
            getcwd(cwd, sizeof(cwd));
            printf("\033[1;36m");
            printf("Kilt@%s:~$ ",cwd);
            printf("\033[0;m");
            continue;
        }
        child=fork();
        if(child==0)
        {
            //this is the child
            //over here before the execvp command we need to add a signal handler resetter
            signal(SIGINT,SIG_DFL);//this is signal defaulter. this will allow us to use ctrl c in out progrmam 
            // fprintf(fp,"%s\n",command);
            fprintf(fp, "%s %s\n",command[0],command[1]);
            //printf("%s \n",command);
            fclose(fp); 
            execvp(command[0],command);
            printf("This is not supposed to get printed \n");//this can happen if the execvp is unknown
            getcwd(cwd, sizeof(cwd));
            printf("\033[1;36m");
            printf("Kilt@%s:~$ ",cwd);
            printf("\033[0;m");
        }
        else if(child!=0)
        {
            domer=waitpid(child,&stat_loc,WUNTRACED);
            //printf("The command is sucessfully run\n");
            printf("\033[1;36m");
            printf("Kilt@%s:~$ ",cwd);
            printf("\033[0;m");
            free(command);
            free(input);
        }
    }
    fclose(fp);
    return 0;

}