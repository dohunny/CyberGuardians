#include "lsh.h"
#include "math.h"

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
