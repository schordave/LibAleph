/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */

int a_startswith(a_cstr str, a_cstr substr)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, 0);
    A_ASSERT_UTF8(substr);
    return (memcmp(str, substr, a_size(substr)) == 0);
}
int a_startswith_cstr(a_cstr str, const char *substr)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, 0);
    A_ASSERT_UTF8(substr);
    return (memcmp(str, substr, strlen(substr)) == 0);
}
int a_istartswith(a_cstr str, a_cstr substr)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, 0);
    return (a_icmp_min_cstr_cstr(str, substr) == 0);
}
int a_istartswith_cstr(a_cstr str, const char *substr)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, 0);
    A_ASSERT_UTF8(substr);
    return (a_icmp_min_cstr_cstr(str, substr) == 0);
}

/**************************************************************/
/**************************************************************/

static int a_endswith_internal(const char *str, const char *substr, size_t size_a, size_t size_b)
{
    if (size_b > size_a)
        return 0;
    return (memcmp(str + size_a - size_b, substr, size_b) == 0);
}
int a_endswith(a_cstr str, a_str substr)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, 0);
    return a_endswith_internal(str, substr, a_size(str), a_size(substr));
}
int a_endswith_cstr(a_cstr str, const char *substr)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, 0);
    return a_endswith_internal(str, substr, a_size(str), strlen(substr));
}
int a_endswith_cstr_cstr(const char *str, const char *substr)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, 0);
    return a_endswith_internal(str, substr, strlen(str), strlen(substr));
}
int a_iendswith(a_cstr str, a_str substr)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, 0);
    return (a_ircmp_cstr_cstr(str, substr, a_size(str), a_size(substr)) == 0);
}
int a_iendswith_cstr(a_cstr str, const char *substr)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, 0);
    return (a_ircmp_cstr_cstr(str, substr, a_size(str), strlen(substr)) == 0);
}
int a_iendswith_cstr_cstr(const char *str, const char *substr)
{
    assert(str != NULL && substr != NULL);
    PASSTHROUGH_ON_FAIL(str != NULL && substr != NULL, 0);
    return (a_ircmp_cstr_cstr(str, substr, strlen(str), strlen(substr)) == 0);
}