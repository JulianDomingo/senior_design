#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>

#include "classify.h"

double root(double input, double n)
{
  return pow(input, (1.0 / n));
}

int main()
{
    uint8_t n = 12;
    uint8_t base = 2;

    // The size of our input array will be be pre-determined in our final code.
    size_t size = pow(base, n); 
    uint64_t inputs[size]; 

    for (int value = 0; value < size; value += 1) 
    {
        inputs[value] = value; 
        printf("%d\n", inputs[value]);
    }

    // Try linear

    // Try n = 2 to n = 4 degree polynomials
    for (int n = 2; n <= 4; n += 1) {
        uint64_t transformed[size];
        memcpy(transformed, inputs, size * sizeof(uint64_t));

        // Compute the appropriate transformation.
        for (int i = 0; i < size; i += 1) {
            // TODO: Potentially change to transform only a subset of the points instead of the entire curve.
            // Take the nth root of the original input
            transformed[i] = root(inputs[i], n); 
            printf("%f\n", transformed[i]);
        }

        // For each transformed input array, try to fit to a perfectly linear curve
        // TODO: Get corresponding input value from target voltage using constant mapping of a 
        // perfectly linear curve, and use the input value to obtain a corresponding output
        // voltage using the transformed curve. Compare the two output voltages; if their
        // difference is within the error margin we specify:
        // 1. Use the original (untransformed) input value as our trim solution (the input value is a bit combination).
        // 2. Classify the original input curve as an "n" degree polynomial.

        // NOTE: unnecessary to "re-transform" the curve since our original input signal is
        // untampered.

        // Otherwise, we try fitting the input signal as a monotonically inc./dec. curve using a binary search to find the best bit combination to trim.
        // TODO: Perform binary search on the "transformed" array (terminates once error margin reached)
        // If a combination resulting in an acceptable error margin is found, perform steps 1. and 2. as explained for the strictly linear case.
    }

    // Try exponential
    // TODO: Figure out how to do natural log of a value (no natural log functionality for the board we're using)

    return 0;
}
