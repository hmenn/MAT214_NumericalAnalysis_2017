#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
  double **array;
  int row,column;
}matrix_t;

void printUsage(const char *execname){
  fprintf(stderr, "Usage: ./%s -i {filename} -m {GESP | JCB}",execname);
}

matrix_t* readMatrix(const char *filename);
void printMatrix(const matrix_t* matrix);
void solveGESP(matrix_t* matrix);

void printMatrix(const matrix_t* matrix){

  int i,j;
  int row,column;

  row = matrix->row;
  column = matrix->column;

  printf("-------------------------------------------\n");
  printf("                  Matrix\n");
  printf("-------------------------------------------\n");
  for(i=0;i<row;++i){
    for(j=0;j<column;++j){
      printf("%08.4f ",matrix->array[i][j]);
      if(j==column-2)
        printf("| " );
    }
    printf("\n");
  }
}

int main(int argc,char *argv[]){
  matrix_t *matrix=NULL;

  if(argc != 5){
    printUsage(argv[0]);
    return 1;
  }

  if((matrix=readMatrix(argv[2])) ==NULL){
    return 1;
  }

  printMatrix(matrix);
  
  return 0;
}

matrix_t* readMatrix(const char *filename){
  FILE *fp=NULL;
  matrix_t *matrix=NULL;
  int row=0,column=1,i=0,j=0;
  int junk1;
  char junk2;

  if( (fp = fopen(filename,"r"))==NULL){
    fprintf(stderr, "Please check input file: %s\n",filename);
    return NULL;
  }

  while(fscanf(fp,"%d%c",&junk1,&junk2) && junk2!='\n'){
    ++column;
  }
  rewind(fp);

  matrix = (matrix_t*)malloc(sizeof(matrix_t));
  matrix->array = (double **)malloc(sizeof(double **)*(column-1));
  for(i=0;i<column;++i)
    matrix->array[i] = (double*)malloc(sizeof(double)*column);


  for(i=0;i<column-1;++i)
    for(j=0;j<column;++j)
      fscanf(fp,"%lf%c",&matrix->array[i][j],&junk2);

  matrix->row=column-1;
  matrix->column=column;

  fclose(fp);
  return matrix;
}