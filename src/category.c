/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */
int a_category(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint);
}
int a_is_alpha(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint) & a_gc_alpha;
}
int a_is_alphanumeric(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint) & a_gc_alphanumeric;
}
int a_is_bmp(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return codepoint <= 0xFFFF;
}
int a_is_control(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint) & a_gc_cc;
}
int a_is_currency(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint) & a_gc_sc;
}
int a_is_digit(a_cp codepoint)
{
    return codepoint < 128 && a_ascii_is_digit(codepoint);
}
int a_is_format(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint) & a_gc_cf;
}
int a_is_graphical(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint) & a_gc_graphical;
}
int a_is_letter(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint) & a_gc_letter;
}
int a_is_lower(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint) & a_gc_ll;
}
int a_is_mark(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint) & a_gc_mark;
}
int a_is_noncharacter(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint) & a_gc_cn;
}
int a_is_number(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint) & a_gc_number;
}
int a_is_private_use(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint) & a_gc_co;
}
int a_is_punctuation(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint) & a_gc_punctuation;
}
int a_is_separator(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint) & a_gc_separator;
}
int a_is_space(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint) & a_gc_zs;
}
int a_is_supplementary(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return codepoint > 0x10000;
}
int a_is_surrogate(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint) & a_gc_cs;
}
int a_is_surrogate_high(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return (codepoint >= 0xD800 && codepoint <= 0xDBFF);
}
int a_is_surrogate_low(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return (codepoint >= 0xDC00 && codepoint <= 0xDFFF);
}
int a_is_symbol(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint) & a_gc_lu;
}
int a_is_title(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint) & a_gc_lt;
}
int a_is_upper(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint) & a_gc_lu;
}
int a_is_math(a_cp codepoint)
{
    A_ASSERT_CODEPOINT(codepoint);
    return A_CATEGORY_MASK(codepoint) & a_gc_sm;
}

static const char a_categories[61] =
"LuLlLtLmLoMnMcMeNdNlNoPcPdPsPePiPfPoSmScSkSoZsZlZpCcCfCsCoCn";
static const char a_categories_strs[90] =
"Lu\0Ll\0Lt\0Lm\0Lo\0Mn\0Mc\0Me\0Nd\0Nl\0No\0Pc\0Pd\0Ps\0Pe\0"
"Pi\0Pf\0Po\0Sm\0Sc\0Sk\0So\0Zs\0Zl\0Zp\0Cc\0Cf\0Cs\0Co\0Cn\0";

const char *a_category_to_str(int category)
{
    unsigned pos = 0, c = (unsigned)category;
    assert(category > 0 && category < 29);
    while (c) ++pos, c >>= 1;
    return a_categories_strs + (pos * 3);
}
int a_category_from_str(const char *category)
{
    assert(category[2] == '\0');
    return 1 << ((strstr(a_categories, category) - a_categories) / 2);
}
const char *a_category_to_description(int category)
{
    assert(category > 0 && category < 29);
    
    switch (category)
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