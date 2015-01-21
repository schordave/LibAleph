#if A_INCLUDE_NAMES == 1

#if A_NAME_JUMP_TABLE
static int a_cmp_names(const void *a, const void *b)
{
    return  (*(const int *)a - *(const int *)b);
}
#else
static int a_cmp_names(const void *a, const void * b)
{
   return *(int*)a - ((struct a_cp_name*)b)->cp;
}
#endif
static const char a_codepoint_jamo_l_shortname[][3] = {
    "G", "GG", "N", "D", "DD", "R", "M", "B", "BB",
    "S", "SS", "", "J", "JJ", "C", "K", "T", "P", "H"
};
static const char a_codepoint_jamo_v_shortname[][4] = {
    "A", "AE", "YA", "YAE", "EO", "E", "YEO", "YE", "O",
    "WA", "WAE", "OE", "YO", "U", "WEO", "WE", "WI",
    "YU", "EU", "YI", "I"
};
static const char a_codepoint_jamo_t_shortname[][3] = {
    "", "G", "GG", "GS", "N", "NJ", "NH", "D", "L", "LG", "LM",
    "LB", "LS", "LT", "LP", "LH", "M", "B", "BS",
    "S", "SS", "NG", "J", "C", "K", "T", "P", "H"
};
char *a_name_cp(a_cp cp, char *buff)
{
    char *out = buff;
#if A_NAME_JUMP_TABLE
    const int *cp_data;
#else
    struct a_cp_name *v;
#endif
    assert(buff != NULL);
    PASSTHROUGH_ON_FAIL(buff != NULL, NULL);
    
    if ((cp >= 0x3400 && cp <= 0x4DB5)      /* CJK Unified Ideographs Extension A */
        || (cp >= 0x4E00 && cp <= 0x9FCC)   /* CJK Unified Ideographs */
        || (cp >= 0x20000 && cp <= 0x2A6D6) /* CJK Unified Ideographs Extension B */
        || (cp >= 0x2A700 && cp <= 0x2b734) /* CJK Unified Ideographs Extension C */
        || (cp >= 0x2B740 && cp <= 0x2B81D) /* CJK Unified Ideographs Extension D */
     )
    {
        sprintf(buff, "CJK UNIFIED IDEOGRAPH-%04X", cp);
        return buff;
    }
    
    else if ((cp >= 0xF900 && cp <= 0xFAD9) /* CJK Compatibility Ideographs */
        || (cp >= 0x2F800 && cp <= 0x2FA1D) /* CJK Compatibility Ideographs Supplement */
    )
    {
        sprintf(buff, "CJK COMPATIBILITY IDEOGRAPH-%04X", cp);
        return buff;
    }
    
    else if (cp >= 0xAC00 && cp <= 0xD7A3) /* Hangul Syllables */
    {
        /* info for this is found in The Unicode Standard Version 7; 3.12 Conjoining Jamo Behavior;
         * page 185, Hangul Syllable Name Generation
         * 
         * JSN_L = Jamo_Short_Name(LPart)
         * JSN_V = Jamo_Short_Name(VPart)
         * JSN_T = Jamo_Short_Name(TPart) if TPart exists, else ""
         * 
         * name="HANGUL SYLLABLE " + JSN_L + JSN_V + JSN_T
         * 
         * constants (taken from the standard at the sections specified above)
         */
        #define A_HANGUL_SYLLABLES_SBase 0xAC00
        #define A_HANGUL_SYLLABLES_LBase 0x1100
        #define A_HANGUL_SYLLABLES_VBase 0x1161
        #define A_HANGUL_SYLLABLES_TBase 0x11A7
        #define A_HANGUL_SYLLABLES_LCount 19
        #define A_HANGUL_SYLLABLES_VCount 21
        #define A_HANGUL_SYLLABLES_TCount 28
        #define A_HANGUL_SYLLABLES_NCount (A_HANGUL_SYLLABLES_VCount * A_HANGUL_SYLLABLES_TCount)
        #define A_HANGUL_SYLLABLES_SCount (A_HANGUL_SYLLABLES_LCount * A_HANGUL_SYLLABLES_NCount)
        /* Syllable Index. First compute the index of the precomposed Hangul syllable s:
         */
        int SIndex = cp - A_HANGUL_SYLLABLES_SBase;        
        /* For full canonical decomposition of a precomposed Hangul syllable,
         * compute the indices and components as follows:
         * 
         * LIndex = SIndex div NCount
         * VIndex = (SIndex mod NCount) div TCount
         * TIndex = SIndex mod TCount
         * LPart = LBase + LIndex
         * VPart = VBase + VIndex
         * TPart = TBase + TIndex  if TIndex > 0
         * 
         * If TIndex = 0, then there is no trailing consonant, so map the
         * precomposed Hangul syllables to its full decomposition d = <LPart, VPart>.
         * Otherwise, there is a trailing consonant, so map s to its full
         * decomposition d = <LPart, VPart, TPart>.
         */
        int LIndex = SIndex / A_HANGUL_SYLLABLES_NCount;
        int VIndex = (SIndex % A_HANGUL_SYLLABLES_NCount) / A_HANGUL_SYLLABLES_TCount;
        int TIndex = SIndex % A_HANGUL_SYLLABLES_TCount;/*
        int LPart = A_HANGUL_SYLLABLES_LBase + LIndex;
        int VPart = A_HANGUL_SYLLABLES_VBase + VIndex;
        int TPart = A_HANGUL_SYLLABLES_TBase + TIndex;*/
        const char *l, *v, *t;
        
        if (SIndex < 0 || SIndex >= A_HANGUL_SYLLABLES_SCount)
        { /* not an Hangul Syllable */
            buff[0] = '\0';
            return buff;
        }

        l = a_codepoint_jamo_l_shortname[LIndex];
        v = a_codepoint_jamo_v_shortname[VIndex];
        t = a_codepoint_jamo_t_shortname[TIndex];
        
        sprintf(buff, "HANGUL SYLLABLE %s%s%s", l, v, t);
        return buff;
    }
    
    else if (cp >= 0xD800 && cp <= 0xDB7F)
    {
        #define A_HS "NON PRIVATE USE HIGH SURROGATES"
        return memcpy(buff, A_HS, sizeof A_HS);
        #undef A_HS
    }
    
    else if (cp >= 0xD800 && cp <= 0xDB7F)
    {
        #define A_HS "NON PRIVATE USE HIGH SURROGATES"
        return memcpy(buff, A_HS, sizeof A_HS);
        #undef A_HS
    }
    
    else if (cp >= 0xDB80 && cp <= 0xDBFF)
    {
        #define A_HS "PRIVATE USE HIGH SURROGATES"
        return memcpy(buff, A_HS, sizeof A_HS);
        #undef A_HS
    }
    
    else if (cp >= 0xDC00 && cp <= 0xDFFF)
    {
        #define A_LS "LOW SURROGATES"
        return memcpy(buff, A_LS, sizeof A_LS);
        #undef A_LS
    }
    
    else if (cp >= 0xE000 && cp <= 0xF8FF)
    {
        #define A_PRIVATE "PRIVATE USE AREA"
        return memcpy(buff, A_PRIVATE, sizeof A_PRIVATE);
        #undef A_PRIVATE
    }
    
    else if (cp >= 0xF0000 && cp <= 0xFFFFD)
    {
        #define A_PRIVATE "SUPPLEMENTARY PRIVATE USE AREA A"
        return memcpy(buff, A_PRIVATE, sizeof A_PRIVATE);
        #undef A_PRIVATE
    }
    
    else if (cp >= 0x100000 && cp <= 0x10FFFD)
    {
        #define A_PRIVATE "SUPPLEMENTARY PRIVATE USE AREA B"
        return memcpy(buff, A_PRIVATE, sizeof A_PRIVATE);
        #undef A_PRIVATE
    }


#if A_NAME_JUMP_TABLE
    /* get the index of the words; or NULL if not in table */
    cp_data = bsearch(&cp, a_codepoint_name_words_offsets, A_NAME_SIZE, sizeof (int) * A_NAME_LEN, a_cmp_names);
    if (cp_data)
    {
        size_t at, l = cp_data[1];
        
        for (at = 0; at < l; ++at)
        {
            int i1 = a_codepoint_name_words_indexes[cp_data[2 + at]]; /* word offset */
            int i2 = a_codepoint_name_words_indexes[cp_data[2 + at] + 1];
            memcpy(buff, a_codepoint_name_words + i1, i2 - i1);
            
            if (at+1 < l)
                buff[i2 - i1] = ' ';
            else
                buff[i2 - i1] = '\0';
            buff += i2 - i1 + 1;
        }
        return out;
    }
#else
    if (v = bsearch(&cp, a_codepoint_name_mapping, A_NAMES_ARRAY_SIZE, sizeof (struct a_cp_name), a_cmp_names))
    {
        return memcpy(buff, v->name, strlen(v->name) + 1);
    }
#endif
    
    buff[0] = '\0';
    return out;
} 
#endif