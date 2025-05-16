#include "utils.h"

void xorEncryptDecrypt(char *text, char key) {
    while (*text != '\0') {
        *text ^= key;
        text++;
    }
}
