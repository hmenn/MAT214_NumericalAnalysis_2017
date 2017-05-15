package com.hasanmen;

/**
 * Created by hmenn on 15.05.2017.
 */
public class DividedDifference {
    public static double[] withNewtonDD(double[] x, double[] fx) {
        double[] output = new double[fx.length];
        for (int i = 0; i < fx.length; ++i)
            output[i] = fx[i];

        for (int i = 1; i < x.length; i++) {
            for (int j = x.length - 1; j >=i; j--) {
                if (j - i >= 0) {
                    output[j] = (output[j] - output[j - 1]) / (x[j] - x[j - i]);
                }
            }
        }
        return output;
    }
}
