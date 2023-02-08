#include <stdio.h>
#include <unistd.h>

int main(){

    int pid = fork();
    if ( pid == 0)
    {
       execlp("./build.sh","bash");
       
    } 
    else 
    {

        waitpid(pid,NULL,0);

        int pid2 = fork();
        char* const tab[2]={"LD_LIBRARY_PATH=.",NULL};

        if(pid2 == 0) 
        {
            execle("./program.out","./program.out",NULL,tab);
        }
        else 
        {
            waitpid(pid2,NULL,0);
            execlp("./delete.sh","bash");
        }
                
       
    }
     return 0;
}