/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */
const char *a_is_valid_utf8(const char *s)
{
    /*
     * EBNF made based on table 3-7 "Well-Formed UTF-8 Byte Sequences"
     * 
     *  UTF8_Str  ::=  UTF8_Chr* ε
     *               | ε
     *  UTF8_Chr  ::=  UTF8_1 | UTF8_2 | UTF8_3 | UTF8_4
     *  UTF8_1    ::=  0x00-0x0F
     *  UTF8_2    ::=  0xC2-DF UTF8_Tail
     *  UTF8_3    ::=  0xE0 0xA0-BF UTF8_Tail
     *               | 0xE1-EC UTF8_Tail UTF8_Tail
     *               | 0xED 0x80-9F UTF8_Tail
     *               | 0xEE-EF UTF8_Tail UTF8_Tail
     *  UTF8_4    ::=  0xF0 0x90-BF UTF8_Tail UTF8_Tail
     *               | 0xF1-F3 UTF8_Tail UTF8_Tail UTF8_Tail
     *               | 0xF4 0x80-8F UTF8_Tail UTF8_Tail
     *  UTF8_Tail ::= 0x80-BF
     * 
     * 
     */
    const unsigned char *p;
    unsigned char c;
    assert(s != NULL);
    PASSTHROUGH_ON_FAIL(s != NULL, NULL);
    
    for (p = (const unsigned char*)s; *p; ++p)
    {
        c = *p;
        
        if (c < 0x80)
            continue;
        
        if ((c & 0xe0) == 0xc0)
        {
            if ((p[1] & 0xc0) != 0x80 /* not continuation */
                || (c & 0xfe) == 0xc0) /* overlong */
                return (const char*)p;
            ++p;
            continue;
        }
        
        if ((c & 0xf0) == 0xe0)
        {
            if ((p[1] & 0xc0) != 0x80 /* not continuation */
                || (p[2] & 0xc0) != 0x80 /* not continuation */
                || (c == 0xe0 && (p[1] & 0xe0) == 0x80) /* overlong */
                || (c == 0xed && (p[1] & 0xe0) == 0xa0) /* surrogate */
                || (c == 0xef && p[1] == 0xbf && (p[2] & 0xfe) == 0xbe))
                return (const char*)p;
            
            p += 2;
            continue;
        }
        
        if ((c & 0xf8) == 0xf0)
        {
            if ((p[1] & 0xc0) != 0x80 /* not continuation */
                || (p[2] & 0xc0) != 0x80 /* '' */
                || (p[3] & 0xc0) != 0x80 /* '' */
                || (c == 0xf0 && (p[1] & 0xf0) == 0x80) /* overlong */
                || (c == 0xf4 && p[1] > 0x8f)
                || c > 0xf4) /* > U+10FFFF */
                return (const char*)p;
            
            p += 3;
            continue;
        }
        return (const char*)p;
    }
    return NULL;
}