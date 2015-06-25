/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */

/*
 * Creation and Destruction
 */

static a_str a_new_chr_internal(const char *chr, size_t size, size_t repeat);

a_str a_new(const char *s)
{
    A_ASSERT_UTF8(s ? s : "");
    return a_new_size(s ? s : "", s ? strlen(s) : 0);
}
a_str a_new_cp(a_cp cp, size_t repeat)
{
    char b[7];
    int size;
    assert(cp != 0);
    A_ASSERT_CODEPOINT(cp);
    
    a_to_utf8_size(cp, b, &size);
    return a_new_chr_internal(b, size, repeat);
}
a_str a_new_chr(char *chr, size_t repeat)
{
    assert(*chr != 0);
    return a_new_chr_internal(chr, a_size_chr_cstr(chr), repeat);
}
a_str a_new_size(const char *str, size_t size)
{
    a_str astr;
    struct a_header *h;
    assert(str != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL, NULL);
    
    if ((astr = a_new_mem_raw(size+1)))
    {
        memcpy(astr, str, size);
        astr[size] = '\0';
        h = a_header(astr);
        h->len = a_len_cstr(astr);
        h->size = size;
    }
    return astr;
}
a_str a_new_validate(const char *str)
{
    assert("Function not implemented.");
    return NULL;
}
/* creates a new Aleph string with enough space to hold l bytes. */
a_str a_new_mem(size_t l)
{
    a_str s;
    struct a_header *h;
    
    if ((s = a_new_mem_raw(l)))
    {
        h = a_header(s);
        *s = '\0';
        h->len = 0;
        h->size = 0;
    }
    return s;
}
a_str a_new_mem_raw(size_t l)
{
    struct a_header *h;
    size_t size;
    
    for (++l, size = A_MIN_STR_SIZE; size < l;)
        size <<= 1;
    
    if (!(h = A_MALLOC(sizeof *h + size))) /* TODO l+1 overflow situation */
        return NULL;
    
    h->mem = size;
    return a_buff(h);
}
a_str a_new_dup(a_cstr s)
{
    a_str dup;
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, NULL);
    
    if ((dup = a_new_mem_raw(a_size(s) + 1)))
        memcpy(a_header(dup), a_header(s), sizeof (struct a_header) + a_size(s) + 1);
    return dup;
}
a_str a_new_long(long val)
{
    a_str str;
    
    if ((str = a_new_mem(A_INT_DIGITS)))
        str = a_cat_long(str, val);
    return str;
}
a_str a_new_ulong(unsigned long val)
{
    a_str str;
    
    if ((str = a_new_mem(A_INT_DIGITS)))
        str = a_cat_ulong(str, val);
    return str;
}
a_str a_new_normalize(a_cstr str, int mode)
{
    assert("Function not implemented.");
    return NULL;
}
static a_str a_new_chr_internal(const char *chr, size_t size, size_t repeat)
{
    size_t l;
    a_str str;
    struct a_header *h;
    
    l = size * repeat;
    if ((str = a_new_mem_raw(l + 1)))
    {
        size_t i;
        
        for (i = 0; i < l; i += size)
            memcpy(str + i, chr, size);
        str[l] = '\0';
        
        h = a_header(str);
        h->len = repeat;
        h->size = l;
    }
    return str;
}

/**************************************************/
/**************************************************/
/**************************************************/

void a_free(a_str s)
{
    free(a_header(s));
}
void a_free_vec(a_str *sv)
{
    a_str *str;
    PASSTHROUGH_ON_FAIL(sv != NULL, ;);
    for (str = sv;*str; ++str)
        a_free(*str); 
    free(sv);
}
void a_free_n(a_str str, ...)
{
    va_list ap;
    a_str s;
    
    a_free(str);
    va_start(ap, str);
    while ((s = va_arg(ap, a_str)))
        a_free(s);
    va_end(ap);
}
