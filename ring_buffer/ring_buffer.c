#include "ring_buffer.h"

void ringbuffer_init(struct ringbuffer *rb,
                     uint8_t *pool,
                     int16_t size)
{
    RINGBUFFER_ASSERT(rb != NULL);
    RINGBUFFER_ASSERT(size > 0);

    /* initialize read and write index */
    rb->read_mirror = rb->read_index = 0;
    rb->write_mirror = rb->write_index = 0;

    /* set buffer pool and size */
    rb->buffer_ptr = pool;
    rb->buffer_size = ALIGN_DOWN(size, 4);
}

/**
 * put a block of data into ring buffer
 */
size_t ringbuffer_put(struct ringbuffer *rb, ringbuffer_copy_callback *copy, const uint8_t *ptr, uint16_t length)
{
    uint16_t size;

    RINGBUFFER_ASSERT(rb != NULL);

    /* whether has enough space */
    size = ringbuffer_space_len(rb);

    /* no space */
    if (size == 0)
        return 0;

    /* drop some data */
    if (size < length)
        length = size;

    if (rb->buffer_size - rb->write_index > length) {
        /* read_index - write_index = empty space */
        copy(&rb->buffer_ptr[rb->write_index], ptr, length);
        /* this should not cause overflow because there is enough space for
         * length of data in current mirror */
        rb->write_index += length;
        return length;
    }

    copy(&rb->buffer_ptr[rb->write_index],
         &ptr[0],
         rb->buffer_size - rb->write_index);
    copy(&rb->buffer_ptr[0],
         &ptr[rb->buffer_size - rb->write_index],
         length - (rb->buffer_size - rb->write_index));

    /* we are going into the other side of the mirror */
    rb->write_mirror = ~rb->write_mirror;
    rb->write_index = length - (rb->buffer_size - rb->write_index);

    return length;
}

/**
 * put a block of data into ring buffer
 *
 * When the buffer is full, it will discard the old data.
 */
size_t ringbuffer_put_force(struct ringbuffer *rb,
                            const uint8_t *ptr,
                            uint16_t length)
{
    uint16_t space_length;

    RINGBUFFER_ASSERT(rb != NULL);

    space_length = ringbuffer_space_len(rb);

    if (length > rb->buffer_size) {
        ptr = &ptr[length - rb->buffer_size];
        length = rb->buffer_size;
    }

    if (rb->buffer_size - rb->write_index > length) {
        /* read_index - write_index = empty space */
        memcpy(&rb->buffer_ptr[rb->write_index], ptr, length);
        /* this should not cause overflow because there is enough space for
         * length of data in current mirror */
        rb->write_index += length;

        if (length > space_length)
            rb->read_index = rb->write_index;

        return length;
    }

    memcpy(&rb->buffer_ptr[rb->write_index],
           &ptr[0],
           rb->buffer_size - rb->write_index);
    memcpy(&rb->buffer_ptr[0],
           &ptr[rb->buffer_size - rb->write_index],
           length - (rb->buffer_size - rb->write_index));

    /* we are going into the other side of the mirror */
    rb->write_mirror = ~rb->write_mirror;
    rb->write_index = length - (rb->buffer_size - rb->write_index);

    if (length > space_length) {
        rb->read_mirror = ~rb->read_mirror;
        rb->read_index = rb->write_index;
    }

    return length;
}

/**
 *  get data from ring buffer
 */
size_t ringbuffer_get(struct ringbuffer *rb, ringbuffer_copy_callback *copy, uint8_t *ptr, uint16_t length)
{
    size_t size;

    RINGBUFFER_ASSERT(rb != NULL);

    /* whether has enough data  */
    size = ringbuffer_data_len(rb);

    /* no data */
    if (size == 0)
        return 0;

    /* less data */
    if (size < length)
        length = size;

    if (rb->buffer_size - rb->read_index > length) {
        /* copy all of data */
        copy(ptr, &rb->buffer_ptr[rb->read_index], length);
        /* this should not cause overflow because there is enough space for
         * length of data in current mirror */
        rb->read_index += length;
        return length;
    }

    copy(&ptr[0],
         &rb->buffer_ptr[rb->read_index],
         rb->buffer_size - rb->read_index);
    copy(&ptr[rb->buffer_size - rb->read_index],
         &rb->buffer_ptr[0],
         length - (rb->buffer_size - rb->read_index));

    /* we are going into the other side of the mirror */
    rb->read_mirror = ~rb->read_mirror;
    rb->read_index = length - (rb->buffer_size - rb->read_index);

    return length;
}

