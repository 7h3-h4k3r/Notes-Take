
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc , char *argv[]){
  char *buffer =(char*)malloc(100);
  char *data_File = (char*)malloc(100);
  int fd,uid;
  uid = getuid();
  strcpy(data_File,"notes.txt");
  
  if(argc<2){
    printf("\nUsage %s <enter a data to stored it in %s \n",argv[0],data_File);
    exit(-1);
  }else{
    strcpy(buffer,argv[1]);
  }
  
  fd = open(data_File, O_WRONLY|O_CREAT|O_APPEND , S_IRUSR|S_IWUSR);
  if(fd == -1){
    printf("File while trying to openig...\n");
    exit(-1);
  }
  
  printf("File discripter %d\n",fd);
  if(write(fd,&uid,4) == -1){
    printf("File while trying to readit\n");
    exit(-1);
  }
  printf("DEBUG @ %p Uid[%d] \n",&uid,uid); 
  
  write(fd,"\n",1);
  if(write(fd,buffer,sizeof(buffer)) == -1){
    printf("File while trying to write it");
    exit(-1);
    }
    printf("DEBUG @ %p User Data's %s \n",buffer,buffer);
    printf("DEBUG @ %p Data's %s\n",&data_File,data_File);
  write(fd,"\n",1);
  free(buffer);
  buffer= NULL;
  free(data_File);
  data_File= NULL;
  printf("Note's has been saved \n");
  
  }
    
  
    
  
