a_str a_cat_len(a_str s, const char *s2, size_t l) 
{
    struct header *h;
    assert(s != NULL && s2 != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL && s2 != NULL, NULL);
    
    s = a_ensure(s, l);
    if (!s)
        return NULL;
    h = head(s);
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
    struct header *h;
    size_t length2;
    assert(s != NULL && s2 != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL && s2 != NULL, NULL);
    
    length2 = a_len(s2);
    s = a_ensure(s, length2);
    h = head(s);
    if (!s)
        return NULL;
    memcpy(s+h->size, s2, length2);
    h->len += a_len(s2);
    h->size += length2;
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