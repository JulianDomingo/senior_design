/*
 * Creates a mapping of index to it's respective nth root value in
 * fixed-point notation, for n = [2, 4].
 * 
 * Specify size as necessary.
 */
#include <stdio.h>

#include "fixed_point.h"

int 
main()
{
    FILE *fp;
    int i, nth_root_fp;

    int size = 1024;

    printf("Size: %d\n", size);

    fp = fopen("mappings.txt", "w");         

    for (int n = 2; n <= 4; n += 1)
    {
        fprintf(fp, "%d, ", 0);
        fprintf(fp, "%d, ", convert_int_to_fp(1));

        for (int i = 2; i < size; i += 1)
        {
            switch (n)
            {
                case 2:
                    nth_root_fp = fp_pow(convert_int_to_fp(i), QUADRATIC_ROOT_FP);
                    break;
                case 3:
                    nth_root_fp = fp_pow(convert_int_to_fp(i), CUBIC_ROOT_FP);
                    break;
                case 4:
                    nth_root_fp = fp_pow(convert_int_to_fp(i), QUARTIC_ROOT_FP);
                    break;
            }

            printf("Writing (%d)^(1/%d) = %d to the file in fixed point...\n", i, n, nth_root_fp);

            if (i == size - 1)
            {
                fprintf(fp, "%d", nth_root_fp);
            }
            else
            {
                fprintf(fp, "%d, ", nth_root_fp);
            }
        }

        // Delimiter for mappings.
        fprintf(fp, "\n");
    }

    fclose(fp);
    return 0;
}
