/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */
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
    
    va_start(ap, str);
    while ((s = va_arg(ap, a_str)))
        a_free(s);
    va_end(ap);
}