void a_dump(a_str s, int val)
{
    if (!s)
        fprintf(stderr, "a_str {adr=0x00000000000}\n");
    else
    {
        struct a_header *h = a_header(s);
        fprintf(stderr,
            "a_str {adr=%p, %s%s%slen=%ld, size=%ld, mem=%ld, valid=%s}\n",
            s,
            val ? "val='" : "",
            val ? s : "",
            val ? "', " : "",
            (long int)h->len,
            (long int)h->size,
            (long int)h->mem,
            a_is_valid_utf8(s) == NULL ? "true" : "false"
        );
    }
}

void a_dump_cp(a_cp cp)
{
    if (cp < A_MIN_CP || cp > A_MAX_CP)
    {
        fprintf(stderr,
                "a_cp {codepoint=%d, error=codepoint outside of the Unicode codespace (%d <= cp <= %d)}\n",
                cp, A_MIN_CP, A_MAX_CP);
        
    }
    else
    {
#if A_INCLUDE_NAMES == 1
        char name[A_NAME_MAX_SIZE];
#endif
        unsigned char chr[5];
        int l, i;
        
        a_to_utf8_size(cp, (char*)chr, &l);
        fprintf(stderr,
                "a_cp {codepoint=%d (0x%X), ref='%s', gc=%s ('%s'), ",
                cp, cp, chr, a_category_to_str(cp), a_category_to_description(cp));
#if A_INCLUDE_NAMES == 1
        fprintf(stderr, "name='%s', ", a_name_cp(cp, name));
#endif
        
        fprintf(stderr, "size=%ld, UTF-8=", (long int)l);
        for (i = 0; chr[i]; ++i)
            fprintf(stderr, "0x%X%s", chr[i], chr[i+1] ? " " : "");
        fprintf(stderr, "}\n");
    }
}