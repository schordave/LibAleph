/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */
a_str a_reverse(a_str str)
{
    char *s, *e;
    assert(str != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL, NULL);
    
    for (s = str; *s; )
    {
        size_t size = a_size_chr_cstr(s);
        char tmp;
        
        /* [0][1][2][3] */
        /* [3][2][1][0] */
        switch (size)
        {
            case 4: tmp = s[3]; s[3] = s[0]; s[0] = tmp;
                    tmp = s[2]; s[2] = s[1]; s[1] = tmp; break;
            case 3: tmp = s[2]; s[2] = s[0]; s[0] = tmp; break;
            case 2: tmp = s[1]; s[1] = s[0]; s[0] = tmp; break;
            case 1:
            default:
                break;
        }
        
        s += size;
    }
    
    for (s = str, e = str + a_size(str) - 1; s < e; ++s, --e)
    {
        char tmp = *e;
        *e = *s;
        *s = tmp;
    }
    
    return str;
}
a_str a_reverse_new(a_cstr str)
{
    a_str newstr;
    assert(str != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL, NULL);
    
    if ((newstr = a_new(NULL)))
        return a_reverse_str(str, newstr);
    return NULL;
}
a_str a_reverse_str(a_cstr str, a_str output)
{
    struct a_header *in_h, *out_h;
    size_t at;
    assert(str != NULL && output != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && output != NULL, NULL);
    A_ASSERT_UTF8(str);
    
    in_h = a_header(str);
    at = in_h->size;
    output = a_reserve(output, at);
    
    out_h = a_header(output);
    output[at] = '\0';
    out_h->len = in_h->len;
    out_h->size = in_h->size;
    while (*str)
    {
        char *t, cont = a_size_chr_cstr(str);
        
        at -= (size_t)cont;
        for (t = output+at; cont; cont--)
            *t++ = *str++;
    }
    return output;
}

a_str a_greverse_new(a_cstr str)
{
    a_str newstr;
    assert(str != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL, NULL);
    
    if ((newstr = a_new(NULL)))
        return a_greverse_str(str, newstr);
    return NULL;
}

a_str a_greverse_str(a_cstr str, a_str output)
{
    struct a_header *in_h, *out_h;
    size_t at;
    assert(str != NULL && output != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && output != NULL, NULL);
    A_ASSERT_UTF8(str);
    
    in_h = a_header(str);
    at = in_h->size;
    output = a_reserve(output, at);
    
    out_h = a_header(output);
    output[at] = '\0';
    out_h->len = in_h->len;
    out_h->size = in_h->size;
    while (*str)
    {
        const char *start, *end;
        char *t;
        size_t cont;
        
        start = str;
        end = a_gnext_cstr(&str);
        cont = end-start;
        at -= (size_t)cont;
        
        for (t = output+at; cont; cont--)
            *t++ = *start++;
    }
    return output;
}
