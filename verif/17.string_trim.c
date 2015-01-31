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
#include <string.h>
#include "ctest.h"
#include "aleph.h"

CTEST(Trimming, check_trim_left)
{ 
    a_str a;
    a_gc;
    
    a = a_trim_left(a_(a_new("")));
    ASSERT_EQUAL(0, a_len(a));
    ASSERT_EQUAL(0, a_size(a));
    
    a = a_trim_left(a_(a_new("                   ")));
    ASSERT_EQUAL(0, a_len(a));
    ASSERT_EQUAL(0, a_size(a));
    
    a = a_trim_left(a_(a_new("                   a")));
    ASSERT_EQUAL(1, a_len(a));
    ASSERT_EQUAL(1, a_size(a));
    
    a = a_trim_left(a_(a_new("                   Ⓐ")));
    ASSERT_EQUAL(1, a_len(a));
    ASSERT_EQUAL(3, a_size(a));
    ASSERT_EQUAL(0, strcmp(a, "Ⓐ"));
    
    a = a_trim_left_cstr(a_(a_new("                   a")), " ");
    ASSERT_EQUAL(1, a_len(a));
    ASSERT_EQUAL(1, a_size(a));
    
    a = a_trim_left_cstr(a_(a_new("ⒶⒶⒶⒶⒶⒶⒶⒶⒶⒶⒶⒶa")), "Ⓐ");
    ASSERT_EQUAL(1, a_len(a));
    ASSERT_EQUAL(1, a_size(a));
    
    a = a_trim_left_cstr(a_(a_new("ⒷⒶⒷⒶⒷⒶⒷ")), "ⒶⒷ");
    ASSERT_EQUAL(0, a_len(a));
    ASSERT_EQUAL(0, a_size(a));
    ASSERT_EQUAL(0, *a);
    
    a = a_trim_left_cstr(a_(a_new("ⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶ")), "ⒶⒷ");
    ASSERT_EQUAL(0, a_len(a));
    ASSERT_EQUAL(0, a_size(a));
    ASSERT_EQUAL(0, *a);
    
    a = a_trim_left_cstr(a_(a_new(" Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ ")), "Ⓐ Ⓑ");
    ASSERT_EQUAL(0, a_len(a));
    ASSERT_EQUAL(0, a_size(a));
    ASSERT_EQUAL(0, *a);
    
    a = a_trim_left_cstr(a_(a_new("ⒷⒶⒷⒶⒷⒶⒷⒸ")), "ⒶⒷ");
    ASSERT_EQUAL(1, a_len(a));
    ASSERT_EQUAL(3, a_size(a));
    
    
    a_gc_done();
}


CTEST(Trimming, check_trim_right)
{ 
    a_str a;
    a_gc;
    
    a = a_trim_right(a_(a_new("")));
    ASSERT_EQUAL(0, a_len(a));
    ASSERT_EQUAL(0, a_size(a));
    
    a = a_trim_right(a_(a_new("                   ")));
    ASSERT_EQUAL(0, a_len(a));
    ASSERT_EQUAL(0, a_size(a));
    
    a = a_trim_right(a_(a_new("a                   ")));
    ASSERT_EQUAL(1, a_len(a));
    ASSERT_EQUAL(1, a_size(a));
    
    a = a_trim_right(a_(a_new("Ⓐ                   ")));
    ASSERT_EQUAL(1, a_len(a));
    ASSERT_EQUAL(3, a_size(a));
    ASSERT_EQUAL(0, strcmp(a, "Ⓐ"));
    
    a = a_trim_right_cstr(a_(a_new("a                   ")), " ");
    ASSERT_EQUAL(1, a_len(a));
    ASSERT_EQUAL(1, a_size(a));
    
    a = a_trim_right_cstr(a_(a_new("aⒶⒶⒶⒶⒶⒶⒶⒶⒶⒶⒶⒶ")), "Ⓐ");
    ASSERT_EQUAL(1, a_len(a));
    ASSERT_EQUAL(1, a_size(a));
    
    a = a_trim_right_cstr(a_(a_new("ⒷⒶⒷⒶⒷⒶⒷ")), "ⒶⒷ");
    ASSERT_EQUAL(0, a_len(a));
    ASSERT_EQUAL(0, a_size(a));
    ASSERT_EQUAL(0, *a);
    
    a = a_trim_right_cstr(a_(a_new("ⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶ")), "ⒶⒷ");
    ASSERT_EQUAL(0, a_len(a));
    ASSERT_EQUAL(0, a_size(a));
    ASSERT_EQUAL(0, *a);
    
    a = a_trim_right_cstr(a_(a_new(" Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ ")), "Ⓐ Ⓑ");
    ASSERT_EQUAL(0, a_len(a));
    ASSERT_EQUAL(0, a_size(a));
    ASSERT_EQUAL(0, *a);
    
    a = a_trim_right_cstr(a_(a_new("ⒸⒷⒶⒷⒶⒷⒶⒷ")), "ⒶⒷ");
    ASSERT_EQUAL(1, a_len(a));
    ASSERT_EQUAL(3, a_size(a));
    
    
    a_gc_done();
}


CTEST(Trimming, check_trim)
{ 
    a_str a;
    a_gc;
    
    a = a_trim(a_(a_new("")));
    ASSERT_EQUAL(0, a_len(a));
    ASSERT_EQUAL(0, a_size(a));
    
    a = a_trim(a_(a_new("                   ")));
    ASSERT_EQUAL(0, a_len(a));
    ASSERT_EQUAL(0, a_size(a));
    
    a = a_trim(a_(a_new("          a         ")));
    ASSERT_EQUAL(1, a_len(a));
    ASSERT_EQUAL(1, a_size(a));
    
    a = a_trim(a_(a_new("         Ⓐ          ")));
    ASSERT_EQUAL(1, a_len(a));
    ASSERT_EQUAL(3, a_size(a));
    ASSERT_EQUAL(0, strcmp(a, "Ⓐ"));
    
    a = a_trim_cstr(a_(a_new("        a           ")), " ");
    ASSERT_EQUAL(1, a_len(a));
    ASSERT_EQUAL(1, a_size(a));
    
    a = a_trim_cstr(a_(a_new("ⒶⒶⒶⒶⒶⒶaⒶⒶⒶⒶⒶⒶ")), "Ⓐ");
    ASSERT_EQUAL(1, a_len(a));
    ASSERT_EQUAL(1, a_size(a));
    
    a = a_trim_cstr(a_(a_new("ⒷⒶⒷⒶⒷⒶⒷ")), "ⒶⒷ");
    ASSERT_EQUAL(0, a_len(a));
    ASSERT_EQUAL(0, a_size(a));
    ASSERT_EQUAL(0, *a);
    
    a = a_trim_cstr(a_(a_new("ⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶⒷⒶ")), "ⒶⒷ");
    ASSERT_EQUAL(0, a_len(a));
    ASSERT_EQUAL(0, a_size(a));
    ASSERT_EQUAL(0, *a);
    
    a = a_trim_cstr(a_(a_new(" Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ  Ⓑ Ⓐ Ⓑ Ⓐ Ⓑ Ⓐ ")), "Ⓐ Ⓑ");
    ASSERT_EQUAL(0, a_len(a));
    ASSERT_EQUAL(0, a_size(a));
    ASSERT_EQUAL(0, *a);
    
    a = a_trim_cstr(a_(a_new("ⒷⒶⒷⒸⒶⒷⒶⒷ")), "ⒶⒷ");
    ASSERT_EQUAL(1, a_len(a));
    ASSERT_EQUAL(3, a_size(a));
    
    
    a_gc_done();
}