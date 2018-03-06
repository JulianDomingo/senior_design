#ifndef FIXED_POINT_H
#define FIXED_POINT_H

#define base 16
#define f (1 << 16)

// Fixed-point representation of (1 / n) with Q = 16 (15.16 format) for n = [2, 4].
#define QUADRATIC_ROOT_FP 32768
#define CUBIC_ROOT_FP 21845
#define QUARTIC_ROOT_FP 16384

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

static int fp_ln(int val);
static int fp_exp(int val);
static int fp_pow(int ebase, int exponent);
static unsigned fp_sqrt(unsigned val);
static int32_t clz(uint32_t x);

/* Computing the number of leading zeros in a word. */
static int32_t 
clz(uint32_t x)
{
    int32_t n;

    /* See "Hacker's Delight" book for more details */
    if (x == 0) return 32;
    n = 0;
    if (x <= 0x0000FFFF) {n = n +16; x = x <<16;}
    if (x <= 0x00FFFFFF) {n = n + 8; x = x << 8;}
    if (x <= 0x0FFFFFFF) {n = n + 4; x = x << 4;}
    if (x <= 0x3FFFFFFF) {n = n + 2; x = x << 2;}
    if (x <= 0x7FFFFFFF) {n = n + 1;}

  return n;
}

static int 
fp_ln(int val)
{
    int fracv, intv, y, ysq, fracr, bitpos;
    /*
    fracv    -    initial fraction part from "val"
    intv    -    initial integer part from "val"
    y        -    (fracv-1)/(fracv+1)
    ysq        -    y*y
    fracr    -    ln(fracv)
    bitpos    -    integer part of log2(val)
    */
    
    const int ILN2 = 94548;        /* 1/ln(2) with 2^16 as base*/
    const int ILOG2E = 45426;    /* 1/log2(e) with 2^16 as base */

    const int ln_denoms[] = {
        (1<<base)/1,
        (1<<base)/3,
        (1<<base)/5,
        (1<<base)/7,
        (1<<base)/9,
        (1<<base)/11,
        (1<<base)/13,
        (1<<base)/15,
        (1<<base)/17,
        (1<<base)/19,
        (1<<base)/21,
    };

    /* compute fracv and intv */
    bitpos = 15 - clz(val);
    if(bitpos >= 0){
        ++bitpos;
        fracv = val>>bitpos;
    } else if(bitpos < 0){
        /* fracr = val / 2^-(bitpos) */
        ++bitpos;
        fracv = val<<(-bitpos);
    }

    // bitpos is the integer part of ln(val), but in log2, so we convert
    // ln(val) = log2(val) / log2(e)
    intv = bitpos * ILOG2E;

    // y = (ln_fraction_value−1)/(ln_fraction_value+1)
    y = ((int64_t)(fracv-(1<<base))<<base) / (fracv+(1<<base));

    ysq = (y*y)>>base;
    fracr = ln_denoms[10];
    fracr = (((int64_t)fracr * ysq)>>base) + ln_denoms[9];
    fracr = (((int64_t)fracr * ysq)>>base) + ln_denoms[8];
    fracr = (((int64_t)fracr * ysq)>>base) + ln_denoms[7];
    fracr = (((int64_t)fracr * ysq)>>base) + ln_denoms[6];
    fracr = (((int64_t)fracr * ysq)>>base) + ln_denoms[5];
    fracr = (((int64_t)fracr * ysq)>>base) + ln_denoms[4];
    fracr = (((int64_t)fracr * ysq)>>base) + ln_denoms[3];
    fracr = (((int64_t)fracr * ysq)>>base) + ln_denoms[2];
    fracr = (((int64_t)fracr * ysq)>>base) + ln_denoms[1];
    fracr = (((int64_t)fracr * ysq)>>base) + ln_denoms[0];
    fracr =  ((int64_t)fracr * (y<<1))>>base;

    return intv + fracr;
}

static 
int fp_exp(int val)
{
    int x;

    x = val;
    x = x - (((int64_t)x*(fp_ln(x) - val))>>base);
    x = x - (((int64_t)x*(fp_ln(x) - val))>>base);
    x = x - (((int64_t)x*(fp_ln(x) - val))>>base);
    x = x - (((int64_t)x*(fp_ln(x) - val))>>base);
    return x;
}

static int 
fp_pow(int ebase, int exponent)
{
    return fp_exp(((int64_t)exponent * fp_ln(ebase))>>base);
}

static unsigned 
fp_sqrt(unsigned val)
{
    unsigned x;
    int bitpos;
    unsigned long long v;

    if(!val)
        return val;

    /* clz = count-leading-zeros. bitpos is the position of the most significant bit,
        relative to "1" or 1 << base */
    bitpos = base - clz(val);
    
    /* Calculate our first estimate.
        We use the identity 2^a * 2^a = 2^(2*a) or:
         sqrt(2^a) = 2^(a/2)
    */
    if(bitpos > 0u) /* val > 1 */
        x = (1u<<base)<<(bitpos >> 1u);
    else if(bitpos < 0) /* 0 < val < 1 */
        x = (1u<<base)<<((unsigned)(-bitpos) << 1u);
    else /* val == 1 */
        x = (1u<<base);
    
    /* We need to scale val with base due to the division.
       Also val /= 2, hence the subtraction of one*/
    v = (unsigned long long)val <<  (base - 1u);

    /* The actual iteration */
    x = (x >> 1u) + v/x;
    x = (x >> 1u) + v/x;
    x = (x >> 1u) + v/x;
    x = (x >> 1u) + v/x;
    return x;
}

/*****************************************************************/ 

// Multiplication, addition, subtraction, and division
// fixed-point arithmetic.
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
int fp_abs(int fp);
int fp_nth_root(int x, int n);
int fp_pow(int fp_base, int n);
int32_t sqrt_int_fp( int32_t v);

int 
convert_int_to_fp(int n)
{
    return n * f;
}

// convert fixed point to integer and round to zero
int 
convert_fp_to_int_rz(int x)
{
    return (x < 0) ? ((x - (f / 2)) / f) : ((x + (f / 2)) / f);
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
