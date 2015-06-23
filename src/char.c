/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */

/*
 * Returns offset from index
 */
size_t a_char_offset(a_cstr str, size_t index)
{
    return a_char_offset_cstr(str, index);
}
size_t a_char_offset_cstr(const char *str, size_t index)
{
    assert(str != NULL && index <= a_len(str));
    PASSTHROUGH_ON_FAIL(str != NULL, 0);

    return a_internal_index_to_offset(str, index);
}

size_t a_char_index(a_cstr str, size_t offset)
{
    return a_char_index_cstr(str, offset);
}
size_t a_char_index_cstr(const char *str, size_t offset)
{
    size_t index;
    const char *start = str;
    
    for (index = 0; *str && (str-start) < offset; ++index)
        a_next_cstr(&str);
    
    return index;
}


/*
 * Returns offset from index from reverse
 */
size_t a_char_offset_rev(a_cstr str, size_t index)
{
    assert(str != NULL && index <= a_len(str));
    PASSTHROUGH_ON_FAIL(str != NULL, 0);
    
    return a_internal_index_to_offset_rev(str, index);
}
