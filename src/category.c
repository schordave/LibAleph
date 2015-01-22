/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */
int a_category(a_cp codepoint)
{
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    
    return A_CATEGORY(codepoint);
}
int a_is_alpha(a_cp codepoint)
{
    register int c;
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    c = A_CATEGORY(codepoint);
    
    return (c == a_gc_lu || c == a_gc_ll || c == a_gc_lt
            || c == a_gc_lm || c == a_gc_lo);
}
int a_is_alphanumeric(a_cp codepoint)
{
    register int c;
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    c = A_CATEGORY(codepoint);
    
    return (c == a_gc_lu || c == a_gc_ll || c == a_gc_lt
            || c == a_gc_lm || c == a_gc_lo || c == a_gc_nd
            || c == a_gc_nl || c == a_gc_no);
}
int a_is_control(a_cp codepoint)
{
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    
    return (A_CATEGORY(codepoint) == a_gc_cc);
}
int a_is_currency(a_cp codepoint)
{
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    
    return (A_CATEGORY(codepoint) == a_gc_sc);
}
int a_is_digit(a_cp codepoint)
{
    return codepoint < 128 && a_ascii_is_digit(codepoint);
}
int a_is_format(a_cp codepoint)
{
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    
    return (A_CATEGORY(codepoint) == a_gc_cf);
}
int a_is_graphical(a_cp codepoint)
{
    register int c;
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    c = A_CATEGORY(codepoint);
    
    return (c == a_gc_lu || c == a_gc_ll || c == a_gc_lt
            || c == a_gc_lm || c == a_gc_lo || c == a_gc_mn
            || c == a_gc_mc || c == a_gc_me || c == a_gc_nd
            || c == a_gc_nl || c == a_gc_no || c == a_gc_pc
            || c == a_gc_pd || c == a_gc_ps || c == a_gc_pe
            || c == a_gc_pi || c == a_gc_pf || c == a_gc_po
            || c == a_gc_sm || c == a_gc_sc || c == a_gc_sk
            || c == a_gc_so || c == a_gc_zs || c == a_gc_zl
            || c == a_gc_zp);
}
int a_is_letter(a_cp codepoint)
{
    register int c;
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    c = A_CATEGORY(codepoint);
    
    return (c == a_gc_lu || c == a_gc_ll || c == a_gc_lt
            || c == a_gc_lm || c == a_gc_lo);
}
int a_is_lower(a_cp codepoint)
{
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    
    return (A_CATEGORY(codepoint) == a_gc_ll);
}
int a_is_mark(a_cp codepoint)
{
    register int c;
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    c = A_CATEGORY(codepoint);
    
    return (c == a_gc_mn || c == a_gc_mc || c == a_gc_me);
}
int a_is_noncharacter(a_cp codepoint)
{
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    
    return (A_CATEGORY(codepoint) == a_gc_cn);
}
int a_is_number(a_cp codepoint)
{
    register int c;
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    c = A_CATEGORY(codepoint);
    
    return (c == a_gc_nd || c == a_gc_nl || c == a_gc_no);
}
int a_is_private_use(a_cp codepoint)
{
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    
    return (A_CATEGORY(codepoint) == a_gc_co);
}
int a_is_punctuation(a_cp codepoint)
{
    register int c;
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    c = A_CATEGORY(codepoint);
    
    return (c == a_gc_pc || c == a_gc_pd || c == a_gc_ps
            || c == a_gc_pe || c == a_gc_pi || c == a_gc_pf
            || c == a_gc_po);
}
int a_is_separator(a_cp codepoint)
{
    register int c;
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    c = A_CATEGORY(codepoint);
    
    return (c == a_gc_zs || c == a_gc_zl || c == a_gc_zp);
}
int a_is_space(a_cp codepoint)
{
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    
    return (A_CATEGORY(codepoint) == a_gc_zs);
}
int a_is_surrogate(a_cp codepoint)
{
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    
    return (A_CATEGORY(codepoint) == a_gc_cs);
}
int a_is_surrogate_high(a_cp codepoint)
{
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    
    return (codepoint >= 0xD800 && codepoint <= 0xDBFF);
}
int a_is_surrogate_low(a_cp codepoint)
{
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    
    return (codepoint >= 0xDC00 && codepoint <= 0xDFFF);
}
int a_is_symbol(a_cp codepoint)
{
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    
    return (A_CATEGORY(codepoint) == a_gc_lu);
}
int a_is_title(a_cp codepoint)
{
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    
    return (A_CATEGORY(codepoint) == a_gc_lt);
}
int a_is_upper(a_cp codepoint)
{
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    
    return (A_CATEGORY(codepoint) == a_gc_lu);
}
int a_is_math(a_cp codepoint)
{
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    
    return (A_CATEGORY(codepoint) == a_gc_sm);
}
const char *a_category_to_str(a_cp codepoint)
{
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    
    switch (A_CATEGORY(codepoint))
    {
        case a_gc_lu: return "Lu";
        case a_gc_ll: return "Ll";
        case a_gc_lt: return "Lt";
        case a_gc_lm: return "Lm";
        case a_gc_lo: return "Lo";
        case a_gc_mn: return "Mn";
        case a_gc_mc: return "Mc";
        case a_gc_me: return "Me";
        case a_gc_nd: return "Nd";
        case a_gc_nl: return "Nl";
        case a_gc_no: return "No";
        case a_gc_pc: return "Pc";
        case a_gc_pd: return "Pd";
        case a_gc_ps: return "Ps";
        case a_gc_pe: return "Pe";
        case a_gc_pi: return "Pi";
        case a_gc_pf: return "Pf";
        case a_gc_po: return "Po";
        case a_gc_sm: return "Sm";
        case a_gc_sc: return "Sc";
        case a_gc_sk: return "Sk";
        case a_gc_so: return "So";
        case a_gc_zs: return "Zs";
        case a_gc_zl: return "Zl";
        case a_gc_zp: return "Zp";
        case a_gc_cc: return "Cc";
        case a_gc_cf: return "Cf";
        case a_gc_cs: return "Cs";
        case a_gc_co: return "Co";
        case a_gc_cn: return "Cn";
        default:      return "";
    }
}
const char *a_category_to_description(a_cp codepoint)
{
    assert(A_MIN_CP <= codepoint && codepoint <= A_MAX_CP);
    
    switch (A_CATEGORY(codepoint))
    {
        case a_gc_lu: return "Letter, uppercase";
        case a_gc_ll: return "Letter, lowercase";
        case a_gc_lt: return "Letter, titlecase";
        case a_gc_lm: return "Letter, modifier";
        case a_gc_lo: return "Letter, other";
        case a_gc_mn: return "Mark, nonspacing";
        case a_gc_mc: return "Mark, spacing combining";
        case a_gc_me: return "Mark, enclosing";
        case a_gc_nd: return "Number, decimal digit";
        case a_gc_nl: return "Number, letter";
        case a_gc_no: return "Number, other";
        case a_gc_pc: return "Punctuation, connector";
        case a_gc_pd: return "Punctuation, dash";
        case a_gc_ps: return "Punctuation, open";
        case a_gc_pe: return "Punctuation, close";
        case a_gc_pi: return "Punctuation, initial";
        case a_gc_pf: return "Punctuation, final";
        case a_gc_po: return "Punctuation, other";
        case a_gc_sm: return "Symbol, math";
        case a_gc_sc: return "Symbol, currency";
        case a_gc_sk: return "Symbol, modifier";
        case a_gc_so: return "Symbol, other";
        case a_gc_zs: return "Separator, space";
        case a_gc_zl: return "Separator, line";
        case a_gc_zp: return "Separator, paragraph";
        case a_gc_cc: return "Other, control";
        case a_gc_cf: return "Other, format";
        case a_gc_cs: return "Other, surrogate";
        case a_gc_co: return "Other, private use";
        case a_gc_cn: return "Other, not assigned";
        default:      return "";
    }
}

