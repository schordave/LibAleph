/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */
a_str a_del(a_str str, size_t start, size_t length)
{
    size_t s, e;
    assert(str != NULL);
    assert(start < a_len(str));
    assert(length+start <= a_len(str));
    PASSTHROUGH_ON_FAIL(str != NULL, NULL);
    
    s = a_internal_index_to_offset(str, start);
    e = a_internal_index_to_offset(str+s, length);
    return a_del_offset(str, s, e);
}
a_str a_del_offset(a_str str, size_t start, size_t length)
{
    struct a_header *h;
    assert(str != NULL);
    assert(start < a_len(str));
    assert(length+start <= a_len(str));
    PASSTHROUGH_ON_FAIL(str != NULL, NULL);
    
    h = a_header(str);
    h->size -= length;
    memmove(str + start, str + start + length, h->size - start);
    str[h->size] = '\0';
    h->len = a_len_cstr_max(str, h->size);
    return str;
}