/**
 * put a character into ring buffer
 */
size_t ringbuffer_putchar(struct ringbuffer *rb, const uint8_t ch)
{
    RINGBUFFER_ASSERT(rb != NULL);

    /* whether has enough space */
    if (!ringbuffer_space_len(rb))
        return 0;

    rb->buffer_ptr[rb->write_index] = ch;

    /* flip mirror */
    if (rb->write_index == rb->buffer_size - 1) {
        rb->write_mirror = ~rb->write_mirror;
        rb->write_index = 0;
    } else {
        rb->write_index++;
    }

    return 1;
}

/**
 * put a character into ring buffer
 *
 * When the buffer is full, it will discard one old data.
 */
size_t ringbuffer_putchar_force(struct ringbuffer *rb, const uint8_t ch)
{
    enum ringbuffer_state old_state;

    RINGBUFFER_ASSERT(rb != NULL);

    old_state = ringbuffer_status(rb);

    rb->buffer_ptr[rb->write_index] = ch;

    /* flip mirror */
    if (rb->write_index == rb->buffer_size - 1) {
        rb->write_mirror = ~rb->write_mirror;
        rb->write_index = 0;
        if (old_state == RINGBUFFER_FULL) {
            rb->read_mirror = ~rb->read_mirror;
            rb->read_index = rb->write_index;
        }
    } else {
        rb->write_index++;
        if (old_state == RINGBUFFER_FULL)
            rb->read_index = rb->write_index;
    }

    return 1;
}

/**
 * get a character from a ringbuffer
 */
size_t ringbuffer_getchar(struct ringbuffer *rb, uint8_t *ch)
{
    RINGBUFFER_ASSERT(rb != NULL);

    /* ringbuffer is empty */
    if (!ringbuffer_data_len(rb))
        return 0;

    /* put character */
    *ch = rb->buffer_ptr[rb->read_index];

    if (rb->read_index == rb->buffer_size - 1) {
        rb->read_mirror = ~rb->read_mirror;
        rb->read_index = 0;
    } else {
        rb->read_index++;
    }

    return 1;
}

/** 
 * get the size of data in rb 
 */
size_t ringbuffer_data_len(struct ringbuffer *rb)
{
    switch (ringbuffer_status(rb)) {
        case RINGBUFFER_EMPTY:
            return 0;
        case RINGBUFFER_FULL:
            return rb->buffer_size;
        case RINGBUFFER_HALFFULL:
        default:
            if (rb->write_index > rb->read_index)
                return rb->write_index - rb->read_index;
            else
                return rb->buffer_size - (rb->read_index - rb->write_index);
    };
}

/** 
 * empty the rb 
 */
void ringbuffer_reset(struct ringbuffer *rb)
{
    RINGBUFFER_ASSERT(rb != NULL);

    rb->read_mirror = 0;
    rb->read_index = 0;
    rb->write_mirror = 0;
    rb->write_index = 0;
}

struct ringbuffer *ringbuffer_create(uint16_t size)
{
    struct ringbuffer *rb;
    uint8_t *pool;

    RINGBUFFER_ASSERT(size > 0);

    size = ALIGN_DOWN(size, 4);

    rb = ringbuff_malloc(sizeof(struct ringbuffer));
    if (rb == NULL)
        goto exit;

    pool = ringbuff_malloc(size);
    if (pool == NULL) {
        ringbuff_free(rb);
        rb = NULL;
        goto exit;
    }
    ringbuffer_init(rb, pool, size);

exit:
    return rb;
}

void ringbuffer_destroy(struct ringbuffer *rb)
{
    RINGBUFFER_ASSERT(rb != NULL);

    ringbuff_free(rb->buffer_ptr);
    ringbuff_free(rb);
}
