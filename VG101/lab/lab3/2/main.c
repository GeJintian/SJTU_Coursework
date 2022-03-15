#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sum.h"
#include "prod.h"
#include "quorem.h"
#include "exp.h"
#define quorem
int main(void){
    int a,b;
    printf("Enter two integers: ");
    scanf("%d %d",&a,&b);
#ifdef quorem
    printf("Quotient: %d\n",quo(a,b));
    printf("Remainder: %d\n",rem(a,b));
#endif
#ifdef sum
    printf("Sum: %d\n",sum(a,b));
#endif
#ifdef prod
    printf("Product: %d\n",prod(a,b));
#endif
#ifdef exp
    printf("Exponent: %d\n",mpow(a,b));
#endif
return 0;
}
