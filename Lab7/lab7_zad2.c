#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int toupper( int ch );
int mkfifo ( const char * name , mode_t mode ) ;

# define ODCZYT 0
# define ZAPIS 1
# define WORKERS 10

int semafor [2];

void LOCK ()
{
    char line [30];
    read ( semafor [ ODCZYT ] , &line , sizeof ( line ) ) ;
}
void UNLOCK ()
{
    char line [30];
    write ( semafor [ ZAPIS ] , &line , sizeof ( line ) ) ;
}

void worker ( int id , int potok_k )
{
    char line [30];
    int i , j ;
    printf (" Worker % d startuje \n " , id ) ;
    LOCK () ;

    for ( i = 0; i < 7; i ++)
    {
        printf ("[% d ] " , id ) ;
        fflush ( stdout ) ;
        sleep (1) ;
    }
    
    UNLOCK () ;
    printf (" Worker % d konczy \n " , id ) ;
    write ( potok_k , &line , sizeof ( line ) ) ;
}

int main ()
{
    char line [30];
    
    int counter = 0;
   
    if(mkfifo("FIFOpipe",0777) == -1){
        printf("Can't create the file");
        return -1;
    } 
    int file = 0;

    int id = fork();
  
    if(id != 0) {
         
        int f = fork();
      
        if(f != 0){
            printf("Proces potomny\n");
            file = open ("FIFOpipe", O_RDWR) ;
            read (file , &line , sizeof ( line ) ) ;            
            

            for (int i=0;i<30;i++){
                line[i] = toupper(line[i]);
            }
            
            write (file , &line , sizeof ( line ) ) ;
            printf (" Proces potomny wyslal\n") ;
            
        }
        else {
            printf (" Proces macierzysty\n ") ;
            file = open ("FIFOpipe" , O_RDONLY ) ;
            read (file , &line , sizeof ( line ) ) ; 
            printf (" Proces macierzysty otrzymal %s \n " , line ) ;
            close ( file ) ;
        }
    }
    else{
        printf (" Proces najpotomniejszy\n") ;
        file = open ("FIFOpipe" , O_WRONLY ) ;
        
        printf("Podaj tekst: ");
        
        scanf("%s",line);
            
        write (file , &line , sizeof ( line ) ) ;
        close ( file ) ;
    }
   
    
}