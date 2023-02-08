# include <stdio.h>

void print_int(int a);
int add (int a, int b);
int sub (int a , int b);
float div (float a, float b);
float print_float_here(float a);

int main() {
    int a = 4;
    int b = 2;
    float x = 4.2;
    float y = 2.2;

    print_int(add(a, b));
    printf("\n");
    print_int(sub(a, b));
    printf("\n");
    
    print_float_here(div(x,y));
    printf("\n");
    return 0;
}