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
void freeMatrix(matrix_t* matrix);
void swapRows(matrix_t* matrix,int r1,int r2);
void reducePivots(matrix_t* matrix,int i);
double* getXVals(const matrix_t* matrix);

int main(int argc,char *argv[]){
  matrix_t *matrix=NULL;
  int i=0;

  if(argc != 5){
    printUsage(argv[0]);
    return 1;
  }

  if((matrix=readMatrix(argv[2])) ==NULL){
    return 1;
  }

  printMatrix(matrix);
  solveGESP(matrix);
  double *results = getXVals(matrix);
  int size = matrix->column-1;

  for(i=0;i<size;++i)
    printf("X[%d]:%9.4f | ",i+1,results[i]);
  printf("\n");



  //freeMatrix(matrix);

  return 0;
}

void freeMatrix(matrix_t* matrix){
  int i=0;
  for(i=0;i<matrix->row;++i)
    free(matrix->array[i]);
}


double* getXVals(const matrix_t* matrix){
  int column = matrix->column;
  int row = matrix->row;
  double * array = malloc(sizeof(double)*(column-1));

  //printf("%f - %f \n", matrix->array[row-1][column-1],matrix->array[row-1][column-2]);
  array[column -2] = matrix->array[row-1][column-1]/matrix->array[row-1][column-2];


  for(int i=row-2;i>=0;--i){
    double sum=0;
    for(int j=column-2;j>i;--j){
      //printf("%d,%d,%f,%f\n",i,j,matrix->array[i][j],array[j] );
      sum+= matrix->array[i][j]*array[j];

    }

    array[i] = (matrix->array[i][column-1] - sum) / matrix->array[i][i];
  }


  return array;
}

void swapRows(matrix_t* matrix,int r1,int r2){
  for(int i=0;i<matrix->column;++i){
    double temp = matrix->array[r1][i];
    matrix->array[r1][i]=matrix->array[r2][i];
    matrix->array[r2][i]=temp;
  }
}



void solveGESP(matrix_t* matrix){
  int i=0,j=0,k=0;
  int row = matrix->row;
  int column = matrix->column;
  double *s  = (double *)malloc(sizeof(double)*(column-1));

  printf("Row: %d, Column:%d\n",row,column);

  /* finding scaled partial pivots */
  for(i=0;i<row;++i){
    s[i] = fabs(matrix->array[i][0]);
    for(j=0;j<column-1;++j){
      if(fabs(matrix->array[i][j]) > s[i])
        s[i] = fabs(matrix->array[i][j]);
    }
  }

  for(i=0;i<column-1;++i)
    printf("S[%d] = %f | ",i+1,s[i]);
  printf("\n");

  for(i=0;i<row-1;++i){
    for(j=i;j<column;++j){
      int maxPivotIndex = i;
      double maxPivot = fabs(matrix->array[i][j]) / s[i];
      //printf("MaxPivot:%f - ",maxPivot);

      for(k=i+1;k<row;++k){
        double second = fabs(matrix->array[k][j]) / s[k];
        //printf("Second:%f\n",second );
        if(second>maxPivot){
          maxPivot=second;
          maxPivotIndex=k;
        }
      }

      if(j==i){
        printf("Max Pivot Index: %d, Pivot:%f\n",maxPivotIndex+1,maxPivot);
        printf("Change Row:%d with Row:%d\n",i+1,maxPivotIndex+1);
        swapRows(matrix,i,maxPivotIndex);
        reducePivots(matrix,i); // i nin alt sutununu sıfırla
        printMatrix(matrix);
      }
    }
  }

}

void reducePivots(matrix_t* matrix,int index){

  int i,j;
  for(i=index+1;i<matrix->row;++i){
    double coef = matrix->array[i][index] / matrix->array[index][index];
    printf("Coeff:%f\n",coef);
    for(j=0;j<matrix->column;++j){
      matrix->array[i][j] = matrix->array[i][j] - coef * matrix->array[index][j];
    }
  }

}

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
      printf("%08.3f ",matrix->array[i][j]);
      if(j==column-2)
        printf("| " );
    }
    printf("\n");
  }
}

matrix_t* readMatrix(const char *filename){
  FILE *fp=NULL;
  matrix_t *matrix=NULL;
  int row=0,column=1,i=0,j=0;
  double junk1;
  char junk2;

  if( (fp = fopen(filename,"r"))==NULL){
    fprintf(stderr, "Please check input file: %s\n",filename);
    return NULL;
  }

  while(fscanf(fp,"%lf%c",&junk1,&junk2) && junk2!='\n'){
    ++column;
  }
  printf("%d\n",column );
  rewind(fp);

  matrix = (matrix_t*)malloc(sizeof(matrix_t));
  matrix->array = (double **)malloc(sizeof(double *)*(column-1));
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