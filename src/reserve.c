/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */

/*
 * Reserves enough buffer space to hold l bytes.
 * (this function adds an implicit +1 to the size to account for a NULL terminator)
 */
a_str a_reserve(a_str s, size_t l)
{
    struct a_header *h;
    size_t size;
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, NULL);
    
    h = a_header(s);
    size = h->mem;
 
    if (size <= l)
    {
        ++l; /* take the null terminator into account */
        while (size < l)
            size <<= 1;
        
        if (h->mem < size)
        {
            struct a_header *newh = A_REALLOC(h, sizeof (struct a_header) + size);
            if (newh)
            {
                newh->mem = size;
                return a_buff(newh);
            }
            else
            {
                free(h);
                return NULL;
            }
        }
    }
    
    return s;
}

/*
 * Ensures the string has enough free buffer space to hold l more bytes.
 */
a_str a_ensure(a_str s, size_t l)
{
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, NULL);
    return a_reserve(s, a_size(s) + l);
}