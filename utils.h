#ifndef _UTILS__H
#define _UTILS__H

/**
 * @brief Memory access macro
 */
#define RD_WORD(addr)       (*((volatile uint32_t *)(addr)))
#define WR_WORD(addr, val)  ((*(volatile uint32_t *)(addr)) = (val))
#define RD_SHORT(addr)      (*((volatile uint16_t *)(addr)))
#define WR_SHORT(addr, val) ((*(volatile uint16_t *)(addr)) = (val))
#define RD_BYTE(addr)       (*((volatile uint8_t *)(addr)))
#define WR_BYTE(addr, val)  ((*(volatile uint8_t *)(addr)) = (val))
#define RDWD_FRM_BYTEP(p)   ((p[3] << 24) | (p[2] << 16) | (p[1] << 8) | (p[0]))
#define WRWD_TO_BYTEP(p, val)      \
    {                              \
        p[0] = val & 0xff;         \
        p[1] = (val >> 8) & 0xff;  \
        p[2] = (val >> 16) & 0xff; \
        p[3] = (val >> 24) & 0xff; \
    }
/**
 * @brief Register access macro
 */
#define RD_REG16(addr, regname)                RD_SHORT(addr + regname##_OFFSET)
#define WR_REG16(addr, regname, val)           WR_SHORT(addr + regname##_OFFSET, val)
#define RD_REG(addr, regname)                  RD_WORD(addr + regname##_OFFSET)
#define WR_REG(addr, regname, val)             WR_WORD(addr + regname##_OFFSET, val)
#define SET_REG_BIT(val, bitname)              ((val) | (1U << bitname##_POS))
#define CLR_REG_BIT(val, bitname)              ((val)&bitname##_UMSK)
#define IS_REG_BIT_SET(val, bitname)           (((val) & (1U << (bitname##_POS))) != 0)
#define SET_REG_BITS_VAL(val, bitname, bitval) (((val)&bitname##_UMSK) | ((uint32_t)(bitval) << bitname##_POS))
#define GET_REG_BITS_VAL(val, bitname)         (((val)&bitname##_MSK) >> bitname##_POS)

#define DRV_DUMMY \
    {             \
        __NOP();  \
        __NOP();  \
        __NOP();  \
        __NOP();  \
    }

/**
 * \defgroup STRUCT
 * \{
 */

//得到一个field在结构体(struct)中的偏移量
#define OFFSET_OF_FIELD(type, field) \
    ((uint32_t) & (((type *)0)->field))

//得到一个结构体中field所占用的字节数
#define SIZE_OF_FIELD(type, field) sizeof(((type *)0)->field)

//根据一个结构体变量中的一个域成员变量的指针(地址)来获取指向整个结构体变量的指针(地址) ptr：field成员的指针   type：结构体类型   field：成员field的名字。
//type是一个结构体，里面有一个链表成员名为field，已知一个ptr链表地址，求出type结构体变量地址
#define CONTAINER_OF_FIELD(ptr, type, field) \
    ((type *)((uint8_t *)(ptr)-OFFSET_OF_FIELD(type, field)))

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

/**
 * @brief Check if a pointer @p ptr lies within @p array.
 *
 * In C but not C++, this causes a compile error if @p array is not an array
 * (e.g. if @p ptr and @p array are mixed up).
 *
 * @param ptr a pointer
 * @param array an array
 * @return 1 if @p ptr is part of @p array, 0 otherwise
 */
#define PART_OF_ARRAY(array, ptr) \
    ((ptr) && ((ptr) >= &array[0] && (ptr) < &array[ARRAY_SIZE(array)]))

#define STRINGIFY(x) #x
/* concatenate the values of the arguments into one */
#define CONCAT(x, y) x##y
/**
 * @brief Value of @p x rounded up to the next multiple of @p align,
 *        which must be a power of 2.
 */
#define ROUND_UP(x, align)                               \
    (((unsigned long)(x) + ((unsigned long)(align)-1)) & \
     ~((unsigned long)(align)-1))

/**
 * @brief Value of @p x rounded down to the previous multiple of @p
 *        align, which must be a power of 2.
 */
#define ROUND_DOWN(x, align) \
    ((unsigned long)(x) & ~((unsigned long)(align)-1))

/** @brief Value of @p x rounded up to the next word boundary. */
#define WB_UP(x) ROUND_UP(x, sizeof(void *))

/** @brief Value of @p x rounded down to the previous word boundary. */
#define WB_DN(x) ROUND_DOWN(x, sizeof(void *))

