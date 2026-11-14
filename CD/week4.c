
#include <stdio.h>
#include <string.h>

char table[5][6] = {
    //  i     +     *     (     )     $
    { ' ', ' ', ' ', ' ', ' ', ' ' },  // Dummy
};

char* getRule(char X, char a) {
    if (X == 'E' && (a == 'i' || a == '('))
        return "TR";

    if (X == 'R' && a == '+')
        return "+TR";
    if (X == 'R' && (a == ')' || a == '$'))
        return "#";

    if (X == 'T' && (a == 'i' || a == '('))
        return "FY";

    if (X == 'Y' && a == '*')
        return "*FY";
    if (X == 'Y' && (a == '+' || a == ')' || a == '$'))
        return "#";

    if (X == 'F' && a == 'i')
        return "i";
    if (X == 'F' && a == '(')
        return "(E)";

    return NULL;
}

int main() {
    char st[100] = "$E";
    char input[100];
    int ip = 0, top = 1;

    printf("Enter input string (use i for identifier): ");
    scanf("%99s", input);

    strcat(input, "$");

    printf("\nStack\t\tInput\t\tAction\n");
    printf("---------------------------------------------\n");

    while (top >= 0) {
        char X = st[top];
        char a = input[ip];

        st[top + 1] = '\0';

        printf("%s\t\t%s\t\t", st, input + ip);

        if (X == '$' && a == '$') {
            printf("Accept\n");
            return 0;
        }

        if (X == a) {
            top--;
            ip++;
            printf("Match %c\n", a);
        }
        else if (X >= 'A' && X <= 'Z') {
            char *rhs = getRule(X, a);

            if (rhs == NULL) {
                printf("Error\n");
                return 0;
            }

            top--;

            printf("%c -> %s\n", X,
                   strcmp(rhs, "#") == 0 ? "epsilon" : rhs);

            if (strcmp(rhs, "#") != 0) {
                int len = strlen(rhs);

                for (int j = len - 1; j >= 0; j--)
                    st[++top] = rhs[j];
            }
        }
        else {
            printf("Error\n");
            return 0;
        }
    }

    printf("Rejected\n");
    return 0;
}