static const short a_ascii_category[128] = 
{
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x4180, 
    0x4100, 0x4100, 0x4100, 0x4100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 
    0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 
    0x0100, 0x0100, 0x5080, 0x3200, 0x3200, 0x3200, 0x3200, 0x3200, 0x3200, 0x3200, 
    0x3200, 0x3200, 0x3200, 0x3200, 0x3200, 0x3200, 0x3200, 0x3200, 0x127c, 0x127c, 
    0x125c, 0x125c, 0x125c, 0x125c, 0x125c, 0x125c, 0x124c, 0x124c, 0x3200, 0x3200, 
    0x3200, 0x3200, 0x3200, 0x3200, 0x3200, 0x1a4a, 0x1a4a, 0x1a4a, 0x1a4a, 0x1a4a, 
    0x1a4a, 0x1a42, 0x1a42, 0x1a42, 0x1a42, 0x1a42, 0x1a42, 0x1a42, 0x1a42, 0x1a42, 
    0x1a42, 0x1a42, 0x1a42, 0x1a42, 0x1a42, 0x1a42, 0x1a42, 0x1a42, 0x1a42, 0x1a42, 
    0x1a42, 0x3200, 0x3200, 0x3200, 0x3200, 0x3200, 0x3200, 0x164a, 0x164a, 0x164a, 
    0x164a, 0x164a, 0x164a, 0x1642, 0x1642, 0x1642, 0x1642, 0x1642, 0x1642, 0x1642, 
    0x1642, 0x1642, 0x1642, 0x1642, 0x1642, 0x1642, 0x1642, 0x1642, 0x1642, 0x1642, 
    0x1642, 0x1642, 0x1642, 0x3200, 0x3200, 0x3200, 0x3200, 0x0100
};


