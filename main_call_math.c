#ifndef CALL_MATH_H
#define CALL_MATH_H

#define M_PI_PURE 3.14159265358979323846
#define M_E_PURE  2.71828182845904523536

typedef struct {
    double real;
    double imag;
} m_complex;

typedef struct {
    double x;
    double y;
    double z;
} m_vector3d;

static long long math_add_int(long long a, long long b) { return a + b; }
static double math_add_double(double a, double b) { return a + b; }
static long long math_sub_int(long long a, long long b) { return a - b; }
static double math_sub_double(double a, double b) { return a - b; }
static long long math_mul_int(long long a, long long b) { return a * b; }
static double math_mul_double(double a, double b) { return a * b; }
static long long math_div_int(long long a, long long b) { return (b == 0) ? 0 : a / b; }
static double math_div_double(double a, double b) { return (b == 0.0) ? 0.0 : a / b; }
static long long math_mod_int(long long a, long long b) { return (b == 0) ? 0 : a % b; }

static long long math_pow(long long base, long long exp) {
    long long result = 1; if (exp < 0) return 0;
    while (exp > 0) { if (exp % 2 == 1) result *= base; base *= base; exp /= 2; }
    return result;
}

static double math_pow_double(double base, int exp) {
    double result = 1.0; int p = (exp < 0) ? -exp : exp;
    for (int i = 0; i < p; i++) result *= base;
    return (exp < 0) ? 1.0 / result : result;
}

static long long math_fact(int n) {
    if (n < 0 || n > 20) return 0; long long result = 1;
    for (int i = 2; i <= n; i++) result *= i; return result;
}

static double math_fabs(double n) { return (n < 0.0) ? -n : n; }
static long long math_abs(long long n) { return (n < 0) ? -n : n; }

static long long math_gcd(long long a, long long b) {
    a = (a < 0) ? -a : a; b = (b < 0) ? -b : b;
    while (b != 0) { long long temp = b; b = a % b; a = temp; } return a;
}

static long long math_lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0; return (math_abs(a) / math_gcd(a, b)) * math_abs(b);
}

static int math_is_prime(long long n) {
    if (n <= 1) return 0; if (n <= 3) return 1; if (n % 2 == 0 || n % 3 == 0) return 0;
    for (long long i = 5; i * i <= n; i += 6) { if (n % i == 0 || n % (i + 2) == 0) return 0; }
    return 1;
}

static long long math_sqrt(long long n) {
    if (n < 0) return -1; if (n == 0 || n == 1) return n;
    long long start = 1, end = n, ans = 0;
    while (start <= end) {
        long long mid = start + (end - start) / 2;
        if (mid <= n / mid) { start = mid + 1; ans = mid; } else { end = mid - 1; }
    }
    return ans;
}

static double math_sqrt_double(double n) {
    if (n < 0.0) return -1.0; if (n == 0.0) return 0.0;
    double x = n, y = 1.0, e = 0.00000000000001;
    while (math_fabs(x - y) > e) { x = (x + y) / 2.0; y = n / x; } return x;
}

static double math_sin(double x) {
    while (x > M_PI_PURE) x -= 2.0 * M_PI_PURE; while (x < -M_PI_PURE) x += 2.0 * M_PI_PURE;
    double term = x, sum = x;
    for (int i = 1; i <= 12; i++) { term = -term * x * x / ((2 * i) * (2 * i + 1)); sum += term; }
    return sum;
}

static double math_cos(double x) {
    while (x > M_PI_PURE) x -= 2.0 * M_PI_PURE; while (x < -M_PI_PURE) x += 2.0 * M_PI_PURE;
    double term = 1.0, sum = 1.0;
    for (int i = 1; i <= 12; i++) { term = -term * x * x / ((2 * i - 1) * (2 * i)); sum += term; }
    return sum;
}

static double math_tan(double x) {
    double c = math_cos(x); return (math_fabs(c) < 0.0000001) ? 0.0 : math_sin(x) / c;
}

