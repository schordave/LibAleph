/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */
char *a_end(a_str str)
{
    assert(str != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL, NULL);
    return str + a_size(str);
}

char *a_end_cstr(const char *str)
{
    assert(str != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL, NULL);
    return (char*)str + strlen(str);
}

static char *a_internal_to_prev(const char **s);
char *a_last(a_str str)
{
    const char *s = str + a_size(str);
    assert(str != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL, NULL);
    return a_internal_to_prev(&s);
}
char *a_last_cstr(const char *str)
{
    const char *s = str + strlen(str);
    assert(str != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL, NULL);
    return a_internal_to_prev(&s);
}