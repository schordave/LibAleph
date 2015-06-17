/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */

/*
 * Returns offset from index
 */
size_t a_char_offset(a_cstr str, size_t index)
{
    const char *s = str;
    size_t size = 0;
    
    assert(s != NULL && index < a_size(str));
    PASSTHROUGH_ON_FAIL(s != NULL, 0);
    
    while (*s && index > size)
        s = a_next_chr(s), ++size;
    return s - str;
}
