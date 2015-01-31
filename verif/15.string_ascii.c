/*
 * Copyright (c) 2006-2015 David Schor (davidschor@zigwap.com), ZigWap LLC
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
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include "ctest.h"
#include "aleph.h"

CTEST(ASCII, check_ascii_is)
{ 
    a_cp cp;
    
    for (cp = A_MIN_CP; cp <= A_MAX_CP; ++cp)
    {
        if (cp < 128)
        {
            if (isalpha(cp)) ASSERT_TRUE(a_ascii_is_alpha(cp));
            if (isdigit(cp)) ASSERT_TRUE(a_ascii_is_digit(cp));
            if (isxdigit(cp)) ASSERT_TRUE(a_ascii_is_xdigit(cp));
            if (cp <= '7' && cp >= '0') ASSERT_TRUE(a_ascii_is_odigit(cp));
            if (cp <= '1' && cp >= '0') ASSERT_TRUE(a_ascii_is_bdigit(cp));
            if (isalnum(cp)) ASSERT_TRUE(a_ascii_is_alnum(cp));
            if (isblank(cp)) ASSERT_TRUE(a_ascii_is_blank(cp));
            if (iscntrl(cp)) ASSERT_TRUE(a_ascii_is_cntrl(cp));
            if (isgraph(cp)) ASSERT_TRUE(a_ascii_is_graph(cp));
            if (islower(cp)) ASSERT_TRUE(a_ascii_is_lower(cp));
            if (isupper(cp)) ASSERT_TRUE(a_ascii_is_upper(cp));
            if (isprint(cp)) ASSERT_TRUE(a_ascii_is_print(cp));
            if (ispunct(cp)) ASSERT_TRUE(a_ascii_is_punct(cp));
            if (isspace(cp)) ASSERT_TRUE(a_ascii_is_space(cp));
        }
        else
        {
            ASSERT_FALSE(a_ascii_is_alpha(cp));
            ASSERT_FALSE(a_ascii_is_digit(cp));
            ASSERT_FALSE(a_ascii_is_xdigit(cp));
            ASSERT_FALSE(a_ascii_is_odigit(cp));
            ASSERT_FALSE(a_ascii_is_bdigit(cp));
            ASSERT_FALSE(a_ascii_is_alnum(cp));
            ASSERT_FALSE(a_ascii_is_blank(cp));
            ASSERT_FALSE(a_ascii_is_cntrl(cp));
            ASSERT_FALSE(a_ascii_is_graph(cp));
            ASSERT_FALSE(a_ascii_is_lower(cp));
            ASSERT_FALSE(a_ascii_is_upper(cp));
            ASSERT_FALSE(a_ascii_is_print(cp));
            ASSERT_FALSE(a_ascii_is_punct(cp));
            ASSERT_FALSE(a_ascii_is_space(cp));
        }
    }
}