#include "lsh.h"
#include "math.h"

int lsh_mv(char **args){
  if (args[1] == NULL || args[2] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"mv\"\n");
    return -1;
  }
  if (rename(args[1], args[2]) == 0) {
    printf("The file or directory was moved successfully.\n");
    return 1;
  } else {
    printf("Rename Error...!");
    return -1;
  }
}

// int lsh_mv(char **args){
//   FILE *in_fp, *out_fp;
//   char buff[4096];
//   size_t size;
//   struct stat file_info;
//   struct utimbuf attr;
//   int tmp_errno;
//   int isRemoved;
//   int mode;

//   if (args[1] == NULL || args[2] == NULL) {
//     fprintf(stderr, "lsh: expected argument to \"mv\"\n");
//     return -1;
//   }
//   if((in_fp = open(args[1], O_RDONLY)) == -1) { 
//     printf("Not Found: %s\n", args[1]);
//     return -1; 
//   }

//   fstat(in_fp, &file_info);
//   out_fp = open(args[2], O_WRONLY | O_CREAT | O_TRUNC, file_info.st_mode);

//   if(out_fp == -1) {
//     printf("Destination Path Error: %s", args[2]);
//     tmp_errno = errno;
//     close(in_fp); 
//     errno = tmp_errno;
//     return -1; 
//   }

//   while(size = read(in_fp, buff, 4096)) {
//     if(size == -1) {
//       if(errno == EINTR) { 
//         continue; 
//       }
//       printf("File Read Error: %s", args[1]);
//       tmp_errno = errno;
//       close(in_fp); 
//       close(out_fp); 
//       errno = tmp_errno;
//       return -1; 
//     }
//     while(write(out_fp, buff, size) == -1) { 
//       if(errno == EINTR) { 
//         continue; 
//       } else { 
//         tmp_errno = errno; 
//         close(in_fp); 
//         close(out_fp); 
//         errno = tmp_errno;
//       } 
//     }
//   }
//   close( in_fp );
//   close( out_fp );

//   attr.actime = file_info.st_atime; 
//   attr.modtime = file_info.st_mtime; 
//   utime(args[2], &attr);
//   chmod(args[2], file_info.st_mode);

//   if ( unlink(args[1]) == -1 )
//   {
//       printf( "Remove Error!\n");
//       return -1;
//   }

//   printf("Moved Successively\n");

//   return 1;
// }
