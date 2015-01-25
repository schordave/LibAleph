/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */
size_t a_len_cstr(const char *s)
{
    size_t size = 0;
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, 0);
    
    while (*s)
        s = a_next_chr(s), ++size;
    return size;
}
size_t a_len_cstr_max(const char *s, size_t max)
{
    size_t size = 0;
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, 0);
    
    while (*s && max)
        s = a_next_chr(s), ++size, --max;
    return size;
}
size_t a_len(a_cstr s)
{
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, 0);
    return a_header(s)->len;
}
size_t a_size(a_cstr s)
{
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, 0);
    return a_header(s)->size;
}