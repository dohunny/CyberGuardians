#include "lsh.h"
#include "math.h"

int lsh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

int checkAuth(char *srcPath){
  int mode[] = {R_OK, W_OK, X_OK};
  int res = 0;
  for(int i = 0; i < 3; i++){
    if(access(srcPath, mode[i]) == 0){
      res = res + pow(2,i);
      continue;
    }
    else printf("cannot access(i:%d)", i);
  }
  return res;
}

int lsh_mv(char **args){
  FILE *in_fp, *out_fp;
  char buff[4096];
  size_t n_size;
  int isRemoved;
  int mode;

  if (args[1] == NULL || args[2] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"mv\"\n");
    return -1;
  }
  in_fp = fopen(args[1], "r");
  if ( in_fp == NULL ) {
    printf("Path Not Found: %s\n", args[1]);
    return -1;
  }
  out_fp = fopen(args[2], "w");
  if ( out_fp == NULL )
  {
    printf( "Path Not Found: %s\n", args[2]);
    fclose(in_fp); 
    return -1;
  }
  while(0 < (n_size = fread(buff, 1, sizeof(buff), in_fp)))
  {
      fwrite(buff, 1, n_size, out_fp);
  }
  fclose( in_fp );
  fclose( out_fp );

  // mode = checkAuth(args[1]);
  // if chmod(args[2], mode)

  if ( unlink(args[1]) == -1 )
  {
      printf( "Remove Error!\n");
      return -1;
  }

  printf("Moved Successively\n");

  return 1;
}

char printTime(struct stat *buf){ 
        struct tm *mtime; 
        char result[50] = {0x00,};
        mtime=localtime(&buf->st_mtime); 
        sprintf(result, "%04d-%02d-%02d %02d:%02d\n", 
                mtime->tm_year+1900, mtime->tm_mon+1, 
                mtime->tm_mday, mtime->tm_hour, 
                mtime->tm_min); 
        return &result;
}

int lsh_ls(char **args){
  DIR* dp = NULL;
  struct  dirent*  entry  =  NULL;
  struct stat buf;
  int option_exist; int longest;
  char detail[50] = { 0x00, };
  char format[50] = { 0x00, };

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
    lstat(entry->d_name, &buf);
    longest = 5;
    if (option_exist){
      if(entry->d_name[0] == 0x2E) continue;
      sprintf(format, "%%-%uld %%-%uld %%-%uld %%-%uld %%-%uld", longest+2, longest+2, longest+2, longest+2, longest+2);
      sprintf(detail, format, buf.st_mode, buf.st_uid, buf.st_gid, buf.st_size, printTime(&buf));
      printf("%s  %s\n", detail, entry->d_name);
    } else {
      if(entry->d_name[0] == 0x2E) continue;
      printf("%5s  ", entry->d_name);
    }
  }

  printf("\n");
  closedir(dp);

  return 1;
}