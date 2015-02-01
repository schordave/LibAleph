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

CTEST(Length, check_length)
{ 
    a_cp cp;
    a_str a;
    a_gc;
    
    a = a_(a_new("abcde"));
    ASSERT_EQUAL(5, a_len(a));
    ASSERT_EQUAL(5, a_size(a));
    ASSERT_EQUAL(5, a_glen(a));
    
    a_clear(a);
    ASSERT_EQUAL(0, a_len(a));
    ASSERT_EQUAL(0, a_size(a));
    ASSERT_EQUAL(0, a_glen(a));
    ASSERT_EQUAL(0, *a);
    
    /* 'น' +  'ี' +  '้' , 1 glyph */
    a = a_(a_set_cstr(a_new(NULL), "นี้"));
    ASSERT_EQUAL(3, a_len(a));
    ASSERT_EQUAL(9, a_size(a));
    ASSERT_EQUAL(1, a_glen(a));
    
    /* taken from http://sbp.so/supercombiner, still 1 single cluster */
    a = a_(a_set_cstr(a_new(NULL), "ừ̴̵̶̷̸̡̢̧̨̖̗̘̙̜̝̞̟̠̣̤̥̦̩̪̫̬̭̮̯̰̱̲̳̹̺̻̼͇͈͉͍͎́̂̃̄̅̆̇̈̉̊̋̌̍̎̏̐̑̒̓̔̽̾̿̀́͂̓̈́͆͊͋͌̕̚ͅ͏͓͔͕͖͙͚͐͑͒͗͛ͣ͘͜͟͢͝͞͠͡"));
    ASSERT_EQUAL(101, a_len(a));
    ASSERT_EQUAL(201, a_size(a));
    ASSERT_EQUAL(1, a_glen(a));
    
    /* the supercombiner limited the combingmarks to 100,
     * let's try with the _entire_  unicode code space */
    a = a_new("A");
    for (cp = A_MIN_CP; cp <= A_MAX_CP; ++cp)
        if (a_category(cp) & a_gc_mark_nonspacing)
            a = a_cat_cp(a, cp);
    ASSERT_EQUAL(1, a_glen(a_(a))); /* should be just 1 */
    
    
    a = a_(a_set_cstr(a_new(NULL), "Z͑ͫ̓ͪ̂ͫ̽͏̴̙̤̞͉͚̯̞̠͍A̴̵̜̰͔ͫ͗͢L̠ͨͧͩ͘G̴̻͈͍͔̹̑͗̎̅͛́Ǫ̵̹̻̝̳͂̌̌͘!͖̬̰̙̗̿̋ͥͥ̂ͣ̐́́͜͞"));
    ASSERT_EQUAL(75, a_len(a));
    ASSERT_EQUAL(144, a_size(a));
    ASSERT_EQUAL(6, a_glen(a));
    
    a = a_(a_set_cstr(a_new(NULL), "😜🇺🇸👍"));
    ASSERT_EQUAL(4, a_len(a));
    ASSERT_EQUAL(16, a_size(a));
    ASSERT_EQUAL(3, a_glen(a));
    
    a = a_(a_set_cstr(a_new(NULL), "ت‍م‍ن"));
    ASSERT_EQUAL(5, a_len(a));
    ASSERT_EQUAL(12, a_size(a));
    ASSERT_EQUAL(3, a_glen(a));
    
    a = a_(a_set_cstr(a_new(NULL), "ຫຼົງໃຫຼ"));
    ASSERT_EQUAL(7, a_len(a));
    ASSERT_EQUAL(21, a_size(a));
    ASSERT_EQUAL(4, a_glen(a));
    
    a = a_(a_set_cstr(a_new(NULL), "שָׁלוֹם"));
    ASSERT_EQUAL(7, a_len(a));
    ASSERT_EQUAL(14, a_size(a));
    ASSERT_EQUAL(4, a_glen(a));
    
    /* regional indicators are a single cluster */
    a = a_(a_set_cstr(a_new(NULL), "🇦🇧🇨🇩🇪🇫🇬🇭🇮🇯🇰🇱🇲🇳🇴🇵🇶🇷🇸🇹🇺🇻🇼🇽🇾🇿🇦🇧🇨🇩🇪🇫🇬🇭🇮🇯🇰🇱🇲🇳🇴🇵🇶🇷🇸🇹🇺🇻🇼🇽🇾🇿🇦🇧🇨🇩🇪🇫🇬🇭🇮🇯🇰🇱🇲🇳🇴🇵🇶🇷🇸🇹🇺🇻🇼🇽🇾🇿🇦🇧🇨🇩🇪🇫🇬🇭🇮🇯🇰🇱🇲🇳🇴🇵🇶🇷🇸🇹🇺🇻🇼🇽🇾🇿🇦🇧🇨🇩🇪🇫🇬🇭🇮🇯🇰🇱🇲🇳🇴🇵🇶🇷🇸🇹🇺🇻🇼🇽🇾🇿🇦🇧🇨🇩🇪🇫🇬🇭🇮🇯🇰🇱🇲🇳🇴🇵🇶🇷🇸🇹🇺🇻🇼🇽🇾🇿🇦🇧🇨🇩🇪🇫🇬🇭🇮🇯🇰🇱🇲🇳🇴🇵🇶🇷🇸🇹🇺🇻🇼🇽🇾🇿🇦🇧🇨🇩🇪🇫🇬🇭🇮🇯🇰🇱🇲🇳🇴🇵🇶🇷🇸🇹🇺🇻🇼🇽🇾🇿🇦🇧🇨🇩🇪🇫🇬🇭🇮🇯🇰🇱🇲🇳🇴🇵🇶🇷🇸🇹🇺🇻🇼🇽🇾🇿🇦🇧🇨🇩🇪🇫🇬🇭🇮🇯🇰🇱🇲🇳🇴🇵🇶🇷🇸🇹🇺🇻🇼🇽🇾🇿🇦🇧🇨🇩🇪🇫🇬🇭🇮🇯🇰🇱🇲🇳🇴🇵🇶🇷🇸🇹🇺🇻🇼🇽🇾🇿"));
    ASSERT_EQUAL(286, a_len(a));
    ASSERT_EQUAL(1144, a_size(a));
    ASSERT_EQUAL(1, a_glen(a));
    
    /* unless we drop a zero-width-space in between each
     * cluster we want to create (here each character) */
    a = a_(a_set_cstr(a_new(NULL), "🇦​🇧​🇨​🇩​🇪​🇫​🇬​🇭​🇮​🇯​🇰​🇱​🇲​🇳​🇴​🇵​🇶​🇷​🇸​🇹​🇺​🇻​🇼​🇽​🇾​🇿"));
    ASSERT_EQUAL(51, a_len(a));
    ASSERT_EQUAL(179, a_size(a));
    ASSERT_EQUAL(51, a_glen(a));
    
    /* without the spaces */
    a = a_(a_set_cstr(a_new(NULL), "🇦🇧🇨🇩🇪🇫🇬🇭🇮🇯🇰🇱🇲🇳🇴🇵🇶🇷🇸🇹🇺🇻🇼🇽🇾🇿"));
    ASSERT_EQUAL(26, a_len(a));
    ASSERT_EQUAL(104, a_size(a));
    ASSERT_EQUAL(1, a_glen(a));
    
    a_gc_done();
}
