/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */
char *a_prev(const char **s)
{
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, NULL);
    return a_internal_critical_to_prev(s);
}

a_cp a_prev_cp(char **s)
{
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, 0);
    return a_prev_cp_cstr((const char **)s);
}
a_cp a_prev_cp_cstr(const char **s)
{
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, 0);
    return a_internal_critical_to_prev_cp(s);
}