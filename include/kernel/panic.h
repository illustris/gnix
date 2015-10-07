#ifndef KERNEL_PANIC_H
#define KERNEL_PANIC_H

#include <kernel/stdint.h>

#define PANIC(msg)	panic_func(msg, __FILE__, __LINE__, __func__)
#define ASSERT(a)	((a) ? (void)0 : panic_assert(#a, __FILE__, __LINE__))

void panic(const int8_t *message, const int8_t *file, uint32_t line);
void panic_assert(const int8_t *assertion, const int8_t *file, uint32_t line);
void panic_func(const int8_t *message, const int8_t *file, uint32_t line, const int8_t *func);

#endif
