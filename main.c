#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv){
  char directory[256]; //string to hold directory name

  if (argc>1) { //command line argument
    strncpy(directory,argv[1],sizeof(directory)-1);
  }
  else { //standard input
    printf("Enter directory to scan:");
    fgets(directory, sizeof(directory),stdin);
  }

  char * nb = strchr(directory,'\n'); //getting rid of the new line char
  if (nb) *nb = '\0'; //adding null terminating byte

  DIR *d;
  d = opendir(directory); //open the directory

  //If the input is invalid
  if (d==NULL){
    printf("Invalid Directory. Error %d: %s", errno, strerror(errno));
    return 0;
  }

  struct stat sb;
  int size = 0;

  struct dirent *entry = readdir(d);

  printf("Statistics for directory: %s\n", entry->d_name);

  //get size of the directory
  while (entry){
    if (entry->d_type==8){
      stat(entry->d_name, &sb);
      size+= sb.st_size;
    }
    entry= readdir(d);
  }

  printf("Total directory size: %d Bytes\n",size);

  rewinddir(d);
  entry= readdir(d);

  //printing the directories
  printf("Directories:\n");
  while (entry && entry->d_type==DT_DIR){
    printf("\t%s\n", entry->d_name);
    entry = readdir(d);
  }

  //printing the regular files
  printf("Regular Files:\n");
  while (entry && entry->d_type==DT_REG){
    printf("\t%s\n", entry->d_name);
    entry = readdir(d);
  }

  closedir(d);
  return 0;
}
