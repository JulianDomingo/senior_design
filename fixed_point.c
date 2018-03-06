#include <stdio.h>
#include <stdlib.h>

#include "fixed_point.h"

int
main()
{
    int fp_base = convert_int_to_fp(41);
    int decimal_base = 41;
    
    for (int root = 2; root <= 4; root += 1)
    {
        int result;

        switch (root) 
        {
            case 2:
                result = fp_pow(fp_base, QUADRATIC_ROOT_FP);
                break;

            case 3:
                result = fp_pow(fp_base, CUBIC_ROOT_FP);
                break;

            case 4:
                result = fp_pow(fp_base, QUARTIC_ROOT_FP);
                break;
        }
        
        printf("The fixed-point value of (%d)^(1 / %d) is: %d\n", decimal_base, root, result);
    }
}
