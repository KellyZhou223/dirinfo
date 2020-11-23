#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>

int main(){
  DIR *d;
  d = opendir("./");
  struct stat sb;
  int size = 0;

  struct dirent *entry = readdir(d);

  printf("Statistics for directory: %s\n", entry->d_name);
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

  printf("Directories:\n");
  while (entry && entry->d_type==4){
    printf("\t%s\n", entry->d_name);
    entry = readdir(d);
  }

  printf("Regular Files:\n");
  while (entry && entry->d_type==8){
    printf("\t%s\n", entry->d_name);
    entry = readdir(d);
  }

  closedir(d);
  return 0;
}
