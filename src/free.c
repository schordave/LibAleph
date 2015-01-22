void a_free(a_str s)
{
    free(a_header(s));
} 

void a_free_vec(a_str *sv)
{
    a_str *str;
    PASSTHROUGH_ON_FAIL(sv != NULL,3)
    for (str = sv;*str; ++str)
        a_free(*str); 
    free(sv);
} 
