#include <stdio.h>
#include <string.h>

int main() {
    char a[] = "Ahora";
    char b[] = "Ahoras";

    int cmp = strcmp(a, b);

    if (cmp < 0)
        printf("%s va antes que %s\n", a, b);
    else if (cmp > 0)
        printf("%s va después que %s\n", a, b);
    else
        printf("Las cadenas son iguales\n");

    return 0;
}
