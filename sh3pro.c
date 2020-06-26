#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int mysys( char* command)
{
    pid_t pid;
    int status;

    if(command == NULL)
    {
        return (1);
    }
    if((pid = fork())<0)
    {
    	status = -1;
    }
    else if(pid == 0)
    {
        execl("/bin/sh", "sh", "-c", command, (char *)0);
        exit(11);
    }
    else
    {
        wait( &status);
    }
    return status;
}

int mypipe(char *str1,char *str2)
{
    int pid;
    int fd[2];
    char buf[32];

    pipe(fd);
    pid = fork();
    if (pid == 0) {
        // child
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);

        execl("/bin/sh", "sh", "-c", str1, (char *)0);
        exit(0);
    }
    // parent
    dup2(fd[0], 0);
    close(fd[0]);
    close(fd[1]);

    read(0, buf, sizeof(buf));
    execl("/bin/sh", "sh", "-c", str2, (char *)0);
    printf("Receive:%s\n", buf);
    return 0;
}
int main()
{
    char str[1000];
	char *p,*mingling1,*mingling2;
	int i;
    while(1)
    {
        printf(">");
        gets(str);
		mingling1 = str;
		mingling2 = str;

        if(strcmp(str,"exit") == 0)
            break;

		for(p=str;p!='\0';p++)
		{
			if(*p == '|')
			{
				mingling1[p-str]='\0';
				mingling2 = p+1;
				break;
			}
		//printf("p=%c,str1=%s,str2=%s\n",*p,mingling1,mingling2);
		}
		//printf("p=%c,str1=%s,str2=%s\n",*p,mingling1,mingling2);
		if(strcmp(mingling1,mingling2))
		{
		//	printf("111111111str1=%s,str2=%s\n",mingling1,mingling2);
            mypipe(mingling1,mingling2);
		}
		else
        {
          //  printf("22222222222");
			mysys(str);
        }
    }

    return 0;
}
