#include <stdio.h>
#include <string.h>

int main() {
    FILE *f;
    char arr[1000];
    int frq[256] = {0};

   
    f = fopen("a.dat", "r");
    if (f == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

   
    fgets(arr, sizeof(arr), f);
    fclose(f);


    fputs(arr, stdout);

 
    f = fopen("a.dat", "r");
    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);

printf("\nThe size of the file in bytes is %ld\n", file_size);

   
    int len = strlen(arr);
    for (int i = 0; i < len; i++) {
        frq[arr[i]]++;
    }

    printf("\nCharacter frequencies:\n");
    for (int i = 0; i < 256; i++) {
        if (frq[i] > 0) {
            printf("Character '%c' appears %d times\n", i, frq[i]);
        }
    }
int sum=0;
for(int i=0;i<256;i++){
sum+=frq[i];}
printf("the total no. of character is :%d \n the file in reverse order :\n",sum);
char c; int i=0;
while(i!=-(file_size)){

fseek(f,i,SEEK_END);
i--;
c=fgetc(f);

fputc(c,stdout);}
fseek(f,i,SEEK_END);
c=fgetc(f);
fputc(c,stdout);
    fclose(f);
    
    return 0;
}
