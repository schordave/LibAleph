/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */
int a_startswith(a_cstr str, a_cstr substr)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, NULL);
    A_ASSERT_UTF8(substr);
    return (strncmp(str, substr, a_size(substr)) == 0);
}
int a_startswith_cstr(a_cstr str, const char *substr)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, NULL);
    A_ASSERT_UTF8(substr);
    return (strncmp(str, substr, strlen(substr)) == 0);
}
int a_istartswith(a_cstr str, a_cstr substr)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, NULL);
    return (a_icmp_min_cstr_cstr(str, str2) == 0);
}
int a_istartswith_cstr(a_cstr str, const char *substr)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, NULL);
    A_ASSERT_UTF8(substr);
    return (a_icmp_min_cstr_cstr(str, str2) == 0);
    
}
