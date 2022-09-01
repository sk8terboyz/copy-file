#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  char path_name[100];
  char* sourceFileName;
  char* destination1;
  char* destination2;
  FILE* source;
  FILE* dest1;
  FILE* dest2;
  int checkr, checkw, checkw2;

  if(argc == 4)
  {
    //store all file names
    sprintf(path_name,"./%s",argv[1]);
		sourceFileName = argv[1];
    sprintf(path_name,"./%s",argv[2]);
    destination1 = argv[2];
    sprintf(path_name,"./%s",argv[3]);
    destination2 = argv[3];
  }
  else
  {
    //print proper usage of the executable and exit the program
    printf("Proper Usage: [executable] [source file] [destination1] [destination2]\n");
    exit(-1);
  }

  //open file and check if it was successful
  source = fopen(sourceFileName, "r");
  if(source == NULL) {
    fprintf(stderr, "File %s could not be opened\n", sourceFileName);
    exit(1);
  }
  //open file and check if it was successful
  dest1 = fopen(destination1, "w");
  if(dest1 == NULL)
  {
    fprintf(stderr, "File %s could not be opened\n", destination1);
    exit(2);
  }
  //open file and check if it was successful
  dest2 = fopen(destination2, "w");
  if(dest2 == NULL)
  {
    fprintf(stderr, "File %s could not be opened\n", destination2);
    exit(3);
  }

  //loop to read the source file and write the 2 copies
  while(feof(source) == 0)
  {
    char buffer[1024];
    if((checkr = fread(buffer, sizeof(char), 1024, source)) != 1024)
    {
      if(ferror(source) != 0)
      {
        fprintf(stderr, "read file error\n");
        exit(1);
      }
    }
    if((checkw = fwrite(buffer, sizeof(char), checkr, dest1)) != checkr)
    {
      fprintf(stderr, "write file error\n");
      exit(1);
    }
    if((checkw2 = fwrite(buffer, sizeof(char), checkr, dest2)) != checkr)
    {
      fprintf(stderr, "write file error\n");
    }
  }

  fclose(dest1);
  fclose(dest2);
  fclose(source);
  return 0;
}
