/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: a4rahim
 *
 * Created on February 13, 2024, 2:03 PM
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/wait.h> 
#include <unistd.h> 

//command line need to be used.
/*
 * 
 */
int main(int argc, char** argv) {
    char *parent_cmd, *child_cmd;
    
    // Creating stack to store char
    //cmd ~ command
    parent_cmd=(char *)malloc(100*sizeof(char));
    child_cmd=(char *)malloc(100*sizeof(char));
    
    
    printf("Your Command> ");
    fgets(parent_cmd, 100, stdin);
    
    // Identifying the Pipe
    child_cmd = strchr(parent_cmd,'|') + 1;
    
    
    //check to see if there is a pipe
    if(child_cmd - 1 == NULL){ 
        fprintf(stderr,"No Pipe Found");
        exit(1);
    }
    //Remove any spaces between pipe and the child command
    for(;child_cmd[0]== ' '; child_cmd = child_cmd + 1); 
    
    //Remove any spaces between pipe and the parent command
    for(char *temp = strchr(parent_cmd,'|')-1; temp[0]== ' '; temp[0]='\0', temp--); 

    //create pipe descriptor
    int pd[2]; 

    //create pipe and check for errors
    if(pipe(pd)<0){ 
        
        fprintf(stderr, "Error in creating pipe");
        exit(1);
    }

    if(fork()==0){
        
        //child process
        dup2(pd[0], 0); //0 is stdin
        close(pd[1]);
        
        system(child_cmd);
        exit(0);
    }
    else{
        
        //parent process
        dup2(pd[1], 1); //1 is stdout
        close(pd[0]);
        
        system(parent_cmd);
    }
    return(0);
}
