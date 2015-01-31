/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */
a_str a_trim_left_cstr(a_str str, const char *chrs)
{
    size_t count = 0;
    const char *s, *t;
    assert(str != NULL && chrs != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && chrs != NULL, NULL);
    A_ASSERT_UTF8(chrs);
    
    for (s = str; *s; ++count)
    {
        int c = a_peek(s), match;
        
        for (t = chrs, match = 0; *t && !match;)
            match = (c == a_next_cp(&t));
        
        if (!match)
            break;
        
        s += a_size_chr_cstr(s);
    }
    
    if (count)
    {
        struct a_header *h = a_header(str);
        h->size -= (s-str);
        h->len -= count;
        memmove(str, s, h->size + 1); /* copy with the null terminator */
    }

    return str;
}
a_str a_trim_right_cstr(a_str str, const char *chrs)
{
    size_t count;
    const char *s, *t;
    assert(str != NULL && chrs != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && chrs != NULL, NULL);
    
    for (count = 0, s = str + a_size(str); s >= str; ++count)
    {
        int c = a_prev_cp(&s), match;
        
        for (t = chrs, match = 0; *t && !match;)
            match = (c == a_next_cp(&t));
        
        if (!match)
        {
            s += a_size_chr_cstr(s); /* go forward once */
            break;
        }
    }
    
    if (count)
    {
        struct a_header *h = a_header(str);
        h->size = (s - str);
        h->len -= count;
        str[h->size] = '\0';
    }
    
    return str;
}
a_str a_trim_cstr(a_str str, const char *chrs)
{
    assert(str != NULL && chrs != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && chrs != NULL, NULL);
    return a_trim_left_cstr(a_trim_right_cstr(str, chrs), chrs);
}

a_str a_trim_left(a_str str)
{
    assert(str != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL, NULL);
    return a_trim_left_cstr(str, " ");
}
a_str a_trim_right(a_str str)
{
    assert(str != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL, NULL);
    return a_trim_right_cstr(str, " ");
}
a_str a_trim(a_str str)
{
    assert(str != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL, NULL);
    return a_trim_cstr(str, " ");
}