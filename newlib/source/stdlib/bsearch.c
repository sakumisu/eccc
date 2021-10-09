/*
 * Copyright (c) 2019 Balaji Kulkarni
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Generic implementation of Binary Search
 *
 * @param key	pointer to first element to search
 * @param array	pointer to item being searched for
 * @param count	number of elements
 * @param size	size of each element
 * @param cmp	pointer to comparison function
 *
 * @return	pointer to key if present in the array, or NULL otherwise
 */

void *bsearch(const void *key, const void *base, size_t nmemb,
              size_t size, int (*cmp)(const void *, const void *))
{
    while (nmemb) {
        size_t mididx = nmemb / 2;
        const void *midobj = (const unsigned char *)base +
                             mididx * size;
        int diff = cmp(key, midobj);

        if (diff == 0)
            return (void *)midobj;

        if (diff > 0) {
            base = (const unsigned char *)midobj + size;
            nmemb -= mididx + 1;
        } else
            nmemb = mididx;
    }

    return NULL;
}
