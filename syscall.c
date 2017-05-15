/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   syscall.c
 * Author: thienthaichotchai
 *
 * Created on May 13, 2017, 3:49 PM
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

/*
 * 
 */

void ignore();
void fork_func();
char *arg_split(char *str);
void list();
void checkFin();
void fished();

int countme = 0;

char *arg_split(char *str){
    const char s[2] = " ";
    char *token;
    token = strtok(str,s);
    while( token != NULL )
    {
     printf( " %s\n", token );
     token = strtok(NULL, s);
    }
    return token;
}

void ignore(){
  exit(3);
}

void checkFin()
{
      int status;
      // pid_t pid = waitpid(-1,&status,WNOHANG);
      waitpid(-1,NULL,0);
      // if (pid < 0 && errno != ECHILD)
      //     perror("Waitpid failed");
      // else if(pid > 0)
      //     printf("Process %d finish with status %d",pid,status);
}

void finished(int *p){
    for(int i = 0; i <= 1000;i++){
        if((int) p[i] != 0){
            printf("process %d done %d\n",p[i], i);
            p[i] = 0;
        }
    }
}

void fork_func(){
//    int child_finish[1000];
//    pid_t child_pids[1000];
    pid_t *child_pids = (pid_t*)calloc(1000, sizeof(pid_t));
//    for(int i = 0;i <= 1000;i++){
//        child_finish[i] = 0;
//    }
    int finCount = 0;
    int child_nb = 0;
    int i = 0;
    int status;
    char command[30];
    while(strcmp(command,"exit") != 0){
      printf("icsh > ");
      scanf("%s",command);
      int pid = fork();
      /*
       * Create a process space for the ls
       */
      if (pid < 0)
      {
        perror ("Fork failed");
        exit(errno);
      }
      else if (pid == 0)
      {
//       int fd;
//       int ret;
//       fd = open("out.txt", O_CREAT | O_APPEND | O_WRONLY);
//       if(fd < 0){
//           perror("open");
//           exit(0);
//       }
//       
//       ret = dup2(fd,1);
//       
//       if(ret < 0){
//           perror("dup2");
//           exit("1");
//       }
//       printf("Start the child process...\n");
//       char *prog_argv[2];
//       prog_argv[0] = "/bin/ls";
//       prog_argv[1] = NULL;
//       execv(prog_argv[0],prog_argv);
//       close(fd);
        //printf("Start the child process...\n");
        sleep(5);
        //printf("\n..Finishing the background process %d..\n",finCount);
        exit(0);
////        char *prog_argv[4];
////        prog_argv[0] = "/bin/ls";
////        prog_argv[1] = "-l";
////        prog_argv[2] = "/";
////        prog_argv[3] = NULL;
////        execvp (prog_argv[0], prog_argv);
      }
      else
      {
//          wait(pid);
        child_pids[child_nb++] = pid;
        bool check = true;
        while(check){
            pid_t p = waitpid(0,&status,WNOHANG);
            if((int) p == 0)
                check = false;
            else{
                printf("[%d] %d finish\n",finCount,(int) p);
                finCount++;
            }
        }
        if(strcmp(command,"jobs") == 0){
            while(child_pids[i] != 0 && i >= finCount){
               printf("[%d] %d   running\n",i,(int) child_pids[i]);
               i++;
            }
        }
      }
  }
    free(child_pids);
}

int main(int argc, char** argv) {

    printf("=== WELCOME TO MY SHELL ===\n");
    fork_func();
    return (EXIT_SUCCESS);
}

