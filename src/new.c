a_str a_new_size_raw(size_t l)
{
    struct header *h;
    size_t size;
    
    for (++l, size = A_MIN_STR_SIZE; size < l;)
        size <<= 1;
    
    if (!(h = A_MALLOC(sizeof *h + size))) /* TODO l+1 overflow situation */
        return NULL;
    
    h->mem = size;
    return buff(h);
}

/* creates a new Aleph string with enough space to hold l bytes. */
a_str a_new_size(size_t l)
{
    a_str s;
    struct header *h;
    
    if ((s = a_new_size_raw(l)))
    {
        h = head(s);
        *s = '\0';
        h->len = 0;
        h->size = 0;
    }
    return s;
}


a_str a_new(const char *s)
{
    A_ASSERT_UTF8(s ? s : "");
    return a_new_len(s ? s : "", s ? strlen(s) : 0);
}

a_str a_new_len(const char *s, size_t l)
{
    a_str str;
    struct header *h;
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, NULL);
    
    if ((str = a_new_size_raw(l)))
    {
        h = head(str);
        memcpy(str, s, l);
        str[l] = '\0';
        h->len = a_len_cstr(s);
        h->size = l;
    }
    return str;
}

a_str a_new_dup(a_cstr s)
{
    a_str dup;
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, NULL);
    
    if ((dup = a_new_size_raw(a_size(s))))
        memcpy(dup, s, sizeof (struct header) + a_size(s));
    return dup;
}