/**
 * @brief Ceiling function applied to @p numerator / @p divider as a fraction.
 */
#define ceiling_fraction(numerator, divider) \
    (((numerator) + ((divider)-1)) / (divider))

/**
 * @def MAX
 * @brief The larger value between @p a and @p b.
 * @note Arguments are evaluated twice.
 */
#ifndef MAX
/* Use Z_MAX for a GCC-only, single evaluation version */
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

/**
 * @def MIN
 * @brief The smaller value between @p a and @p b.
 * @note Arguments are evaluated twice.
 */
#ifndef MIN
/* Use Z_MIN for a GCC-only, single evaluation version */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

/**
 * @def CLAMP
 * @brief Clamp a value to a given range.
 * @note Arguments are evaluated multiple times.
 */
#ifndef CLAMP
/* Use Z_CLAMP for a GCC-only, single evaluation version */
#define CLAMP(val, low, high) (((val) <= (low)) ? (low) : MIN(val, high))
#endif

/** @brief Number of bytes in @p x kibibytes */
#ifdef _LINKER
/* This is used in linker scripts so need to avoid type casting there */
#define KB(x) ((x) << 10)
#else
#define KB(x) (((size_t)x) << 10)
#endif
/** @brief Number of bytes in @p x mebibytes */
#define MB(x) (KB(x) << 10)
/** @brief Number of bytes in @p x gibibytes */
#define GB(x) (MB(x) << 10)

/** @brief Number of Hz in @p x kHz */
#define KHZ(x) ((x)*1000)
/** @brief Number of Hz in @p x MHz */
#define MHZ(x) (KHZ(x) * 1000)

/**
 * @brief Unsigned integer with bit position @p n set (signed in
 * assembly language).
 */
#define BIT(n) (1UL << (n))

#define AT_ADDR(x)       __attribute__((section(".ARM.__AT_" #x)))
#define DECL_ALIGN(type) __aligned(__alignof(type)) type

#define __in_section(a, b, c) \
    __attribute__((section("." STRINGIFY(a) "." STRINGIFY(b) "." STRINGIFY(c))))
/*
 * Convenience helper combining __in_section() and Z_DECL_ALIGN().
 * The section name is the struct type prepended with an underscore.
 * The subsection is "static" and the subsubsection is the variable name.
 *
 * In the linker script, create output sections for these using
 * Z_ITERABLE_SECTION_ROM or Z_ITERABLE_SECTION_RAM.
 */
