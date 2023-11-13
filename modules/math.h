//
// Created by bruh on 10/7/23.
//


#ifndef SML_DIALECT_MATH_H
#define SML_DIALECT_MATH_H

#include "common_bindings.h"
#include <stdbool.h>
#include <bits/types/FILE.h>

#define HIGH_ACCURACY // changes some double's to long double's

#define CONSTANTS
#ifdef CONSTANTS
#pragma region const_defs
// Mathematical Constants
// instead doing the research for this I think should have gotten a PhD. in statistics and maths.
#define SML_RAMANUJAN_CONSTANT 262537412640768743.999999999250073
// Ramanujan's constant, a mathematical constant with a specific value.
// -1/12 :D

#define SML_GELFOND_CONSTANT 23.1406926327792690057
// Gelfond's constant, e raised to the power of pi.

#define SML_TAU_CONSTANT 6.28318530717958647692
// Tau, a mathematical constant equal to 2*pi.

#define SML_FEIGENBAUM_CONSTANT_DELTA 4.66920160910299067185
// Feigenbaum constant (delta), related to chaotic behavior in dynamical systems.

#define SML_VAN_DER_PAUW_CONSTANT (M_PI / log(2.0))
// Van der Pauw constant, used in electrical conductivity measurements.

#define SML_RECIPROCAL_FIBONACCI_CONSTANT 3.35988566624317755317
// Reciprocal Fibonacci constant, related to the Fibonacci sequence.

#define SML_LEVY_CONSTANT_2 3.2758229187218115978
// Lévy's constant (2), used in probability theory.

#define SML_PI 3.14159265358979323846264338327950288419716939937510
// Pi, the well-known mathematical constant representing the ratio of a circle's circumference to its diameter.
// btw here is a pie (*-*) (use your imagination)

#define SML_FRANSEN_ROBINSON_CONSTANT 2.80777024202851936522
// Fransén-Robinson constant, a mathematical constant with specific mathematical properties.

#define SML_EULER_NUMBER 2.71828182845904523536
// Euler's number (e), the base of the natural logarithm.

#define SML_KHINCHIN_CONSTANT_K0 2.68545200106530644530
// Khinchin's constant (K0), related to continued fractions.

#define SML_GELFOND_SCHNEIDER_CONSTANT (pow(2.0, sqrt(2.0)))
// Gelfond–Schneider constant, arising from Gelfond–Schneider theorem.

#define SML_LEMNISCATE_CONSTANT 2.62205755429211981046
// Lemniscate constant, related to the Lemniscate of Bernoulli.

#define SML_SIERPINSKI_CONSTANT 2.58498175957925321706
// Sierpiński's constant, used in number theory and fractal geometry.

#define SML_FEIGENBAUM_CONSTANT_ALPHA 2.50290787509589282228
// Feigenbaum constant (alpha), related to chaos theory.

#define SML_SILVER_RATIO_DELTA_S 2.41421356237309504880
// Silver ratio (delta S), a mathematical constant similar to the golden ratio.

#define SML_GOLDEN_ANGLE_G 2.39996322972865332223
// Golden angle (g), an angle related to the golden ratio and phyllotaxis.

#define SML_UNIVERSAL_PARABOLIC_CONSTANT_P 2.29558714939263807403
// Universal parabolic constant (P), used in mathematical physics.

#define SML_SQUARE_ROOT_OF_5 (sqrt(5.0))
// Square root of 5, a common mathematical operation.

#define SML_WALLIS_CONSTANT 2.09455148154232659148
// Wallis's constant, used in calculus and mathematical analysis.

#define SML_TWO 2.0
// The number two. what did you expect. the number 3? nah! we 2 here.

#define SML_Z_SCORE_97_5_PERCENTILE 1.95996398454005423552
// Z score for the 97.5 percentile point, used in statistics.

