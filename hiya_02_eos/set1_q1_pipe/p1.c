#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t id;
    int fd1 = 0;
    int fd[2];
    unsigned char buff[128];
    size_t nbytes_read;
    size_t nbytes_write;
    pipe(fd);
    id = fork();
    if (0==id)
    {   //Child process
        close(fd[1]);//closing write system call
        execl("../p2/p2","","-al",NULL);
        close(fd[0]);//closing read system call
    }
    else
    {   //Parent process
        close(fd[0]);//closing read system call
        fd = open("/usr/include/stdio.h",O_WRONLY);
        if(fd1 == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
        nbytes_write = write(fd[1],"/usr/include/stdio.h",39);//will return no. of successful bytes written
        printf("Written number of bytes: %ld\n",nbytes_write);
        close(fd[1]);//closing write system call
    }

    return 0;
}