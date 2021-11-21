#include "string.h"

void *memset(void *s, int c, size_t n) {
    unsigned char *ptr = s;
    while (n--) {
        *ptr++ = c;
    }
    return s;
}

void reverse(char *s) {
    for (int i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        char c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

size_t strlen(const char *s) {
	size_t len = 0;
	while (s[len]) {
		len++;
    }
	return len;
}
