/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */

static char    *a_internal_cp_to_char(a_cp cp, char *buffer);
static a_cp     a_internal_char_to_cp(const char *s);
/*static a_cp   a_internal_to_next(const char **s);*/
static a_cp     a_internal_to_next_cp(const char **s);
static char    *a_internal_to_prev(const char **s);
static a_cp     a_internal_to_prev_cp(const char **s);
static size_t   a_internal_index_to_offset(const char *s, size_t index);
static size_t   a_internal_gindex_to_offset(const char *s, size_t index);


static size_t a_internal_index_to_offset(const char *s, size_t index)
{
    const char *start;
    
    for (start = s; *s && index; --index)
        a_next_cstr(&s);
    
    return (s-start);
}
static size_t a_internal_gindex_to_offset(const char *s, size_t index)
{
    const char *start;
    
    for (start = s; *s && index; --index)
        a_gnext_cstr(&s);
    
    return (s-start);
}

static size_t a_internal_index_to_offset_rev(const char *str, size_t index)
{
    const char *s = a_end_cstr(str);
    
    while (s > str && index--)
        a_prev_cstr(&s);
    
    return s - str;
}