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

CTEST(Reversal, check_reversal)
{ 
    a_str a, b;
    a_gc;
    
    a = a_(a_reverse(a_new("")));
    ASSERT_EQUAL(0, *a);
    
    a = a_(a_reverse(a_new("a")));
    ASSERT_EQUAL(0, strcmp(a, "a"));
    
    a = a_(a_reverse(a_new("aa")));
    ASSERT_EQUAL(0, strcmp(a, "aa"));
    
    a = a_(a_reverse(a_new("ΑαΒβΓγΔδΕεΖζΗηΘθΙιΚκΛλΜμΝνΞξΟοΠπΡρΣσΤτΥυΦφΧχΨψΩω")));
    ASSERT_EQUAL(0, strcmp(a, "ωΩψΨχΧφΦυΥτΤσΣρΡπΠοΟξΞνΝμΜλΛκΚιΙθΘηΗζΖεΕδΔγΓβΒαΑ"));
    
    a = a_(a_reverse(a_new("अइउऋऌएओआईऊॠॡऐऔ")));
    ASSERT_EQUAL(0, strcmp(a, "औऐॡॠऊईआओएऌऋउइअ"));
    
    a = a_(a_reverse(a_new("❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃")));
    ASSERT_EQUAL(0, strcmp(a, "☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄"));
    
    a = a_(a_reverse_new(a_(a_new(""))));
    ASSERT_EQUAL(0, *a);
    
    a = a_(a_reverse_new(a_(a_new("a"))));
    ASSERT_EQUAL(0, strcmp(a, "a"));
    
    a = a_(a_reverse_new(a_(a_new("ΑαΒβΓγΔδΕεΖζΗηΘθΙιΚκΛλΜμΝνΞξΟοΠπΡρΣσΤτΥυΦφΧχΨψΩω"))));
    ASSERT_EQUAL(0, strcmp(a, "ωΩψΨχΧφΦυΥτΤσΣρΡπΠοΟξΞνΝμΜλΛκΚιΙθΘηΗζΖεΕδΔγΓβΒαΑ"));
    
    a = a_(a_reverse_new(a_(a_new("अइउऋऌएओआईऊॠॡऐऔ"))));
    ASSERT_EQUAL(0, strcmp(a, "औऐॡॠऊईआओएऌऋउइअ"));
    
    a = a_(a_reverse_new(a_(a_new("❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃"))));
    ASSERT_EQUAL(0, strcmp(a, "☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄"));
    
    b = a_new(NULL);
    b = a_(a_reverse_str(a_(a_new("❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃")), b));
    ASSERT_EQUAL(0, strcmp(b, "☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄☃❄"));

    b = a_new(NULL);
    b = a_(a_reverse_str(a_(a_new("अइउऋऌएओआईऊॠॡऐऔ")), b));
    ASSERT_EQUAL(0, strcmp(b, "औऐॡॠऊईआओएऌऋउइअ"));

    b = a_new(NULL);
    b = a_(a_reverse_str(a_(a_new("")), b));
    ASSERT_EQUAL(0, *b);
    
    b = a_new(NULL);
    b = a_(a_reverse_str(a_(a_new("a")), b));
    ASSERT_EQUAL(0, strcmp(b, "a"));
    
    a_gc_done();
}