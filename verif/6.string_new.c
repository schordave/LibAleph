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

CTEST(Creation, check_new)
{
    a_str a, b, c, d, e, f, g, h, i, j;
    
    a = a_new("happy birthday");
    b = a_new("Ծնունդդ շնորհավոր");
    c = a_new("ᎤᎵᎮᎵᏍᏗ ᏂᏣᏕᏘᏯ");
    d = a_new("生日快樂");
    e = a_new("عيد ميلاد سعيد");
    f = a_new("Bonne fête");
    g = a_new("जन्मदिन मुबारक हो");
    h = a_new("יום הולדת שמח");
    i = a_new("¡feliz cumpleaños!");
    j = a_new("జన్మదిన శుభాకాంక్షలు");
    
    ASSERT_EQUAL(14, a_len(a));
    ASSERT_EQUAL(17, a_len(b));
    ASSERT_EQUAL(12, a_len(c));
    ASSERT_EQUAL(4, a_len(d));
    ASSERT_EQUAL(14, a_len(e));
    ASSERT_EQUAL(10, a_len(f));
    ASSERT_EQUAL(17, a_len(g));
    ASSERT_EQUAL(13, a_len(h));
    ASSERT_EQUAL(18, a_len(i));
    ASSERT_EQUAL(20, a_len(j));
    
    ASSERT_EQUAL(14, a_size(a));
    ASSERT_EQUAL(16*2+1, a_size(b));
    ASSERT_EQUAL(11*3+1, a_size(c));
    ASSERT_EQUAL(4*3, a_size(d));
    ASSERT_EQUAL(12*2+2, a_size(e));
    ASSERT_EQUAL(11, a_size(f));
    ASSERT_EQUAL(15*3+2, a_size(g));
    ASSERT_EQUAL(11*2+2, a_size(h));
    ASSERT_EQUAL(20, a_size(i));
    ASSERT_EQUAL(19*3+1, a_size(j));
    
    a_free_n(a, b, c, d, e, f, g, h, i, j, NULL);
}

CTEST(Creation, check_new_len)
{
    a_str a, b, c, d, e, f, g, h, i, j;
    
    a = a_new_len("happy birthday", 5);
    b = a_new_len("Ծնունդդ շնորհավոր", 14);
    c = a_new_len("ᎤᎵᎮᎵᏍᏗ ᏂᏣᏕᏘᏯ", 18);
    d = a_new_len("生日快樂", 6);
    e = a_new_len("عيد ميلاد سعيد", 6);
    f = a_new_len("Bonne fête", 5);
    g = a_new_len("जन्मदिन मुबारक हो", 21);
    h = a_new_len("יום הולדת שמח", 6);
    i = a_new_len("¡feliz cumpleaños!", 7);
    j = a_new_len("జన్మదిన శుభాకాంక్షలు", 21);
    
    ASSERT_EQUAL(5, a_len(a));
    ASSERT_EQUAL(7, a_len(b));
    ASSERT_EQUAL(6, a_len(c));
    ASSERT_EQUAL(2, a_len(d));
    ASSERT_EQUAL(3, a_len(e));
    ASSERT_EQUAL(5, a_len(f));
    ASSERT_EQUAL(7, a_len(g));
    ASSERT_EQUAL(3, a_len(h));
    ASSERT_EQUAL(6, a_len(i));
    ASSERT_EQUAL(7, a_len(j));
    
    ASSERT_EQUAL(5, a_size(a));
    ASSERT_EQUAL(14, a_size(b));
    ASSERT_EQUAL(18, a_size(c));
    ASSERT_EQUAL(6, a_size(d));
    ASSERT_EQUAL(6, a_size(e));
    ASSERT_EQUAL(5, a_size(f));
    ASSERT_EQUAL(21, a_size(g));
    ASSERT_EQUAL(6, a_size(h));
    ASSERT_EQUAL(7, a_size(i));
    ASSERT_EQUAL(21, a_size(j));
    
    ASSERT_EQUAL(0, strcmp(a, "happy"));
    ASSERT_EQUAL(0, strcmp(b, "Ծնունդդ"));
    ASSERT_EQUAL(0, strcmp(c, "ᎤᎵᎮᎵᏍᏗ"));
    ASSERT_EQUAL(0, strcmp(d, "生日"));
    ASSERT_EQUAL(0, strcmp(e, "عيد"));
    ASSERT_EQUAL(0, strcmp(f, "Bonne"));
    ASSERT_EQUAL(0, strcmp(g, "जन्मदिन"));
    ASSERT_EQUAL(0, strcmp(h, "יום"));
    ASSERT_EQUAL(0, strcmp(i, "¡feliz"));
    ASSERT_EQUAL(0, strcmp(j, "జన్మదిన"));
    
    a_free_n(a, b, c, d, e, f, g, h, i, j, NULL);
}

CTEST(Creation, check_new_cp_n_chr)
{
    a_str a;
    
    a = a_new_cp('@', 100);
    ASSERT_EQUAL(100, a_len(a));
    ASSERT_EQUAL(100, a_size(a));
    ASSERT_EQUAL(a_size(a), strlen(a));
    
    a_free(a);
    
    /* should ONLY copy the FIRST character */
    a = a_new_chr("تفاح", 100);
    ASSERT_EQUAL(100, a_len(a));
    ASSERT_EQUAL(100*2, a_size(a));
    ASSERT_EQUAL(a_size(a), strlen(a));
    
    a_free(a);
}

CTEST(Creation, check_new_dup)
{
    a_str a, b;
    
    a = a_new("こんにちは");
    ASSERT_EQUAL(5, a_len(a));
    ASSERT_EQUAL(5*3, a_size(a));
    ASSERT_EQUAL(a_size(a), strlen(a));
    
    b = a_new_dup(a);
    ASSERT_EQUAL(5, a_len(b));
    ASSERT_EQUAL(5*3, a_size(b));
    ASSERT_EQUAL(a_size(b), strlen(b));
    
    ASSERT_EQUAL(0, memcmp(a, b, a_size(b)));
    
    a_free_n(a, b, NULL);
}