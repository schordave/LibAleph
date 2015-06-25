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