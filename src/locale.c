/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */
static int a_local_parse_unicode_language_id(const char **l);
static int a_local_parse_locale(const char *l);

/*
 * Accepts a Unicode Locale Identifier as defined by UTS #35.
 * 
 * Accept ANY Unicode compliant locale.
 * Including Unicode BCP 47 U Extension
 * Including Unicode BCP 47 T Extension
 * 
 * although for now, we just accept them and discard them.
 * 
 * http://unicode.org/reports/tr35/
 */
int a_locale_set(const char *unicode_locale_id);
int a_locale_set(const char *id)
{
    if (a_local_parse_locale(id))
        return 1;
    
    return 0;
}

/*
         unicode_locale_id =  unicode_language_id
                              (transformed_extensions unicode_locale_extensions?
                               | unicode_locale_extensions? transformed_extensions?) ;
 unicode_locale_extensions =  sep "u" ((sep keyword)+ |(sep attribute)+ (sep keyword)*) ;
    transformed_extensions = sep "t" (("-" tlang ("-" tfield)*) | ("-" tfield)+) ;
                   keyword = key (sep type)? ;
                       key = alphanum{2} ;
                      type = alphanum{3,8} (sep alphanum{3,8})* ;
                 attribute = alphanum{3,8} ;
                     tlang = unicode_language_subtag
                             ("-" unicode_script_subtag)?
                             ("-" unicode_region_subtag)?
                             ("-" unicode_variant_subtag)* ;
                                                      
                    tfield = fsep ("-" alphanum{3,8})+ ;
       unicode_language_id = "root"
                             | unicode_language_subtag 
                             (sep unicode_script_subtag)? 
                             (sep unicode_region_subtag)?
                             (sep unicode_variant_subtag)* ;
   unicode_language_subtag = alpha{2,8} ;
   unicode_script_subtag   = alpha{4} ;
   unicode_region_subtag   = (alpha{2} | digit{3}) ;
   unicode_variant_subtag  = (alphanum{5,8} | digit alphanum{3}) ;
                     digit = [0-9] ;
                      fsep = [A-Z a-z] [0-9] ;
                       sep = [-_] ;
                     alpha = [A-Z a-z] ;
                  alphanum = [0-9 A-Z a-z] ;
     
                        
 */

static int loc_is_alnum(const char **str, int min, int max)
{
    const char *s = *str;
    
    while ((a_ascii_is_alnum(*s) && min)) 
        --min, ++s, --max;
    if (min) return 0;
    while (a_ascii_is_alnum(*s) && max) 
        --max, ++s;
    *str = s;
    return 1;
}
static int loc_is_alpha(const char **str, int min, int max)
{
    const char *s = *str;
    
    while ((a_ascii_is_alpha(*s) && min)) 
        --min, ++s, --max;
    if (min) return 0;
    while (a_ascii_is_alpha(*s) && max) 
        --max, ++s;
    *str = s;
    return 1;
}

static int loc_is_digit(const char **str, int min, int max)
{
    const char *s = *str;
    
    while ((a_ascii_is_digit(*s) && min)) 
        --min, ++s, --max;
    if (min) return 0;
    while (a_ascii_is_digit(*s) && max) 
        --max, ++s;
    *str = s;
    return 1;
}

static int loc_is_sep(const char **str)
{
    if (**str == '-' || **str == '_')
    {
        *str += 1;
        return 1;
    }
    return 0;
}

