int a_icmp(a_cstr str1, a_cstr str2)
{
    return a_icmp_cstr_cstr(str1, str2);
}
int a_icmp_cstr(a_cstr str1, const char *str2)
{
    return a_icmp_cstr_cstr(str1, str2);
}
int a_icmp_cstr_cstr(const char *str1, const char *str2)
{
    size_t index_a, index_b;
    a_cp buff_a[A_MAX_CASEFOLD_SIZE+1];/*  */
    a_cp buff_b[A_MAX_CASEFOLD_SIZE+1];
    
    index_a = index_b = 0;
    buff_a[0] = buff_b[0] = 0;
    for (;;)
    {
        /* if the buffer is empty, grab the next codepoint and casefold it */
        if (!buff_a[index_a])
            a_to_fold_cp_cp(a_next_cp(&str1), buff_a), index_a = 0;
        if (!buff_b[index_b])
            a_to_fold_cp_cp(a_next_cp(&str2), buff_b), index_b = 0;
        
        /* exit point - if one of the strings NULL terminated */
        if (!buff_a[index_a] || !buff_b[index_b])
            return (buff_a[index_a] == buff_b[index_b]) ? 0 : -1;
        
        /* compare the buffers until one of them is empty
         * jump to the start and re-fill the buffer */
        while (buff_a[index_a] && buff_b[index_b])
        {
            if (buff_a[index_a] != buff_b[index_b])
                return -1;
            index_a++, index_b++;
        }
    }
    
    return -1;
}
int a_icmp_simple(a_cstr str1, a_cstr str2)
{
    return a_icmp_simple_cstr_cstr(str1, str2);
}
int a_icmp_simple_cstr(a_cstr str1, const char *str2)
{
    return a_icmp_simple_cstr_cstr(str1, str2);
}
int a_icmp_simple_cstr_cstr(const char *str1, const char *str2)
{
    register a_cp a, b;
    
    while ((a = a_to_fold_simple_chr_cp(a_next_cp(&str1))) 
            == (b = a_to_fold_simple_chr_cp(a_next_cp(&str2))))
    {
        if (a == 0)
            return 0;
    }
    return -1;
}
int a_icmp_min(a_cstr str1, a_cstr str2)
{
    return a_icmp_min_cstr_cstr(str1, str2);
}
int a_icmp_min_cstr(a_cstr str1, const char *str2)
{
    return a_icmp_min_cstr_cstr(str1, str2);
}
int a_icmp_min_cstr_cstr(const char *str1, const char *str2)
{
    size_t index_a, index_b;
    a_cp buff_a[A_MAX_CASEFOLD_SIZE+1];/*  */
    a_cp buff_b[A_MAX_CASEFOLD_SIZE+1];
    
    index_a = index_b = 0;
    buff_a[0] = buff_b[0] = 0;
    for (;;)
    {
        /* if the buffer is empty, grab the next codepoint and casefold it */
        if (!buff_a[index_a])
            a_to_fold_cp_cp(a_next_cp(&str1), buff_a), index_a = 0;
        if (!buff_b[index_b])
            a_to_fold_cp_cp(a_next_cp(&str2), buff_b), index_b = 0;
        
        /* exit point - if one of the strings NULL terminated */
        if (!buff_a[index_a] || !buff_b[index_b])
            return !buff_b[index_b] ? 0 : -1; /* equal if str2 reached its end */
        
        /* compare the buffers until one of them is empty
         * jump to the start and re-fill the buffer */
        while (buff_a[index_a] && buff_b[index_b])
        {
            if (buff_a[index_a] != buff_b[index_b])
                return -1;
            index_a++, index_b++;
        }
    }
    
    return -1;
}