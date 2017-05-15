package com.hasanmen;

/**
 * Created by hmenn on 15.05.2017.
 */
public class LeastSquare {
    public static double[] polynomial(double[] x, double[] y, int m) {

        int equNum = x.length - m;
        double[][] a = new double[equNum][equNum + 1];

        for (int i = 0; i < equNum; ++i) {
            for (int j = 0; j < equNum + 1; ++j) {
                for (int t = 0; t < x.length; ++t) {
                    if (j == equNum) { // calculate b
                        a[i][j] += y[t] * Math.pow(x[t], i);
                    } else
                        a[i][j] += Math.pow(x[t], j + i);
                }
            }
        }

        System.out.printf("\nx Values:\n");
        for(int i=0;i<x.length;++i)
            System.out.printf("x[%d]:%f ",i,x[i]);
        System.out.printf("\n");

        System.out.printf("\ny Values:\n");
        for(int i=0;i<y.length;++i)
            System.out.printf("y[%d]:%f ",i,y[i]);
        System.out.printf("\n\n");



        System.out.println("Three normal equations are:");
        System.out.printf("%6s %6s %6s %6s\n", "x1", "x2", "x3", "b");
        printArray(a);

        System.out.printf("\nApply Gaussian to solve matrix\n");
        double [] sol = solveWithGaussian(a);

        return sol;
    }

    private static void printArray(double[][] array) {
        for (int i = 0; i < array.length; ++i) {
            for (int j = 0; j < array[0].length; ++j) {
                System.out.printf("%6.4f ", array[i][j]);
            }
            System.out.println(" ");
        }
    }


    private static double[] solveWithGaussian(double[][] array) {

        double[] res = new double[array.length];
        double[] s = new double[array.length];
        int i, j, k;

        for (i = 0; i < array.length; ++i) {
            s[i] = Math.abs(array[i][0]);
            for (j = 0; j < array.length; ++j) {
                if (Math.abs(array[i][j]) > s[i])
                    s[i] = Math.abs(array[i][j]);

            }
        }

        /*for (i = 0; i < s.length; ++i)
            System.out.println("S[" + i + "] = " + s[i]);*/

        for (i = 0; i < array.length - 1; ++i) {
            for (j = i; j < array.length; ++j) {
                int maxPivotIndex = i;
                double maxPivot = Math.abs(array[i][j]) / s[i];

                if (i == j) {
                    for (k = i; k < array.length; ++k) {
                        double second = Math.abs(array[k][j]) / s[k];
                        //System.out.printf("Pivot[%d,%d]:%f\n",k+1,j+1,second);
                        if (second > maxPivot) {
                            maxPivot = second;
                            maxPivotIndex = k;
                        }
                    }
                    //System.out.printf("\nMax Pivot Index: %d, Pivot:%f\n",maxPivotIndex+1,maxPivot);
                    //System.out.printf("Change Row:%d with Row:%d\n",i+1,maxPivotIndex+1);
                    swapRows(array, i, maxPivotIndex, s);
                    reducePivots(array, i);
                }
            }
        }

        printArray(array);
        double []sol = applyBackwardSubs(array);

        return sol;
    }

    private static double [] applyBackwardSubs(double[][] array) {
        int column = array[0].length;
        int row = array.length;
        double[] sol = new double[row];

        //printf("%f - %f \n", matrix->array[row-1][column-1],matrix->array[row-1][column-2]);
        sol[column - 2] = array[row - 1][column - 1] / array[row - 1][column - 2];

        for (int i = row - 2; i >= 0; --i) {
            double sum = 0;
            for (int j = column - 2; j > i; --j) {
                //printf("%d,%d,%f,%f\n",i,j,matrix->array[i][j],array[j] );
                sum += array[i][j] * sol[j];
            }
            sol[i] = (array[i][column - 1] - sum) / array[i][i];
        }
        return sol;
    }


    private static void swapRows(double[][] array, int r1, int r2, double[] s) {
        double temp;
        for (int i = 0; i < array.length + 1; ++i) {
            temp = array[r1][i];
            array[r1][i] = array[r2][i];
            array[r2][i] = temp;
        }
        temp = s[r1];
        s[r1] = s[r2];
        s[r2] = temp;
    }

    private static void reducePivots(double[][] array, int index) {
        for (int i = index + 1; i < array.length; ++i) {
            double coef = array[i][index] / array[index][index];
            //System.out.printf("m_%d_%d:%f\n",i+1,index+1,coef);
            for (int j = 0; j < array[0].length; ++j) {
                array[i][j] -= coef * array[index][j];
            }
        }
    }
}
