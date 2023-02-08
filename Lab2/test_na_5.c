# include <stdio.h>

int main() {
    int a = 4;
    int b = 2;
    float x = 4.8;
    float y = 2.2;

    print_int(add(a, b));
    printf("\n");
    print_int(sub(a, b));
    printf("\n");
    print_float(div(x, y));
    printf("\n");
    return 0;
}