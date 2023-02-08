#include <unistd.h>
#include <stdio.h>

int toupper( int ch );
pid_t waitpid(pid_t pid,int * status_ptr, int options);
# define ODCZYT 0
# define ZAPIS 1

int main ()
{
    int potok [2];
    char line [30];
    char big_line[30];
    int counter = 0;
    puts (" Program pipes startuje ") ;
    puts (" Tworze potok ") ;
    pipe ( potok ) ;
    puts (" fork ") ;

    int id = fork();
  
    if(id != 0) {
         
        waitpid(id,NULL,0);
        int f = fork();
      
        if(f != 0){
            printf("Proces potomny\n");
            //printf (" Czekam na proces najpotomniejszy ") ;
            read ( potok [ ODCZYT ] , &line , sizeof ( line ) ) ;
           
            close(potok[ODCZYT]);
            for (int i=0;i<30;i++){
                big_line[i] = toupper(line[i]);
            }

            write ( potok [ ZAPIS ] , &big_line , sizeof ( big_line ) ) ;
            printf (" Proces potomny wyslal\n") ;
            close ( potok [ ZAPIS ]) ;
        }
        else {
            waitpid(f,NULL,0);
            printf (" Proces macierzysty\n ") ;
            close ( potok [ ZAPIS ]) ;
            //printf (" Czekam na proces potomny ") ;
            read ( potok [ ODCZYT ] , &big_line , sizeof ( big_line ) ) ;
            printf (" Proces macierzysty otrzymal %s \n " , big_line ) ;
            close ( potok [ ODCZYT ]) ;
        }
    }
    else{
        printf (" Proces najpotomniejszy\n") ;
        close ( potok [ ODCZYT ]) ;
        printf("Podaj tekst: ");
        sleep(5);
        scanf("%s",line);
            
        write ( potok [ ZAPIS ] , &line , sizeof ( line ) ) ;
        //printf (" Proces najpotomniejszy wyslal ") ;
        close ( potok [ ZAPIS ]) ;
    }
   
    
}