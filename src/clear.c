a_str a_clear(a_str str) 
{
    struct header *h;
    assert(str != NULL);
    
    h = head(str);
    h->size = 0;
    h->len = 0;
    str[0] = '\0';
    return str;
}