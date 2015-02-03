a_str a = a_new(u8"Déjà vu");

/* iterate over code points */
for (const char *s = a; *s;) 
    printf("U+%.4x\n", a_next_cp_cstr(&s));

/* iterate over grapheme clusters */
for (const char *s = a, *t = s; *s; t = s) 
    printf("'%.*s'\n", (int)(a_gnext_cstr(&s) - t), t);
    
a_free(a);