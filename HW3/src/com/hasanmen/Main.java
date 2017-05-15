package com.hasanmen;

public class Main {

    public static void main(String[] args) {

        System.out.println("\n#############################\nPART1.\n a) Nearest Neighbor Interpolation");
        int[][] array = new int[10][10];
        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j)
                array[i][j] = (i + 1) * (j + 1);

        System.out.println("Simple 2D Array");
        print2DArray(array);

        System.out.println("Zoom with 2 factor");
        int[][] out = ImageZoom.withNNInterpolation(array, 2);
        print2DArray(out);

        System.out.println("Zoom with 3 factor");
        int[][] out2 = ImageZoom.withNNInterpolation(array, 3);
        print2DArray(out2);

        System.out.println("\n#############################\nPART1.\n b) Bilinear Interpolation");
        System.out.println("Simple 2D Array");
        print2DArray(array);

        System.out.println("Zoom with 2 factor");
        double[][] outBilinear2 = ImageZoom.withBilinearInterpolation(array, 2);
        print2DArray(outBilinear2);

        System.out.println("Zoom with 3 factor");
        double[][] outBilinear3 = ImageZoom.withBilinearInterpolation(array, 3);
        print2DArray(outBilinear3);

        System.out.println("\n#############################\nPART2. Newton's Divided-Difference Formula");
        double [] x = new double[]{1.0,1.3,1.6,1.9,2.2};
        double [] y = new double[]{0.7651977,0.6200860,0.4554022,0.2818186,0.1103623};
        for(int i=0;i<x.length;++i)
            System.out.println("X["+i+"]:"+x[i]+"\tf(x"+i+")="+y[i]);
        System.out.println("");
        double [] outDD = DividedDifference.withNewtonDD(x,y);
        for(int i=0;i<outDD.length;++i)
            System.out.printf("Divided Differences [%d]:%-10.6f\n",i,outDD[i]);


        // PART3. Least Square Polynomial
        System.out.println("\n#############################\nPART3. Least Square Polynomial");
        double[] xx = new double[]{0.00, 0.25, 0.50, 0.75, 1.0};
        double[] fx = new double[]{1.0, 1.2840, 1.6487, 2.1170, 2.7183};
        double[] out3 = LeastSquare.polynomial(xx, fx, 2);

        System.out.printf("\nSolution:\n");
        for (int i = 0; i < out3.length; ++i)
            System.out.printf("X[%d]:%f ", i, out3[i]);
        System.out.printf("\n");
    }

    public static void print2DArray(int[][] array) {
        System.out.println("[");
        for (int i = 0; i < array.length; ++i) {
            for (int j = 0; j < array[i].length; ++j)
                System.out.printf("%3d ", array[i][j]);
            System.out.println("");
        }
        System.out.println("]");
    }

    public static void print2DArray(double[][] array) {
        System.out.println("[");
        for (int i = 0; i < array.length; ++i) {
            for (int j = 0; j < array[i].length; ++j)
                System.out.printf("%5.2f ", array[i][j]);
            System.out.println("");
        }
        System.out.println("]");
    }

}