#define SML_BRUN_CONSTANT_B2 1.902160583104
// Brun's constant (B2), related to twin primes.

#define SML_CONNECTIVE_CONSTANT_MU 1.84775906502257351225
// Connective constant for the hexagonal lattice.

#define SML_TRIBONACCI_CONSTANT 1.83928675521416113255
// Tribonacci constant, related to the Tribonacci sequence.

#define SML_KOMORNIK_LORETI_CONSTANT_Q 1.78723165018296593301
// Komornik–Loreti constant, related to number theory.

#define SML_SQUARE_ROOT_OF_3 (sqrt(3.0))
// Square root of 3, a common mathematical operation.

#define SML_THEODORUS_CONSTANT 1.73205080756887729352
// Theodorus' constant, related to the square root of 3.

#define SML_NIVEN_CONSTANT_C 1.7052111401053676428
// Niven's constant, related to rational numbers.

#define SML_SOMOS_QUADRATIC_RECURRENCE_CONSTANT_SIGMA 1.6616879463359412129
// Somos' quadratic recurrence constant (sigma), related to number sequences.

#define SML_PHI_GOLDEN_RATIO 1.61803398874989484820
// Phi (Golden ratio), a famous mathematical constant.

#define SML_ERDOS_BORWEIN_CONSTANT_E 1.60669515241529176378
// Erdős–Borwein constant (E), used in number theory.

#define SML_LIEB_SQUARE_ICE_CONSTANT 1.53960071783900203869
// Lieb's square ice constant, related to statistical mechanics.

#define SML_PORTER_CONSTANT_C 1.46707807943397547289
// Porter's constant (C), used in quantum mechanics.

#define SML_SUPERGOLDEN_RATIO_PSI 1.46557123187676802665
// Supergolden ratio (psi), a mathematical constant related to golden ratios.

#define SML_BACKHOUSE_CONSTANT_B 1.45607494858268967139
// Backhouse's constant (B), related to sml_nth_prime numbers.

#define SML_RAMANUJAN_SOLDNER_CONSTANT_MU 1.45136923348833050128
// Ramanujan–Soldner constant (mu), related to transcendental equations.

#define SML_PLASTIC_NUMBER_RHO 1.32471795724474602596
// Plastic number (rho), related to irrational numbers.

#define SML_MILLS_CONSTANT_A 1.306377883608069046
// Mills' constant (A), related to sml_nth_prime numbers.

#define SML_CONWAY_CONSTANT_LAMBDA 1.30357726903429639125
// Conway's constant (lambda), used in number theory.

#define SML_GLAISHER_KINKELIN_CONSTANT_A 1.28242712910062263687
// Glaisher–Kinkelin constant (A), related to special functions.

#define SML_CUBE_ROOT_OF_2 (pow(2.0, 1.0 / 3.0))
// Cube root of 2, a mathematical operation.

#define SML_SECOND_FAVARD_CONSTANT_K2 1.23370055013616982735
// Second Favard constant (K2), related to Fourier analysis.

#define SML_APERY_CONSTANT_ZETA_3 1.20205690315959428539
// Apéry's constant (zeta(3)), related to number theory and mathematical analysis.

#define SML_FOIAS_CONSTANT_ALPHA 1.18745235112650105459
// Foias constant (alpha), related to operator theory.

#define SML_LEVY_CONSTANT_1_BETA 1.18656911041562545282
// Lévy's constant (1) (beta), used in probability theory.

#define SML_SALEM_CONSTANT_SIGMA_10 1.17628081825991750654
// Salem constant (sigma_10), related to complex dynamics.

#define SML_SECOND_HERMITE_CONSTANT_GAMMA_2 1.15470053837925152901
// Second Hermite constant (gamma_2), related to special functions.

#define SML_VISWANATH_CONSTANT 1.1319882487943
// Viswanath constant, related to number theory.

#define SML_GIESKING_CONSTANT_G 1.01494160640965362502
// Gieseking constant (G), related to transcendental numbers.

