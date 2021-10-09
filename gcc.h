#ifndef _GCC_H
#define _GCC_H

/* CPP header guards */
#ifdef __cplusplus
#define EXTERN_C_BEGIN extern "C" {
#define EXTERN_C_END   }
#else
#define EXTERN_C_BEGIN
#define EXTERN_C_END
#endif

#define __MACRO_BEGIN do {
#define __MACRO_END \
    }               \
    while (0)

#if defined(__GNUC__) /* GNU Compiler */
#ifndef __ASM
#define __ASM __asm
#endif
#ifndef __INLINE
#define __INLINE inline
#endif
#ifndef __ALWAYS_INLINE
#define __ALWAYS_INLINE inline __attribute__((always_inline))
#endif
#ifndef __ALWAYS_STATIC_INLINE
#define __ALWAYS_STATIC_INLINE __attribute__((always_inline)) static inline
#endif
#ifndef __ALWAYS_INLINE
#define __ALWAYS_INLINE inline __attribute__((always_inline))
#endif
#ifndef __STATIC_INLINE
#define __STATIC_INLINE static inline
#endif
#ifndef __STATIC
#define __STATIC static
#endif
#ifndef __VOLATILE
#define __VOLATILE volatile
#endif
#ifndef __NO_RETURN
#define __NO_RETURN __attribute__((noreturn))
#endif
#ifndef __FUNC_NORETURN
#define __FUNC_NORETURN __attribute__((noreturn))
#endif
#ifndef __USED
#define __USED __attribute__((used))
#endif
#ifndef __UNUSED
#define __UNUSED __attribute__((unused))
#endif
#ifndef __NAKED
#define __NAKED __attribute__((naked))
#endif
#ifndef __WEAK
#define __WEAK __attribute__((weak))
#endif
#ifndef __PACKED
#define __PACKED __attribute__((packed, aligned(1)))
#endif
#ifndef __PACKED_STRUCT
#define __PACKED_STRUCT struct __attribute__((packed, aligned(1)))
#endif
#ifndef __PACKED_UNION
#define __PACKED_UNION union __attribute__((packed, aligned(1)))
#endif
#ifndef __IRQ
#define __IRQ __attribute__((interrupt))
#endif
#ifndef __IRQ_ALIGN64
#define __IRQ_ALIGN64 __attribute__((interrupt, aligned(64)))
#endif
#ifndef __ALIGN4
#define __ALIGN4 __attribute((aligned(4)))
#endif
#ifndef __CONST
#define __CONST __attribute__((__const__))
#endif
#ifndef __deprecated
#define __deprecated __attribute__((deprecated))
#endif
#ifndef __API
#define __API __declspec(dllexport)
#endif
#ifndef __PURE
#define __PURE __attribute__((__pure__))
#endif
#ifndef __no_optimization
#define __no_optimization __attribute__((optimize("-O0")))
#endif
#ifndef likely
#define likely(x) __builtin_expect(!!(x), 1)
#endif
#ifndef unlikely
#define unlikely(x) __builtin_expect(!!(x), 0)
#endif
#ifndef ALIAS_OF
#define ALIAS_OF(of) __attribute__((alias(#of)))
#endif
#ifndef PACK_START
#define PACK_START
#endif
#ifndef PACK_END
#define PACK_END __attribute__((packed))
#endif
#ifndef ALIGNED
#define ALIGNED(x) __attribute__((aligned(x)))
#endif
#ifndef SECTION
#define SECTION(x) __attribute__((section(x)))
#endif
#endif /* __GNUC__ */

#ifndef ARG_UNUSED
#define ARG_UNUSED(x) (void)(x)
#endif

//#define VOID                                    void
//typedef char                                    CHAR;
//typedef unsigned char                           UCHAR;
//typedef int                                     INT;
//typedef unsigned int                            UINT;
//typedef long                                    LONG;
//typedef unsigned long                           ULONG;
//typedef short                                   SHORT;
//typedef unsigned short                          USHORT;

#endif
