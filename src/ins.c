/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */

/*
 * insert string str2 into str at positin index'th.
 */
a_str a_ins(a_str str, a_cstr str2, size_t index)
{
    size_t size;
    struct a_header *h, *h2;
    assert(str != NULL && str2 != NULL);
    assert(index <= (a_size(str) + a_size(str2)));
    
    h2 = a_header(str2);
    size = h2->size;
    str = a_ensure(str, size);
    h = a_header(str);
    
    memmove(str+index+size, str+index, h->size - index + 1);
    memcpy(str+index, str2, size);
    
    h->size += size;
    h->len += h2->len;
    return str;
}