#define SML_DEVICCI_TESSERACT_CONSTANT 1.00743475688427937609
// DeVicci's tesseract constant, a mathematical constant with specific properties.

#define SML_ONE 1.0
// The number one. truly one of the numbers

#define SML_ASYMPTOTIC_LEBESGUE_CONSTANT_C 0.98943127383114695174
// Constant related to the asymptotic behavior of Lebesgue constants.

#define SML_LOCHS_CONSTANT_L 0.97027011439203392574
// Lochs constant (L), related to special functions.

#define SML_MAGIC_ANGLE_THETA_M 0.955316618124509278163
// Magic angle (theta_m), used in physics.

#define SML_CATALAN_CONSTANT_G 0.91596559417721901505
// Catalan's constant (G), related to combinatorics and number theory.

#define SML_ERDOS_TENENBAUM_FORD_CONSTANT_DELTA 0.86071332055934206887
// Erdős–Tenenbaum–Ford constant (delta), related to number theory.

#define SML_REGULAR_PAPERFOLDING_SEQUENCE_CONSTANT_P 0.85073618820186726036
// Regular paperfolding sequence constant (P), related to fractals.

#define SML_GAUSS_CONSTANT_G 0.83462684167407318628
// Gauss's constant (G), used in mathematical analysis.

#define SML_FIRST_NIELSEN_RAMANUJAN_CONSTANT_A1 0.82246703342411321823
// First Nielsen–Ramanujan constant (a1), related to modular forms.

#define SML_CHVATAL_SANKOFF_CONSTANT_GAMMA_2 0.788071
// Chvátal–Sankoff constant for the binary alphabet (gamma_2), used in bioinformatics.

#define SML_LANDAU_RAMANUJAN_CONSTANT_K 0.76422365358922066299
// Landau–Ramanujan constant (K), related to partition theory.

#define SML_DOTTIE_NUMBER 0.7390851332151664165
// Dottie number, related to fixed-point iteration.

#define SML_EMBREE_TREFETHEN_CONSTANT_BETA_STAR 0.70258
// Embree–Trefethen constant (beta*), related to numerical analysis.

#define SML_FIRST_CONTINUED_FRACTION_CONSTANT_C1 0.69777465796400798201
// First continued fraction constant (C1), related to continued fractions.

#define SML_NATURAL_LOGARITHM_OF_2 0.69314718055994530941
// Natural logarithm of 2 (ln(2)), a fundamental constant in mathematics.

#define SML_TANIGUCHI_CONSTANT 0.67823449191739197803
// Taniguchi constant, related to transcendental numbers.

#define SML_LAPLACE_LIMIT 0.662743419349158097
// Laplace limit, related to probability and number theory.

#define SML_ROBBINS_CONSTANT_DELTA_3 0.66170718226717623515
// Robbins constant (delta(3)), related to mathematical series.

#define SML_FELLER_TORNIER_CONSTANT_CF_T 0.66131704946962233528
// Feller–Tornier constant (CF_T), used in mathematical analysis.

#define SML_TWIN_PRIMES_CONSTANT_C2 0.66016181584686957392
// Twin primes constant (C2), related to twin sml_nth_prime conjecture.

#define SML_CAHEN_CONSTANT_C 0.64341054628833802618
// Cahen's constant (C), related to continued fractions.

#define SML_GOLOMB_DICKMAN_CONSTANT_LAMBDA 0.62432998854355087099
// Golomb–Dickman constant (lambda), used in number theory.

#define SML_GOMPERTZ_CONSTANT_DELTA 0.59634736232319407434
// Gompertz constant (delta), related to population dynamics.

#define SML_LOGARITHMIC_CAPACITY_OF_UNIT_DISK 0.59017029950804811302
// Logarithmic capacity of the unit disk, related to complex analysis.

