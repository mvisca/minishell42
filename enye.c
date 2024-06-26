#include <stdio.h>

int main() {
    // Imprime la letra ñ directamente usando su representación en UTF-8
    printf("La letra ñ en UTF-8: ñ\n");

    // Otra forma de imprimir la letra ñ usando su código Unicode (0xC3 0xB1)
    char n_tilde[] = {0xC3, 0xB1, '\0'};
    printf("La letra ñ usando su código Unicode: %s\n", n_tilde);

    return 0;
}
