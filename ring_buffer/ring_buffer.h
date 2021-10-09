#ifndef _RING_BUFFER_H
#define _RING_BUFFER_H

#include "system.h"

#define ringbuff_malloc(size)   malloc(size)
#define ringbuff_free(block)    free(block)
#define ALIGN_DOWN(size, align) ((size) & ~((align)-1))

#define RINGBUFFER_ASSERT(val)

typedef void *(ringbuffer_copy_callback)(void *dst, const void *src, size_t size);
/* ring buffer */
struct ringbuffer {
    uint8_t *buffer_ptr;
    /* use the msb of the {read,write}_index as mirror bit. You can see this as
     * if the buffer adds a virtual mirror and the pointers point either to the
     * normal or to the mirrored buffer. If the write_index has the same value
     * with the read_index, but in a different mirror, the buffer is full.
     * While if the write_index and the read_index are the same and within the
     * same mirror, the buffer is empty. The ASCII art of the ringbuffer is:
     *
     *          mirror = 0                    mirror = 1
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     * | 0 | 1 | 2 | 3 | 4 | 5 | 6 ||| 0 | 1 | 2 | 3 | 4 | 5 | 6 | Full
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     *  read_idx-^                   write_idx-^
     *
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     * | 0 | 1 | 2 | 3 | 4 | 5 | 6 ||| 0 | 1 | 2 | 3 | 4 | 5 | 6 | Empty
     * +---+---+---+---+---+---+---+|+~~~+~~~+~~~+~~~+~~~+~~~+~~~+
     * read_idx-^ ^-write_idx
     *
     * The tradeoff is we could only use 32KiB of buffer for 16 bit of index.
     * But it should be enough for most of the cases.
     *
     * Ref: http://en.wikipedia.org/wiki/Circular_buffer#Mirroring */
    uint16_t read_mirror  : 1;
    uint16_t read_index   : 15;
    uint16_t write_mirror : 1;
    uint16_t write_index  : 15;
    /* as we use msb of index as mirror bit, the size should be signed and
     * could only be positive. */
    int16_t buffer_size;
};

enum ringbuffer_state {
    RINGBUFFER_EMPTY,
    RINGBUFFER_FULL,
    /* half full is neither full nor empty */
    RINGBUFFER_HALFFULL,
};

/**
 * kfifo for DeviceDriver
 *
 * Please note that the ring buffer implementation of RT-Thread
 * has no thread wait or resume feature.
 */
void ringbuffer_init(struct ringbuffer *rb, uint8_t *pool, int16_t size);
void ringbuffer_reset(struct ringbuffer *rb);
size_t ringbuffer_put(struct ringbuffer *rb, ringbuffer_copy_callback *copy, const uint8_t *ptr, uint16_t length);
size_t ringbuffer_put_force(struct ringbuffer *rb, const uint8_t *ptr, uint16_t length);
size_t ringbuffer_putchar(struct ringbuffer *rb, const uint8_t ch);
size_t ringbuffer_putchar_force(struct ringbuffer *rb, const uint8_t ch);
size_t ringbuffer_get(struct ringbuffer *rb, ringbuffer_copy_callback *copy, uint8_t *ptr, uint16_t length);
size_t ringbuffer_getchar(struct ringbuffer *rb, uint8_t *ch);
size_t ringbuffer_data_len(struct ringbuffer *rb);

struct ringbuffer *rt_ringbuffer_create(uint16_t length);
void ringbuffer_destroy(struct ringbuffer *rb);

static __inline enum ringbuffer_state ringbuffer_status(struct ringbuffer *rb)
{
    if (rb->read_index == rb->write_index) {
        if (rb->read_mirror == rb->write_mirror)
            return RINGBUFFER_EMPTY;
        else
            return RINGBUFFER_FULL;
    }
    return RINGBUFFER_HALFFULL;
}
static __inline uint16_t ringbuffer_get_size(struct ringbuffer *rb)
{
    RINGBUFFER_ASSERT(rb != NULL);
    return rb->buffer_size;
}

/** return the size of empty space in rb */
#define ringbuffer_space_len(rb) ((rb)->buffer_size - ringbuffer_data_len(rb))

#endif