#define SML_EULER_CONSTANT_GAMMA 0.57721566490153286060
// Euler's constant (gamma), used in mathematical analysis.

#define SML_STEPHENS_CONSTANT 0.57595996889294543964
// Stephens' constant, related to number theory.

#define SML_OMEGA_CONSTANT 0.56714329040978387299
// Omega constant (omega), related to calculus.

#define SML_ONE_HALF 0.5
// One-half, a fraction.

#define SML_LANDAU_CONSTANT_L 0.54326
// Landau's constant (L), related to sml_nth_prime number distribution.

#define SML_LANDAU_THIRD_CONSTANT_A 0.7853
// Landau's third constant (A), related to sml_nth_prime number distribution.

#define SML_WEIERSTRASS_CONSTANT 0.47494937998792065033
// Weierstrass constant, related to elliptic functions.

#define SML_BLOCH_CONSTANT_B 0.4719
// Bloch's constant (B), used in physics.

#define SML_PRIME_CONSTANT_RHO 0.4146825098511166024
// Prime constant (rho), related to sml_nth_prime number distribution.

#define SML_PROUHET_THUE_MORSE_CONSTANT_TAU 0.41245403364010759778
// Prouhet–Thue–Morse constant (tau), related to number theory.

#define SML_ARTIN_CONSTANT_C_ARTIN 0.37395581361920228805
// Artin's constant (C_Artin), related to algebraic number theory.

#define SML_HAFNER_SARNAK_MCCURLEY_CONSTANT_SIGMA 0.35323637185499598454
// Hafner–Sarnak–McCurley constant (sigma), related to number theory.

#define SML_BERNSTEIN_CONSTANT_BETA 0.28016949902386913303
// Bernstein's constant (beta), related to the Riemann zeta function.

#define SML_MEISSEL_MERTENS_CONSTANT_M 0.26149721284764278375
// Meissel–Mertens constant (M), related to sml_nth_prime number theory.

#define SML_COPELAND_ERDOS_CONSTANT_CCE 0.2357113171923293137
// Copeland–Erdős constant (CCE), related to sml_nth_prime number theory.

#define SML_SECOND_DU_BOIS_REYMOND_CONSTANT_C2 0.19452804946532511361
// Second du Bois-Reymond constant (C2), related to calculus.

#define SML_MRB_CONSTANT_S 0.18785964246206712024
// MRB constant (S), used in number theory.

#define SML_BASE_10_CHAMPERNOWNES_CONSTANT_C10 0.12345678910111213141
// Base 10 Champernowne constant (C10), related to irrational numbers.

#define SML_KEPLER_BOUWKAMP_CONSTANT_K_PRIME 0.1149420485329620070
// Kepler–Bouwkamp constant (K'), used in number theory.

#define SML_LIOUVILLE_CONSTANT_L 0.110001000000000000001
// Liouville's constant (L), an example of a transcendental number.

#define SML_CHAITIN_CONSTANT_OMEGA 0.0078749969978123844
// Chaitin's constant (Omega), an uncomputable number with specific properties.

#define SML_HEATH_BROWN_MOROZ_CONSTANT_C 0.00131764115485317810
// Heath-Brown–Moroz constant (C), a mathematical constant.

#define SML_ZERO 0.0
// Zero, the number zero.

#define SML_DE_BRUIJN_NEWMAN_CONSTANT (0.0 <= Λ && Λ <= 0.2)
// De Bruijn–Newman constant (Λ), a complex number in a specific range.

#define SML_NEGATIVE_ONE (-1.0)
// Negative one, the number -1.

#define SML_E 2.71828182845904523536

/* Prime numbers */
#define SML_PRIME_1  2
#define SML_PRIME_2  3
#define SML_PRIME_3  5
#define SML_PRIME_4  7
#define SML_PRIME_5  11
#define SML_PRIME_6  13
#define SML_PRIME_7  17
#define SML_PRIME_8  19
#define SML_PRIME_9  23
#define SML_PRIME_10 29
/* Prime numbers */

