/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */
a_str a_cat_len(a_str s, const char *s2, size_t l) 
{
    struct a_header *h;
    assert(s != NULL && s2 != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL && s2 != NULL, NULL);
    
    s = a_ensure(s, l);
    if (!s)
        return NULL;
    h = a_header(s);
    memcpy(s+h->size, s2, l);
    h->size += l;
    s[h->size] = '\0';
    h->len += a_len_cstr_max(s+h->size-l, l);
    return s;
}

a_str a_cat(a_str s, const char *s2) 
{
    assert(s != NULL && s2 != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL && s2 != NULL, NULL);
    return a_cat_len(s, s2, strlen(s2));
}

a_str a_cat_str(a_str s, a_str s2) 
{
    struct a_header *h;
    size_t s2_size;
    assert(s != NULL && s2 != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL && s2 != NULL, NULL);
    
    s2_size = a_size(s2);
    s = a_ensure(s, s2_size);
    if (!s)
        return NULL;
    h = a_header(s);
    memcpy(s+h->size, s2, s2_size);
    h->len += a_len(s2);
    h->size += s2_size;
    s[h->size] = '\0';
    return s;
}

a_str a_cat_cp(a_str s, int cp) 
{
    char b[7];
    int size;
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, NULL);
    
    a_to_utf8_size(cp, b, &size);
    return a_cat_len(s, b, size);
}

a_str a_cat_chr(a_str s, const char *chr)
{
    assert(s != NULL && chr != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL && chr != NULL, NULL);
    return a_cat_len(s, chr, a_size_chr_cstr(chr));
}