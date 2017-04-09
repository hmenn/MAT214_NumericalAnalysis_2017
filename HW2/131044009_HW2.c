#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct{
  double **array;
  int row,column;
}matrix_t;

void printUsage(const char *execname){
  fprintf(stderr, "Usage: ./%s -i {filename} -m {GESP | JCB}",execname);
}

/* Read matrix from file and return an Matrix struct*/
matrix_t* readMatrix(const char *filename);

/* Print Matrint to standart output*/
void printMatrix(const matrix_t* matrix);

/* Free matrix */
void freeMatrix(matrix_t* matrix);

/* Solve matrix with Gauss Elimination with Scaled Partial Pivot */
void solveGESP(matrix_t* matrix);

void swapRows(matrix_t* matrix,int r1,int r2,double *s);

void reducePivots(matrix_t* matrix,int i);

/* find X values with using backward substitution*/
double* getXVals(const matrix_t* matrix);

/* Solve Matrix with Jacobi*/
void solveJCB(matrix_t* matrix);

int main(int argc,char *argv[]){
  matrix_t *matrix=NULL;

  int i=0;

  if(argc != 5 || strcmp(argv[1],"-i")!=0 || strcmp(argv[3],"-m")!=0 ||
      (strcmp(argv[4],"GESP")!=0 && strcmp(argv[4],"JCB"))!=0 ){
    fprintf(stderr, "Invalid parameter\n");
    printUsage(argv[0]);
    return 1;
  }


  if((matrix=readMatrix(argv[2])) ==NULL){
    fprintf(stderr, "Matrix read error\n");
    return 1;
  }

  printMatrix(matrix);
  if(strcmp(argv[4],"GESP")==0){
    solveGESP(matrix);
    double *results = getXVals(matrix);
    int size = matrix->column-1;

    printf(ANSI_COLOR_GREEN "Results:");
    for(i=0;i<size;++i)
      printf("X[%d]:%9.4f | ",i+1,results[i]);
    printf("\n" ANSI_COLOR_RESET);
  }else if(strcmp(argv[4],"JCB")==0){
    solveJCB(matrix);
  }

  //freeMatrix(matrix);
  return 0;
}

void solveJCB(matrix_t* matrix){
  int found=0;
  int i=0,j=0;
  int stopState=0;
  int step=0;

  double *oldXVals = (double *)calloc(sizeof(double),matrix->row);
  double *newXVals = (double *)calloc(sizeof(double),matrix->row);

  printf(ANSI_COLOR_GREEN "Iterations:\n" ANSI_COLOR_RESET);
  while(stopState!=matrix->row){
    printf(ANSI_COLOR_RED"Step:%d - "ANSI_COLOR_RESET,step++ );
    //printf("%d",step++ );
    for(i=0;i<matrix->row;++i)
      //printf("&%8.4f",oldXVals[i] );
      printf("X[%d]:%10f ",i,oldXVals[i]);
    printf("\\\\\n");
    stopState=0;
    for(i=0;i<matrix->row;++i){
      double res = 0;
      double stopCriteria=0;

      for(j=0;j<matrix->column-1;++j){
        if(i!=j){
          //printf("i%d-j:%d->%f*%f\n",i,j,oldXVals[j],matrix->array[i][j] );
          res+= oldXVals[j]*matrix->array[i][j];
        }
      }
      newXVals[i] =  (matrix->array[i][j]-res)/matrix->array[i][i];
      stopCriteria = fabs(newXVals[i]-oldXVals[i])/fabs(newXVals[i]);

      if(stopCriteria<0.001)
        stopState++;
      //printf("OldX:%f New:%f Stop:%f\n",oldXVals[i],newXVals[i],stopCriteria);
    }
    for(i=0;i<matrix->row;++i)
      oldXVals[i]=newXVals[i];
    if(step==50)
        break;
  }
  free(oldXVals);
  free(newXVals);
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

void swapRows(matrix_t* matrix,int r1,int r2,double *s){
  double temp ;
  for(int i=0;i<matrix->column;++i){
    temp = matrix->array[r1][i];
    matrix->array[r1][i]=matrix->array[r2][i];
    matrix->array[r2][i]=temp;
  }
  // swap scaled pivots
  temp=s[r1];
  s[r1]=s[r2];
  s[r2]=temp;
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
    printf(ANSI_COLOR_CYAN "S[%d] = %f | ",i+1,s[i]);
  printf("\n"ANSI_COLOR_RESET);

  for(i=0;i<row-1;++i){
    for(j=i;j<column;++j){
      int maxPivotIndex = i;
      double maxPivot = fabs(matrix->array[i][j]) / s[i];

      if(j==i){
        for(k=i;k<row;++k){
          double second = fabs(matrix->array[k][j]) / s[k];
          printf(ANSI_COLOR_RED "Pivot[%d,%d]:%f - " ANSI_COLOR_RESET,k+1,j+1,second);
          if(second>maxPivot){
            maxPivot=second;
            maxPivotIndex=k;
          }
        }
        printf("\nMax Pivot Index: %d, Pivot:%f\n",maxPivotIndex+1,maxPivot);
        printf("Change Row:%d with Row:%d\n",i+1,maxPivotIndex+1);
        swapRows(matrix,i,maxPivotIndex,s);
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
    printf("m_%d_%d:%f\n",i+1,index+1,coef);
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

  printf(ANSI_COLOR_BLUE "-------------------------------------------\n");
  printf("                  Matrix\n");
  printf("-------------------------------------------\n" ANSI_COLOR_RESET);
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

  while(fscanf(fp,"%lf%c",&junk1,&junk2)!=EOF && junk2!='\n'){
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