/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
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