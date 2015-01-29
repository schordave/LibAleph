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
#include "ctest.h"
#include "aleph.h"

CTEST(Categories, check_block_greek)
{
    a_cp cp;
    
    for (cp = 0x0370; cp <= 0x03FF; ++cp)
    {
        ASSERT_EQUAL(a_block_greek_and_coptic, a_block_cp(cp));
        ASSERT_EQUAL(0x0370, a_block_start(a_block_cp(cp)));
        ASSERT_EQUAL(0x03FF, a_block_end(a_block_cp(cp)));
        ASSERT_EQUAL(0x03FF-0x0370+1, a_block_size(a_block_cp(cp)));
        ASSERT_EQUAL(0, a_icmp_cstr_cstr(a_block_name_cp(cp), "Greek and Coptic"));
    }
}

CTEST(Categories, check_block_hebrew)
{
    a_cp cp;
    
    for (cp = 0x0590; cp <= 0x05FF; ++cp)
    {
        ASSERT_EQUAL(a_block_hebrew, a_block_cp(cp));
        ASSERT_EQUAL(0x0590, a_block_start(a_block_cp(cp)));
        ASSERT_EQUAL(0x05FF, a_block_end(a_block_cp(cp)));
        ASSERT_EQUAL(0x05FF-0x0590+1, a_block_size(a_block_cp(cp)));
        ASSERT_EQUAL(0, a_icmp_cstr_cstr(a_block_name_cp(cp), "Hebrew"));
    }
}



CTEST(Categories, check_block_arabic)
{
    a_cp cp;
    
    for (cp = 0x0600; cp <= 0x06FF; ++cp)
    {
        ASSERT_EQUAL(a_block_arabic, a_block_cp(cp));
        ASSERT_EQUAL(0x0600, a_block_start(a_block_cp(cp)));
        ASSERT_EQUAL(0x06FF, a_block_end(a_block_cp(cp)));
        ASSERT_EQUAL(0x06FF-0x0600+1, a_block_size(a_block_cp(cp)));
        ASSERT_EQUAL(0, a_icmp_cstr_cstr(a_block_name_cp(cp), "Arabic"));
    }
}
