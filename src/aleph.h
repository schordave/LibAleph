/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
/**
 * \mainpage LibAleph, A Unicode string library for C.
 * 
 * LibAleph is a portable Unicode string library for C. LibAleph operates on
 * UTF-8 encoded strings, provides utilities to work and manipulate them, as
 * well as passing them back to legacy interfaces that expect NULL-terminated
 * strings. 
 * 
 * 
 * Aleph Concepts:
 * ==============
 * 
 *  "grapheme clusters" - That's what the Unicode standard calls user-perceived characters.
 *                        They are what the USER thinks are characters. In reality a single
 *                        grapheme cluster might be composed of one or more code points. When
 *                        Aleph operates on grapheme clusters, we mean extended grapheme clusters.
 * 
 *  "character"         - In LibAleph, a code point. (avoid using that term.)
 * 
 *  "code point"        - Any numerical value in the Unicode codespace, I.E. any value from
 *                        0x0 to 0x10FFFF.
 * 
 *  "code unit"         - A minimal bit-combination that represents a valid code point, in UTF-8.
 * 
 */
/**
 * \file aleph.h
 * \brief Prototypes and macros for working with aleph strings.
 * 
 * This file contains all the function prototypes and macros for working
 * with aleph strings. This is the only header needed to be included by
 * your project.
 * 
 * Aleph operates on dynamically allocated strings called Aleph Strings formally
 * called \link #a_str \em a_str \endlink and \link #a_cstr \em a_cstr \endlink.
 * \em a_cstr is just a const version of a_str.
 * 
 * \author Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * \copyright MIT License
 */
#include <stddef.h>
#include <assert.h>
/*
 * 
 */
#ifndef A_MIN_STR_SIZE
/**
 * \brief Used as the minimum buffer size for newly-allocated strings. You can
 *        define this yourself if you know your application will be dealing
 *        with mostly larger strings.
 */
#   define A_MIN_STR_SIZE 16
#endif
/**
 * \brief Define to use custom allocation routines instead of the standard
 *        library ones.
 */
#ifndef A_CUSTOM_ALLOC
#   define A_MALLOC(size) malloc(size)
#   define A_CALLOC(nmemb, size) calloc(nmemb, size)
#   define A_REALLOC(ptr, size) realloc(ptr, size)
#   define A_FREE(ptr) free(ptr)
#else
#   ifdef A_CUSTOM_ALLOC_HOOK

#   endif
#endif
/**
 * \brief Defining A_INCLUDE_NAMES will include name look-up 
 *        functionality. (Which includes a name lookup table
 *        of considerable size.)
 */
#ifndef A_INCLUDE_NAMES
#   define A_INCLUDE_NAMES 1
#endif
#ifndef A_INCLUDE_IO
#   define A_INCLUDE_IO 0
#else
#   include <stdio.h>
#endif
#ifndef A_INCLUDE_MEM
#   define A_INCLUDE_MEM 0
#else
#   ifndef A_MIN_STR_POOL_SIZE
        /**
        * \brief Used as the minimum string pool size for newly-allocated strings.
        *        You can define this yourself if you know your application will be
        *        dealing with mostly larger string pools.
        */
#       define A_MIN_STR_POOL_SIZE 16
#   endif
#endif
#define A_ASSERT_UTF8(s) \
    assert(((void)"LibAleph: Precondition Violated: string passed is not a valid UTF-8 string.", \
    !a_is_valid_utf8(s)))
#define A_ASSERT_CODEPOINT(cp) \
    assert(((void)"LibAleph: Precondition Violated: codepoint provided is outside of the Unicode codespace.", \
    (A_MIN_CP <= (cp) && (cp) <= A_MAX_CP)))
#ifdef __STDC_VERSION__
#   if __STDC_VERSION__ >= 199901L
#       define ALEPH_C_V 2
#   endif
#else
#   define ALEPH_C_V 1
#endif
/**
 * \brief Enables NULL passthrough for all library functions. I.e. allows for safe
 *        chaining of functions where if one fails and returns NULL, it will be 
 *        propagated onward without causing issues.
 * 
 * \note  NDEBUG must be defined to disable the standard assert that check for NULL values.
 */
#ifndef A_NULL_PASSTHROUGH
#   define A_NULL_PASSTHROUGH 0
#   define PASSTHROUGH_ON_FAIL(condition,val)
#else
#   if A_NULL_PASSTHROUGH
#       define PASSTHROUGH_ON_FAIL(condition,val) do { if (!(condition)) { return val; } } while (0)
#   else
#       define PASSTHROUGH_ON_FAIL(condition,val)
#   endif
#endif
/**
 * \brief The minimum codepoint possible in the Unicode codespace.
 */
#define A_MIN_CP (0x000000)
/**
 * \brief The maximum codepoint possible in the Unicode codespace.
 */
#define A_MAX_CP (0x10FFFF)
/**
 * \brief A typedef that should be used when dealing with aleph strings
 *        in order to distinguish them from normal NULL-terminated strings.
 */
typedef char *a_str;
/**
 * \brief A typedef that should be used when dealing with a const aleph
 *        strings in order to distinguish them from normal const NULL-terminated
 *        strings.
 */
typedef const char *a_cstr;
/**
 * \brief A typedef that represents a single Unicode code point.
 */
typedef int a_cp;
#if A_INCLUDE_MEM == 1
/**
 * \brief A struct typdef that hold a temp string pool object.
 */
typedef struct a_pool *a_pool;
#endif
/**
 * \brief A sentinel value representing EOS.
 */
#define A_EOS ((size_t)-1U)
/*
 */
extern const char a_next_char_size[256];

/* creation/destruction */
/**
 * \brief Creates a new Aleph string from a standard NULL-terminated UTF-8 string.
 * 
 * Creates a new Aleph string from the contents of \b str. If \b str is
 * NULL, a new empty string is created instead.
 * 
 * \param str A NULL-terminated UTF-8 string to initize the string to, or NULL.
 * \return a_str, otherwise NULL on failure.
 */
