#include <stdio.h>
#include <math.h>

int main() {
    double x = 1;
    double(*f[5])(double) = {sin, cos, tan, exp ,log};
    printf("%lf\n", f[((int)x)<<2](x));
    return 0;
}