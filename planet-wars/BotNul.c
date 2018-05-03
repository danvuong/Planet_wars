#include<stdio.h>

void NulBot(char fichier)
{
  FILE* fd = fopen(fichier,"r+");
  fputs("go",fichier);
  fclose(fichier);
}
