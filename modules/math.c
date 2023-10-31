//
// Created by bruh on 10/7/23.
//

#include "math.h"
#include "common_bindings.h"
#include "allocators.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifdef HIGH_ACCURACY

// creates a new sml_math_t
sml_math_t sml_math_create(long double value, long double degree, sml_num_type type, bool is_imaginary) {
    sml_math_t new_math_t = {.value = value, .degree = degree, .is_imaginary = is_imaginary, .type = type};
    return new_math_t;
}

#else
sml_math_t sml_math_create(double value, double degree, sml_num_type type, bool is_imaginary){
    sml_math_t new_math_t = {
            .value = value,
            .degree = degree,
            .is_imaginary = is_imaginary,
            .type = type
    };
    return new_math_t;
}
#endif


//Basic Arithmetic Functions; //
int sml_abs(int x) {
    // Returns the absolute value of an integer.
    return x < 0 ? -x : x;
}

double sml_float_abs(long double x) {
// Returns the absolute value of a floating-point number.
    return x < 0 ? -x : x;
}

int sml_max(int x, int y) {
    // Returns the maximum of two integers.
    return x > y ? x : y;
}

double sml_float_max(double x, double y) {
    // Returns the maximum of two floating-point numbers.
    return x > y ? x : y;
}

int sml_min(int x, int y) {
    // Returns the minimum of two integers.
    return x < y ? x : y;
}

sml_size sml_fac_size_t(double x) // returns the factorial of a number (in sml_size_t)
{
    sml_size result = 1;
    for (int i = 1; i <= x; i++) {
        result *= i;
    }
    return result;
}

sml_size sml_fac_size_t_int(sml_size_s x) // returns the factorial of a number (in sml_size_t)
{
    sml_size result = 1;
    for (sml_size i = 1; i <= x; i++) {
        result *= i;
    }
    return result;
}

