#include <functional>

/* Tries to find a zero crossing in f() in the interval [a,b] with the bisection method
 * Returns true if a root is found. The crossing is stored in root.
 * Returns false if a crossing could not be found. Finding a root
 * is only guarenteed if f is continous within the interval and
 * a & b have opposite signs
 */
bool bisection(std::function<double(double)> f,double a, double b, double *root) {
    if (f(a) * f(b) >= 0){
        return false;
    }
    double c;
    double result;
    double tolerance = 1e-6;
    while(true) {
        c = (a + b)/2;
        result = f(c);
        if (std::abs(result) < tolerance) {
            *root = c;
            return true;
        }
        if (f(a) * result < 0) {
            b = c;
        }
        else {
            a = c;
        }
    }
}

/* Tries to find a zero crossing in f() in the interval [a,b] with the
 * false positive / regula falsi method
 * Returns true if a root is found. The crossing is stored in root.
 * Returns false if a crossing could not be found. Finding a root
 * is only guarenteed if f is continous within the interval and
 * a & b have opposite signs
 */
bool regula_falsi(std::function<double(double)> f, double a, double b, double *root) {
    if (f(a) * f(b) >= 0){
        return false;
    }
    double c;
    double result;
    double tolerance = 1e-6;
    while(true) {
        c = a - (f(a) * (b - a)) / (f(b) - f(a));
        result = f(c);
        if (std::abs(result) < tolerance) {
            *root = c;
            return true;
        }
         if (f(a) * result < 0) {
            b = c;
        }
        else {
            a = c;
        }
    }
}

/* Tries to find a zero crossing in f() in the interval [a,b] with
 * the netwon-raphson method, given a function that computes the
 * derivative g() and a starting guess c.
 * Returns true if a root is found. The crossing is stored in root.
 * Returns false if a crossing could not be found, which can happen
 * if iteration leaves the interval, or the derivative is zero.
 */
bool newton_raphson(std::function<double(double)> f, std::function<double(double)> g,
                     double a, double b, double c, double *root) {
    double result;
    double tolerance = 1e-6;
    while (true) {
        result = c - f(c) / g(c);
        if ((result < a) | (result > b)){
            return false;
        }
        if (std::abs(c - result) < tolerance){
            *root = result;
            return true;
        }
        else { 
            c = result;
        }
    }

}

/* Tries to find a zero crossing in f() in the interval [a,b] with
 * the secant method, given a starting guess c.
 * Returns true if a root is found. The crossing is stored in root.
 * Returns false if a crossing could not be found, which can happen
 * if iteration leaves the interval, or derivative is zero.
 */
bool secant(std::function<double(double)> f,
            double a, double b, double c, double *root) {
    double result;
    double tolerance = 1e-6;
    double d = c + tolerance;
    while (true) {
        result = d - f(d) * (d - c) / (f(d) - f(c));
         if ((result < a) | (result > b)){
            return false;
        }
        if (std::abs(result - d) < tolerance) {
            *root = result;
            return true;
        }
        else {
            c = d;
            d = result;
        }
    }
}

