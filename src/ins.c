/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */

static a_str a_ins_internal(a_str str, const char * const instr,
                            const size_t offset, const size_t size, 
                            const size_t len)
{
    struct a_header *h;
    
    str = a_ensure(str, size);
    if (!str)
        return NULL;
    
    h = a_header(str);
    memmove(str+offset+size, str+offset, h->size - offset + 1);
    memcpy(str+offset, instr, size);
    h->size += size;
    h->len += len;
    
    return str;
}

/*
 * insert string str2 into str at positin index'th.
 */
a_str a_ins(a_str str, a_cstr str2, size_t index)
{
    struct a_header *h;
    assert(str != NULL && str2 != NULL);
    assert(a_size(str) >= index); /* only treats index as offset */
    
    h = a_header(str2);
    return a_ins_internal(str, str2, 
                a_internal_index_to_offset(str, index),
                h->size, h->len);
}
a_str a_ins_chr(a_str str, const char *chr, size_t index)
{
    assert(str != NULL && chr != NULL);
    assert(a_size(str) >= index); /* only treats index as offset */
    
    return a_ins_internal(str, chr, 
                a_internal_index_to_offset(str, index),
                a_size_chr_cstr(chr), 1);
}
a_str a_ins_cstr(a_str str, const char *str2, size_t index)
{
    assert(str != NULL && str2 != NULL);
    assert(a_size(str) >= index); /* only treats index as offset */
    
    return a_ins_internal(str, str2,
                a_internal_index_to_offset(str, index),
                strlen(str2), a_len_cstr(str2));
}
a_str a_ins_cp(a_str str, a_cp cp, size_t index)
{
    int s;
    char chr[A_MAX_CHAR];
    assert(str != NULL);
    A_ASSERT_CODEPOINT(cp);
    
    a_to_utf8_size(cp, chr, &s);
    return a_ins_internal(str, chr,
                a_internal_index_to_offset(str, index), s, 1);
}
a_str a_ins_offset(a_str str, a_cstr str2, size_t offset)
{
    struct a_header *h;
    assert(str != NULL && str2 != NULL);
    assert(a_size(str) >= offset);
    
    h = a_header(str2);
    return a_ins_internal(str, str2, offset, h->size, h->len);
}
a_str a_ins_offset_chr(a_str str, const char *chr, size_t offset)
{
    assert(str != NULL && chr != NULL);
    assert(a_size(str) >= offset);
    
    return a_ins_internal(str, chr, 
                offset, a_size_chr_cstr(chr), 1);
}
a_str a_ins_offset_cstr(a_str str, const char *str2, size_t offset)
{
    assert(str != NULL && str2 != NULL);
    assert(a_size(str) >= offset);
    
    return a_ins_internal(str, str2, 
                offset, strlen(str2), a_len_cstr(str2));
}
a_str a_ins_offset_cp(a_str str, a_cp cp, size_t offset)
{
    int s;
    char chr[A_MAX_CHAR];
    assert(str != NULL);
    A_ASSERT_CODEPOINT(cp);
    
    a_to_utf8_size(cp, chr, &s);
    return a_ins_internal(str, chr, offset, s, 1);
}
a_str a_gins(a_str str, a_cstr str2, size_t index)
{
    struct a_header *h;
    assert(str != NULL && str2 != NULL);
    assert(a_size(str) >= index); /* only treats index as offset */
    
    h = a_header(str2);
    return a_ins_internal(str, str2, 
                a_internal_gindex_to_offset(str, index),
                h->size, h->len);
}
a_str a_gins_chr(a_str str, const char *chr, size_t index)
{
    assert(str != NULL && chr != NULL);
    assert(a_size(str) >= index); /* only treats index as offset */
    
    return a_ins_internal(str, chr, 
                a_internal_gindex_to_offset(str, index),
                a_size_chr_cstr(chr), 1);
}
a_str a_gins_cstr(a_str str, const char *str2, size_t index)
{
    assert(str != NULL && str2 != NULL);
    assert(a_size(str) >= index); /* only treats index as offset */
    
    return a_ins_internal(str, str2,
                a_internal_gindex_to_offset(str, index),
                strlen(str2), a_len_cstr(str2));
}
a_str a_gins_cp(a_str str, a_cp cp, size_t index)
{
    int s;
    char chr[A_MAX_CHAR];
    assert(str != NULL);
    A_ASSERT_CODEPOINT(cp);
    
    a_to_utf8_size(cp, chr, &s);
    return a_ins_internal(str, chr,
                a_internal_gindex_to_offset(str, index), s, 1);
}