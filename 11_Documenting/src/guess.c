#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <libintl.h>
#include <locale.h>

/** @mainpage guess
 * Wonderful Guess Game
 * @section SYNOPSIS
 * `guess` [ \a -p | \a --help ]
 * @section DESCRIPTION
 * Here is Wonderful Guess Game!
 * You can enjoy it for days. What a lovely one!
 * You can play it using arabic and roman numbers. What a diversity!
 * @copydetails library
*/

/**
 * @file guess.c
*/

/** Arabic to roman numbers mapping
*/
const char *roman[] = {
    "I",
    "II",
    "III",
    "IV",
    "V",
    "VI",
    "VII",
    "VIII",
    "IX",
    "X",
    "XI",
    "XII",
    "XIII",
    "XIV",
    "XV",
    "XVI",
    "XVII",
    "XVIII",
    "XIX",
    "XX",
    "XXI",
    "XXII",
    "XXIII",
    "XXIV",
    "XXV",
    "XXVI",
    "XXVII",
    "XXVIII",
    "XXIX",
    "XXX",
    "XXXI",
    "XXXII",
    "XXXIII",
    "XXXIV",
    "XXXV",
    "XXXVI",
    "XXXVII",
    "XXXVIII",
    "XXXIX",
    "XL",
    "XLI",
    "XLII",
    "XLIII",
    "XLIV",
    "XLV",
    "XLVI",
    "XLVII",
    "XLVIII",
    "XLIX",
    "L",
    "LI",
    "LII",
    "LIII",
    "LIV",
    "LV",
    "LVI",
    "LVII",
    "LVIII",
    "LIX",
    "LX",
    "LXI",
    "LXII",
    "LXIII",
    "LXIV",
    "LXV",
    "LXVI",
    "LXVII",
    "LXVIII",
    "LXIX",
    "LXX",
    "LXXI",
    "LXXII",
    "LXXIII",
    "LXXIV",
    "LXXV",
    "LXXVI",
    "LXXVII",
    "LXXVIII",
    "LXXIX",
    "LXXX",
    "LXXXI",
    "LXXXII",
    "LXXXIII",
    "LXXXIV",
    "LXXXV",
    "LXXXVI",
    "LXXXVII",
    "LXXXVIII",
    "LXXXIX",
    "XC",
    "XCI",
    "XCII",
    "XCIII",
    "XCIV",
    "XCV",
    "XCVI",
    "XCVII",
    "XCVIII",
    "XCIX",
    "C"
};

/**
 * Convert arabic number @p i to roman using @p roman
 * @param i arabic number
 * @return string representing roman number
*/
const char *to_roman(int i) {
    assert(i > 0 && i <= 100);
    return roman[i - 1];
}

/**
 * Convert roman number @p i to roman using @p roman
 * @param i roman number
 * @return number corresponding to @p i
*/
int from_roman(const char *i) {
    for (int k = 0; k < 100; ++k) {
        if (!strcmp(i, roman[k - 1])) {
            return k + 1;
        }
    }
    assert(0);
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    bindtextdomain("guess", "po");
    textdomain("guess");
    
    int roman_mode = 0;
    if (argc == 2 && !strcmp("-r", argv[1])) {
        roman_mode = 1;
    }
    else if (argc == 2 && !strcmp("--help", argv[1])) {
        printf(gettext("Here is Wonderful Guess Game!\n"));
        printf(gettext("You can enjoy it for days. What a lovely one!\n"));
        printf(gettext("You can play it using arabic and roman numbers. What a diversity!\n"));
        return 0;
    }

    int l = 1, r = 100;
    if (roman_mode)
        printf(gettext("Guess the number from I to C\n"));
    else
        printf(gettext("Guess the number from 1 to 100\n"));
    while (r - l >= 1) {
        int mid = l + (r - l) / 2;
        if (roman_mode)
            printf(gettext("Is the number greater then %s?\n"), to_roman(mid));
        else
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
    if (roman_mode)
        printf(gettext("The number is %s\n"), to_roman(l));
    else
        printf(gettext("The number is %d\n"), l);
    return 0;
 }