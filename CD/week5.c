
#include <stdio.h>
#include <string.h>

int action(int state, char ch) {
    if (state == 0 || state == 1 || state == 3) {
        if (ch == 'c') return 3;
        if (ch == 'd') return 4;
    }
    else if (state == 2 && ch == '$')
        return 100;

    else if (state == 4)
        return -3;

    else if (state == 5 && ch == '$')
        return -1;

    else if (state == 6)
        return -2;

    return 0;
}

int goTo(int state, char ch) {
    if (state == 0 && ch == 'S') return 1;
    if (state == 0 && ch == 'C') return 2;
    if (state == 1 && ch == 'C') return 5;
    if (state == 3 && ch == 'C') return 6;

    return -1;
}

void parse(char str[]) {
    int st[100], top = 0, i = 0;
    int act, p, length, ns;
    char ch;

    strcat(str, "$");
    st[0] = 0;

    printf("\nParsing Steps:\n");

    while (1) {
        int s = st[top];
        ch = str[i];

        act = action(s, ch);

        printf("State: %d Input: %s", s, str + i);

        if (act == 0) {
            printf(" Action: ERROR\n");
            printf("\nString Rejected!\n");
            return;
        }

        if (act == 100) {
            printf(" Action: ACCEPT\n");
            printf("\nString Accepted!\n");
            return;
        }

        if (act > 0) {
            printf(" Action: s%d\n", act);
            st[++top] = act;
            i++;
        }
        else {
            p = -act;

            if (p == 1) {
                printf(" Action: r1 (S -> CC)\n");
                length = 2;
            }
            else if (p == 2) {
                printf(" Action: r2 (C -> cC)\n");
                length = 2;
            }
            else {
                printf(" Action: r3 (C -> d)\n");
                length = 1;
            }

            top -= length;

            ns = goTo(st[top], p == 1 ? 'S' : 'C');

            if (ns == -1) {
                printf("\nString Rejected!\n");
                return;
            }

            st[++top] = ns;
        }
    }
}

int main() {
    char str[100];

    printf("Grammar:\n");
    printf("S -> CC\n");
    printf("C -> cC\n");
    printf("C -> d\n");

    printf("\nEnter input string: ");
    scanf("%99s", str);

    parse(str);

    return 0;
}
