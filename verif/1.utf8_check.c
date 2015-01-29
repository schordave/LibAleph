/*
 * Copyright (c) 2006-2014 David Schor (davidschor@zigwap.com), ZigWap LLC
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

CTEST(Sequences, valid_sequences_null)
{
    ASSERT_NULL(a_is_valid_utf8(""));
}

CTEST(Sequences, valid_sequences_from_various_planes)
{
    
    ASSERT_NULL(a_is_valid_utf8("˙ʇsǝʇ ɐ sı sıɥʇ"));
    ASSERT_NULL(a_is_valid_utf8("Hello, Goodbye"));
    ASSERT_NULL(a_is_valid_utf8("\xD7\xA9\xD7\x9C\xD7\x95\xD7\x9D")); /* שלום */
    ASSERT_NULL(a_is_valid_utf8("\xCE\x93\xCE\xB5\xCE\xB9\xCE\xB1\x20\xCF\x83\xCE\xB1\xCF\x82")); /* Γεια σας */
    ASSERT_NULL(a_is_valid_utf8("\xE4\xBD\xA0\xE5\xA5\xBD")); /* 你好 */
    ASSERT_NULL(a_is_valid_utf8("\xE3\x81\x93\xE3\x82\x93\xE3\x81\xAB\xE3\x81\xA1\xE3\x81\xAF")); /* こんにちは */
    ASSERT_NULL(a_is_valid_utf8("\xEC\x95\x88\xEB\x85\x95\xED\x95\x98\xEC\x84\xB8\xEC\x9A\x94")); /* 안녕하세요 */
    ASSERT_NULL(a_is_valid_utf8("\xE0\xA4\xA8\xE0\xA4\xAE\xE0\xA4\xB8\xE0\xA5\x8D\xE0\xA4\xA4")); /* नमस्त */
    ASSERT_NULL(a_is_valid_utf8("\xE0\xAE\xB5\xE0\xAE\xA3\xE0\xAE\x95\xE0\xAF\x8D\xE0\xAE\x95\xE0\xAE\xAE\xE0\xAF\x8D")); /* வணக்கம் */
    ASSERT_NULL(a_is_valid_utf8("\xD0\xB7\xD0\xB4\xD1\x80\xD0\xB0\xD1\x81\xD1\x82\xD0\xB8")); /* здрасти */
    ASSERT_NULL(a_is_valid_utf8("\xD0\x97\xD0\xB4\xD1\x80\xD0\xB0\xD0\xB2\xD0\xBE")); /* Здраво */
    ASSERT_NULL(a_is_valid_utf8("\xD4\xB2\xD5\xA1\xD6\x80\xD6\x87")); /* Բարև */
    ASSERT_NULL(a_is_valid_utf8("\xD8\xB3\xD9\x84\xD8\xA7\xD9\x85")); /* سلام */
    /* this one tests a mixture of 1, 2, and 3 bytes code points */
    /* 0ؠ12ء3ش4غ5א6ב7ג8ד9הAࡀBࡁBࡂCࡃDࡄEࡅFࡊGܔHܞIܣJܮKܗLܮMچNشOؽPᜡQᜬRᜱSᜃTᜐUᜂVㄆWㄜXYZㄐaㄚb丽c乲d伿e伺f侲g倱h倿iꓤj꒦k꓂l꒨mキnツoボpビqヴrニs꒖t꒳uꥧvꥴwڞxyz */
    ASSERT_NULL(a_is_valid_utf8("\x30\xD8\xA0\x31\x32\xD8\xA1\x33\xD8\xB4\x34\xD8\xBA\x35\xD7"
                                "\x90\x36\xD7\x91\x37\xD7\x92\x38\xD7\x93\x39\xD7\x94\x41\xE0"
                                "\xA1\x80\x42\xE0\xA1\x81\x42\xE0\xA1\x82\x43\xE0\xA1\x83\x44"
                                "\xE0\xA1\x84\x45\xE0\xA1\x85\x46\xE0\xA1\x8A\x47\xDC\x94\x48"
                                "\xDC\x9E\x49\xDC\xA3\x4A\xDC\xAE\x4B\xDC\x97\x4C\xDC\xAE\x4D"
                                "\xDA\x86\x4E\xD8\xB4\x4F\xD8\xBD\x50\xE1\x9C\xA1\x51\xE1\x9C"
                                "\xAC\x52\xE1\x9C\xB1\x53\xE1\x9C\x83\x54\xE1\x9C\x90\x55\xE1"
                                "\x9C\x82\x56\xE3\x84\x86\x57\xE3\x84\x9C\x58\x59\x5A\xE3\x84"
                                "\x90\x61\xE3\x84\x9A\x62\xE4\xB8\xBD\x63\xE4\xB9\xB2\x64\xE4"
                                "\xBC\xBF\x65\xE4\xBC\xBA\x66\xE4\xBE\xB2\x67\xE5\x80\xB1\x68"
                                "\xE5\x80\xBF\x69\xEA\x93\xA4\x6A\xEA\x92\xA6\x6B\xEA\x93\x82"
                                "\x6C\xEA\x92\xA8\x6D\xE3\x82\xAD\x6E\xE3\x83\x84\x6F\xE3\x83"
                                "\x9C\x70\xE3\x83\x93\x71\xE3\x83\xB4\x72\xE3\x83\x8B\x73\xEA"
                                "\x92\x96\x74\xEA\x92\xB3\x75\xEA\xA5\xA7\x76\xEA\xA5\xB4\x77"
                                "\xDA\x9E\x78\x79\x7A"));
    /* ⠀⠁⠂⠃⠄⠅⠆⠇⠈⠉⠊⠋⠌⠍⠎⠐⠑⠒⠓⠔⠕⠖⠗⠘⠙⠚⠛⠜⠝⠞⠟⠠⠡⠢⠣⠤⠥⠦⠧⠨⠩⠪⠫⠬⠭⠮⠯⠰⠱⠲⠳⠴⠵⠶⠷⠸⠹⠺⠻⠼⠽⠾⠿⡀⡁⡂⡃⡄⡅⡆⡇⡈⡉⡊⡋⡌⡍⡎⡏⡐⡑⡒⡓⡔⡕⡖⡗⡘⡙⡚⡛⡜⡝⡞⡟ */
    ASSERT_NULL(a_is_valid_utf8("\xE2\xA0\x80\xE2\xA0\x81\xE2\xA0\x82\xE2\xA0\x83\xE2\xA0\x84"
                                "\xE2\xA0\x85\xE2\xA0\x86\xE2\xA0\x87\xE2\xA0\x88\xE2\xA0\x89"
                                "\xE2\xA0\x8A\xE2\xA0\x8B\xE2\xA0\x8C\xE2\xA0\x8D\xE2\xA0\x8E"
                                "\xE2\xA0\x90\xE2\xA0\x91\xE2\xA0\x92\xE2\xA0\x93\xE2\xA0\x94"
                                "\xE2\xA0\x95\xE2\xA0\x96\xE2\xA0\x97\xE2\xA0\x98\xE2\xA0\x99"
                                "\xE2\xA0\x9A\xE2\xA0\x9B\xE2\xA0\x9C\xE2\xA0\x9D\xE2\xA0\x9E"
                                "\xE2\xA0\x9F\xE2\xA0\xA0\xE2\xA0\xA1\xE2\xA0\xA2\xE2\xA0\xA3"
                                "\xE2\xA0\xA4\xE2\xA0\xA5\xE2\xA0\xA6\xE2\xA0\xA7\xE2\xA0\xA8"
                                "\xE2\xA0\xA9\xE2\xA0\xAA\xE2\xA0\xAB\xE2\xA0\xAC\xE2\xA0\xAD"
                                "\xE2\xA0\xAE\xE2\xA0\xAF\xE2\xA0\xB0\xE2\xA0\xB1\xE2\xA0\xB2"
                                "\xE2\xA0\xB3\xE2\xA0\xB4\xE2\xA0\xB5\xE2\xA0\xB6\xE2\xA0\xB7"
                                "\xE2\xA0\xB8\xE2\xA0\xB9\xE2\xA0\xBA\xE2\xA0\xBB\xE2\xA0\xBC"
                                "\xE2\xA0\xBD\xE2\xA0\xBE\xE2\xA0\xBF\xE2\xA1\x80\xE2\xA1\x81"
                                "\xE2\xA1\x82\xE2\xA1\x83\xE2\xA1\x84\xE2\xA1\x85\xE2\xA1\x86"
                                "\xE2\xA1\x87\xE2\xA1\x88\xE2\xA1\x89\xE2\xA1\x8A\xE2\xA1\x8B"
                                "\xE2\xA1\x8C\xE2\xA1\x8D\xE2\xA1\x8E\xE2\xA1\x8F\xE2\xA1\x90"
                                "\xE2\xA1\x91\xE2\xA1\x92\xE2\xA1\x93\xE2\xA1\x94\xE2\xA1\x95"
                                "\xE2\xA1\x96\xE2\xA1\x97\xE2\xA1\x98\xE2\xA1\x99\xE2\xA1\x9A"
                                "\xE2\xA1\x9B\xE2\xA1\x9C\xE2\xA1\x9D\xE2\xA1\x9E\xE2\xA1\x9F"));
    /* ✁✂✂✃✄✅✆✇✈✉✊✋✌✍✎✐✑✒✓✔✕✖✗✘✙✚✛✜✝✞✠✡✢✣✤✥✦✧✨✩✪✫✬✭✮✰✱✲✳✴✶✷✸✹✺✻✼✽✾✿❀❁❂❃❄❅❆❇❈❉❊❋ */
    ASSERT_NULL(a_is_valid_utf8("\xE2\x9C\x81\xE2\x9C\x82\xE2\x9C\x82\xE2\x9C\x83\xE2\x9C\x84"
                                "\xE2\x9C\x85\xE2\x9C\x86\xE2\x9C\x87\xE2\x9C\x88\xE2\x9C\x89"
                                "\xE2\x9C\x8A\xE2\x9C\x8B\xE2\x9C\x8C\xE2\x9C\x8D\xE2\x9C\x8E"
                                "\xE2\x9C\x90\xE2\x9C\x91\xE2\x9C\x92\xE2\x9C\x93\xE2\x9C\x94"
                                "\xE2\x9C\x95\xE2\x9C\x96\xE2\x9C\x97\xE2\x9C\x98\xE2\x9C\x99"
                                "\xE2\x9C\x9A\xE2\x9C\x9B\xE2\x9C\x9C\xE2\x9C\x9D\xE2\x9C\x9E"
                                "\xE2\x9C\xA0\xE2\x9C\xA1\xE2\x9C\xA2\xE2\x9C\xA3\xE2\x9C\xA4"
                                "\xE2\x9C\xA5\xE2\x9C\xA6\xE2\x9C\xA7\xE2\x9C\xA8\xE2\x9C\xA9"
                                "\xE2\x9C\xAA\xE2\x9C\xAB\xE2\x9C\xAC\xE2\x9C\xAD\xE2\x9C\xAE"
                                "\xE2\x9C\xB0\xE2\x9C\xB1\xE2\x9C\xB2\xE2\x9C\xB3\xE2\x9C\xB4"
                                "\xE2\x9C\xB6\xE2\x9C\xB7\xE2\x9C\xB8\xE2\x9C\xB9\xE2\x9C\xBA"
                                "\xE2\x9C\xBB\xE2\x9C\xBC\xE2\x9C\xBD\xE2\x9C\xBE\xE2\x9C\xBF"
                                "\xE2\x9D\x80\xE2\x9D\x81\xE2\x9D\x82\xE2\x9D\x83\xE2\x9D\x84"
                                "\xE2\x9D\x85\xE2\x9D\x86\xE2\x9D\x87\xE2\x9D\x88\xE2\x9D\x89"
                                "\xE2\x9D\x8A\xE2\x9D\x8B"));
    /* ❶❷❸❹❺❻❼❽❾❿➀➁➂➃➄➅➆➇➈➉➊➋➌➍➎➏➐➑➒➓ */
    ASSERT_NULL(a_is_valid_utf8("\xE2\x9D\xB6\xE2\x9D\xB7\xE2\x9D\xB8\xE2\x9D\xB9\xE2\x9D\xBA"
                                "\xE2\x9D\xBB\xE2\x9D\xBC\xE2\x9D\xBD\xE2\x9D\xBE\xE2\x9D\xBF"
                                "\xE2\x9E\x80\xE2\x9E\x81\xE2\x9E\x82\xE2\x9E\x83\xE2\x9E\x84"
                                "\xE2\x9E\x85\xE2\x9E\x86\xE2\x9E\x87\xE2\x9E\x88\xE2\x9E\x89"
                                "\xE2\x9E\x8A\xE2\x9E\x8B\xE2\x9E\x8C\xE2\x9E\x8D\xE2\x9E\x8E"
                                "\xE2\x9E\x8F\xE2\x9E\x90\xE2\x9E\x91\xE2\x9E\x92\xE2\x9E\x93"));
    /* mixture of 1-4 bytes units */
    /* A¿ℵ𠜎ℵ¿A𠜎AℵA¿ℵ */
    ASSERT_NULL(a_is_valid_utf8("\x41\xC2\xBF\xE2\x84\xB5\xF0\xA0\x9C\x8E\xE2\x84\xB5\xC2\xBF"
                                "\x41\xF0\xA0\x9C\x8E\x41\xE2\x84\xB5\x41\xC2\xBF\xE2\x84\xB5"));
}