a_str       a_new(const char *str);
a_str       a_new_cp(a_cp chr, size_t repeat);
a_str       a_new_chr(char *chr, size_t repeat);
a_str       a_new_len(const char *str, size_t length);
a_str       a_new_valid(const char *str);
a_str       a_new_size(size_t length);
a_str       a_new_size_raw(size_t length);
a_str       a_new_dup(a_cstr s);
a_str       a_new_normalize(a_cstr str, int mode); /* see norm modes below */
void        a_free(a_str str);
void        a_free_n(a_str str, ...);
void        a_free_vec(a_str *strv);
/* clear */
a_str       a_clear(a_str str);
/* set */
a_str       a_set(a_str str, a_str newstr);
a_str       a_set_cstr(a_str str, const char *newstr);
a_str       a_set_cstr_size(a_str str, const char *newstr, size_t size);
/* index */
a_cp        a_char_at(a_cstr str, size_t index);
/* iterator */
a_cp        a_peek(const char *str);
char       *a_next(const char **str);
a_cp        a_next_cp(const char **str);
#define     a_next_chr(str) ((char*)(str + a_next_char_size[(int)*(unsigned char*)(str)]))
a_str       a_last(a_str str);
char       *a_last_cstr(const char *str);
char       *a_prev(const char **str);
a_cp        a_prev_cp(const char **s);
#ifdef A_ITERATOR
char       *a_it_at(a_str s);
char       *a_it_next(a_str s);
char       *a_it_prev(a_str s);
char       *a_it_begin(a_str s);
char       *a_it_end(a_str s);
int         a_it_at_end(a_cstr s);
int         a_it_at_start(a_cstr s);
#endif
/* validation */
const char *a_is_valid_utf8(const char *cstr);
a_str       a_validate(a_str str);
/* debug */
void        a_dump(a_str str, int val);
void        a_dump_cp(a_cp cp);
/* length */
size_t      a_len(a_cstr str);
size_t      a_len_cstr(const char *str);
size_t      a_len_cstr_max(const char *str, size_t max);
size_t      a_size(a_cstr s);
#define     a_size_chr(c) ((a_next_char_size[(int)c]))
#define     a_size_chr_cstr(s) (a_size_chr((unsigned char)*s))
/* concatentation */
a_str       a_cat(a_str str, const char *str2);
a_str       a_cat_chr(a_str str, const char *chr);
a_str       a_cat_str(a_str str, a_str str2);
a_str       a_cat_len(a_str str, const char *str2, size_t l);
a_str       a_cat_cp(a_str str, a_cp codepoint);
/* insertion */
a_str       a_ins(a_str str, a_cstr str2, size_t index);
a_str       a_ins_chr(a_str str, const char *chr, size_t index);
a_str       a_ins_cstr(a_str str, const char *strs, size_t index);
a_str       a_ins_cp(a_str str, a_cp codepoint, size_t index);
a_str       a_ins_offset(a_str str, a_cstr str2, size_t offset);
a_str       a_ins_offset_chr(a_str str, const char *chr, size_t offset);
a_str       a_ins_offset_cstr(a_str str, const char *str2, size_t offset);
a_str       a_ins_offset_cp(a_str str, a_cp codepoint, size_t offset);
/* splitting */
a_str      *a_split(const char *str, a_cp codepoint);
a_str      *a_split_cstr(const char *str, a_cp codepoint);
a_str      *a_split_delim_opts(const char *str, const char *delimiters, size_t *count, int options);
a_str      *a_split_delim_count(const char *str, const char *delimiters, size_t *count);
a_str      *a_split_delim(const char *str, const char *delimiters);
enum a_split_options
{
    a_split_no_options   = 0x00,
    a_split_remove_empty = 0x01,
    a_split_trim_tokens  = 0x02
};
/* join */
a_str       a_join(a_str, ...);
a_str       a_join_on(a_str, const char *glue, ...);
a_str       a_join_on_opts(a_str, int opts, ...); /* skip blanks, etc.. */
/* buffer manipulation */
a_str       a_reserve(a_str str, size_t l);
a_str       a_ensure(a_str str, size_t l);
/* count */
size_t      a_count(a_cstr str, const char *delmiters);
size_t      a_count_cp(a_cstr str, a_cp codepoint);
size_t      a_count_cstr(const char *str, const char *delmiters);
size_t      a_count_cstr_cp(const char *str, a_cp codepoint);
/* extraction */
a_str       a_substr(a_cstr str, long start, long length);
a_str       a_substr_inplace(a_str str, long start, long length);
a_str       a_substr_offset(a_cstr str, long start, long length);
a_str       a_substr_offset_inplace(a_str str, long start, long length);
a_str       a_substr_between_cstr(a_cstr str, const char *sub1, const char *sub2, int inclusive);
a_str       a_substr_between_cstr_inplace(a_str str, const char *sub1, const char *sub2, int inclusive);
a_str       a_left(a_cstr str, size_t length);
a_str       a_left_offset(a_cstr str, size_t length);
a_str       a_left_offset_inplace(a_str str, size_t length);
a_str       a_right(a_cstr str, size_t length);
a_str       a_right_offset(a_cstr str, size_t length);
a_str       a_right_offset_inplace(a_str str, size_t length);
/* remove */
a_str       a_trim(a_str str);
a_str       a_trim_str(a_str str, const char *chars);
a_str       a_trim_left(a_str str);
a_str       a_trim_left_cstr(a_str str, const char *chars);
a_str       a_trim_right(a_str str);
a_str       a_trim_right_cstr(a_str str, const char *chars);
/* match */
int         a_cmp(a_cstr str1, a_cstr str2);
int         a_cmp_cstr(const char *str, const char *str2);
int         a_icmp(a_cstr str1, a_cstr str2);
int         a_icmp_cstr(a_cstr str1, const char *str2);
int         a_icmp_cstr_cstr(const char *str1, const char *str2);
int         a_icmp_simple(a_cstr str1, a_cstr str2);
int         a_icmp_simple_cstr(a_cstr str1, const char *str2);
int         a_icmp_simple_cstr_cstr(const char *str1, const char *str2);
int         a_icmp_min(a_cstr str1, a_cstr str2);
int         a_icmp_min_cstr(a_cstr str1, const char *str2);
int         a_icmp_min_cstr_cstr(const char *str1, const char *str2);
int         a_icmpn(a_cstr str1, a_cstr str2, size_t n);
int         a_icmpn_cstr(a_cstr str1, const char *str2, size_t n);
int         a_icmpn_cstr_cstr(const char *str1, const char *str2, size_t n);/*
int         a_icmp_canonical(a_cstr str1, a_cstr str2);
int         a_icmp_canonical_cstr(a_cstr str1, const char *str2);
int         a_icmp_canonical_cstr_cstr(const char *str1, const char *str2);
int         a_icmp_compatibility(a_cstr str1, a_cstr str2);
int         a_icmp_compatibility_cstr(a_cstr str1, const char *str2);
int         a_icmp_compatibility_cstr_cstr(const char *str1, const char *str2);
int         a_cmp_wild(const char *str, const char *pattern);
int         a_cmp_regex(const char *str, const char *pattern);
int         a_icmp_wild(const char *str, const char *pattern);
int         a_icmp_regex(const char *str, const char *pattern);*/
/* find */
size_t      a_find(a_cstr str, a_cstr substr);
size_t      a_find_cstr(a_cstr str, const char *substr);
size_t      a_find_cp(a_cstr str, a_cp codepoint);
size_t      a_find_from(a_cstr str, a_cstr substr, size_t index);
size_t      a_find_from_cstr(a_cstr str, const char *substr, size_t index);/*
size_t      a_find_from_cp(a_cstr str, a_cp codepoint, size_t index);*/
size_t      a_find_offset(a_cstr str, a_cstr substr);
size_t      a_find_offset_cstr(a_cstr str, const char *substr);/*
size_t      a_find_offset_cp(a_cstr str, a_cp codepoint);*/
size_t      a_find_offset_from(a_cstr str, a_cstr substr, size_t offset);
size_t      a_find_offset_from_cstr(a_cstr str, const char *substr, size_t offset);/*
size_t      a_find_offset_from_cp(a_cstr str, a_cp codepoint, size_t offset);
size_t      a_rfind(a_cstr str, a_cstr substr);
size_t      a_rfind_cstr(a_cstr str, const char *substr);
size_t      a_rfind_cp(a_cstr str, a_cp codepoint);
size_t      a_rfind_from(a_cstr str, a_cstr substr, size_t index);
size_t      a_rfind_from_cstr(a_cstr str, const char *substr, size_t index);
size_t      a_rfind_from_cp(a_cstr str, a_cp codepoint, size_t index);
size_t      a_rfind_offset(a_cstr str, a_cstr substr);
size_t      a_rfind_offset_cstr(a_cstr str, const char *substr);
size_t      a_rfind_offset_cp(a_cstr str, a_cp codepoint);
size_t      a_rfind_offset_from(a_cstr str, a_cstr substr, size_t offset);
size_t      a_rfind_offset_from_cstr(a_cstr str, const char *substr, size_t offset);
size_t      a_rfind_offset_from_cp(a_cstr str, a_cp codepoint, size_t offset);*/
            /* case insensitive version ... *//*
size_t      a_ifind(a_cstr str, a_cstr substr);
size_t      a_ifind_cstr(a_cstr str, const char *substr);
size_t      a_ifind_cp(a_cstr str, a_cp codepoint);
size_t      a_ifind_from(a_cstr str, a_cstr substr, size_t index);
size_t      a_ifind_from_cstr(a_cstr str, const char *substr, size_t index);
size_t      a_ifind_from_cp(a_cstr str, a_cp codepoint, size_t index);
size_t      a_ifind_offset(a_cstr str, a_cstr substr);
size_t      a_ifind_offset_cstr(a_cstr str, const char *substr);
size_t      a_ifind_offset_cp(a_cstr str, a_cp codepoint);
size_t      a_ifind_offset_from(a_cstr str, a_cstr substr, size_t offset);
size_t      a_ifind_offset_from_cstr(a_cstr str, const char *substr, size_t offset);
size_t      a_ifind_offset_from_cp(a_cstr str, a_cp codepoint, size_t offset);
size_t      a_irfind(a_cstr str, a_cstr substr);
size_t      a_irfind_cstr(a_cstr str, const char *substr);
size_t      a_irfind_cp(a_cstr str, a_cp codepoint);
size_t      a_irfind_from(a_cstr str, a_cstr substr, size_t index);
size_t      a_irfind_from_cstr(a_cstr str, const char *substr, size_t index);
size_t      a_irfind_from_cp(a_cstr str, a_cp codepoint, size_t index);
size_t      a_irfind_offset(a_cstr str, a_cstr substr);
size_t      a_irfind_offset_cstr(a_cstr str, const char *substr);
size_t      a_irfind_offset_cp(a_cstr str, a_cp codepoint);
size_t      a_irfind_offset_from(a_cstr str, a_cstr substr, size_t offset);
size_t      a_irfind_offset_from_cstr(a_cstr str, const char *substr, size_t offset);
size_t      a_irfind_offset_from_cp(a_cstr str, a_cp codepoint, size_t offset);*/
/* starts with */
int         a_startswith(a_cstr str, a_cstr substr);
int         a_startswith_cstr(a_cstr str, const char *substr);
int         a_startswith_norm(a_str str, a_str substr);
int         a_endswith(a_cstr str, a_str substr);
int         a_endswith_cstr(a_cstr str, const char *substr);
int         a_endswith_norm(a_str str, a_str substr);

