#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>

#include "p4log.h"

void
die(const char *message){
  if(errno){
    perror(message);
  }else{
    printf("ERROR: %s\n", message);
  }
  exit(1);
}

bool
check_file_integrity(){
  FILE *f = fopen(LOGFILE, "a+");
  fflush(f);
  fclose(f);
  //for now I'm just checking size, because I don't want to write a full check/repair method
  struct stat st;
  stat(LOGFILE, &st);
  int size = st.st_size;
  if(size > 1) {
    return true;
  } else {
    return false;
  }
}

void
file_init(){
  printf("nii-chan, fairu wa nai.  atashi ni makasete!\n");
  FILE *f = fopen(LOGFILE, "w+");
  if(!f) die("nii-chan, fairu hirogenakatta.");

  int i;
  for (i = 0; i < FILE_LENGTH; i++){
    fprintf(f, "%s", filelines[i]);
  }
  fflush(f);
  fclose(f);
}

//reads the character name and returns the name with trailing spaces truncated
char *read_name(FILE *f, int line){
  char *result = malloc(sizeof(char) * (MAX_NAME_WIDTH + 1));
  if(!result) die("malloc error.");

  fseek(f, line * LINE_LENGTH, SEEK_SET);
  fscanf(f, "%s", result);

  return result;
}

//rewinds file cursor to beginning of current line
void line_rewind(FILE *f){
  if(!f) return;
  int pos = ftell(f);
  //integer division drops remainder, so we always iterate a whole number of lines
  int prevline = (int) (pos / LINE_LENGTH);
  fseek(f, prevline * LINE_LENGTH, SEEK_SET);
}

void
store_result(char *matchup, char *result)
{
  FILE *f = fopen(LOGFILE, "r+");
  if (!f) die("nii-chan, fairu hirogenakatta.");
  
  int i;
  char *s;
  for(i = 0; i < FILE_LENGTH; i++){
    s = read_name(f,i);
    line_rewind(f);

    int offset = 0;
    if(strcmp(matchup,s) == 0 || strcmp(s, "total") == 0){
      if (result[0] == 'w'){
        offset = WIN_OFFSET;
      } else {
        offset = LOSS_OFFSET;
      }

      fseek(f, offset, SEEK_CUR);
      int temp = 0;
      fscanf(f, "%4d", &temp);
      line_rewind(f);
      fseek(f, offset, SEEK_CUR);
      temp++;
      fprintf(f,"%d", temp);
       
    }
    free(s);
  }

  fflush(f);
  fclose(f);
}

//todo: if you pass args it ignores width and uses a set char width (based on MAX_NAME_WIDTH)
//todo: get rid of width/argc; pass a format string instead.
//  string should allow you to set each coloumn to a variable width
void
pretty_table(int width, int argc, ...){
  
  va_list ap;
  char *result = malloc(sizeof(char) * (width + 5));
  if(!result) die("memory error.");

  if(argc == 0){
    strncpy(result, "\0", 1);
    int i;
    for (i = 0; i < width; i++){
      strncat(result, HORIZONTAL_LINE, 1);
    }
    strncat(result, "\n", 1);
    printf("%s", result);
    free(result);
    return;
  }

  char *s;
  strncpy(result, "| ", 3); 
  va_start(ap,argc);
  int i;
  for(i = 0; i < argc; i++){
    s = va_arg(ap, char *);
    if(!s) die("va_arg failed.");

    int l = strlen(s);
    if(l < MAX_NAME_WIDTH){
      int j;
      for(j = 0; j < MAX_NAME_WIDTH - l; j++){
        strncat(s, " ", 1);
      }
    }

    strncat(result, s, MAX_NAME_WIDTH);
    strncat(result, " | ", 3);
  }
  
  va_end(ap);
  strncat(result, "\n", 1);
  printf("%s", result);
  free(result);
}

void
print_summary()
{
  FILE *f = fopen(LOGFILE, "r");
  if (!f) die("nii-chan, fairu hirogenakatta.");

  pretty_table(40,0);
  int i;
  char *s = "";
  int win = 0;
  char w_str[5] = "";
  int loss = 0; 
  char l_str[5] = "";
  for(i = 0; i < FILE_LENGTH; i++){
    s = read_name(f,i);
    line_rewind(f);

    fseek(f,WIN_OFFSET,SEEK_CUR);
    fscanf(f,"%d",&win);
    snprintf(w_str, 5, "%d", win);
    line_rewind(f);
    fseek(f,LOSS_OFFSET,SEEK_CUR);
    fscanf(f," %d",&loss);
    snprintf(l_str, 5, "%d", loss);

    pretty_table(40,3,s,w_str,l_str);
    pretty_table(40,0);
    free(s);
  }

  fclose(f); 
}

int
main (int argc, char *argv[])
{
  if(!check_file_integrity()) file_init();//todo: prompt before overwriting

  if (argc < 3){ 
    print_summary();
    return 0;
  }

  store_result(argv[1], argv[2]);
  print_summary();

  return 0;
}
