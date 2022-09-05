#pragma once

#define STRINGIFY_HELPER(x) #x
#define STRINGIFY2(x) STRINGIFY_HELPER(x)

void kassert(const char *expr, const char *message, char const *file, unsigned line);

#define panic()                           \
    do {                                  \
        for (;;) { asm volatile("hlt"); } \
    } while (0)

#define assert(expr, message)                             \
    do {                                                  \
        if (!static_cast<bool>(expr)) [[unlikely]] {      \
            kassert(#expr, #message, __FILE__, __LINE__); \
            panic();                                      \
        }                                                 \
    } while (0)
