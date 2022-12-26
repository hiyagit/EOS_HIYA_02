#include <stdio.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct mq_attr usr_mq_attr;

int main(int argc,const char *argv[])
{
    mqd_t mqd = 0; //message queue descriptor
    int err_send = 0;
    int err_cl = 0;
    unsigned char buff[128];
    ssize_t nbytes_read;

    usr_mq_attr.mq_flags = 0;
    usr_mq_attr.mq_maxmsg = 4;
    usr_mq_attr.mq_msgsize = 128;
    usr_mq_attr.mq_curmsgs = 0;
    
    mqd = mq_open("/usr/include/stdio.h", O_RDONLY);
    if(mqd == -1) //Error handling for opening a file
    {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    nbytes_read = read(mqd,buff,128);
    if(-1 == mqd)
    {
        perror("file");
        exit(EXIT_FAILURE);
    }
    printf("Received: %s",buff);
    printf("Read number of bytes: %ld\n",nbytes_read);
    if(-1 == nbytes_read)
    {
        perror("nbytes_read");
        exit(EXIT_FAILURE);
    }

    /*
     int mq_send(mqd_t mqdes, const char *msg_ptr,
                     size_t msg_len, unsigned int msg_prio);
    */

    err_send = mq_send(mqd, buff,strlen(buff), 0);
    if(err_send == -1) //Error handling for sending message queue
    {
        perror("mq_send");
        exit(EXIT_FAILURE);
    }

    err_cl = mq_close(mqd);
    if(err_cl == -1) //Error handling for closing of message queue
    {
        perror("mq_close");
        exit(EXIT_FAILURE);
    }

    return 0;
}