#pragma endregion const_defs
#endif

// this will be the accuracy of the logarithm. if you want a more accurate accuracy use something like 1e-15
#define LOGARITHM_ACC 1e-9
// SML_IS_UNSIGNED: Checks if x is an unsigned integer.
#define SML_IS_UNSIGNED(x) ((x) >= 0)

// SML_IS_ODD: Checks if x is an odd integer.
#define SML_IS_ODD(x) ((x) % 2 != 0)

// SML_IS_EVEN: Checks if x is an even integer.
#define SML_IS_EVEN(x) ((x) % 2 == 0)

#define SML_GET_FLOAT_OF_FLOATING(x) ((x) - (int)(x))

// SML_GET_WHOLE_OF_FLOATING: Extracts the whole part of a floating-point number x.
#define SML_GET_WHOLE_OF_FLOATING(x) ((int)(x))

#define SML_IS_NUMBER(x) ((x) - (int)(x) == 0)

typedef enum {
    _int = 0, _float, _irrational, _imaginary, _degree, _radian, _gradian
} sml_num_type;

typedef struct sml_math_t {
#ifdef HIGH_ACCURACY
    long double value;
    long double degree;
#else
    double value;
    double degree; // ie. degree.th root of val
#endif
    sml_num_type type; // ie. sqrt/imaginary or not
    bool is_imaginary; // I mean it can be sqrt(-1) so its both a sqrt and imaginary
    struct sml_math_t *related; // this is for adding ie. 3sqrt(5) or i5 + 3
} sml_math_t;

#ifdef HIGH_ACCURACY

sml_math_t sml_math_create(long double value, long double degree, sml_num_type type, bool is_imaginary);

#else
sml_math_t sml_math_create(double value, double degree, sml_num_type type, bool is_imaginary);
#endif

//Basic Arithmetic Functions; //
int sml_abs(int x); // Returns the absolute value of an integer.
double sml_float_abs(long double x); // Returns the absolute value of a floating-point number.
int sml_max(int x, int y); // Returns the maximum of two integers.
double sml_float_max(double x, double y); // Returns the maximum of two floating-point numbers.
int sml_min(int x, int y); // returns the minimum of two integers.
double sml_float_min(double x, double y); // returns the minimum of two floating-point numbers.
float sml_pow_basic(double x, sml_size expo);

// basic math functions; //
bool sml_is_prime(unsigned long long is_prime); // Returns true if the number is prime
sml_size sml_nth_prime(sml_size nth_prime); // Returns the nth sml_nth_prime number.
sml_size sml_greatest_common_divisor(sml_size num1, sml_size num2); // returns the greatest common divisor (GCD)
sml_size sml_smallest_common_multiple(sml_size num1, sml_size num2); // returns the smallest common multiple (GCM)


sml_size sml_fac_size_t(double x); // returns the factorial of a double (in sml_size_t)
sml_size sml_fac_size_t_int(sml_size_s x); // returns the factorial of a number (in sml_size_t)
sml_size sml_fac_size_t_unsigned(sml_size x); // returns the factorial of an unsigned number (in sml_size_t)
double sml_fac(double n); // returns the factorial of a double (in sml_size_t)
int sml_fac_int(int n); // returns the factorial of an integer (in int)
// e; //
long double sml_e(sml_size accuracy); // Returns the e constant to a given accuracy

// exponential functions; //
long double sml_exp_pi(void); // Returns the exponential value of x (e^pi).
long double sml_exp(double x); // Returns the exponential value of x (e^x).

long double sml_log2(double x); // Returns the base 2 logarithm of x.
long double sml_log10(double x); // Returns the base 10 logarithm of x. But wit high accuracy
long double sml_log_e(double x); // Returns the natural logarithm of x (base e). But wit high accuracy
long double sml_log_pi(double x); // Returns the natural logarithm of x (base pi). But wit high accuracy
long double sml_nlog(double x, double n); // Returns the natural logarithm of x (x^n). But wit high accuracy