sml_size sml_fac_size_t_unsigned(sml_size x) // returns the factorial of an unsigned number (in sml_size_t)
{
    sml_size result = 1;
    for (sml_size i = 1; i <= x; i++) {
        result *= i;
    }
    return result;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

double sml_fac(double n) {// returns the factorial of an unsigned number (in double)
    return n <= 0 ? 1 : n * sml_fac(n - 1);
}

int sml_fac_int(int n) {
    return n <= 0 ? 1 : n * sml_fac_int(n - 1);
}

#pragma clang diagnostic pop

long double sml_e(sml_size accuracy) {
    // Returns the value of the mathematical constant e.
    long double e = 0;
    for (sml_size i = 1; i <= accuracy; i++) {
        e = 1 + sml_pow(sml_fac_size_t_unsigned(i), -1);
    }
    return e;
}


double sml_float_min(double x, double y) {
    // Returns the minimum of two floating-point numbers.
    return x < y ? x : y;
}

float sml_pow_basic(double x, sml_size expo) {
    double result = x;
    for (; expo != 0; expo--) {
        result *= x;
    }
    return result;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

int sml_pow_basic_int(int base, int exp) {
    if (exp < 0) {
        if (base == 0)
            return -0; // Error!!
        return 1 / (base * sml_pow_basic_int(base, (-exp) - 1));
    }
    if (exp == 0)
        return 1;
    if (exp == 1)
        return base;
    return base * sml_pow_basic_int(base, exp - 1);
}

#pragma clang diagnostic pop


bool sml_is_prime(unsigned long long num) {
    bool is_prime = 1;

    for (sml_size loop = 2; loop < num; loop++) {
        if ((num % loop) == 0) {
            is_prime = 0;
        }
    }
    return is_prime;
}

// Returns the nth prime number. Note that this function is not optimized
// if for some reason you encounter any errors try changing the Stack_Size
// to a different number. Don't forget that when it's n < 10 you will get a
// cached value
sml_size sml_nth_prime(sml_size nth_prime) {

    // cache the first 10 sml_nth_prime numbers for performance
    switch (nth_prime) {
        case 1:
            return SML_PRIME_1;
        case 2:
            return SML_PRIME_2;
        case 3:
            return SML_PRIME_3;
        case 4:
            return SML_PRIME_4;
        case 5:
            return SML_PRIME_5;
        case 6:
            return SML_PRIME_6;
        case 7:
            return SML_PRIME_7;
        case 8:
            return SML_PRIME_8;
        case 9:
            return SML_PRIME_9;
        case 10:
            return SML_PRIME_10;
        default:
            break;
    }

    sml_size prime_counter = 10;
    sml_size last_pos = 30;

    while (prime_counter <= nth_prime) {
        if (sml_is_prime(last_pos++)) {
            prime_counter++;
        }
    }
    return prime_counter;
}

sml_size sml_greatest_common_divisor(sml_size num1, sml_size num2) // returns the greatest common divisor (GCD)
{

    sml_size gcd;
    for (sml_size i = 1; i <= num1 && i <= num2; ++i) {
        // Checks if i is factor of both integers
        if (num1 % i == 0 && num2 % i == 0)
            gcd = i;
    }
    return gcd;
}

sml_size sml_smallest_common_multiple(sml_size num1, sml_size num2) // returns the smallest common multiple (GCM)
{
    sml_size max = (num1 > num2) ? num1 : num2;

    while (1) {
        if ((max % num1 == 0) && (max % num2 == 0)) {
            return max;
        }
        ++max;
    }
    return -1;
}

// exponential functions; //

long double sml_log2(double x) // Returns the base 2 logarithm of x.
{
    return sml_nlog(x, 2);
}

long double sml_log10(double x) // Returns the base 10 logarithm of x.
{
    return sml_nlog(x, 10);
}

long double sml_log_ln(double x) // Returns the natural logarithm of x (base e).
{
    return (sml_nlog(x, SML_E));
}

long double sml_log_pi(double x) // Returns the natural logarithm of x (base pi).
{
    return (sml_nlog(x, SML_PI));
}


// Returns the natural logarithm of x log_n(x);
// Returns the nth logarithm of x (x^n).
// uses the binary search method :d
//
// nlog(n) function
// maybe the most important function in this whole library.
// you cannot even believe how many simple things are being derived from this.
// and yet they are showing this as the final boss in the educational system in Turkey..
// _We definitely need a better education system_
long double sml_nlog(double x, double n) {

    // wikipedia go brr...
    long double left = 0.0;
    long double right = x;
    long double mid;
    long double result;

    while (right - left > LOGARITHM_ACC) { // Smaller tolerance can be used i.e. (1e-15)
        mid = (left + right) / 2.0;
        result = sml_pow(mid, n);

        if (result > x) {
            right = mid;
        } else {
            left = mid;
        }
    }

    return (left + right) / 2.0;
}

long double sml_pow2(double x) // Returns 2 raised to the power of x.
{
    return sml_pow(x, 2);
}

long double sml_pow10(double x) // Returns 10 raised to the power of x.
{
    return sml_pow(x, 10);
}

long double sml_pow_only_positive(long double base, sml_size expo) //  Returns x^y if y > 0
{
    CHECK(expo >= 0);
    long double power = 1;

    while (expo > 0) {
        power = power * base;
        expo--;
    }
    return power;
}

long double sml_pow_only_negative(long double base, long double expo) //  Returns x^y if y < 0
{
//to calculate the power of negative exponents
    CHECK(expo < 0);

    long double power = 1;
    while (expo < 0) {
        power = power / base;
        expo++;
    }
    return power;
}

double sml_sqrt(double n) // Returns the square root of x. is a fast boi
{
    if (n < 0) {
#ifdef SML_LIB_ERRORS_AND_LOGGING_H
        sml_error_config cfg = init_sml_error("SML_MATH", false, NULL);
        throw_error(&cfg, ERROR_INVALID_INPUT, LOG_SEVERITY_WARNING, "n value is in the negative range which means that the value is imaginary. this function cannot calculate it correctly because it returns a double. duh\n");
#else
        printf("[SML_SQRT] n value is in the negative range which means that the value is imaginary. this function cannot calculate it correctly because it returns a double. duh\n");
#endif
        return -1;
    }

    double x = n;
    double y = 1;

    // e decides the accuracy level
    // this is the babylonian method that.
    double e = 0.000001;
    while (x - y > e) {
        x = (x + y) / 2;
        y = n / x;
    }
    return x;
}

// Returns the nth root of x in sml_math_t.
// if you want the numerical result use the sml_nth_root_double() function.
sml_math_t sml_nth_root(double num, double n) {
    // you might think that this is a cheat code. but it's not for advanced functions.
    // you can always use the another version of this function to get the __correct__ result
    sml_math_t result;
    result.type = _irrational;
    result.degree = n;
    result.value = num;
    result.is_imaginary = (n < 0) ? 1 : 0;
    return result;
}


static long double sml_internal_f(double x, int p, double num) {
    return sml_pow_basic(x, p) - num;
}

// calculating the value
// of the differential of the function
static double sml_internal_f_prime(double x, int p) {
    return p * sml_pow_basic(x, p - 1);
}

// Returns the nth root of x in numerical form
// note that if n is in whole numbers and is divisible by 2
// it can be both negative and positive hece ABS.
// for this functino I'm selecting the positive value for return value.
// if you need a better solution please implement it and I will make sure to add it to the library.
//  :D

double sml_nth_root_double(double num, sml_size_s p) {

    if (num < 0) {
#ifdef SML_LIB_ERRORS_AND_LOGGING_H
        sml_error_config cfg = init_sml_error("SML_MATH", false, NULL);
        throw_error(&cfg, ERROR_INVALID_INPUT, LOG_SEVERITY_WARNING, "n value is in the negative range which means that the value is imaginary. this function cannot calculate it correctly because it returns a double. duh\n");
#else
        printf("n value is in the negative range which means that the value is imaginary. this function cannot calculate it correctly because it returns a double. duh");
#endif
        return -1;
    }


    // Defining range
    // on which answer can be found
    double left = -num;
    double right = num;

    double x;
    while (1) {

        // finding mid value
        x = (left + right) / 2.0;
        double value = sml_internal_f(x, p, num);
        double prime = sml_internal_f_prime(x, p);
        if (value * prime <= 0)
            left = x;
        else
            right = x;
        if (value < 0.000001 && value >= 0) {
            return x;
        }
    }

}

// this is a hard function to implement becuase pow is not only defined in
// (x,y ∈ Z) but defined in (x,y ∈ Q | ∀y > 0). in this function
// wow fancy math :D
// and the reason for ∀y > 0 is that im too lazy to implement it at this stage.
long double sml_pow(long double base, long double expo) // Returns x raised to the power of y (x^y).
{
    if (expo == 1) { return base; }
    if (expo == 0) { return 0; }


    if SML_IS_NUMBER(expo) { // check if the numer is well a number.
        if (base > 0) {
            return sml_pow_only_positive(base, (unsigned long long) expo);
        }
        if (base < 0) {
            return sml_pow_only_negative(base, expo);
        }
    } else {
        // if base^expo's expo is not a whole number we go by the technique of
        // expo = a/b where a and b is the fractional values that is equal to expo
        // if we do
        // base^(a/b) * base^(a/b) ... (b times) * base^(a/b) = base.
        // this means that if the number is not a whole number we should do this
        // nth_root(base) where n is b times a .

        sml_size_s numerator, denominator, power;
        numerator = SML_GET_FLOAT_OF_FLOATING(expo);
        denominator = 1;

        // find how many digits are after 0.
        for (sml_size_s temp_numerator = numerator; temp_numerator < 1; temp_numerator *= 10, denominator *= 10);
        power = numerator * sml_nth_root_double(base, denominator);
        return power;
    }

#ifdef SML_LIB_ERRORS_AND_LOGGING_H
    sml_error_config cfg = init_sml_error("SML_MATH", false, NULL);
    throw_error(&cfg, ERROR_INVALID_INPUT, LOG_SEVERITY_WARNING, "For some reason sml_pow() cannot work as intended please open an issue on githubn\n");
#else
    printf("pow() function cannot work as intended. Please open an issue on github\n");
#endif
    return -1;
}


long double sml_exp_pi(void) // Returns the exponential value of x (e^pi).
{
    return 23.1406926328;
}

long double sml_exp(double x) // Returns the exponential value of x (e^x).
{
    return sml_pow(SML_E, x);
}


//Trigonometric Functions; //
double sml_rad_to_deg(double Rad) // Returns the radian to degrees of x
{
    return (Rad * (180 / SML_PI));
}

double sml_deg_to_rad(double d) // returns the degrees to radian
{
    return d * (SML_PI / 180.0);
}


double sml_internal_trig_power(float base, int exp) {
    if (exp < 0) {
        if (base == 0)
            return -0; // Error!!
        return 1 / (base * sml_internal_trig_power(base, (-exp) - 1));
    }
    if (exp == 0)
        return 1;
    if (exp == 1)
        return base;
    return base * sml_internal_trig_power(base, exp - 1);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

double sml_internal_trig_fact(double n) {
    return n <= 0 ? 1 : n * sml_internal_trig_fact(n - 1);
}

#pragma clang diagnostic pop

// finds sin by using taylor approximation
float sml_sin(int deg) {
    deg %= 360; // make it less than 360
    float rad = deg * SML_PI / 180;
    float sin = 0;

    int i;
    for (i = 0; i < 7; i++) { // That's Taylor series!!.
        sin += sml_internal_trig_power(-1, i) * sml_internal_trig_power(rad, 2 * i + 1) /
               sml_internal_trig_fact(2 * i + 1);
    }
    return sin;
}

// finds cos by using the theorem
// sin^2(x) + cos^2(x) = 1, therefore
// cos = sqrt(1 - sin^2). do not forget that this generates some loss of accuracy
// but makes up for it in optimization ie cache locality.

float sml_cos(int deg) // Returns the Cosine of x
{
    return sml_sqrt(1 - sml_sin(deg) * sml_sin(deg));
}

float sml_tan(int deg) // Returns the tangent of x
{
    return sml_sin(deg) / sml_cos(deg);
}

float sml_sec(int deg) // Returns the secand of x
{
    return 1 / sml_cos(deg);
}

float sml_cot(int deg) // Returns the co-tangent of x
{
    return sml_cos(deg) / sml_sin(deg);
}

float sml_csc(int deg) // Returns the cosecand of x
{
    return 1 / sml_sin(deg);
}

// calculates the arcsin using taylor series.
double sml_arc_sin(double x) {
    double result = 0.0;
    int sign = 1;
    double power = x;

    for (int n = 1; n <= 8; n += 2) {
        result += sign * power / n;
        power *= x * x;
        sign = -sign;
    }

    return result;
}

// calculates the arcsin using SML_PI / 2 - sml_arc_sin(x)
double sml_arc_cos(double x) {
    return SML_PI / 2 - sml_arc_sin(x);
}

// calculates sinh using (e^2x - 1)/(2e^x)
double sml_sinh(double x) {
    return (sml_exp(2 * x) - 1) / (2 * sml_exp(x));
}

// calculates cosh using (e^2x + 1)/(2e^x)
double sml_cosh(double x) {
    return (sml_exp(2 * x) + 1) / (2 * sml_exp(x));
}

// calculates cosh using (e^2x - 1)/(e^x + 1)
double sml_tanh(double x) {
    return (sml_exp(2 * x) - 1) / (sml_exp(2 * x) + 1);
}

// calculates coth using (e^2x + 1)/(e^x - 1)
double sml_coth(double x) {
    return (sml_exp(2 * x) + 1) / (sml_exp(2 * x) - 1);
}


//Rounding and Ceiling Functions; //
double sml_ceil(double x) // Rounds x to the smallest integer not less than x (ceiling).
{
// if it's not a number we subtract the numbres after dots and increase x by one
    if (!SML_IS_NUMBER(x)) {
        x -= SML_GET_FLOAT_OF_FLOATING(x);
        x++;
    }
    return x;
}

double sml_floor(double x) // Rounds x to the largest integer not greater than x (floor).
{
    return x - SML_GET_FLOAT_OF_FLOATING(x);
}

double sml_round(double x) // Rounds x to the nearest integer.
{
    if (SML_GET_FLOAT_OF_FLOATING(x) >= 0.5) {
        x = sml_floor(x) + 1;
    } else {
        x = sml_floor(x);
    }
    return x;
}

//misc Mathematical Functions; //
double sml_fmod(double x, double y) // Returns the remainder when x is divided by y.
{
    if (y == 0.0) {
// Handling division by zero error
        return 0.0;
    }

    double quotient = x / y;
    int integerPart = (int) quotient;
    double remainder = x - integerPart * y;

    return remainder;
}

// Returns the nth fibonacci number.
// Standard algorithm.
// > It ain't much but it's honest work
sml_size sml_fib(sml_size n) {
    if (n <= 0ULL) {
        return 0ULL;
    } else if (n == 1ULL) {
        return 1ULL;
    }

    unsigned long long prev = 0ULL;
    unsigned long long current = 1ULL;
    unsigned long long result = 0ULL;

    for (unsigned long long i = 2ULL; i <= n; i++) {
        result = prev + current;
        prev = current;
        current = result;
    }

    return result;
}

//Combinations and Permutations:
double sml_npr(double n, double r) // Returns the permutation NPR(x,y) of the given numbers.
{
    return sml_fac(n) / sml_fac(n - r);
}

double sml_ncr(double n, double r) // Returns the combination NCR(x,y) of the given numbers.
{
    return sml_fac(n) / (sml_fac(r) * sml_fac(n - r));
}

unsigned long long sml_rpr(int n, int r) { // Returns the repeated permutation RPR(x,y) of the given numbers.
    unsigned long long result = 1;

    for (int i = 0; i < r; i++) {
        result *= n;
    }

    return result;
}

unsigned long long sml_sml_rcr(int n, int r) {
    unsigned long long result = 1;

    for (int i = 1; i <= r; i++) {
        result *= (n + r - i);
        result /= i;
    }

    return result;
} // Returns the repeated combination RCR(x,y) of the given numbers.

// Returns the circular permutation CPR(x,y) of the given numbers.
// No. this function does not give CPR to anybody that is near you.
// If you need to give somebody CPR please call 911, 111, 112 or whatever is your local EMS
// AND STOP READING A LIBRARY MANUAL FOR GIVIN' CPR.
unsigned long long sml_cpr(int n, int r) {
    if (n <= 0 || r <= 0) {
        return 0; // Invalid input
    }

    if (n == 1) {
        return 1; // Only one element, so only one permutation
    }

    return (sml_rpr(n, r) / r);
}

unsigned long long sml_ccr(int n, int r) {// Returns the circular combination CCR(x,y) of the given numbers.
    if (n <= 0 || r <= 0) {
        return 0; // Invalid input
    }

    if (n == 1) {
        return 1; // Only one element, so only one combination
    }

    return (sml_sml_rcr(n, r) / r);
}
// Matrix operations; //


#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"



// prints a math_t duh
// can be improved, but it's the initial release. if you
// are not using imaginary numbers too much, you'll be fine
// (I hope ...)





void sml_math_t_print(sml_math_t *num, FILE *stream) {

    // haha branchless programming go brr.
    if (num->value < 0) {
        printf("(");
    }

    if (num->type != _imaginary && num->is_imaginary == true) {
        fprintf(stream, "i");
    }
    if (num->type == _imaginary && num->is_imaginary == true) {
        fprintf(stream, "i%.3Lf", num->value);
    }
    switch (num->type) {
        case _int:
            fprintf(stream, "%.0Lf", num->value);
            break;
        case _float:
            fprintf(stream, "%3.3Lf", num->value);
            break;
        case _irrational:
            switch ((SML_IS_NUMBER(num->degree)) ? (int) num->degree : 0) {
                case 1:
                    fprintf(stream, "%3.3Lf(q)", num->value);
                    break;

                case 2:
                    fprintf(stream, "sqrt(%3.3Lf)", num->value);
                    break;

                case 3:
                    fprintf(stream, "cbrt(%3.3Lf)", num->value);
                    break;
                default:
                    if (SML_IS_NUMBER(num->degree)) {
                        fprintf(stream, "%.0Lf(%3.3Lf)", num->degree, num->value);
                    } else {
                        fprintf(stream, "%.3Lf(%3.3Lf)", num->degree, num->value);
                    }
                    break;
            }
        case _imaginary:
            if (num->is_imaginary == false) {
                fprintf(stream, "i%.3Lf", num->value);
            }
            break;
        case _degree:
            fprintf(stream, "%.3Lf(deg)", num->value);
            break;
        case _radian:
            fprintf(stream, "%.3Lf(rad)", num->value);
            break;
        case _gradian:
            fprintf(stream, "%.3Lf(grad)", num->value);
            break;
        default:
            fprintf(stream, "cannot print sml_math_t %p because type is not valid", num);
            break;
    }
    if (num->degree != 0.0 && num->type != _irrational) {
        fprintf(stream, "^(%.1Lf)", num->degree);
    }
    if (num->value < 0) {
        printf(")");
    }
    if (num->related != NULL) {
        fprintf(stream, "+");
        sml_math_t_print(num->related, stream);
    }
    fprintf(stream, "\n");
}

#pragma clang diagnostic pop


// create a matrix
sml_matrix_t *sml_matrix_create(sml_size rows, sml_size cols) {
    // Allocate memory for the sml_matrix_t structure
    sml_matrix_t *matrix = (sml_matrix_t *) malloc(sizeof(sml_matrix_t));

    if (matrix == NULL) {
        // Handle allocation failure if needed
        perror("Memory allocation failed");
        return NULL;
    }

    // Set the rows and cols fields
    matrix->rows = rows;
    matrix->cols = cols;

    // Allocate memory for the data array of pointers
    matrix->data = (sml_math_t **) malloc(rows * sizeof(sml_math_t *));

    if (matrix->data == NULL) {
        // Handle allocation failure if needed
        perror("Memory allocation failed");
        free(matrix); // Free the previously allocated structure
        return NULL;
    }

    // Allocate memory for the data arrays for each row
    for (sml_size i = 0; i < rows; i++) {
        matrix->data[i] = (sml_math_t *) malloc(cols  * sizeof(sml_math_t));

        if (matrix->data[i] == NULL) {
            // Handle allocation failure if needed
            perror("Memory allocation failed");
            // Free previously allocated memory
            for (sml_size j = 0; j < i; j++) {
                free(matrix->data[j]);
            }
            free(matrix->data);
            free(matrix);
            return NULL;
        }
    }

    // Initialize the data arrays with default values if needed

    return matrix;
}

// destroy a matrix
void sml_matrix_destroy(sml_matrix_t *matrix) {

// Function to free a sml_matrix_t structure and its data
    if (matrix != NULL) {
        for (sml_size i = 0; i < matrix->rows; i++) {
            free(matrix->data[i]);
        }
        if (matrix->data != NULL) {
            free(matrix->data);
        }
        if (matrix != NULL) {
            free(matrix);
        }
    }

}


void sml_matrix_print(sml_matrix_t *matrix) {
    printf("╔");
    for (int i = 0; i < matrix->cols; ++i) {
        printf("══════════");
        if (i < matrix->cols - 1) {
            printf("╦");
        }
    }
    printf("╗\n");

    for (sml_size row = 0; row < matrix->rows; ++row) {
        printf("║ ");
        for (int col = 0; col < matrix->cols; ++col) {
            printf("%8.2Lf ", matrix->data[row][col].value);
            if (col < matrix->cols - 1) {
                printf("║ ");
            }
        }
        printf("║\n");

        if (row < matrix->rows - 1) {
            printf("╠");
            for (int i = 0; i < matrix->cols; ++i) {
                printf("══════════");
                if (i < matrix->cols - 1) {
                    printf("╬");
                }
            }
            printf("╣\n");
        }
    }

    printf("╚");
    for (int i = 0; i < matrix->cols; ++i) {
        printf("══════════");
        if (i < matrix->cols - 1) {
            printf("╩");
        }
    }
    printf("╝\n");
}

void sml_matrix_zero_init(sml_matrix_t *matrix) {
    for (sml_size row = 0; row < matrix->rows; ++row) {
        for (int col = 0; col < matrix->cols; ++col) {
            matrix->data[col][row].value = 0;
        }
    }
}

sml_matrix_t *sml_matrix_dup(sml_matrix_t *src) {
    sml_matrix_t *new_matrix = sml_matrix_create(src->rows, src->cols);
    memcpy(new_matrix, src, src->cols * src->rows * sizeof(sml_matrix_t));
    return new_matrix;
}

// transposes the matrix
sml_matrix_t *sml_matrix_transpose(sml_matrix_t *matrix) {

    sml_size transpose_rows = matrix->cols;
    sml_size transpose_cols = matrix->rows;
    sml_matrix_t *transpose = sml_matrix_create(transpose_rows, transpose_cols);

    for (sml_size i = 0; i < transpose_rows; i++) {
        for (sml_size j = 0; j < matrix->cols; j++) {
            transpose->data[i][j] = matrix->data[j][i];
        }
    }
    return transpose;
}