int a_ascii_is_alpha(a_cp cp)  { assert(cp < 128); return a_ascii_category[cp] & (1 << 1); } 
int a_ascii_is_digit(a_cp cp)  { assert(cp < 128); return a_ascii_category[cp] & (1 << 2); } 
int a_ascii_is_xdigit(a_cp cp) { assert(cp < 128); return a_ascii_category[cp] & (1 << 3); } 
int a_ascii_is_odigit(a_cp cp) { assert(cp < 128); return a_ascii_category[cp] & (1 << 4); } 
int a_ascii_is_bdigit(a_cp cp) { assert(cp < 128); return a_ascii_category[cp] & (1 << 5); } 
int a_ascii_is_alnum(a_cp cp)  { assert(cp < 128); return a_ascii_category[cp] & (1 << 6); } 
int a_ascii_is_blank(a_cp cp)  { assert(cp < 128); return a_ascii_category[cp] & (1 << 7); } 
int a_ascii_is_cntrl(a_cp cp)  { assert(cp < 128); return a_ascii_category[cp] & (1 << 8); } 
int a_ascii_is_graph(a_cp cp)  { assert(cp < 128); return a_ascii_category[cp] & (1 << 9); } 
int a_ascii_is_lower(a_cp cp)  { assert(cp < 128); return a_ascii_category[cp] & (1 << 10); } 
int a_ascii_is_upper(a_cp cp)  { assert(cp < 128); return a_ascii_category[cp] & (1 << 11); } 
int a_ascii_is_print(a_cp cp)  { assert(cp < 128); return a_ascii_category[cp] & (1 << 12); } 
int a_ascii_is_punct(a_cp cp)  { assert(cp < 128); return a_ascii_category[cp] & (1 << 13); } 
int a_ascii_is_space(a_cp cp)  { assert(cp < 128); return a_ascii_category[cp] & (1 << 14); } 