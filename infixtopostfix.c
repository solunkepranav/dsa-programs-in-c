#include <stdio.h>
#include <string.h>

int icp(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '(':
            return 3;
        default:
            return 0;
    }
}

int isp(char c) {
    switch (c) {
        case '#':
            return -1;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '(':
            return 0;
        default:
            return 0;
    }
}

int main() {
    int n;
    printf("Enter the number of characters in the expression: ");
    scanf("%d", &n);
    getchar();  // consume the leftover newline from scanf

    char infix[n + 1];  // +1 for null terminator
    printf("Enter the infix expression: ");
    fgets(infix, sizeof(infix), stdin);

    // Remove trailing newline if present
    size_t len = strlen(infix);
    if (infix[len - 1] == '\n') {
        infix[len - 1] = '\0';
        len--;
    }

    char opstk[50];  // operator stack
    char pstk[100];  // output/postfix stack
    int t1 = -1, t2 = -1;

    opstk[++t1] = '#';

    for (int i = 0; i < len; i++) {
        char ch = infix[i];

        if (ch >= 'a' && ch <= 'z') {
            pstk[++t2] = ch;
        } else if (ch == ')') {
            while (opstk[t1] != '(') {
                pstk[++t2] = opstk[t1--];
            }
            t1--;  // Pop the '('
        } else if (ch == '(' || icp(ch) > isp(opstk[t1])) {
            opstk[++t1] = ch;
        } else {
            while (icp(ch) <= isp(opstk[t1])) {
                pstk[++t2] = opstk[t1--];
            }
            opstk[++t1] = ch;
        }
    }

    while (opstk[t1] != '#') {
        pstk[++t2] = opstk[t1--];
    }

    pstk[++t2] = '\0';  // null-terminate the postfix expression

    printf("The postfix expression: %s\n", pstk);

    return 0;
}
