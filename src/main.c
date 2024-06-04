#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum TokenType { _exit, intval, semicol, openp, closep } TokenType;

typedef struct Token {
    TokenType type;
    char *value;
} Token;

typedef struct Var {
    char value[100];
    int count;
    void (*insert)(struct Var var, char c);
} Var;

void var_func(Var var, char c) {
    {
        var.value[var.count] = c;
        var.count++;
    }
}

int main(void) {
    /* Opening the source file main.ds for now */
    FILE *file = fopen("main.ds", "r+");
    Var var;
    var.insert = &var_func;
	var.count = 0;

    char c;
    while ((c = fgetc(file)) != EOF) {
        if (isalpha(c)) {
            var_func(var, c);
			putchar(c);
            while ((c = fgetc(file)) != EOF && isalpha(c)) {
				putchar(c);
                var_func(var, c);
            }
        }
    }
    puts(var.value);

    /* Closing the file to free and clean the heap */
    fclose(file);
    return (0);
}
