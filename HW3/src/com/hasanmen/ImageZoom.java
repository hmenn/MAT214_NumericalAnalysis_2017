package com.hasanmen;

/**
 * Created by hmenn on 14.05.2017.
 */
public class ImageZoom {
    public static int[][] withNNInterpolation(int[][] input, int zFactor) {

        int ic = 0, ir = 0;
        int newSize = input.length * zFactor;
        int[][] output;

        if (zFactor < 2)
            return input;

        output = new int[newSize][newSize];

        for (int i = 0; i < newSize; ++i) {
            if (i % zFactor == 0 && i != 0)
                ++ir;
            ic = 0;

            for (int j = 0; j < newSize; ++j) {
                if (j % zFactor == 0 && j != 0)
                    ++ic;
                output[i][j] = input[ir][ic];
            }
        }

        return output;
    }

    public static double[][] withBilinearInterpolation(int[][] input, int zFactor) {
        int y = 0, x = 0;
        double[][] newArray = new double[input.length * zFactor][input.length * zFactor];

        double step = 1.0 / (double) zFactor;
        for (int i = 0; i < input.length - 1; i++) {
            for (int j = 0; j < input.length - 1; j++) {
                int value1 = input[j][i];
                int value2 = input[j + 1][i];

                for (int k = 0; k < zFactor; k++) {
                    for (int l = 0; l < zFactor; l++) {
                        double a = 1.0 - (step * l);
                        double ma = 1.0 - (step * (zFactor - l));
                        double b = 1.0 - (step * k);
                        double mb = 1.0 - (step * (zFactor - k));
                        int tempUp = (int) (value1 * a + value2 * ma);
                        int tempDown = (int) (value1 * a + value2 * ma);
                        newArray[x + l][y + k] = (int) (tempUp * b + tempDown * mb);
                    }
                }
                x += zFactor;
            }
            x=0;
            y += zFactor;
        }
        return newArray;
    }
}