CTEST(Sequences, invalid_continuation_bytes)
{
    size_t i;
    const char *s, *s2; 
    
    /* Check ALL 64 continuation bytes: 0x80 - 0xBF */
    s = "\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F\x90\x91\x92\x93\x94"
        "\x95\x96\x97\x98\x99\x9A\x9B\x9C\x9D\x9E\x9F\xA0\xA1\xA2\xA3\xA4\xA5\xA6\xA7\xA8\xA9"
        "\xAA\xAB\xAC\xAD\xAE\xAF\xB0\xB1\xB2\xB3\xB4\xB5\xB6\xB7\xB8\xB9\xBA\xBB\xBC\xBD\xBE"
        "\xBFXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    for (i = 0, s2 = s; a_is_valid_utf8(s); ++i, ++s)
        ASSERT_EQUAL((long)(s2 + i), (long)a_is_valid_utf8(s)); /* make sure the offset matches the invalid byte */
    ASSERT_EQUAL(64, i); /* make sure all 64 were found */
    
    /* Check ALL 32 first byte 2-byte sequences: 0xC0 - 0xDF */
    s = "\xC0\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF\xD0\xD1\xD2\xD3\xD4"
        "\xD5\xD6\xD7\xD8\xD9\xDA\xDB\xDC\xDD\xDE\xDFXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    for (i = 0, s2 = s; a_is_valid_utf8(s); ++i, ++s)
        ASSERT_EQUAL((long)(s2 + i), (long)a_is_valid_utf8(s)); /* make sure the offset matches the invalid byte */
    ASSERT_EQUAL(32, i); /* make sure all 32 were found */
    
    /* Check ALL 16 first byte 3-byte sequences: 0xE0 - 0xEF */
    s = "\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEFXXXXXXXXXXXXXXXXXXXX";
    for (i = 0, s2 = s; a_is_valid_utf8(s); ++i, ++s)
        ASSERT_EQUAL((long)(s2 + i), (long)a_is_valid_utf8(s)); /* make sure the offset matches the invalid byte */
    ASSERT_EQUAL(16, i); /* make sure all 16 were found */
    
    /* Check ALL 8 first byte 4-byte sequences: 0xF0 - 0xF7 */
    s = "\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF7XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    for (i = 0, s2 = s; a_is_valid_utf8(s); ++i, ++s)
        ASSERT_EQUAL((long)(s2 + i), (long)a_is_valid_utf8(s)); /* make sure the offset matches the invalid byte */
    ASSERT_EQUAL(8, i); /* make sure all 16 were found */

}

