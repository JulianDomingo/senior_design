#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include <inttypes.h>

#include "classify.h"

// Change as specified
static const double dac_voltage = 3.3;
static const double target_voltage = 2.75;
static const double trim_error_margin = 0.05;
static const double noise_threshold = 0.005;


double 
*get_strict_linear_mapping(size_t size)
{
    double voltage_increment = dac_voltage / (double) size;         
    double *strict_linear = (double *) malloc(size * sizeof(double)); 

    for (int i = 0; i < (int) size; i += 1)
    {
        strict_linear[i] = ((double) i * voltage_increment);                        
    }

    return strict_linear;
}


double 
root(double input, double n)
{
    return pow(input, (1.0 / n));
}


bool 
is_voltage_within_error_margin(double v1, double v2, double error_margin)
{
    return (fabs(v1 - v2) <= error_margin);
}


/*
 * Generates test signals of the following type:
 *
 * 1. Linear
 * 2. Quadratic
 * 3. Cubic
 * 4. Quartic
 * 5. TODO: Exponential
 */
double 
*generate_sample_curve(signal_class class, size_t size)
{
    double *curve = (double *) malloc(size * sizeof(double));
    double voltage_increment = dac_voltage / (double) size;         
    /*double mu = 0.0;*/
    /*double sigma = 1.0;*/

    for (int i = 0; i < size; i += 1) 
    {
        curve[i] = (double) (((double) i) * voltage_increment);
    }

    // TODO: Use commented-out code once integrated with HW 
    /*int counter = 0;
    while (counter < size)
    {
        curve[counter] = ADC_In();
        counter += 1;    
    }*/

    // TODO: remove below code once able to read input from ADC
    switch (class)
    {
        case linear:
            // Already linear, so only add noise
            for (int i = 0; i < size; i += 1)
            {
                curve[i] += noise_threshold; 
            }

            break;

        case exponential:
            for (int i = 0; i < size; i += 1)
            {
                curve[i] = exp(curve[i]) + noise_threshold; 
            }

            break;

        default:
            // Quadratic, Cubic, Quartic
            for (int i = 0; i < size; i += 1)
            {
                curve[i] = pow(curve[i], (double) class) + noise_threshold;
            }

            break;
    }

    return curve;
}


bool 
can_fit_strict_linear(double *curve_to_test, double *strict_linear, size_t size)
{
    // Must first determine error margin based on precision of DAC.
    double strict_linear_error_margin = target_voltage / (double) size;

    // Obtain the closest input based on target voltage. 
    // This is a deterministic linear search, so it doesn't account to the runtime complexity.
    int closest_input_value = 0;

    for (int i = 0; i < size; i += 1)
    {
        if (is_voltage_within_error_margin(
                    target_voltage, 
                    strict_linear[i], 
                    strict_linear_error_margin))
        {
            closest_input_value = i;
            break;
        }
    }

    return (is_voltage_within_error_margin(
                target_voltage,
                curve_to_test[closest_input_value],
                trim_error_margin));
}


bool 
can_fit_monotonic(double *curve_to_test, size_t size)
{
    // TODO: Implement binary search on curve_to_test
    return false;
}


void 
linearize_original_curve(
        size_t size,
        double (*transformed)[size], 
        double **original_curve, 
        signal_class class)
{
    for (int i = 0; i < size; i += 1) {
        // TODO: Potentially change to transform only a subset of the points 
        // instead of the entire curve. 
        (*transformed)[i] = root((double) (*original_curve)[i], (double) class); 
    }
}


/*int */
/*main()*/
/*{*/
    /*signal_class result_class = undetermined;*/

    /*uint8_t n = 12;*/
    /*uint8_t base = 2;*/
    /*size_t orig_size = pow(base, n); */

    /*double *strict_linear = generate_sample_curve(linear, orig_size);*/
    /*double transformed[orig_size];*/

    /*double *original_curve = generate_sample_curve(quartic, orig_size);*/

    /*for (int class = linear; class <= exponential; class += 1)*/
    /*{*/
        /*switch (class)*/
        /*{*/
            /*case linear:*/
                /*printf("Testing linear...\n");*/
                /*if (can_fit_strict_linear(original_curve, strict_linear, orig_size) ||*/
                    /*can_fit_monotonic(original_curve, orig_size))*/
                /*{*/
                    /*result_class = linear;*/
                    /*printf("The signal was classified as linear.\n");*/
                    /*exit(EXIT_SUCCESS);*/
                /*}*/

                /*break;*/

            /*case exponential:*/
                /*[>memcpy(transformed, original_curve, orig_size * sizeof(double));<]*/

                /*// TODO: Figure out how to trasnform without natural log*/
                /*[>printf("The signal was classified as exponential.\n");<]*/
                /*[>exit(EXIT_SUCCESS);<]*/

                /*break;*/

            /*default:*/
                /*printf("Testing %s...\n", (class == 2) ? "quadratic" : (class == 3) ? */
                        /*"cubic" : "quartic");*/

                /*// Quadratic, Cubic, and Quartic inputs.*/
                /*memcpy(transformed, original_curve, orig_size * sizeof(double));*/
                /*linearize_original_curve(orig_size, &transformed, &original_curve, class);*/

                /*if (can_fit_strict_linear(transformed, strict_linear, orig_size) ||*/
                    /*can_fit_monotonic(transformed, orig_size))*/
                /*{*/
                    /*switch (class) */
                    /*{*/
                        /*case quadratic:*/
                            /*result_class = quadratic;*/
                            /*printf("The signal was classified as quadratic.\n");*/
                            /*break;*/
                        /*case cubic:*/
                            /*result_class = cubic;*/
                            /*printf("The signal was classified as cubic.\n");*/
                            /*break;*/
                        /*case quartic:*/
                            /*result_class = quartic;*/
                            /*printf("The signal was classified as quartic.\n");*/
                            /*break;*/
                    /*}*/

                    /*exit(EXIT_SUCCESS);*/
                /*}*/
        /*}*/
    /*}*/

    /*if (result_class == undetermined) { printf("The signal was unable to be classified.\n"); }*/

    /*return 0;*/
/*}*/
