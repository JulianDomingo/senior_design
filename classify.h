// Vars
typedef enum 
{ 
    undetermined,
    linear, 
    quadratic, 
    cubic, 
    quartic,
    exponential
} signal_class;

// Function prototypes
double root(double input, double n);
double *generate_sample_curve(size_t size);
double *get_strict_linear_mapping(size_t size);
bool is_voltage_within_error_margin(double v1, double v2, double error_margin);
void transform_original_curve(
        size_t size,
        double (*transformed)[size], 
        double **original_curve, 
        signal_class class);