int         a_istartswith(a_cstr str, a_cstr substr);
int         a_istartswith_cstr(a_cstr str, const char *substr);
int         a_istartswith_norm(a_str str, a_str substr);
int         a_iendswith(a_cstr str, a_str substr);
int         a_iendswith_cstr(a_cstr str, const char *substr);
int         a_iendswith_norm(a_str str, a_str substr);
/* reverse */
a_str       a_reverse(a_str str);
a_str       a_reverse_str(a_str str, a_str output);
/* escape */
a_str       a_escape(a_str str); /* escape '\b', '\f', '\n', '\r', '\t', '\v', '\' and '"'; 0x01-0x1F, and 0x7F-0xFF  */
a_str       a_escape_except(a_str str, const char *except);
a_str       a_unescape(a_str str);
#if 0
#ifdef A_INCLUDE_TOKEN/
/* token/list manipulation (most of those are just convenience variations of the same internal function) */
a_str       a_tok_add(a_str str, a_cstr token, const char *delimiter);
a_str       a_tok_add_cp(a_str str, a_cstr token, a_cp codepoint);
a_str       a_tok_add_cstr(a_str str, const char *token, const char *delimiter);
a_str       a_tok_add_cstr_cp(a_str str, const char *token, a_cp codepoint);
a_str       a_tok_rem(a_str str, a_cstr token, const char *delimiter, size_t nth);
a_str       a_tok_rem_cp(a_str str, a_cstr token, a_cp codepoint, size_t nth);
a_str       a_tok_rem_cstr(a_str str, const char *token, const char *delimiter, size_t nth);
a_str       a_tok_rem_cstr_cp(a_str str, const char *token, a_cp codepoint, size_t nth);
a_str       a_tok_del(a_str str, const char *delimiter, size_t nth);
a_str       a_tok_del_cp(a_str str, a_cp codepoint, size_t nth);
a_str       a_tok_find(a_str str, a_cstr token, const char *delimiter, size_t nth);
a_str       a_tok_find_cp(a_str str, a_cstr token, a_cp codepoint, size_t nth);
a_str       a_tok_find_cstr(a_str str, const char *token, const char *delimiter, size_t nth);
a_str       a_tok_find_cstr_cp(a_str str, const char *token, a_cp codepoint, size_t nth);
a_str       a_tok_get(a_str str, const char *delimiter, size_t nth);
a_str       a_tok_get_cp(a_str str, a_cp codepoint, size_t nth);
a_str       a_tok_len(a_str str, const char *delimiter, size_t nth);
a_str       a_tok_len_cp(a_str str, a_cp codepoint, size_t nth);
a_str       a_tok_ins(a_str str, a_cstr token, const char *delimiter, size_t nth); /* insert as the Nth token */
a_str       a_tok_ins_cp(a_str str, a_cstr token, a_cp codepoint, size_t nth);
a_str       a_tok_ins_cstr(a_str str, const char *token, const char *delimiter, size_t nth);
a_str       a_tok_ins_cstr_cp(a_str str, const char *token, a_cp codepoint, size_t nth);
a_str       a_tok_put(a_str str, a_str token, const char *delimiter, size_t nth);               /* override Nth token */
a_str       a_tok_put_cp(a_str str, a_str token, a_cp codepoint, size_t nth);
a_str       a_tok_put_cstr(a_str str, const char *token, const char *delimiter, size_t nth);
a_str       a_tok_put_cstr_cp(a_str str, const char *token, a_cp codepoint, size_t nth);
a_str       a_tok_rep(a_str str, a_cstr token, a_cstr new_token, a_cp codepoint, size_t nth);      /* replace a token */
a_str       a_tok_rep_cp(a_str str, a_cstr token, a_cstr new_token, const char *delimiter, size_t nth);
a_str       a_tok_rep_cstr(a_str str, a_cstr token, const char *new_token, a_cp codepoint, size_t nth);
a_str       a_tok_rep_cstr_cp(a_str str, a_cstr token, const char *new_token, const char *delimiter, size_t nth);
a_str       a_tok_rep_cstr_cstr(a_str str, const char *token, const char *new_token, a_cp codepoint, size_t nth);
a_str       a_tok_rep_cstr_cstr_cp(a_str str, const char *token, const char *new_token, const char *delimiter, size_t nth);
a_str       a_tok_rem(a_str str, a_cstr token, a_cp codepoint, size_t nth);
a_str       a_tok_rem_cp(a_str str, a_cstr token, const char *delimiter, size_t nth);
a_str       a_tok_rem_cstr(a_str str, const char *token, a_cp codepoint, size_t nth);
a_str       a_tok_rem_cstr_cp(a_str str, const char *token, const char *delimiter, size_t nth);
a_str       a_tok_wild(a_str str, a_cstr pattern, a_cp codepoint, size_t nth);                       /* wildmatch Nth token */
a_str       a_tok_wild_cp(a_str str, a_cstr pattern, const char *delimiter, size_t nth);
a_str       a_tok_wild_cstr(a_str str, const char *pattern, a_cp codepoint, size_t nth);
a_str       a_tok_wild_cstr_cp(a_str str, const char *pattern, const char *delimiter, size_t nth);
a_str       a_tok_cont(a_str str, a_cstr pattern, a_cp codepoint, size_t nth);                       /* match Nth token */
a_str       a_tok_cont_cp(a_str str, a_cstr pattern, const char *delimiter, size_t nth);
a_str       a_tok_cont_cstr(a_str str, const char *pattern, a_cp codepoint, size_t nth);             /* match Nth token */
a_str       a_tok_cont_cstr_cp(a_str str, const char *pattern, const char *delimiter, size_t nth);
a_str       a_tok_sort(a_str str, const char *delimiter, int sort_option);
a_str       a_tok_sort_cp(a_str str, a_cp codepoint, int sort_option);
            /* case insensitive version ... */
