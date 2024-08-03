#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#define NOTES "notes.txt"
int print_notes(int ,int ,char*);
int find_uid_len(int ,int );
int print_data(char*,char*);
int main(int argc, char *argv[]){
    int fd,uid,true =1;
    char search_string[100];
    if(argc<1){
        strcpy(search_string,argv[1]);
    }
    else{
        search_string[0] = 0;
    }
    fd = open(NOTES,O_RDONLY);
    uid =getuid();
    if(fd == -1){
        printf("Cannot open  the file discripter \n");
        return -1;
    }

    while(true){
        true = print_notes(fd,uid,search_string);
    }
    printf("\n==========={ Notes has been End }==========\n");
}
int print_notes(int fd , int uid ,char *search_string){
    int len;
    char note_buffer[100];
    len = find_uid_len(fd,uid);
    if(len==-1){
        return 0;
    }
    read(fd,note_buffer,len);
    note_buffer[len] = 0;
    //printf(note_buffer);
    if(print_data(note_buffer,search_string)){
        return 1;
    }

}
int find_uid_len(int fd ,int uid){
    int noteuid =-1 ;
    unsigned char byte;
    int length;
    while(noteuid != uid){
        if(read(fd,&noteuid,4) != 4){
            return -1;
        }
        if(read(fd,&byte,1)!=1){
            return -1;
        }
        length = byte = 0;
        while(byte != '\n'){
            if(read(fd,&byte,1)!=1){
                return -1;
            }
        length++;
        }
    }
    lseek(fd,length *-1,SEEK_CUR);
    printf("DEBUG{UID %d DATA LENGTH %d}\n",uid,length);
    return length;
}
int print_data(char *note,char *keyword){
    int size;
    size = strlen(keyword);
    if(size == 0){
        return 1;
    }
    for(int i=0;i<size;i++){
        if(note[i] == keyword[i]){
            printf("%s",keyword);
        }
    }
}