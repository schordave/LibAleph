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

a_str a_cat_cstr(a_str s, const char *s2) 
{
    assert(s != NULL && s2 != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL && s2 != NULL, NULL);
    return a_cat_len(s, s2, strlen(s2));
}
a_str a_cat(a_str s, a_str s2)
{
    assert(s != NULL && s2 != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL && s2 != NULL, NULL);
    return a_cat_len(s, s2, a_size(s2));
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

a_str a_cat_cp(a_str s, a_cp cp) 
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



/* number of digits in an integer */ 
static int a_digits_count(const long n)
{
    if (n < 100000)
    {
        if (n < 10) return 1;
        
        if (n < 1000)
        {
            if (n < 100) return 2;
        /*  if (n < 1000)*/ return 3;
        }
        
        if (n < 10000) return 4;
       /*if (n < 100000)*/ return 5;
    }
    else
    {
        if (n < 10000000)
        {
            if (n < 1000000) return 6;
         /* if (n < 10000000) */ return 7;
        }
        if (n < 100000000) return 8;
        
        if (n < 10000000000)
        {
            if (n < 1000000000) return 9;
            return 10;
        }
        
        if (n < 1000000000000)
        {
            if (n < 100000000000) return 11;
            return 12;
        }
    }
    
    return 1;
}

static const char a_digits_1sts[100] =
    "00000000001111111111"
    "22222222223333333333"
    "44444444445555555555"
    "66666666667777777777"
    "88888888889999999999"
;
static const char a_digits_2nds[100] =
    "01234567890123456789"
    "01234567890123456789"
    "01234567890123456789"
    "01234567890123456789"
    "01234567890123456789"
;

a_str a_cat_uint(a_str s, unsigned long val)
{
    int const length = a_digits_count(val);
    int pos = length - 1;
    
    struct a_header *h;
    char *buf;
    
    h = a_header(s);
    buf = s + h->size;
    
    s = a_ensure(s, length);
    if (!s)
        return NULL;
    
    while (val >= 100)
    {
        const int n = val % 100;  /* hopfuly it turns into an IDIVL */
        val /= 100;
        
        buf[pos] = a_digits_2nds[n];
        buf[pos-1] = a_digits_1sts[n];
        
        pos -= 2;
    }
    
    
    buf[pos] = a_digits_2nds[val];
    if (val > 9)
        buf[pos-1] = a_digits_1sts[val];
    
    buf[length] = 0;
    h->size += length;
    h->len += length;
    
    return s;
}

a_str a_cat_int(a_str s, long val)
{
    unsigned long uval = val;
    
    if(val < 0)
    {
        s = a_cat_chr(s, "-");
        uval = -uval; /* this avoid implemention-defined behavior */
    }
    
    return a_cat_uint(s, uval);
}