a_str       a_tok_i_add(a_str str, a_cstr token, const char *delimiter);
a_str       a_tok_i_add_cp(a_str str, a_cstr token, a_cp codepoint);
a_str       a_tok_i_add_cstr(a_str str, const char *token, const char *delimiter);
a_str       a_tok_i_add_cstr_cp(a_str str, const char *token, a_cp codepoint);
a_str       a_tok_i_rem(a_str str, a_cstr token, const char *delimiter, size_t nth);
a_str       a_tok_i_rem_cp(a_str str, a_cstr token, a_cp codepoint, size_t nth);
a_str       a_tok_i_rem_cstr(a_str str, const char *token, const char *delimiter, size_t nth);
a_str       a_tok_i_rem_cstr_cp(a_str str, const char *token, a_cp codepoint, size_t nth);
a_str       a_tok_i_del(a_str str, const char *delimiter, size_t nth);
a_str       a_tok_i_del_cp(a_str str, a_cp codepoint, size_t nth);
a_str       a_tok_i_find(a_str str, a_cstr token, const char *delimiter, size_t nth);
a_str       a_tok_i_find_cp(a_str str, a_cstr token, a_cp codepoint, size_t nth);
a_str       a_tok_i_find_cstr(a_str str, const char *token, const char *delimiter, size_t nth);
a_str       a_tok_i_find_cstr_cp(a_str str, const char *token, a_cp codepoint, size_t nth);
a_str       a_tok_i_get(a_str str, const char *delimiter, size_t nth);
a_str       a_tok_i_get_cp(a_str str, a_cp codepoint, size_t nth);
a_str       a_tok_i_len(a_str str, const char *delimiter, size_t nth);
a_str       a_tok_i_len_cp(a_str str, a_cp codepoint, size_t nth);
a_str       a_tok_i_ins(a_str str, a_cstr token, const char *delimiter, size_t nth); /* insert as the Nth token */
a_str       a_tok_i_ins_cp(a_str str, a_cstr token, a_cp codepoint, size_t nth);
a_str       a_tok_i_ins_cstr(a_str str, const char *token, const char *delimiter, size_t nth);
a_str       a_tok_i_ins_cstr_cp(a_str str, const char *token, a_cp codepoint, size_t nth);
a_str       a_tok_i_put(a_str str, a_str token, const char *delimiter, size_t nth);               /* override Nth token */
a_str       a_tok_i_put_cp(a_str str, a_str token, a_cp codepoint, size_t nth);
a_str       a_tok_i_put_cstr(a_str str, const char *token, const char *delimiter, size_t nth);
a_str       a_tok_i_put_cstr_cp(a_str str, const char *token, a_cp codepoint, size_t nth);
a_str       a_tok_i_rep(a_str str, a_cstr token, a_cstr new_token, a_cp codepoint, size_t nth);      /* replace a token */
a_str       a_tok_i_rep_cp(a_str str, a_cstr token, a_cstr new_token, const char *delimiter, size_t nth);
a_str       a_tok_i_rep_cstr(a_str str, a_cstr token, const char *new_token, a_cp codepoint, size_t nth);
a_str       a_tok_i_rep_cstr_cp(a_str str, a_cstr token, const char *new_token, const char *delimiter, size_t nth);
a_str       a_tok_i_rep_cstr_cstr(a_str str, const char *token, const char *new_token, a_cp codepoint, size_t nth);
a_str       a_tok_i_rep_cstr_cstr_cp(a_str str, const char *token, const char *new_token, const char *delimiter, size_t nth);
a_str       a_tok_i_rem(a_str str, a_cstr token, a_cp codepoint, size_t nth);
a_str       a_tok_i_rem_cp(a_str str, a_cstr token, const char *delimiter, size_t nth);
a_str       a_tok_i_rem_cstr(a_str str, const char *token, a_cp codepoint, size_t nth);
a_str       a_tok_i_rem_cstr_cp(a_str str, const char *token, const char *delimiter, size_t nth);
a_str       a_tok_i_wild(a_str str, a_cstr pattern, a_cp codepoint, size_t nth);                       /* wildmatch Nth token */
a_str       a_tok_i_wild_cp(a_str str, a_cstr pattern, const char *delimiter, size_t nth);
a_str       a_tok_i_wild_cstr(a_str str, const char *pattern, a_cp codepoint, size_t nth);
a_str       a_tok_i_wild_cstr_cp(a_str str, const char *pattern, const char *delimiter, size_t nth);
a_str       a_tok_i_cont(a_str str, a_cstr pattern, a_cp codepoint, size_t nth);                       /* match Nth token */
a_str       a_tok_i_cont_cp(a_str str, a_cstr pattern, const char *delimiter, size_t nth);
a_str       a_tok_i_cont_cstr(a_str str, const char *pattern, a_cp codepoint, size_t nth);             /* match Nth token */
a_str       a_tok_i_cont_cstr_cp(a_str str, const char *pattern, const char *delimiter, size_t nth);
a_str       a_tok_i_sort(a_str str, const char *delimiter, int sort_option);
a_str       a_tok_i_sort_cp(a_str str, a_cp codepoint, int sort_option);
#endif
#endif
/* file i/o */
#if A_INCLUDE_IO == 1
a_str       a_file_read(FILE *fp);
a_str       a_file_readline(FILE *fp);
a_str       a_file_readline_delim(FILE *fp, const char *delim);
a_str       a_file_readline_delim_str(FILE *fp, const char *delim, a_str str);
size_t      a_file_line_count(FILE *fp);
#endif
#if A_INCLUDE_MEM == 1
a_str       a_gc_collect(a_pool *pool, a_str str);
void        a_gc_free(a_pool pool);
a_pool      a_gc_new();
#define     a_gc a_pool a_tmp_pool = a_gc_new()
#define     a_gc_done() a_gc_free(a_tmp_pool)
#define     a_(s) a_gc_collect(&a_tmp_pool, s)
#define     A_(p, s) a_gc_collect(&p, s)
#endif
/* formatting */
#if ALEPH_C_V == 2
a_str       a_format(a_str str, const char *format, ...);
#endif 
/* to / conersions */
a_cp        a_to_cp(const char *str);
const char *a_to_utf8(a_cp codepoint, char *buffer);
const char *a_to_utf8_size(a_cp codepoint, char *buffer, int *size);
a_str       a_to_upper(a_str str);
a_str       a_to_lower(a_str str);
a_str       a_to_title(a_str str);
a_str       a_to_fold(a_str str);
char       *a_to_fold_cp(a_cp cp, char *b);
a_cp       *a_to_fold_cp_cp(a_cp cp, a_cp *b);
char       *a_to_fold_simple_chr(a_cp cp, char *b);
a_cp        a_to_fold_simple_chr_cp(a_cp cp);
/* categories */
int         a_ascii_is_alpha(a_cp codepoint);
int         a_ascii_is_digit(a_cp codepoint);
int         a_ascii_is_xdigit(a_cp codepoint);
int         a_ascii_is_odigit(a_cp codepoint);
int         a_ascii_is_bdigit(a_cp codepoint);
int         a_ascii_is_alnum(a_cp codepoint);
int         a_ascii_is_blank(a_cp codepoint);
int         a_ascii_is_cntrl(a_cp codepoint);
int         a_ascii_is_graph(a_cp codepoint);
int         a_ascii_is_lower(a_cp codepoint);
int         a_ascii_is_upper(a_cp codepoint);
int         a_ascii_is_print(a_cp codepoint);
int         a_ascii_is_punct(a_cp codepoint);
int         a_ascii_is_space(a_cp codepoint);
int         a_is_alpha(a_cp codepoint);
int         a_is_alphanumeric(a_cp codepoint);
int         a_is_bmp(a_cp codepoint);
int         a_is_control(a_cp codepoint);
int         a_is_currency(a_cp codepoint);
int         a_is_digit(a_cp codepoint);
int         a_is_format(a_cp codepoint);
int         a_is_graphical(a_cp codepoint);
int         a_is_letter(a_cp codepoint);
int         a_is_lower(a_cp codepoint);
int         a_is_mark(a_cp codepoint);
int         a_is_noncharacter(a_cp codepoint);
int         a_is_number(a_cp codepoint);
int         a_is_private_use(a_cp codepoint);
int         a_is_punctuation(a_cp codepoint);
int         a_is_separator(a_cp codepoint);
int         a_is_space(a_cp codepoint);
int         a_is_supplementary(a_cp codepoint);
int         a_is_surrogate(a_cp codepoint);
int         a_is_surrogate_high(a_cp codepoint);
int         a_is_surrogate_low(a_cp codepoint);
int         a_is_symbol(a_cp codepoint);
int         a_is_title(a_cp codepoint);
int         a_is_upper(a_cp codepoint);
int         a_is_math(a_cp codepoint);
int         a_category(a_cp codepoint);
const char *a_category_to_str(int category);
const char *a_category_to_description(int category);
int         a_category_from_str(const char *category);
enum a_general_categories
{
    a_gc_lu                         = 1 << 0 ,
    a_gc_letter_uppercase           = a_gc_lu,
    a_gc_ll                         = 1 << 1 ,
    a_gc_letter_lowercase           = a_gc_ll,
    a_gc_lt                         = 1 << 2 ,
    a_gc_letter_titlecase           = a_gc_lt,
    a_gc_lm                         = 1 << 3 ,
    a_gc_letter_modifier            = a_gc_lm,
    a_gc_lo                         = 1 << 4 ,
    a_gc_letter_other               = a_gc_lo,
    a_gc_mn                         = 1 << 5 ,
    a_gc_mark_nonspacing            = a_gc_mn,
    a_gc_mc                         = 1 << 6 ,
    a_gc_mark_spacing_combining     = a_gc_mc,
    a_gc_me                         = 1 << 7 ,
    a_gc_mark_enclosing             = a_gc_me,
    a_gc_nd                         = 1 << 8 ,
    a_gc_number_decimal_digit       = a_gc_nd,
    a_gc_nl                         = 1 << 9 ,
    a_gc_number_letter              = a_gc_nl,
    a_gc_no                         = 1 << 10,
    a_gc_number_other               = a_gc_no,
    a_gc_pc                         = 1 << 11,
    a_gc_punctuation_connector      = a_gc_pc,
    a_gc_pd                         = 1 << 12,
    a_gc_punctuation_dash           = a_gc_pd,
    a_gc_ps                         = 1 << 13,
    a_gc_punctuation_open           = a_gc_ps,
    a_gc_pe                         = 1 << 14,
    a_gc_punctuation_close          = a_gc_pe,
    a_gc_pi                         = 1 << 15,
    a_gc_punctuation_initial        = a_gc_pi,
    a_gc_pf                         = 1 << 16,
    a_gc_punctuation_final          = a_gc_pf,
    a_gc_po                         = 1 << 17,
    a_gc_punctuation_other          = a_gc_po,
    a_gc_sm                         = 1 << 18,
    a_gc_symbol_math                = a_gc_sm,
    a_gc_sc                         = 1 << 19,
    a_gc_symbol_currency            = a_gc_sc,
    a_gc_sk                         = 1 << 20,
    a_gc_symbol_modifier            = a_gc_sk,
    a_gc_so                         = 1 << 21,
    a_gc_symbol_other               = a_gc_so,
    a_gc_zs                         = 1 << 22,
    a_gc_separator_space            = a_gc_zs,
    a_gc_zl                         = 1 << 23,
    a_gc_separator_line             = a_gc_zl,
    a_gc_zp                         = 1 << 24,
    a_gc_separator_paragraph        = a_gc_zp,
    a_gc_cc                         = 1 << 25,
    a_gc_other_control              = a_gc_cc,
    a_gc_cf                         = 1 << 26,
    a_gc_other_format               = a_gc_cf,
    a_gc_cs                         = 1 << 27,
    a_gc_other_surrogate            = a_gc_cs,
    a_gc_co                         = 1 << 28,
    a_gc_other_private_use          = a_gc_co,
    a_gc_cn                         = 1 << 29,
    a_gc_other_not_assigned         = a_gc_cn,
    /* derived categories */
    a_gc_alpha          = a_gc_lu|a_gc_ll|a_gc_lt|a_gc_lm|a_gc_lo,
    a_gc_alphanumeric   = a_gc_lu|a_gc_ll|a_gc_lt|a_gc_lm|a_gc_lo|a_gc_nd|a_gc_nl|a_gc_no,
    a_gc_graphical      = a_gc_lu|a_gc_ll|a_gc_lt|a_gc_lm|a_gc_lo|a_gc_mn|a_gc_mc|a_gc_me|a_gc_nd|a_gc_nl|a_gc_no|a_gc_pc|a_gc_pd|a_gc_ps|a_gc_pe|a_gc_pi|a_gc_pf|a_gc_po|a_gc_sm|a_gc_sc|a_gc_sk|a_gc_so|a_gc_zs|a_gc_zl|a_gc_zp,
    a_gc_letter         = a_gc_lu|a_gc_ll|a_gc_lt|a_gc_lm|a_gc_lo,
    a_gc_mark           = a_gc_mn|a_gc_mc|a_gc_me,
    a_gc_number         = a_gc_nd|a_gc_nl|a_gc_no,
    a_gc_punctuation    = a_gc_pc|a_gc_pd|a_gc_ps|a_gc_pe|a_gc_pi|a_gc_pf|a_gc_po,
    a_gc_separator      = a_gc_zs|a_gc_zl|a_gc_zp
};
/* blocks */
a_cp        a_block_start(int block);
a_cp        a_block_end(int block);
a_cp        a_block_size(int block);
const char *a_block_name(int block);
const char *a_block_name_cp(a_cp codepoint);
int         a_block_cp(a_cp codepoint);
enum a_blocks
{
        a_block_basic_latin                                        = 0,
        a_block_latin_1_supplement                                 = 1,
        a_block_latin_extended_a                                   = 2,
        a_block_latin_extended_b                                   = 3,
        a_block_ipa_extensions                                     = 4,
        a_block_spacing_modifier_letters                           = 5,
        a_block_combining_diacritical_marks                        = 6,
        a_block_greek_and_coptic                                   = 7,
        a_block_cyrillic                                           = 8,
        a_block_cyrillic_supplement                                = 9,
        a_block_armenian                                           = 10,
        a_block_hebrew                                             = 11,
        a_block_arabic                                             = 12,
        a_block_syriac                                             = 13,
        a_block_arabic_supplement                                  = 14,
        a_block_thaana                                             = 15,
        a_block_nko                                                = 16,
        a_block_samaritan                                          = 17,
        a_block_mandaic                                            = 18,
        a_block_arabic_extended_a                                  = 19,
        a_block_devanagari                                         = 20,
        a_block_bengali                                            = 21,
        a_block_gurmukhi                                           = 22,
        a_block_gujarati                                           = 23,
        a_block_oriya                                              = 24,
        a_block_tamil                                              = 25,
        a_block_telugu                                             = 26,
        a_block_kannada                                            = 27,
        a_block_malayalam                                          = 28,
        a_block_sinhala                                            = 29,
        a_block_thai                                               = 30,
        a_block_lao                                                = 31,
        a_block_tibetan                                            = 32,
        a_block_myanmar                                            = 33,
        a_block_georgian                                           = 34,
        a_block_hangul_jamo                                        = 35,
        a_block_ethiopic                                           = 36,
        a_block_ethiopic_supplement                                = 37,
        a_block_cherokee                                           = 38,
        a_block_unified_canadian_aboriginal_syllabics              = 39,
        a_block_ogham                                              = 40,
        a_block_runic                                              = 41,
        a_block_tagalog                                            = 42,
        a_block_hanunoo                                            = 43,
        a_block_buhid                                              = 44,
        a_block_tagbanwa                                           = 45,
        a_block_khmer                                              = 46,
        a_block_mongolian                                          = 47,
        a_block_unified_canadian_aboriginal_syllabics_extended     = 48,
        a_block_limbu                                              = 49,
        a_block_tai_le                                             = 50,
        a_block_new_tai_lue                                        = 51,
        a_block_khmer_symbols                                      = 52,
        a_block_buginese                                           = 53,
        a_block_tai_tham                                           = 54,
        a_block_combining_diacritical_marks_extended               = 55,
        a_block_balinese                                           = 56,
        a_block_sundanese                                          = 57,
        a_block_batak                                              = 58,
        a_block_lepcha                                             = 59,
        a_block_ol_chiki                                           = 60,
        a_block_sundanese_supplement                               = 61,
        a_block_vedic_extensions                                   = 62,
        a_block_phonetic_extensions                                = 63,
        a_block_phonetic_extensions_supplement                     = 64,
        a_block_combining_diacritical_marks_supplement             = 65,
        a_block_latin_extended_additional                          = 66,
        a_block_greek_extended                                     = 67,
        a_block_general_punctuation                                = 68,
        a_block_superscripts_and_subscripts                        = 69,
        a_block_currency_symbols                                   = 70,
        a_block_combining_diacritical_marks_for_symbols            = 71,
        a_block_letterlike_symbols                                 = 72,
        a_block_number_forms                                       = 73,
        a_block_arrows                                             = 74,
        a_block_mathematical_operators                             = 75,
        a_block_miscellaneous_technical                            = 76,
        a_block_control_pictures                                   = 77,
        a_block_optical_character_recognition                      = 78,
        a_block_enclosed_alphanumerics                             = 79,
        a_block_box_drawing                                        = 80,
        a_block_block_elements                                     = 81,
        a_block_geometric_shapes                                   = 82,
        a_block_miscellaneous_symbols                              = 83,
        a_block_dingbats                                           = 84,
        a_block_miscellaneous_mathematical_symbols_a               = 85,
        a_block_supplemental_arrows_a                              = 86,
        a_block_braille_patterns                                   = 87,
        a_block_supplemental_arrows_b                              = 88,
        a_block_miscellaneous_mathematical_symbols_b               = 89,
        a_block_supplemental_mathematical_operators                = 90,
        a_block_miscellaneous_symbols_and_arrows                   = 91,
        a_block_glagolitic                                         = 92,
        a_block_latin_extended_c                                   = 93,
        a_block_coptic                                             = 94,
        a_block_georgian_supplement                                = 95,
        a_block_tifinagh                                           = 96,
        a_block_ethiopic_extended                                  = 97,
        a_block_cyrillic_extended_a                                = 98,
        a_block_supplemental_punctuation                           = 99,
        a_block_cjk_radicals_supplement                            = 100,
        a_block_kangxi_radicals                                    = 101,
        a_block_ideographic_description_characters                 = 102,
        a_block_cjk_symbols_and_punctuation                        = 103,
        a_block_hiragana                                           = 104,
        a_block_katakana                                           = 105,
        a_block_bopomofo                                           = 106,
        a_block_hangul_compatibility_jamo                          = 107,
        a_block_kanbun                                             = 108,
        a_block_bopomofo_extended                                  = 109,
        a_block_cjk_strokes                                        = 110,
        a_block_katakana_phonetic_extensions                       = 111,
        a_block_enclosed_cjk_letters_and_months                    = 112,
        a_block_cjk_compatibility                                  = 113,
        a_block_cjk_unified_ideographs_extension_a                 = 114,
        a_block_yijing_hexagram_symbols                            = 115,
        a_block_cjk_unified_ideographs                             = 116,
        a_block_yi_syllables                                       = 117,
        a_block_yi_radicals                                        = 118,
        a_block_lisu                                               = 119,
        a_block_vai                                                = 120,
        a_block_cyrillic_extended_b                                = 121,
        a_block_bamum                                              = 122,
        a_block_modifier_tone_letters                              = 123,
        a_block_latin_extended_d                                   = 124,
        a_block_syloti_nagri                                       = 125,
        a_block_common_indic_number_forms                          = 126,
        a_block_phags_pa                                           = 127,
        a_block_saurashtra                                         = 128,
        a_block_devanagari_extended                                = 129,
        a_block_kayah_li                                           = 130,
        a_block_rejang                                             = 131,
        a_block_hangul_jamo_extended_a                             = 132,
        a_block_javanese                                           = 133,
        a_block_myanmar_extended_b                                 = 134,
        a_block_cham                                               = 135,
        a_block_myanmar_extended_a                                 = 136,
        a_block_tai_viet                                           = 137,
        a_block_meetei_mayek_extensions                            = 138,
        a_block_ethiopic_extended_a                                = 139,
        a_block_latin_extended_e                                   = 140,
        a_block_meetei_mayek                                       = 141,
        a_block_hangul_syllables                                   = 142,
        a_block_hangul_jamo_extended_b                             = 143,
        a_block_high_surrogates                                    = 144,
        a_block_high_private_use_surrogates                        = 145,
        a_block_low_surrogates                                     = 146,
        a_block_private_use_area                                   = 147,
        a_block_cjk_compatibility_ideographs                       = 148,
        a_block_alphabetic_presentation_forms                      = 149,
        a_block_arabic_presentation_forms_a                        = 150,
        a_block_variation_selectors                                = 151,
        a_block_vertical_forms                                     = 152,
        a_block_combining_half_marks                               = 153,
        a_block_cjk_compatibility_forms                            = 154,
        a_block_small_form_variants                                = 155,
        a_block_arabic_presentation_forms_b                        = 156,
        a_block_halfwidth_and_fullwidth_forms                      = 157,
        a_block_specials                                           = 158,
        a_block_linear_b_syllabary                                 = 159,
        a_block_linear_b_ideograms                                 = 160,
        a_block_aegean_numbers                                     = 161,
        a_block_ancient_greek_numbers                              = 162,
        a_block_ancient_symbols                                    = 163,
        a_block_phaistos_disc                                      = 164,
        a_block_lycian                                             = 165,
        a_block_carian                                             = 166,
        a_block_coptic_epact_numbers                               = 167,
        a_block_old_italic                                         = 168,
        a_block_gothic                                             = 169,
        a_block_old_permic                                         = 170,
        a_block_ugaritic                                           = 171,
        a_block_old_persian                                        = 172,
        a_block_deseret                                            = 173,
        a_block_shavian                                            = 174,
        a_block_osmanya                                            = 175,
        a_block_elbasan                                            = 176,
        a_block_caucasian_albanian                                 = 177,
        a_block_linear_a                                           = 178,
        a_block_cypriot_syllabary                                  = 179,
        a_block_imperial_aramaic                                   = 180,
        a_block_palmyrene                                          = 181,
        a_block_nabataean                                          = 182,
        a_block_phoenician                                         = 183,
        a_block_lydian                                             = 184,
        a_block_meroitic_hieroglyphs                               = 185,
        a_block_meroitic_cursive                                   = 186,
        a_block_kharoshthi                                         = 187,
        a_block_old_south_arabian                                  = 188,
        a_block_old_north_arabian                                  = 189,
        a_block_manichaean                                         = 190,
        a_block_avestan                                            = 191,
        a_block_inscriptional_parthian                             = 192,
        a_block_inscriptional_pahlavi                              = 193,
        a_block_psalter_pahlavi                                    = 194,
        a_block_old_turkic                                         = 195,
        a_block_rumi_numeral_symbols                               = 196,
        a_block_brahmi                                             = 197,
        a_block_kaithi                                             = 198,
        a_block_sora_sompeng                                       = 199,
        a_block_chakma                                             = 200,
        a_block_mahajani                                           = 201,
        a_block_sharada                                            = 202,
        a_block_sinhala_archaic_numbers                            = 203,
        a_block_khojki                                             = 204,
        a_block_khudawadi                                          = 205,
        a_block_grantha                                            = 206,
        a_block_tirhuta                                            = 207,
        a_block_siddham                                            = 208,
        a_block_modi                                               = 209,
        a_block_takri                                              = 210,
        a_block_warang_citi                                        = 211,
        a_block_pau_cin_hau                                        = 212,
        a_block_cuneiform                                          = 213,
        a_block_cuneiform_numbers_and_punctuation                  = 214,
        a_block_egyptian_hieroglyphs                               = 215,
        a_block_bamum_supplement                                   = 216,
        a_block_mro                                                = 217,
        a_block_bassa_vah                                          = 218,
        a_block_pahawh_hmong                                       = 219,
        a_block_miao                                               = 220,
        a_block_kana_supplement                                    = 221,
        a_block_duployan                                           = 222,
        a_block_shorthand_format_controls                          = 223,
        a_block_byzantine_musical_symbols                          = 224,
        a_block_musical_symbols                                    = 225,
        a_block_ancient_greek_musical_notation                     = 226,
        a_block_tai_xuan_jing_symbols                              = 227,
        a_block_counting_rod_numerals                              = 228,
        a_block_mathematical_alphanumeric_symbols                  = 229,
        a_block_mende_kikakui                                      = 230,
        a_block_arabic_mathematical_alphabetic_symbols             = 231,
        a_block_mahjong_tiles                                      = 232,
        a_block_domino_tiles                                       = 233,
        a_block_playing_cards                                      = 234,
        a_block_enclosed_alphanumeric_supplement                   = 235,
        a_block_enclosed_ideographic_supplement                    = 236,
        a_block_miscellaneous_symbols_and_pictographs              = 237,
        a_block_emoticons                                          = 238,
        a_block_ornamental_dingbats                                = 239,
        a_block_transport_and_map_symbols                          = 240,
        a_block_alchemical_symbols                                 = 241,
        a_block_geometric_shapes_extended                          = 242,
        a_block_supplemental_arrows_c                              = 243,
        a_block_cjk_unified_ideographs_extension_b                 = 244,
        a_block_cjk_unified_ideographs_extension_c                 = 245,
        a_block_cjk_unified_ideographs_extension_d                 = 246,
        a_block_cjk_compatibility_ideographs_supplement            = 247,
        a_block_tags                                               = 248,
        a_block_variation_selectors_supplement                     = 249,
        a_block_supplementary_private_use_area_a                   = 250,
        a_block_supplementary_private_use_area_b                   = 251,
        a_block_count
};

