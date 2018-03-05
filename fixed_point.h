#ifndef FIXED_POINT_H
#define FIXED_POINT_H

#define f (1 << 14)

int convert_int_to_fp(int n);
int convert_fp_to_int_rz(int x);
int convert_fp_to_int_rn(int x);
int add_fp(int x, int y);
int sub_fp(int x, int y);
int add_fp_int(int x, int n);
int sub_fp_int(int x, int n);
int mult_fp(int x, int y);
int mult_fp_int(int x, int n);
int mult_fp(int x, int y);
int div_fp(int x, int y);
int div_fp_int(int x, int n);

int 
convert_int_to_fp(int n)
{
    return n * f;
}

// convert fixed point to integer and round to zero
int 
convert_fp_to_int_rz(int x)
{
    return (x < 0) ? ((x - (f /2)) / f) : ((x + (f /2)) / f);
}

// convert fixed point to interger and round to nearest
int 
convert_fp_to_int_rn(int x)
{
    return x / f;
}

int 
add_fp(int x, int y)
{
    return x + y;
}

int 
sub_fp(int x, int y)
{
    return x - y;
}

int 
add_fp_int(int x, int n)
{
    return x + convert_int_to_fp(n);
}

int 
sub_fp_int(int x, int n)
{
    return x - convert_int_to_fp(n);
}

int 
mult_fp(int x, int y)
{
    return (((int64_t) x) * y / f);
}

int 
mult_fp_int(int x, int n)
{
    return x * n;
}

int 
div_fp(int x, int y)
{
    return (((int64_t) x) * f / y);
}

int 
div_fp_int(int x, int n)
{
    return x / n;
}

#endif

