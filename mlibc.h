#ifndef MLIBC_H
#define MLIBC_H

typedef unsigned long size_t;
typedef long ssize_t;

static ssize_t sys_write(int fd, const char *buf, size_t count);
void print_char(char c);
void print_string(const char *s);
void print_number(long num, int base, int is_signed);
void printf(const char *fmt, ...);
size_t strlen(const char *s);
int strcmp(const char *a, const char *b);
void *memset(void *buf, int value, size_t n);
void *memcpy(void *dest, const void *src, size_t n);

#endif