/* Normalization Forms */
a_str       a_normalize(a_str str, int mode);
a_str       a_normalize_cstr(const char *str, int mode);
a_str       a_new_normalize(a_cstr str, int mode); /* also declared above */
int         a_is_quick_normalized(a_str str, int mode);
enum a_normalization_forms
{
    a_norm_nfc,  /* Canonical decomposition followed by canonical composition.     */
    a_norm_nfd,  /* Canonical decomposition.                                       */
    a_norm_nfkc, /* Compatibility decomposition followed by canonical composition. */
    a_norm_nfkd  /* Compatibility decomposition. */
};
enum a_normalization_forms_quick_check
{
    a_norm_yes,
    a_norm_no,
    a_norm_maybe
};
/* hash */
unsigned long   a_hash(a_cstr str);
unsigned int    a_crc32(a_cstr str);
/* version */
const char     *a_unicode_version(void);
const char     *a_unicode_version_reference(void);
const char     *a_unicode_version_url(void);
#ifdef A_INCLUDE_NAMES
/**
 * \brief Size for a buffer large enough to store
 *        any Unicode character name.
 */
#   define A_NAME_MAX_SIZE 100
char       *a_name_cp(a_cp codepoint, char *buff);
#endif


/*
 * 
 * 
 * 
 */
struct a_header
{
    size_t len;  /* length (in codepoints)          */
    size_t size; /* size (in bytes)                 */
    size_t mem;  /* mem size                        */
    #ifdef A_ITERATOR
    char *it;    /* pointer to the current char     */
    #endif
};


#define a_buff(b) ((char*)b + sizeof (struct a_header))
#define a_header(b) ((struct a_header*)((char*)b - sizeof (struct a_header)))
