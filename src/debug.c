void a_dump(a_str s, int val)
{
    if (!s)
        fprintf(stderr, "a_str {adr=0x00000000000}\n");
    else
    {
        struct header *h = head(s);
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