long double sml_pow2(double x); // Returns 2 raised to the power of x.
long double sml_pow10(double x); // Returns 10 raised to the power of x.
long double sml_pow_only_positive(long double x, sml_size y); //  Returns x^y if y > 0
long double sml_pow_only_negative(long double x, long double y); //  Returns x^y if y < 0
long double sml_pow(long double base, long double expo); // Returns x raised to the power of y (x^y).
int sml_pow_basic_int(int x, int expo); // basic pow. internally used for trigonometric calculations.

// rooting and tooting; //
sml_math_t sml_nth_root(double x, double n);

double sml_sqrt(double n); // Returns the square root of x.
double sml_nth_root_double(double x, sml_size_s n); // Returns the nth root of x

typedef struct {
    sml_math_t value_rad; //
    sml_math_t value_deg; //
    sml_math_t value_numerical; //
} sml_trig_t;


//Trigonometric Functions; //
double sml_rad_to_deg(double d); // Returns the radian to degrees of d
double sml_deg_to_rad(double d); // returns the degrees to radian

double sml_internal_trig_power(float base, int exp);

double sml_internal_trig_fact(double n);

double sml_hypot(double x, double y); // Returns the hypotenuse of a right triangle with sides x and y.

float sml_sin(int deg); // Returns the sml_sin of x
float sml_cos(int deg); // Returns the cosine of x
float sml_tan(int deg); // Returns the tangent of x
float sml_sec(int deg); // Returns the secand of x
float sml_cot(int deg); // Returns the co-tangent of x
float sml_csc(int deg); // Returns the cosecand of x

double sml_arc_sin(double x); // Returns the arcsine of x, in radians.
double sml_arc_cos(double x); // Returns the arccosine of x, in radians.

//Hyperbolic Trig Functions; //
double sml_sinh(double x); // Returns the hyperbolic sml_sin of x.
double sml_cosh(double x); // Returns the hyperbolic cosine of x.
double sml_tanh(double x); // Returns the hyperbolic tangent of x.
double sml_coth(double x); // Returns the hyperbolic co-tangent of x

//Rounding and Ceiling Functions; //
double sml_ceil(double x); // Rounds x to the smallest integer not less than x (ceiling).
double sml_floor(double x); // Rounds x to the largest integer not greater than x (floor).
double sml_round(double x); // Rounds x to the nearest integer.

//misc Mathematical Functions; //
double sml_fmod(double x, double y); // Returns the remainder when x is divided by y.

sml_size sml_fib(sml_size n); // Returns the nth fibonacci number


//Combinations and Permutations:
double sml_npr(double n, double r); // Returns the permutation NPR(x,y) of the given numbers.
double sml_ncr(double n, double r); // Returns the combination NCR(x,y) of the given numbers.
unsigned long long sml_rpr(int n, int r); // Returns the repeated permutation RPR(x,y) of the given numbers.
unsigned long long sml_rcr(int n, int r); // Returns the repeated combination RCR(x,y) of the given numbers.
unsigned long long sml_cpr(int n, int r); // Returns the circular permutation CPR(x,y) of the given numbers.
unsigned long long sml_ccr(int n, int r); // Returns the circular combination CCR(x,y) of the given numbers.

