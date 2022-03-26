#ifndef TYPES_H
#define TYPES_H

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int int16_t;
typedef unsigned short int uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
#if __WORDSIZE == 64
typedef signed long int64_t;
typedef unsigned long uint64_t;
#else
typedef signed long long int64_t;
typedef unsigned long long uint64_t;
#endif

typedef unsigned int uintptr_t;
typedef unsigned int size_t;

#endif
