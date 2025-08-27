#include <mlibc.h>

typedef unsigned long size_t;
typedef long ssize_t;

ssize_t sys_write(int fd, const char *buf, size_t count) {
    ssize_t ret;
    __asm__ (
        "movq $1, %%rax\n\t"   // syscall number for write
        "movq %1, %%rdi\n\t"   // fd
        "movq %2, %%rsi\n\t"   // buf
        "movq %3, %%rdx\n\t"   // count
        "syscall\n\t"
        "movq %%rax, %0"
        : "=r"(ret)
        : "r"((long)fd), "r"(buf), "r"(count)
        : "rax","rdi","rsi","rdx"
    );
    return ret;
}

void print_char(char c) {
    sys_write(1, &c, 1);
}

void print_string(const char *s) {
    while (*s) {
        print_char(*s++);
    }
}

void print_number(long num, int base, int is_signed) {
    char buf[65];
    int i = 0;
    int neg = 0;

    if (is_signed && num < 0) {
        neg = 1;
        num = -num;
    }

    if (num == 0) {
        print_char('0');
        return;
    }

    while (num) {
        int digit = num % base;
        buf[i++] = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
        num /= base;
    }

    if (neg) buf[i++] = '-';

    while (i--) {
        print_char(buf[i]);
    }
}

void printf(const char *fmt, ...) {
    char **arg = (char **)&fmt + 1;
    for (; *fmt; fmt++) {
        if (*fmt == '%') {
            fmt++;
            if (*fmt == 's') {
                print_string(*arg++);
            } else if (*fmt == 'd') {
                print_number((long)(int)(*arg++), 10, 1);
            } else if (*fmt == 'u') {
                print_number((long)(unsigned int)(*arg++), 10, 0);
            } else if (*fmt == 'x') {
                print_number((long)(unsigned int)(*arg++), 16, 0);
            } else if (*fmt == 'c') {
                print_char((char)(long)(*arg++));
            } else {
                print_char(*fmt);
            }
        } else {
            print_char(*fmt);
        }
    }
}

// strlen: returns length of a string
size_t strlen(const char *s) {
    size_t len = 0;
    while (*s++) len++;
    return len;
}

// strcmp: compares two strings, returns 0 if equal
int strcmp(const char *a, const char *b) {
    while (*a && (*a == *b)) {
        a++;
        b++;
    }
    return *(unsigned char*)a - *(unsigned char*)b;
}

// memset: fills a buffer with a value
void *memset(void *buf, int value, size_t n) {
    unsigned char *p = buf;
    for (size_t i = 0; i < n; i++) p[i] = (unsigned char)value;
    return buf;
}

// memcpy: copies n bytes from src to dest
void *memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = dest;
    const unsigned char *s = src;
    for (size_t i = 0; i < n; i++) d[i] = s[i];
    return dest;
}
