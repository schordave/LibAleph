/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */
static a_cp a_internal_char_to_cp(const char *s)
{
#if 1
    const unsigned char *p = (const unsigned char*)s;
    unsigned char c = *p;
    switch (a_next_char_size[c])
    {
        case 1:
            return *p;
        case 2:
            return ((*p & 0x1F) << 6) | (p[1] & 0x3F);
        case 3:
            return ((*p & 0x0F) << 12) | ((p[1] & 0x3F) << 6) | (p[2] & 0x3F);
        case 4:
            return ((*p & 0x07) << 18) | ((p[1] & 0x3F) << 12) | ((p[2] & 0x3F) << 6) | (p[3] & 0x3F);
        default:
            return 0;
    }
#elif 0
    unsigned char c = *s;
    
    if (c < 0x80)
        return c;
    if ((c & 0xE0) == 0xC0/*&& (s[1] & 0xC0) == 0x80*/)
        return ((c & 0x1F) << 6) | (s[1] & 0x3F);
    if ((c & 0xF0) == 0xE0/* && (s[1] & 0xC0) == 0x80 && (s[2] & 0xC0) == 0x80*/)
        return ((c & 0x0F) << 12) | ((s[1] & 0x3F) << 6) | (s[2] & 0x3F);
    if ((c & 0xF8) == 0xF0/* && (s[1] & 0xC0) == 0x80 && (s[2] & 0xC0) == 0x80 && (s[3] & 0xC0) == 0x80*/)
        return ((c & 0x07) << 18) | ((s[1] & 0x3F) << 12) | ((s[2] & 0x3F) << 6) | (s[3] & 0x3F);
    return -1;
#endif
}
a_cp a_to_cp(const char *s)
{
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, 0);
    return a_internal_char_to_cp(s);
}

static char *a_internal_cp_to_char(a_cp cp, char *b)
{
    unsigned int c = (unsigned int)cp;
    
    if (c < 0x80)
        b[0] = (char)c, b[1] = '\0';
    else if (c < 0x0800)
        b[0] = (char)(0xC0 | (c >> 6)), 
        b[1] = (char)(0x80 | (c & 0x3F)),
        b[2] = '\0';
    else if (c < 0x10000)
        b[0] = (char)(0xE0 | (c >> 12)),
        b[1] = (char)(0x80 | ((c >> 6) & 0x3F)),
        b[2] = (char)(0x80 | (c & 0x3F)),
        b[3] = '\0';
    else if (c < 0x110000)
        b[0] = (char)(0xF0 | (c >> 18)),
        b[1] = (char)(0x80 | ((c >> 12) & 0x3F)),
        b[2] = (char)(0x80 | ((c >> 6) & 0x3F)),
        b[3] = (char)(0x80 | (c & 0x3F)),
        b[4] = '\0';
    else
        b[0] = '\0';
    
    return b;
}
const char *a_to_utf8_size(a_cp cp, char *b, int *s)
{
    A_ASSERT_CODEPOINT(cp);
    PASSTHROUGH_ON_FAIL(b != NULL, NULL);
    
    a_internal_cp_to_char(cp, b);
    if (s)
        *s = a_size_chr_cstr(b);
    return b;
}

const char *a_to_utf8(a_cp c, char *b)
{
    A_ASSERT_CODEPOINT(c);
    PASSTHROUGH_ON_FAIL(b != NULL, NULL);
    return a_to_utf8_size(c, b, NULL);
}

