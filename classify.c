#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <math.h>

// "inputs" is for testing purposes. We'll know the size of the input array
// before classification of the curve occurs
/*int root(int input, int n)*/
/*{*/
  /*return round(pow(input, 1./n));*/
/*}*/

uint8_t n = 6;
uint8_t base = 2;
/*size_t size = pow(base, n); */
/*uint16_t inputs[size]; */

uint32_t test = 1;
printf("%d", test);

// Try linear
// [Samuel's code here]

// Try n = 2 to n = 4 degree polynomials
/*for (int n = 2; n <= 4; n += 1) {*/
    // Potentially change to transform only a subset of the points instead of the entire curve
    /*uint16_t transformed[size];*/
    /*memcpy(transformed, inputs, size * sizeof(uint16_t));*/

    // Compute the appropriate transformation.
    /*for (int i = 0; i < size; i += 1) {*/
        /*transformed[i] = */
    /*}*/

    // For each transformed input array, try to fit to a perfectly linear curve and a monotonically increasing curve (bsearch)
/*}*/

// Try exponential
// TODO: Figure out how to do natural log of a value (no natural log functionality for the board we're using)