CTEST(Sequences, sequences_with_last_cont_byte_missing)
{
    size_t i;
    const char *s; 
    
    /* Sequences with last continuation byte missing */
    
    /* 2-byte sequences with last byte missing every other one */
    s = "\xD7\x90\xD7\xD7\x90\xD7\xD7\x90\xD7\xD7\x90\xD7\xD7\x90\xD7\xD7\x90\xD7\xD7\x90\xD7"
        "\xD7\x90\xD7\xD7\x90\xD7\xD7\x90\xD7ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ";
    for (i = 0; (s = a_is_valid_utf8(s)); ++i, ++s);
    ASSERT_EQUAL(10, i); /* make sure all 16 were found */
    
    /* 3-byte sequences with last byte missing every other one */
    s = "\xE3\x84\x9E\xE3\x84\xE3\x84\x9E\xE3\x84\xE3\x84\x9E\xE3\x84\xE3\x84\x9E\xE3\x84\xE3"
        "\x84\x9E\xE3\x84\xE3\x84\x9E\xE3\x84\xE3\x84\x9E\xE3\x84\xE3\x84\x9E\xE3\x84\xE3\x84"
        "\x9E\xE3\x84\xE3\x84\x9E\xE3\x84ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ";
    for (i = 0; (s = a_is_valid_utf8(s)); ++i, s += 2);
    ASSERT_EQUAL(10, i); /* make sure all 16 were found */
    
    /* 4-byte sequences with last byte missing every other one */
    s = "\xF0\x9F\x98\x81\xF0\x9F\x98\xF0\x9F\x98\x81\xF0\x9F\x98\xF0\x9F\x98\x81\xF0\x9F\x98"
        "\xF0\x9F\x98\x81\xF0\x9F\x98\xF0\x9F\x98\x81\xF0\x9F\x98\xF0\x9F\x98\x81\xF0\x9F\x98"
        "\xF0\x9F\x98\x81\xF0\x9F\x98\xF0\x9F\x98\x81\xF0\x9F\x98\xF0\x9F\x98\x81\xF0\x9F\x98"
        "\xF0\x9F\x98\x81\xF0\x9F\x98XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    for (i = 0; (s = a_is_valid_utf8(s)); ++i, s += 3);
    ASSERT_EQUAL(10, i); /* make sure all 16 were found */
    
    /* combination of all above */
    s = "\xD7\xE3\x84\xF0\x9F\x98\xE3\x84\xD7";
    for (i = 0; (s = a_is_valid_utf8(s)); ++i, ++s);
    ASSERT_EQUAL(9, i); /* make sure all 16 were found */
    
}