#define STRUCT_SECTION_ITERABLE(struct_type, name) \
    DECL_ALIGN(struct struct_type)                 \
    name                                           \
        __in_section(_##struct_type, static, name) __USED__

/* Special variant of Z_STRUCT_SECTION_ITERABLE, for placing alternate
 * data types within the iterable section of a specific data type. The
 * data type sizes and semantics must be equivalent!
 */
#define STRUCT_SECTION_ITERABLE_ALTERNATE(out_type, struct_type, name) \
    DECL_ALIGN(struct struct_type)                                     \
    name                                                               \
        __in_section(_##out_type, static, name) __USED__

/*
 * Itterator for structure instances gathered by Z_STRUCT_SECTION_ITERABLE().
 * The linker must provide a _<struct_type>_list_start symbol and a
 * _<struct_type>_list_end symbol to mark the start and the end of the
 * list of struct objects to iterate over.
 */
#define STRUCT_SECTION_FOREACH(struct_type, iterator)                \
    extern struct struct_type CONCAT(_##struct_type, _list_start)[]; \
    extern struct struct_type CONCAT(_##struct_type, _list_end)[];   \
    for (struct struct_type *iterator =                              \
             CONCAT(_##struct_type, _list_start);                    \
         ({ assert(iterator <= CONCAT(_##struct_type, _list_end), \
			 "unexpected list end location"); \
		iterator < CONCAT(_##struct_type, _list_end); });                                                      \
         iterator++)

/**
 * @brief Is @p x a power of two?
 * @param x value to check
 * @return true if @p x is a power of two, false otherwise
 */
static inline bool is_power_of_two(unsigned int x)
{
    return (x != 0U) && ((x & (x - 1U)) == 0U);
}

/**
 * @brief Arithmetic shift right
 * @param value value to shift
 * @param shift number of bits to shift
 * @return @p value shifted right by @p shift; opened bit positions are
 *         filled with the sign bit
 */
static inline int64_t arithmetic_shift_right(int64_t value, uint8_t shift)
{
    int64_t sign_ext;

    if (shift == 0U) {
        return value;
    }

    /* extract sign bit */
    sign_ext = (value >> 63) & 1;

    /* make all bits of sign_ext be the same as the value's sign bit */
    sign_ext = -sign_ext;

    /* shift value and fill opened bit positions with sign bit */
    return (value >> shift) | (sign_ext << (64 - shift));
}

/** 
 * \defgroup SORT_Private_Functions
 * \{
 */
#define BUBBLE_SORT(src)                     \
    for (i = 0; i < size - 1; i++) {         \
        for (j = 0; j < size - i - 1; j++) { \
            if ((src)[j] > (src)[j + 1]) {   \
                tmp = (src)[j];              \
                (src)[j] = (src)[j + 1];     \
                (src)[j + 1] = tmp;          \
            }                                \
        }                                    \
    }

#define SELECTION_SORT(src)              \
    for (i = 0; i < size - 1; i++) {     \
        k = i;                           \
        for (j = i + 1; j < size; j++) { \
            if ((src)[j] < (src)[k]) {   \
                k = j;                   \
            }                            \
        }                                \
        tmp = (src)[k];                  \
        (src)[k] = (src)[i];             \
        (src)[i] = tmp;                  \
    }

#define INSERTION_SORT(src)                                  \
    for (i = 1; i < size; i++) {                             \
        if ((src)[i] < (src)[i - 1]) {                       \
            tmp = (src)[i];                                  \
            for (j = i - 1; j >= 0 && (src)[j] > tmp; j--) { \
                (src)[j + 1] = (src)[j];                     \
            }                                                \
            (src)[j + 1] = tmp;                              \
        }                                                    \
    }

static void *memcpy_byte(void *dst, const void *src, uint32_t n)
{
    const uint8_t *p = src;
    uint8_t *q = dst;

    while (n--) {
        *q++ = *p++;
    }
    return dst;
}

static uint32_t *memcpy_word(uint32_t *dst, const uint32_t *src, uint32_t n)
{
    const uint32_t *p = src;
    uint32_t *q = dst;

    while (n--) {
        *q++ = *p++;
    }
    return dst;
}

__STATIC_INLINE__ void *memcpy_fast(void *pdst, const void *psrc, uint32_t n)
{
    uint32_t left, done, i = 0;
    uint8_t *dst = (uint8_t *)pdst;
    uint8_t *src = (uint8_t *)psrc;

    if (((uint32_t)dst & 0x3) == 0 && ((uint32_t)src & 0x3) == 0) {
        memcpy_word((uint32_t *)dst, (const uint32_t *)src, n >> 2);
        left = n % 4;
        done = n - left;
        while (i < left) {
            dst[done + i] = src[done + i];
            i++;
        }
    } else {
        memcpy_byte(dst, src, n);
    }
    return dst;
}

__STATIC_INLINE__ uint8_t *fifo2mem_copy(void *pdst, const void *psrc, uint32_t n)
{
    uint8_t *q = (uint8_t *)psrc;
    uint8_t *p = (uint8_t *)pdst;

    while (n--) {
        *p++ = *q;
    }
    return pdst;
}

__STATIC_INLINE__ uint8_t *mem2fifo_copy(void *pdst, const void *psrc, uint32_t n)
{
    uint8_t *p = (uint8_t *)pdst;
    uint8_t *q = (uint8_t *)psrc;

    while (n--) {
        *p = *q++;
    }
    return pdst;
}

__STATIC_INLINE__ uint32_t *memset_fast(uint32_t *dst, const uint32_t val, uint32_t n)
{
    uint32_t *q = dst;

    while (n--) {
        *q++ = val;
    }
    return dst;
}

//判断字符是不是10进制的数字
#define DECCHK(c) ((c) >= '0' && (c) <= '9')
//判断字符是不是16进制的数字
#define HEXCHK(c) (((c) >= '0' && (c) <= '9') || ((c) >= 'A' && (c) <= 'F') || ((c) >= 'a' && (c) <= 'f'))
//获取X中bit位从N到M的的数
#define GET_DATA_N_TO_M_BIT(X, N, M) ((X & (~(~(0u) << (M - N + 1))) << (N)) >> (N))

#define cast(t, exp)              ((t)(exp))
#define sq(x)                     ((x) * (x))
#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

//#define SET_BIT(value, bit)       (value |= (1 << bit))   //置位指定位
//#define CLR_BIT(value, bit)       (value &= ~(1 << bit))  //清零指定位
//#define GET_BIT(value, bit)       (value & (1 << bit))    //读取指定位
//#define CPL_BIT(value, bit)       (value ^= (1 << bit))   //取反指定位

#endif