char *a_to_fold_cp(a_cp cp, char *b)
{
    const struct a_char_record *r = A_RECORD_PTR(cp);
    register int new_cp = cp + r->casefold_diff;
    A_ASSERT_CODEPOINT(cp);
    assert(b != NULL);
    PASSTHROUGH_ON_FAIL(b != NULL, NULL);
    
#if A_INCLUDE_LOCALE == 1
    /*
     * special exception for turkish language
     * 
     * 0049; T; 0131; # LATIN CAPITAL LETTER I
     * 0130; T; 0069; # LATIN CAPITAL LETTER I WITH DOT ABOVE
     */
    if (a_locale_get()->exceptions & A_LOCALE_TURKISH_EXCEPTION)
    {
        if (cp == 0x49)
        {
            b[0] = (char)0xC4, b[1] = (char)0xB1, b[2] = '\0';
            return b;
        }
        else if (cp == 0x130)
        {
            b[0] = (char)0x69, b[1] = '\0';
            return b;
        }
    }
#endif
    
    /* common case */
    if (!(r->special & A_SPECIAL_MASK_CASEFOLD))
        return a_internal_cp_to_char(new_cp, b);
    
    /* casefolding has a set of exceptional characters
     * that fold into multiple code points, sometimes
     * as much as 3. we handle those seperatly.
     *//*
    if (r->special & A_SPECIAL_MASK_CASEFOLD)*/
    {
        int index = -1;
        int high = A_CASEFOLD_SPECIAL_TABLE_SIZE;
        int low = 0;
        
        while (high)
        {
            int mid = low + ((high - low) / 2);
            a_cp cur_cp = a_codepoint_casefold_special[mid].cp;

            if (cur_cp == cp)
            {
                index = mid;
                break;
            }
            else if (cur_cp < cp)
                low = mid + 1;
            else
                high = mid - 1;
        }
        
        /* this should NEVER EVER happen unless the
         * table was generated incorrectly */
        assert(index != -1); 
        
        memcpy(b, a_codepoint_casefold_special[index].str, A_MAX_CASEFOLD_UTF8_BUFFER_SIZE);
    }
    return b;
}

a_cp *a_to_fold_cp_cp(a_cp cp, a_cp *b)
{
    const struct a_char_record *r = A_RECORD_PTR(cp);
    A_ASSERT_CODEPOINT(cp);
    assert(b != NULL);
    PASSTHROUGH_ON_FAIL(b != NULL, NULL);
    
#if A_INCLUDE_LOCALE == 1
    /*
     * special exception for turkish language
     * 
     * 0049; T; 0131; # LATIN CAPITAL LETTER I
     * 0130; T; 0069; # LATIN CAPITAL LETTER I WITH DOT ABOVE
     */
    if (a_locale_get()->exceptions & A_LOCALE_TURKISH_EXCEPTION)
    {
        if (cp == 0x49)
        {
            b[0] = 0x131;
            return b;
        }
        else if (cp == 0x130)
        {
            b[0] = 0x69;
            return b;
        }
    }
#endif
    
    /* common case */
    if (!(r->special & A_SPECIAL_MASK_CASEFOLD))
    {
        b[0] = cp + r->casefold_diff;
        b[1] = 0;
        return b;
    }
    
    /* casefolding has a set of exceptional characters
     * that fold into multiple code points, sometimes
     * as much as 3. we handle those seperatly.
     *//*
    if (r->special & A_SPECIAL_MASK_CASEFOLD)*/
    {
        int index = -1;
        int high = A_CASEFOLD_SPECIAL_TABLE_SIZE;
        int low = 0;
        
        while (high)
        {
            int mid = low + ((high - low) / 2);
            a_cp cur_cp = a_codepoint_casefold_special[mid].cp;

            if (cur_cp == cp)
            {
                index = mid;
                break;
            }
            else if (cur_cp < cp)
                low = mid + 1;
            else
                high = mid - 1;
        }
        
        /* this should NEVER EVER happen unless the
         * table was generated incorrectly */
        assert(index != -1); 
        
        memcpy(b, a_codepoint_casefold_special[index].codepoints, (A_MAX_CASEFOLD_SIZE+1) *  sizeof (int));
    }
    return b;
}


char *a_to_fold_simple_chr(a_cp cp, char *b)
{
    A_ASSERT_CODEPOINT(cp);
    assert(b != NULL);
    PASSTHROUGH_ON_FAIL(b != NULL, NULL);
    
    return a_internal_cp_to_char(
                cp + A_RECORD_PTR(cp)->simplecasefold_diff, b);
}

a_cp a_to_fold_simple_chr_cp(a_cp cp)
{
    A_ASSERT_CODEPOINT(cp);
    return cp + A_RECORD_PTR(cp)->simplecasefold_diff;
}