CTEST(Sequences, impossible_bytes)
{
    
    /* impossible bytes that can never appear */
    ASSERT_NOT_NULL(a_is_valid_utf8("Hello, \xFEGoodbye"));
    ASSERT_NOT_NULL(a_is_valid_utf8("Hello, \xFFGoodbye"));
    ASSERT_NOT_NULL(a_is_valid_utf8("\xD7\xA9\xFE\xD7\x9C\xD7\x95\xD7\x9D")); /* שלום */
    ASSERT_NOT_NULL(a_is_valid_utf8("\xD7\xA9\xD7\x9C\xD7\x95\xFE\xD7\x9D")); /* שלום */
    ASSERT_NOT_NULL(a_is_valid_utf8("\xCE\x93\xFF\xCE\xB5\xCE\xB9\xCE\xB1\x20\xCF\x83\xCE\xB1\xCF\x82")); /* Γεια σας */
    
}

CTEST(Sequences, overlong_character_sequences)
{
    /* overlong characters sequences */
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xC0\xAFZZZZZZZZZZZZZZZZZ"));
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xE0\x80\xAFZZZZZZZZZZZZZ"));
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xF0\x80\x80\xAFZZZZZZZZZ"));
    
}

CTEST(Sequences, boundry_tests_highest_overlong_characters)
{
    
    /* boundry test; highest unicode that is encoded as an overlong character */
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xC1\xBFZZZZZZZZZZZZZZZZZ"));
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xE0\x9F\xBFZZZZZZZZZZZZZ"));
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xF0\x8F\xBF\xBFZZZZZZZZZ"));
    
}

