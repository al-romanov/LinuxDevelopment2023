#include <stdio.h>
#include <string.h>

#include <libintl.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");
    bindtextdomain("guess", "po");
    textdomain("guess");

    int l = 1, r = 100;
    printf(gettext("Guess the number from 1 to 100\n"));
    while (r - l >= 1) {
        int mid = l + (r - l) / 2;
        printf(gettext("Is the number greater then %d?\n"), mid);
        char answer[7];
        int ret = scanf("%6s", answer);
        if (ret != 1) {
            continue;
        }
        if (strcmp(answer, gettext("Yes")) == 0) {
            l = mid + 1;
        }
        else if (strcmp(answer, gettext("No")) == 0) {
            r = mid;
        }
        else {
            puts(gettext("Enter Yes or No"));
        }
    }
    printf(gettext("The number is %d\n"), l);
    return 0;
 }