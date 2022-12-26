#include <stdio.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 128
char buff[BUFF_SIZE];

struct mq_attr usr_mq_attr;

int main()
{
    mqd_t mqd = 0; //message queue descriptor
    int err_rec = 0;
    int err_cl = 0;
    usr_mq_attr.mq_flags = 0;
    usr_mq_attr.mq_maxmsg = 4;
    usr_mq_attr.mq_msgsize = 128;
    usr_mq_attr.mq_curmsgs = 0;
    
    mqd = mq_open("/usr/include/stdio.h", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &usr_mq_attr);
    if(mqd == -1) //Error handling for opening a file
    {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    err_rec = mq_receive(mqd, buff, 128, 0);
    if(err_rec == -1) //Error handling for receiving message queue
    {
        perror("mq_receive");
        exit(EXIT_FAILURE);
    }

    printf("Received message: %s\n",buff);

    err_cl = mq_close(mqd);
    if(err_cl == -1) //Error handling for closing message
    {
        perror("mq_close");
        exit(EXIT_FAILURE);
    }

    return 0;
}