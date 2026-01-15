#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *original, *paperback, *hardback, *both;
    char book_type;
    char title[20];
    int pages;

    original = fopen("Original.dat", "r");
    if (original == NULL) {
        printf("Error: Cannot open Original.dat\n");
        return 1;
    }

    paperback = fopen("p.dat", "w");
    hardback = fopen("e.dat", "w");
    both = fopen("both.dat", "w");
    if (paperback == NULL || hardback == NULL || both == NULL) {
        printf("Error: Cannot create output files\n");
        fclose(original);
        return 1;
    }

    while (fscanf(original, " %c %19s %d", &book_type, title, &pages) == 3) {
        if (book_type == 'p')
            fprintf(paperback, "%c %s %d\n", book_type, title, pages);
        else if (book_type == 'h')
            fprintf(hardback, "%c %s %d\n", book_type, title, pages);
        else if (book_type == 'b')
            fprintf(both, "%c %s %d\n", book_type, title, pages);
    }

    fclose(original);
    fclose(paperback);
    fclose(hardback);
    fclose(both);

    return 0;
}