static double math_exp(double x) {
    double sum = 1.0, term = 1.0;
    for (int i = 1; i <= 20; i++) { term = term * x / i; sum += term; } return sum;
}

static double math_ln(double x) {
    if (x <= 0.0) return -1.0;
    double sum = 0.0, y = (x - 1.0) / (x + 1.0), term = y, y_squared = y * y;
    for (int i = 1; i <= 30; i += 2) { if (i > 1) term *= y_squared; sum += term / i; }
    return 2.0 * sum;
}

static m_complex math_complex_add(m_complex a, m_complex b) { m_complex res = { a.real + b.real, a.imag + b.imag }; return res; }
static m_complex math_complex_sub(m_complex a, m_complex b) { m_complex res = { a.real - b.real, a.imag - b.imag }; return res; }
static m_complex math_complex_mul(m_complex a, m_complex b) { m_complex res = { (a.real * b.real) - (a.imag * b.imag), (a.real * b.imag) + (a.imag * b.real) }; return res; }
static m_complex math_complex_div(m_complex a, m_complex b) {
    double denom = (b.real * b.real) + (b.imag * b.imag); m_complex res = {0};
    if (denom != 0.0) { res.real = ((a.real * b.real) + (a.imag * b.imag)) / denom; res.imag = ((a.imag * b.real) - (a.real * b.imag)) / denom; }
    return res;
}

static m_vector3d math_vector_add(m_vector3d a, m_vector3d b) { m_vector3d res = { a.x + b.x, a.y + b.y, a.z + b.z }; return res; }
static m_vector3d math_vector_sub(m_vector3d a, m_vector3d b) { m_vector3d res = { a.x - b.x, a.y - b.y, a.z - b.z }; return res; }
static double math_vector_dot(m_vector3d a, m_vector3d b) { return (a.x * b.x) + (a.y * b.y) + (a.z * b.z); }
static m_vector3d math_vector_cross(m_vector3d a, m_vector3d b) { m_vector3d res = { (a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x) }; return res; }
static double math_vector_mag(m_vector3d a) { return math_sqrt_double((a.x * a.x) + (a.y * a.y) + (a.z * a.z)); }

#define m_addi(a,b)      math_add_int(a,b)
#define m_addd(a,b)      math_add_double(a,b)
#define m_subi(a,b)      math_sub_int(a,b)
#define m_subd(a,b)      math_sub_double(a,b)
#define m_muli(a,b)      math_mul_int(a,b)
#define m_muld(a,b)      math_mul_double(a,b)
#define m_divi(a,b)      math_div_int(a,b)
#define m_divd(a,b)      math_div_double(a,b)
#define m_modi(a,b)      math_mod_int(a,b)
#define m_pow(b,e)       math_pow(b,e)
#define m_powd(b,e)      math_pow_double(b,e)
#define m_fact(n)        math_fact(n)
#define m_abs(n)         math_abs(n)
#define m_fabs(n)        math_fabs(n)
#define m_gcd(a,b)       math_gcd(a,b)
#define m_lcm(a,b)       math_lcm(a,b)
#define m_prime(n)       math_is_prime(n)
#define m_sqrt(n)        math_sqrt(n)
#define m_sqrtd(n)       math_sqrt_double(n)
#define m_sin(x)         math_sin(x)
#define m_cos(x)         math_cos(x)
#define m_tan(x)         math_tan(x)
#define m_exp(x)         math_exp(x)
#define m_ln(x)          math_ln(x)
#define m_cadd(a,b)      math_complex_add(a,b)
#define m_csub(a,b)      math_complex_sub(a,b)
#define m_cmul(a,b)      math_complex_mul(a,b)
#define m_cdiv(a,b)      math_complex_div(a,b)
#define v_add(a,b)       math_vector_add(a,b)
#define v_sub(a,b)       math_vector_sub(a,b)
#define v_dot(a,b)       math_vector_dot(a,b)
#define v_cross(a,b)     math_vector_cross(a,b)
#define v_mag(a)         math_vector_mag(a)

#endif