static int a_local_parse_locale(const char *id)
{
    char lang_subtag[9];
    char script_subtag[5] = {0,0,0,0,0};
    char region_subtag[4] = {0,0,0,0};
    char variant_subtag[10];
    const char *start;
    size_t c = 0;
    
    if (!a_local_parse_unicode_language_id(&id))
    {
        /* sep (transformed_extensions unicode_locale_extensions?
            | unicode_locale_extensions? transformed_extensions?) */
        if (*id)
        {
            if (!loc_is_sep(&id))
                return 1;
            
            /* Unicode BCP 47 T Extension */
            if (*id == 't' || *id == 'T')
            {
                ++id;
                
                /*  transformed_extensions unicode_locale_extensions? 
             
                    transformed_extensions = "t" (("-" tlang ("-" tfield)*) | ("-" tfield)+) ;
                */
                if (*id++ != '-')
                    return 1;
                
                /*
                    ("-" tlang ("-" tfield)*)
                 
                     tlang = unicode_language_subtag
                             ("-" unicode_script_subtag)?
                             ("-" unicode_region_subtag)?
                             ("-" unicode_variant_subtag)* ;
                             
                    tfield = [A-Z a-z] [0-9] ("-" [0-9 A-Z a-z]{3,8})+ ;
                */
                
                /* unicode_language_subtag = alpha{2,8} ; */
                start = id;
                if (loc_is_alpha(&id, 2, 8))
                {
                    memcpy(lang_subtag, start, id-start);
                    lang_subtag[id-start] = 0;
                    (void)lang_subtag;
                    
                    /* unicode_script_subtag */
                    start = id + 1;
                    if (*id++ == '-' && loc_is_alpha(&id, 4, 4))
                    {
                        memcpy(script_subtag, start, id-start);
                        script_subtag[id-start] = 0;
                        (void)script_subtag;
                    }
                    else --id;
            
                    /* unicode_region_subtag */
                    start = id + 1;
                    if (*id++ == '-' &&
                        (loc_is_alpha(&id, 2, 2) || loc_is_digit(&id, 3, 3)))
                    {
                        memcpy(region_subtag, start, id-start);
                        (void)region_subtag;
                    }
                    
                    /* ("-" ([0-9 A-Z a-z]{5,8} | [0-9][0-9 A-Z a-z]{3}))* 
                    */
                    while (*id == '-')
                    {
                        start = id++;
                        
                        if (a_ascii_is_digit(*id) && loc_is_alnum(&id, 4, 4))
                        {
                            memcpy(variant_subtag, start+1, 4);
                            variant_subtag[4] = 0;
                            (void)variant_subtag;
                        }
                        else if (loc_is_alnum(&id, 5, 8))
                        {
                            memcpy(variant_subtag, start+1, id-start-1);
                            variant_subtag[id-start-1] = 0;
                            (void)variant_subtag;
                        }
                        else
                        {
                            --id;
                            break;
                        }
                    }
                    
                    c = 1; /* optional: ("-" tfield)* */
                }
                
                /* "-" tfield */
                while (*id == '-')
                {
                    ++id;
                    /* tfield = [A-Z a-z] [0-9]("-" [0-9 A-Z a-z]{3,8})+ ; */
                    if (loc_is_alpha(&id, 1, 1)  && loc_is_digit(&id, 1, 1))
                    {
                        int i = 0;
                        /* ("-" [0-9 A-Z a-z]{3,8})+ */
                        while (*id++ == '-' && loc_is_alnum(&id, 3, 8)) ++i;
                        if (i) ++c;
                    }
                }
                
                if (!c)
                    return 1;
            }
            /* Unicode BCP 47 U Extension */
            else if (*id == 'u' || *id == 'U')
            {
                ++id;
            /* unicode_locale_extensions? transformed_extensions?
             
               unicode_locale_extensions =  "u" (
                                                (sep keyword)+ 
                                                |(sep attribute)+ (sep keyword)*) ;
              
                  keyword = key (sep type)? ;
                      key = alphanum{2} ;
                     type = alphanum{3,8} (sep alphanum{3,8})* ;
                attribute = alphanum{3,8} ;
               
                
                sep alphanum{2} sep alphanum{3,8} (sep alphanum{3,8})*
             */
                if (loc_is_sep(&id) && loc_is_alnum(&id, 2, 2))
                {
                    if (loc_is_sep(&id) && loc_is_alnum(&id, 3, 8))
                        while (loc_is_sep(&id) && loc_is_alnum(&id, 3, 8));
                }
                /* (sep attribute)+ (sep keyword)* */
                else if (loc_is_sep(&id) && loc_is_alnum(&id, 3, 8))
                {
                    while (loc_is_sep(&id) && loc_is_alnum(&id, 3, 8));
                    while (loc_is_sep(&id) && loc_is_alnum(&id, 2, 2))
                    {
                        if (loc_is_sep(&id) && loc_is_alnum(&id, 3, 8))
                            while (loc_is_sep(&id) && loc_is_alnum(&id, 3, 8));
                    }
                }
            }
            else
                return 1;
        }
    }
    return 0;
}
static int a_local_parse_unicode_language_id (const char **l)
{
    const char *start, *at = *l;
    char lang_subtag[9];
    char script_subtag[5] = {0,0,0,0,0};
    char region_subtag[4] = {0,0,0,0};
    char variant_subtag[10];
/*
       unicode_language_id = "root"
                             | unicode_language_subtag 
                             (sep unicode_script_subtag)? 
                             (sep unicode_region_subtag)?
                             (sep unicode_variant_subtag)* ;
 */
    if (!a_icmpn_cstr_cstr(at, "root", 4))
    {
        *l += 4;
        return 0;
    }
    
    /* unicode_language_subtag = alpha{2,8} ; */
    start = at;
    if (!loc_is_alpha(&at, 2, 8))
        return 1;
    memcpy(lang_subtag, start, at-start);
    lang_subtag[at-start] = 0;
    
    (void)lang_subtag;
    
    /* [-_] */
    if (!loc_is_sep(&at))
        return 0;
    
    /* unicode_script_subtag   = alpha{4} ; */
    start = at;
    if (loc_is_alpha(&at, 4, 4))
    {
        memcpy(script_subtag, start, at-start);
        script_subtag[at-start] = 0;
        
        (void)script_subtag;
        
        /* [-_] */
        if (!loc_is_sep(&at))
            return 0;
    }
    
    /* unicode_region_subtag = (alpha{2} | digit{3}) */
    start = at;
    if (loc_is_alpha(&at, 2, 2)) 
        memcpy(region_subtag, start, 2);
    else if (loc_is_digit(&at, 3, 3))
        memcpy(region_subtag, start, 3);
    
    (void)region_subtag;
    
    
    /* ([-_] ([0-9 A-Z a-z]{5,8} | [0-9][0-9 A-Z a-z]{3}))* 
     */
    while (loc_is_sep(&at))
    {
        start = at - 1;
        
        if (a_ascii_is_digit(*at) && loc_is_alnum(&at, 4, 4))
        {
            memcpy(variant_subtag, start+1, 4);
            variant_subtag[4] = 0;
            (void)variant_subtag;
        }
        else if (loc_is_alnum(&at, 5, 8))
        {
            memcpy(variant_subtag, start+1, at-start-1);
            variant_subtag[at-start-1] = 0;
            (void)variant_subtag;
        }
        else
        {
            --at;
            break;
        }
    }
    
    *l = at;
    return 0;
}