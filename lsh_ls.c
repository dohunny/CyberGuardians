#include "lsh.h"



void rwx(file_mode){

  if (S_ISDIR(file_mode)) printf("d");
  else printf("-");

  if (file_mode & S_IRUSR) printf("r");
  else printf("-");

  if (file_mode & S_IWUSR) printf("w");
  else printf("-");

  if (file_mode & S_IXUSR) printf("x");
  else printf("-"); 

  if (file_mode & S_IRGRP) printf("r");
  else printf("-");

  if (file_mode & S_IWGRP) printf("w");
  else printf("-");

  if(file_mode & S_IXGRP) printf("x");
  else printf("-"); 

  if (file_mode & S_IROTH) printf("r");
  else printf("-");

  if (file_mode & S_IWOTH) printf("w");
  else printf("-");

  if(file_mode & S_IXOTH) printf("x");
  else printf("-");

  printf("  ");
}



int lsh_ls(char **args){
  DIR* dp = NULL;
  struct dirent* entry = NULL;
  struct stat file_info;
  int option_exist; int longest;
  char detail[50] = { 0x00, };
  char format[50] = { 0x00, };
  char buf1[80];
	struct passwd *my_passwd;
  struct group *my_group;
  struct tm *tminfo;

  if(args[1] == NULL){
    // Path X, Option X
    if ((dp=opendir("./")) == NULL) {
      printf("Not Found: %s\n", "./");
      return -1;
    }
    option_exist = 0;
  } else if(args[1][0] != '-') {
    // Path O, Option X
    if ((dp=opendir(args[1])) == NULL) {
      printf("Not Found: %s\n", args[1]);
      return -1;
    }
    option_exist = 0;
  } else {
    option_exist = 1;
    if (args[2] == NULL) {
    // Path X, Option O
      if ((dp=opendir("./")) == NULL) {
        printf("Not Found: %s\n", "./");
        return -1;
      }
    }else{
      // Path O, Option O
      if ((dp=opendir(args[2])) == NULL) {
        printf("Not Found: %s\n", args[2]);
        return -1;
      }
    }
  }

  while ((entry = readdir(dp)) != NULL) {
    lstat(entry->d_name, &file_info);
    longest = 5;
    if (option_exist){
      if(entry->d_name[0] == 0x2E) continue;
      
      rwx(file_info.st_mode);
      printf("%ld  ", file_info.st_nlink);

      my_passwd = getpwuid(file_info.st_uid);
      my_group  = getgrgid(file_info.st_gid);
      printf("%s  ", my_passwd->pw_name);
      printf("%s  ", my_group->gr_name);
      printf("%ld  ", file_info.st_size);

      tminfo = localtime(&(file_info.st_atime));
      strftime(buf1, 80, "%m-%d %H:%M", tminfo); 
      printf("%s  ", buf1); 

      if(entry->d_ino != 0) 
      printf("%s\n", entry->d_name);

    } else {
      if(entry->d_name[0] == 0x2E) continue;
      printf("%s  ", entry->d_name);
    }
  }

  printf("\n");
  closedir(dp);

  return 1;
}