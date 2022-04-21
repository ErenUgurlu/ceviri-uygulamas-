#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "dllist.h"

int main(int argc, char **argv)
{
  IS sozluk;
  IS input;
  int i;
  int j;
  int isHave;
  int countTrue = 0;
  int countFalse = 0;

  
  Dllist list = new_dllist();
  Dllist tmpList;

  if (argc != 4) { fprintf(stderr, "Yanlis formatta girdi(bin/ceviri dil txt/input.txt txt/sozluk.txt formatini kullanin)\n"); exit(1); }
 
  /* Open the file as an inputstruct.  Error check. */

  
  input = new_inputstruct(argv[2]);
  sozluk = new_inputstruct(argv[3]);

  if(!strcmp(argv[1],"tr")&& !strcmp(argv[2],"txt/input.txt") && !strcmp(argv[3],"txt/sozluk.txt"))
  {
    while(get_line(input) >= 0) 
    {
      for (j = 0; j < input->NF; j++) 
      {
        isHave = 0;
        sozluk = new_inputstruct(argv[3]);
        while(get_line(sozluk) >= 0) 
        {
          for (i = 0; i < sozluk->NF; i++)
          {
            if(!strcmp(sozluk->fields[i],input->fields[j]))
            {
              dll_append(list, new_jval_s(strdup(sozluk->fields[i-1])));
              isHave=1;
              countTrue = countTrue+1;
            }
          }
        }
        if(isHave == 0)
        {
          dll_append(list, new_jval_s(strdup(input->fields[j])));
          countFalse = countFalse +1;
        }
          
      }
    }
  	
  }
  else if(!strcmp(argv[1],"eng") && !strcmp(argv[2],"txt/input.txt") && !strcmp(argv[3],"txt/sozluk.txt"))
  {
    while(get_line(input) >= 0) 
    {
      for (j = 0; j < input->NF; j++) 
      {
        isHave = 0;
        sozluk = new_inputstruct(argv[3]);
        while(get_line(sozluk) >= 0) 
        {
          for (i = 0; i < sozluk->NF; i++)
          {
            if(!strcmp(sozluk->fields[i],input->fields[j]))
            {
              dll_append(list, new_jval_s(strdup(sozluk->fields[i+1])));
              isHave=1;
              countTrue = countTrue+1;
            }
          }
        }
        if(isHave == 0)
        {
          dll_append(list, new_jval_s(strdup(input->fields[j])));
          countFalse = countFalse +1;
        }
          
      }
    }
  }
  else
  {
    fprintf( stderr,"Yanlis formatta girdi(bin/ceviri dil txt/input.txt txt/sozluk.txt formatini kullanin)\n"); exit(1);
  }
  /* Read each line with get_line().  Print out each word. */
  tmpList = list->flink;

  FILE *f = fopen("txt/output.txt", "w");
  if (f == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }

  while (tmpList != list) {
    
    fprintf(f,"%s ", tmpList->val.s);
    tmpList = tmpList->flink;
  }

  printf("Karşılaştırılan Kelime Sayısı: %d \n", countTrue+countFalse);
  printf("Çevirisi Başarılı Kelime Sayısı : %d \n", countTrue);
  printf("Çevirisi Yapılamamış Kelime Sayısı : %d \n", countFalse);

  jettison_inputstruct(sozluk);
  jettison_inputstruct(input);
  return 0;
}
