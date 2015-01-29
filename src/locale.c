/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */
#if A_INCLUDE_LOCALE == 1

struct a_locale
{
    int language;
    int script;
    int region;
    int exceptions;
#define A_LOCALE_TURKISH_EXCEPTION (1 << 0)
};

static struct a_locale *a_locale_get(void)
{
    static struct a_locale a_locale = { -1, -1, -1, -1 };
    return &a_locale;
}

int a_locale_language(void)
{
    return a_locale_get()->language;
}


static int a_local_parse_unicode_language_id(const char **l, struct a_locale *locale);
static int a_local_parse_locale(const char *l, struct a_locale *locale);
static int a_local_parse_language_subtag(const char **lang);
static int a_local_parse_script_subtag(const char **lang);
static int a_local_parse_region_subtag(const char **lang);

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
 * http://www.w3.org/International/articles/bcp47/
 * 
 * Accepts only well-formed tags (grammar-wise AND content-wise).
 * As per UTS #35, no BCP47 grandfathered tag are accepted.
 * 
 * Returns 0 on success, else failure.
 */
int a_locale_set(const char *unicode_locale_id);
int a_locale_set(const char *id)
{
    struct a_locale locale = { 0, 0, 0, 0};
    struct a_locale *l;
    
    if (id != NULL)
    {
        if (a_local_parse_locale(id, &locale))
            return 1;
    }
    else
    {
        id = "root";
        locale.language = locale.script = locale.region = 0;
    }
    
    l = a_locale_get();
    l->language = locale.language;
    l->script = locale.script;
    l->region = locale.region;
    
    if (locale.language == a_locale_country_tur
        || locale.language ==  a_locale_country_aze)
        l->exceptions |= (1 << 0);
    
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

static int a_local_parse_locale(const char *id, struct a_locale *locale)
{
    char lang_subtag[9];
    char script_subtag[5] = {0,0,0,0,0};
    char region_subtag[4] = {0,0,0,0};
    char variant_subtag[10];
    const char *start;
    size_t c = 0;
    
    if (!a_local_parse_unicode_language_id(&id, locale))
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
                else
                    return 1;
            }
            else
                return 1;
        }
    }
    return 0;
}
static int a_local_parse_unicode_language_id (const char **l, struct a_locale *locale)
{
    const char *start, *at = *l;
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
    
    /* unicode_language_subtag */
    if ((locale->language = a_local_parse_language_subtag(&at)) < 0)
        return 1;    

    /* [-_] */
    if (!loc_is_sep(&at))
        return 0;
    
    /* unicode_script_subtag */
    if ((locale->script = a_local_parse_script_subtag(&at)) >= 0)
    {
        /* [-_] */
        if (!loc_is_sep(&at))
            return 0;
    }
    
    /* unicode_region_subtag */
    locale->region = a_local_parse_region_subtag(&at);
    
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

/* ISO 639
 * 
 * We only accept the 2-letter ISO-639-2 and 3-letter ISO-639-3
 */
static int a_local_parse_language_subtag(const char **lang)
{
    const char *start;
    size_t i;
    
    start = *lang;
    if (!loc_is_alpha(lang, 2, 8))
        return -1;
    
    if (*lang-start == 2)
    {
        for (i = 0; i <= A_LOCALE_LANG_SIZE; ++i)
            if (!a_icmpn_cstr_cstr(start, a_locale_data_lookup[i].iso639_2, 2))
                return i;
    }
    else if (*lang-start == 3)
    {
        for (i = 0; i <= A_LOCALE_LANG_SIZE; ++i)
            if (!a_icmpn_cstr_cstr(start, a_locale_data_lookup[i].iso639_3, 3))
                return i;
    }
    
    return -1;
}


/* ISO-15924 script code -
 * 
 * this is simply the 4-letter script code
 */
static int a_local_parse_script_subtag(const char **script)
{
    const char *start;
    size_t i;
    
    start = *script;
    if (!loc_is_alpha(script, 4, 4))
        return -1;
    
    for (i = 0; i <= A_LOCALE_SCRIPT_SIZE; ++i)
        if (!a_icmpn_cstr_cstr(start, a_script_data_lookup[i].iso15924, 4))
            return i;
        
    return -1;
}

/* ISO-3166 region code -
 * 
 *  this is either a 2-letter region code or their equivilent numeric value
 */
static int a_local_parse_region_subtag(const char **region)
{
    size_t i;
    
    if (loc_is_alpha(region, 2, 2))
    {
        for (i = 0; i <= A_LOCALE_REGION_SIZE; ++i)
            if (!a_icmpn_cstr_cstr(*region-2, a_region_data_lookup[i].iso3166_2, 2))
                return i;
    }
    else if (loc_is_digit(region, 3, 3))
    {
        int val;
        char num[4];
        
        memcpy(num, *region-3, 3);
        num[3] = '\0';
        val = strtol(num, NULL, 10);
            
        for (i = 0; i <= A_LOCALE_REGION_SIZE; ++i)
            if (a_region_data_lookup[i].iso3166_code == val)
                return i;
    }
    return -1;
}


#endif