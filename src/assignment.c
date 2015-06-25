/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */

/*
 * Assignments
 */

a_str a_clear(a_str str) 
{
    struct a_header *h;
    assert(str != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL, NULL);
    
    h = a_header(str);
    h->size = 0;
    h->len = 0;
    str[0] = '\0';
    return str;
}

/**************************************************/
/**************************************************/
/**************************************************/

a_str a_set(a_str str, a_str newstr) 
{
    size_t size;
    assert(str != NULL && newstr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && newstr != NULL, NULL);
    
    if (str == newstr)
        return str;
    
    size = a_size(newstr);
    str = a_reserve(str, size);
    if (str)
        memcpy(a_header(str), a_header(newstr), sizeof (struct a_header) + size + 1);

    return str;
}
a_str a_set_cstr(a_str str, const char *newstr) 
{
    assert(str != NULL && newstr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && newstr != NULL, NULL);
    A_ASSERT_UTF8(newstr);
    return a_set_cstr_size(str, newstr, strlen(newstr));
}
a_str a_set_cstr_validate(a_str str, const char *newstr)
{
    assert("Function not implemented.");
    return NULL;
}
a_str a_set_cstr_size(a_str str, const char *newstr, size_t size) 
{
    assert(str != NULL && newstr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && newstr != NULL, NULL);
    A_ASSERT_UTF8(newstr);
    str = a_reserve(str, size);
    
    if (str)
    {
        struct a_header *h = a_header(str);
        memcpy(str, newstr, size);
        str[size] = '\0';
        h->len = a_len_cstr_max(str, size);
        h->size = size;
    }
    return str;
}