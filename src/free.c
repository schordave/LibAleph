void a_free(a_str s)
{
    free(head(s));
} 

void a_free_vec(a_str *sv)
{
    a_str *str = sv;
    for (;*str; ++str)
        a_free(*str); 
    free(sv);
} 