/*
 *A little touch-up comment for the functions above.
 * The following functions calculate counts or possibilities related to combinations and permutations:
 *
 * 1. `sml_npr(n, r)` - NPR (n Permutations of r):
 *   - Calculates the number of permutations of r items from a set of n distinct items without repetition.
 *
 * 2. `sml_ncr(n, r)` - NCR (n Combinations of r):
 *   - Calculates the number of combinations of r items from a set of n distinct items without repetition.
 *
 * 3. `sml_rpr(n, r)` - RPR (n Permutations of r with Repetition):
 *   - Calculates the number of permutations of r items from a set of n distinct items with repetition allowed.
 *
 * 4. `sml_rcr(n, r)` - RCR (n Combinations of r with Repetition):
 *   - Calculates the number of combinations of r items from a set of n distinct items with repetition allowed.
 *
 * 5. `sml_cpr(n, r)` - CPR (n Circular Permutations of r):
 *   - Calculates the number of circular permutations of r items from a set of n distinct items.
 *
 * 6. `sml_ccr(n, r)` - CCR (n Circular Combinations of r):
 *   - Calculates the number of circular combinations of r items from a set of n distinct items.
 */


// Matrix Operations; //
typedef struct {
    sml_size rows;
    sml_size cols;
    sml_math_t **data;
} sml_matrix_t;


// adds 2 sml_math_t's together
sml_math_t sml_math_t_add(sml_math_t *num1, sml_math_t *num2);

void sml_math_t_print(sml_math_t *num, FILE *stream);

sml_matrix_t *sml_matrix_create(sml_size rows, sml_size cols);

void sml_matrix_destroy(sml_matrix_t *matrix);

void sml_matrix_print(sml_matrix_t *matrix);

void sml_matrix_zero_init(sml_matrix_t *matrix);

// duplicates the matrix in a different malloced space
sml_matrix_t *sml_matrix_dup(sml_matrix_t *src);

sml_matrix_t *sml_matrix_transpose(sml_matrix_t *matrix);

// Planned functions to add
//
//sml_matrix_t *sml_matrix_add(sml_matrix_t *matrix1, sml_matrix_t *matrix2);
//
//sml_matrix_t *sml_matrix_subtract(sml_matrix_t *matrix1, sml_matrix_t *matrix2);
//
//sml_matrix_t *sml_matrix_multiply(sml_matrix_t *matrix1, sml_matrix_t *matrix2);
//
//sml_matrix_t *sml_matrix_divide(sml_matrix_t *matrix1, sml_matrix_t *matrix2);
//
//sml_matrix_t *sml_matrix_scalar_multiply(sml_matrix_t *matrix, double scalar);
//
//sml_matrix_t *sml_matrix_scalar_divide(sml_matrix_t *matrix, double scalar);
//
//sml_matrix_t *sml_matrix_scalar_add(sml_matrix_t *matrix, double scalar);
//
//sml_matrix_t *sml_matrix_scalar_subtract(sml_matrix_t *matrix, double scalar);
//
//sml_matrix_t *sml_matrix_identity(sml_size_t size);
//
//sml_matrix_t *sml_matrix_zero(sml_size_t size);
//
//sml_matrix_t *sml_matrix_ones(sml_size_t size);
//
//sml_matrix_t *sml_matrix_diagonal(sml_size_t size, sml_math_t value);
//
//sml_matrix_t *sml_matrix_random(sml_size_t rows, sml_size_t cols, sml_size_t seed);
//
//sml_matrix_t *sml_matrix_random_gaussian(sml_size_t rows, sml_size_t cols, sml_size_t seed);
//
//sml_matrix_t *sml_matrix_random_uniform(sml_size_t rows, sml_size_t cols, sml_size_t seed);
//
//sml_matrix_t *sml_matrix_random_normal(sml_size_t rows, sml_size_t cols, sml_size_t seed);
//
//sml_matrix_t *sml_matrix_random_bernoulli(sml_size_t rows, sml_size_t cols, sml_size_t seed);
//
//sml_matrix_t *sml_matrix_random_binomial(sml_size_t rows, sml_size_t cols, sml_size_t seed);
//
//sml_matrix_t *sml_matrix_random_poisson(sml_size_t rows, sml_size_t cols, sml_size_t seed);

#endif //SML_DIALECT_MATH_H
