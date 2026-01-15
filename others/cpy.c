#include <stdio.h>

int main() {
    FILE *f;
    FILE *f1;
    char str[1000];

   
    f = fopen("a.dat", "r+");
    if (f == NULL) {
        printf("Error: Could not open copy.dat for reading.\n");
        return 1;
    }

   
    f1 = fopen("copy.dat", "w+");
    if (f1 == NULL) {
        printf("Error: Could not open a.dat for writing.\n");
        fclose(f);
        return 1;
    }

    
    while (fgets(str, sizeof(str), f) != NULL) {
        fputs(str, f1);
    }

    
    rewind(f1);

 
    printf("Content of a.dat:\n");
    while (fgets(str, sizeof(str), f1) != NULL) {
        fputs(str, stdout);
    }

    
    fclose(f);
    fclose(f1);

    return 0;
}
