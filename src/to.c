/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */
a_cp a_to_cp(const char *s)
{
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, 0);
    return a_internal_critical_char_to_cp(s);
}

const char *a_to_utf8_size(a_cp cp, char *b, int *s)
{
    PASSTHROUGH_ON_FAIL(b != NULL, NULL);
    
    a_internal_critical_cp_to_char(cp, b);
    *s = a_size_chr_cstr(b);
    return b;
}

const char *a_to_utf8(a_cp c, char *b)
{
    PASSTHROUGH_ON_FAIL(b != NULL, NULL);
    return a_to_utf8_size(c, b, NULL);
}

char *a_to_fold_cp(a_cp cp, char *b)
{
    const struct a_char_record *r = A_RECORD_PTR(cp);
    register int new_cp = cp + r->casefold_diff;
    assert(A_MIN_CP <= cp && cp <= A_MAX_CP);
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
        return a_internal_critical_cp_to_char(new_cp, b);
    
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
    assert(A_MIN_CP <= cp && cp <= A_MAX_CP);
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
    assert(A_MIN_CP <= cp && cp <= A_MAX_CP);
    assert(b != NULL);
    PASSTHROUGH_ON_FAIL(b != NULL, NULL);
    
    return a_internal_critical_cp_to_char(
                cp + A_RECORD_PTR(cp)->simplecasefold_diff, b);
}

a_cp a_to_fold_simple_chr_cp(a_cp cp)
{
    assert(A_MIN_CP <= cp && cp <= A_MAX_CP);
    return cp + A_RECORD_PTR(cp)->simplecasefold_diff;
}