CTEST(Sequences, overlong_null_values)
{
    /* overlong NULL values */
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xC0\x80ZZZZZZZZZZZZZZZZZZ"));
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xE0\x80\x80ZZZZZZZZZZZZZZ"));
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xF0\x80\x80\x80ZZZZZZZZZZ"));
    
}

CTEST(Sequences, utf16_surrogates)
{
    
    /* UTF-16 surrogates */
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xED\xA0\x80ZZZZZZZZZZ"));
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xED\xAD\xBFZZZZZZZZZZ"));
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xED\xAE\x80ZZZZZZZZZZ"));
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xED\xAF\xBFZZZZZZZZZZ"));
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xED\xB0\x80ZZZZZZZZZZ"));
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xED\xBE\x80ZZZZZZZZZZ"));
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xED\xBF\xBFZZZZZZZZZZ"));
    
    /* UTF-16 surrogate pairs*/
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xED\xA0\x80\xED\xB0\x80ZZZZZZZZZ"));
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xED\xA0\x80\xED\xBF\xBFZZZZZZZZZ"));
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xED\xAD\xBF\xED\xB0\x80ZZZZZZZZZ"));
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xED\xAD\xBF\xED\xBF\xBFZZZZZZZZZ"));
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xED\xAE\x80\xED\xB0\x80ZZZZZZZZZ"));
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xED\xAE\x80\xED\xBF\xBFZZZZZZZZZ"));
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xED\xAF\xBF\xED\xB0\x80ZZZZZZZZZ"));
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xED\xAF\xBF\xED\xBF\xBFZZZZZZZZZ"));
    
}

CTEST(Sequences, additional_checks)
{
    
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xEF\xBF\xBEZZZZZZZZZ"));
    ASSERT_NOT_NULL(a_is_valid_utf8("ZZZZZZZZ\xEF\xBF\xBFZZZZZZZZZ"));
    
}