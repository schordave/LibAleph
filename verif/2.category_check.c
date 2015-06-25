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

CTEST(Categories, check_category)
{
    a_cp cp;
    
    for (cp = 'a'; cp < 'z'; ++cp)
    {
        ASSERT_TRUE(a_category(cp) == a_gc_letter_lowercase);
        ASSERT_TRUE(a_is_lower_cp(cp));
        ASSERT_TRUE(a_is_letter(cp));
        ASSERT_TRUE(a_is_graphical(cp));
    }
    
    for (cp = 'A'; cp < 'Z'; ++cp)
    {
        ASSERT_TRUE(a_category(cp) == a_gc_letter_uppercase);
        ASSERT_TRUE(a_is_upper_cp(cp));
        ASSERT_TRUE(a_is_letter(cp));
        ASSERT_TRUE(a_is_graphical(cp));
    }

    ASSERT_TRUE(a_category(' ') & a_gc_separator);
}

CTEST(Categories, check_currency_category)
{
    ASSERT_TRUE(a_is_currency(a_to_cp("₠")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₰")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₡")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₱")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₢")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₲")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₣")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₳")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₤")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₴")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₥")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₵")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₦")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₶")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₧")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₷")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₸")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₩")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₹")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₪")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₺")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₫")));
    ASSERT_TRUE(a_is_currency(a_to_cp("€")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₭")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₮")));
    ASSERT_TRUE(a_is_currency(a_to_cp("₯")));
    
    ASSERT_FALSE(a_is_currency(a_to_cp("X")));
} 

CTEST(Categories, check_is_alpha)
{
    const char *s = "ƜƝƟƠƢƤƦƧƩƬƮƯƱƲƳƵƷƸƼǄǇǊǍǏǑǓǕǗǙǛǞǠǢǤǦǨǪǬǮ";
    
    while (*s)
    {
        a_cp c = a_next_cp_cstr(&s);
        ASSERT_TRUE(a_is_alpha(c));
        ASSERT_TRUE(a_is_alphanumeric(c));
        ASSERT_TRUE(a_is_bmp(c));
        ASSERT_TRUE(a_is_letter(c));
        ASSERT_TRUE(a_is_graphical(c));
    }
}

CTEST(Categories, check_is_control)
{
    a_cp cp;
    
    for (cp = 0; cp < 32; ++cp)
    {
        ASSERT_TRUE(a_is_control(cp));
        ASSERT_FALSE(a_is_graphical(cp));
    }
}

CTEST(Categories, check_is_digit)
{
    a_cp cp;
    
    for (cp = '0'; cp <= '9'; ++cp)
    {
        ASSERT_TRUE(a_is_digit(cp));
        ASSERT_TRUE(a_is_number(cp));
        ASSERT_TRUE(a_is_bmp(cp));
        ASSERT_TRUE(a_is_graphical(cp));
    }
}

CTEST(Categories, check_is_math)
{
    const char *s = "+<=>|~¬±×÷϶؆؇؈⁄⁒⁺⁻⁼₊₋₌℘⅀⅁⅂⅃⅄⅋←↑→↓↔↚↛↠↣↦↮⇎⇏⇒⇔⇴⇵⇶⇷⇸⇹⇺⇻⇼⇽⇾⇿∀∁∂∃∄∅∆∇∈∉∊∋∌∍∎∏∐∑−∓∔∕∖∗∘∙√∛∜∝∞∟∠∡∢∣∤∥∦∧∨∩∪∫∬∭∮∯∰∱∲∳∴∵∶∷∸∹∺∻∼∽∾∿≀≁≂≃≄≅≆≇≈≉≊≋≌≍≎≏≐≑≒≓≔≕≖≗≘≙≚≛≜≝≞≟≠≡≢≣≤≥≦≧≨≩≪≫≬≭≮≯≰≱≲≳≴≵≶≷≸≹≺≻≼≽≾≿⊀⊁⊂⊃⊄⊅⊆⊇⊈⊉⊊⊋⊌⊍⊎⊏⊐⊑⊒⊓⊔⊕⊖⊗⊘⊙⊚⊛⊜⊝⊞⊟⊠⊡⊢⊣⊤⊥⊦⊧⊨⊩⊪⊫⊬⊭⊮⊯⊰⊱⊲⊳⊴⊵⊶⊷⊸⊹⊺⊻⊼⊽⊾⊿⋀⋁⋂⋃⋄⋅⋆⋇⋈⋉⋊⋋⋌⋍⋎⋏⋐⋑⋒⋓⋔⋕⋖⋗⋘⋙⋚⋛⋜⋝⋞⋟⋠⋡⋢⋣⋤⋥⋦⋧⋨⋩⋪⋫⋬⋭⋮⋯⋰⋱⋲⋳⋴⋵⋶⋷⋸⋹⋺⋻⋼⋽⋾⋿⌠⌡⍼⎛⎜⎝⎞⎟⎠⎡⎢⎣⎤⎥⎦⎧⎨⎩⎪⎫⎬⎭⎮⎯⎰⎱⎲⎳⏜⏝⏞⏟⏠⏡▷◁◸◹◺◻◼◽◾◿♯⟀⟁⟂⟃⟄⟇⟈⟉⟊⟋⟌⟍⟎⟏⟐⟑⟒⟓⟔⟕⟖⟗⟘⟙⟚⟛⟜⟝⟞⟟⟠⟡⟢⟣⟤⟥⟰⟱⟲⟳⟴⟵⟶⟷⟸⟹⟺⟻⟼⟽⟾⟿⤀⤁⤂⤃⤄⤅⤆⤇⤈⤉⤊⤋⤌⤍⤎⤏⤐⤑⤒⤓⤔⤕⤖⤗⤘⤙⤚⤛⤜⤝⤞⤟⤠⤡⤢⤣⤤⤥⤦⤧⤨⤩⤪⤫⤬⤭⤮⤯⤰⤱⤲⤳⤴⤵⤶⤷⤸⤹⤺⤻⤼⤽⤾⤿⥀⥁⥂⥃⥄⥅⥆⥇⥈⥉⥊⥋⥌⥍⥎⥏⥐⥑⥒⥓⥔⥕⥖⥗⥘⥙⥚⥛⥜⥝⥞⥟⥠⥡⥢⥣⥤⥥⥦⥧⥨⥩⥪⥫⥬⥭⥮⥯⥰⥱⥲⥳⥴⥵⥶⥷⥸⥹⥺⥻⥼⥽⥾⥿⦀⦁⦂⦙⦚⦛⦜⦝⦞⦟⦠⦡⦢⦣⦤⦥⦦⦧⦨⦩⦪⦫⦬⦭⦮⦯⦰⦱⦲⦳⦴⦵⦶⦷⦸⦹⦺⦻⦼⦽⦾⦿⧀⧁⧂⧃⧄⧅⧆⧇⧈⧉⧊⧋⧌⧍⧎⧏⧐⧑⧒⧓⧔⧕⧖⧗⧜⧝⧞⧟⧠⧡⧢⧣⧤⧥⧦⧧⧨⧩⧪⧫⧬⧭⧮⧯⧰⧱⧲⧳⧴⧵⧶⧷⧸⧹⧺⧻⧾⧿⨀⨁⨂⨃⨄⨅⨆⨇⨈⨉⨊⨋⨌⨍⨎⨏⨐⨑⨒⨓⨔⨕⨖⨗⨘⨙⨚⨛⨜⨝⨞⨟⨠⨡⨢⨣⨤⨥⨦⨧⨨⨩⨪⨫⨬⨭⨮⨯⨰⨱⨲⨳⨴⨵⨶⨷⨸⨹⨺⨻⨼⨽⨾⨿⩀⩁⩂⩃⩄⩅⩆⩇⩈⩉⩊⩋⩌⩍⩎⩏⩐⩑⩒⩓⩔⩕⩖⩗⩘⩙⩚⩛⩜⩝⩞⩟⩠⩡⩢⩣⩤⩥⩦⩧⩨⩩⩪⩫⩬⩭⩮⩯⩰⩱⩲⩳⩴⩵⩶⩷⩸⩹⩺⩻⩼⩽⩾⩿⪀⪁⪂⪃⪄⪅⪆⪇⪈⪉⪊⪋⪌⪍⪎⪏⪐⪑⪒⪓⪔⪕⪖⪗⪘⪙⪚⪛⪜⪝⪞⪟⪠⪡⪢⪣⪤⪥⪦⪧⪨⪩⪪⪫⪬⪭⪮⪯⪰⪱⪲⪳⪴⪵⪶⪷⪸⪹⪺⪻⪼⪽⪾⪿⫀⫁⫂⫃⫄⫅⫆⫇⫈⫉⫊⫋⫌⫍⫎⫏⫐⫑⫒⫓⫔⫕⫖⫗⫘⫙⫚⫛⫝̸⫝⫞⫟⫠⫡⫢⫣⫤⫥⫦⫧⫨⫩⫪⫫⫬⫭⫮⫯⫰⫱⫲⫳⫴⫵⫶⫷⫸⫹⫺⫻⫼⫽⫾⫿⬰⬱⬲⬳⬴⬵⬶⬷⬸⬹⬺⬻⬼⬽⬾⬿⭀⭁⭂⭃⭄⭇⭈⭉⭊⭋⭌﬩﹢﹤﹥﹦＋＜＝＞｜～￢￩￪￫￬";
    
    while (*s)
    {
        a_cp c = a_next_cp_cstr(&s);
        ASSERT_TRUE(a_is_math(c));
        ASSERT_TRUE(a_is_bmp(c));
        ASSERT_FALSE(a_is_alphanumeric(c));
        ASSERT_TRUE(a_is_graphical(c));
        ASSERT_EQUAL(0, strcmp(a_category_to_str(a_category(c)), "Sm"));
        ASSERT_EQUAL(0, strcmp(a_category_to_description(a_category(c)), "Symbol, math"));
    }
}

CTEST(Categories, check_is_title)
{
    a_str s;
    a_cp cp;
    
    s = a_new("ǅǈǋǲᾈᾉᾊᾋᾌᾍᾎᾏᾘᾙᾚᾛᾜᾝᾞᾟᾨᾩᾪᾫᾬᾭᾮᾯᾼῌῼ");
    
    for (cp = A_MIN_CP; cp <= A_MAX_CP; ++cp)
    {
        if (cp < 32)
            ASSERT_FALSE(a_is_graphical(cp));
        
        if (a_find_cp(s, cp) != A_EOS)
        {
            ASSERT_TRUE(a_is_title_cp(cp));
            ASSERT_TRUE(a_is_graphical(cp));
        }
        else
            ASSERT_FALSE(a_is_title_cp(cp));
    }
    
    a_free(s);
}

CTEST(Categories, check_is_format)
{
    ASSERT_TRUE(a_is_format(0x200B));
    ASSERT_TRUE(a_is_format(0x200C));
    ASSERT_TRUE(a_is_format(0x00AD));
}

CTEST(Categories, check_is_mark)
{
    const char *s = "҈҉᪾⃝⃞⃟⃠⃢⃣⃤꙰꙱꙲";
    
    while (*s)
    {
        a_cp c = a_next_cp_cstr(&s);
        ASSERT_TRUE(a_is_mark(c));
        ASSERT_TRUE(a_is_bmp(c));
        ASSERT_TRUE(a_is_graphical(c));
    }
}

CTEST(Categories, check_is_nonchar)
{
    a_cp cp;
    
    for (cp = 0x0378; cp <= 0x0379; ++cp)
        ASSERT_TRUE(a_is_noncharacter(cp));
    for (cp = 0x0380; cp <= 0x0383; ++cp)
        ASSERT_TRUE(a_is_noncharacter(cp));
    ASSERT_TRUE(a_is_noncharacter(0x038B));
    ASSERT_TRUE(a_is_noncharacter(0x038D));
}

CTEST(Categories, check_is_private_use)
{
    a_cp cp;
    
    for (cp = A_MIN_CP; cp <= A_MAX_CP; ++cp)
    {
        if ((0xE000 <= cp && cp <= 0xF8FF)
            || (0xF0000 <= cp && cp <= 0xFFFFD)
            || (0x100000 <= cp && cp <= 0x10FFFD)
        )
        {
            ASSERT_TRUE(a_is_private_use(cp));
            ASSERT_EQUAL(0, strcmp(a_category_to_str(a_category(cp)), "Co"));
            ASSERT_EQUAL(0, strcmp(a_category_to_description(a_category(cp)), "Other, private use"));
        }
        else
            ASSERT_FALSE(a_is_private_use(cp));
        ASSERT_EQUAL(a_category(cp), a_category_from_str(a_category_to_str(a_category(cp))));
        ASSERT_EQUAL(0, strcmp(a_category_to_description(a_category(cp)), a_category_to_description(a_category_from_str(a_category_to_str(a_category(cp))))));
    }
}

CTEST(Categories, check_is_punct)
{
    const char *s = "-֊־᐀᠆‐‑‒–—―⸗⸚⸺⸻⹀〜〰゠︱︲﹘﹣－([{༺༼᚛‚„⁅⁽₍⌈⌊〈❨❪❬❮❰❲❴⟅⟦⟨⟪⟬⟮⦃⦅⦇⦉⦋⦍⦏⦑⦓⦕⦗⧘⧚⧼⸢⸤⸦⸨⹂〈《「『【〔〖〘〚〝﴿︗︵︷︹︻︽︿﹁﹃﹇﹙﹛﹝（［｛｟｢)]}༻༽᚜⁆⁾₎⌉⌋〉❩❫❭❯❱❳❵⟆⟧⟩⟫⟭⟯⦄⦆⦈⦊⦌⦎⦐⦒⦔⦖⦘⧙⧛⧽⸣⸥⸧⸩〉》」』】〕〗〙〛〞〟﴾︘︶︸︺︼︾﹀﹂﹄﹈﹚﹜﹞）］｝｠｣";
    
    while (*s)
    {
        a_cp c = a_next_cp_cstr(&s);
        ASSERT_TRUE(a_is_punctuation(c));
        ASSERT_TRUE(a_is_bmp(c));
        ASSERT_TRUE(a_is_graphical(c));
    }
}

CTEST(Categories, check_is_sep_space)
{
    const char *s = "                　";
    
    while (*s)
    {
        a_cp c = a_next_cp_cstr(&s);
        ASSERT_TRUE(a_is_separator(c));
        ASSERT_TRUE(a_is_space(c));
        ASSERT_TRUE(a_is_bmp(c));
        ASSERT_TRUE(a_is_graphical(c));
        ASSERT_EQUAL(0, strcmp(a_category_to_str(a_category(c)), "Zs"));
        ASSERT_EQUAL(0, strcmp(a_category_to_description(a_category(c)), "Separator, space"));
    }
}

CTEST(Categories, check_is_supplementary)
{
    a_cp cp;
    
    for (cp = A_MIN_CP; cp <= A_MAX_CP; ++cp)
    {
        if (cp < 0x10000)
            ASSERT_FALSE(a_is_supplementary(cp));
        else
            ASSERT_TRUE(a_is_supplementary(cp));
    }
}

CTEST(Categories, check_is_surrogate)
{
    a_cp cp;
    
    for (cp = A_MIN_CP; cp <= A_MAX_CP; ++cp)
    {
        if (a_is_surrogate_high(cp) || a_is_surrogate_low(cp))
            ASSERT_TRUE(a_is_surrogate(cp));
        else
            ASSERT_FALSE(a_is_surrogate(cp));
    }
}

CTEST(Categories, check_is_symbol)
{
    const char *s = "+<=>|~¬±×÷϶؆؇؈⁄⁒⁺⁻⁼₊₋₌℘⅀⅁⅂⅃⅄⅋←↑→↓↔↚↛↠↣↦↮⇎⇏⇒⇔⇴⇵⇶⇷⇸⇹⇺⇻⇼⇽⇾⇿∀∁∂∃∄∅∆∇∈∉∊∋∌∍∎∏∐∑−∓∔∕∖∗∘∙√∛∜∝∞∟∠∡∢∣∤∥∦∧∨∩∪∫∬∭∮∯∰∱∲∳∴∵∶∷∸∹∺∻∼∽∾∿≀≁≂≃≄≅≆≇≈≉≊≋≌≍≎≏≐≑≒≓≔≕≖≗≘≙≚≛≜≝≞≟≠≡≢≣≤≥≦≧≨≩≪≫≬≭≮≯≰≱≲≳≴≵≶≷≸≹≺≻≼≽≾≿⊀⊁⊂⊃⊄⊅⊆⊇⊈⊉⊊⊋⊌⊍⊎⊏⊐⊑⊒⊓⊔⊕⊖⊗⊘⊙⊚⊛⊜⊝⊞⊟⊠⊡⊢⊣⊤⊥⊦⊧⊨⊩⊪⊫⊬⊭⊮⊯⊰⊱⊲⊳⊴⊵⊶⊷⊸⊹⊺⊻⊼⊽⊾⊿⋀⋁⋂⋃⋄⋅⋆⋇⋈⋉⋊⋋⋌⋍⋎⋏⋐⋑⋒⋓⋔⋕⋖⋗⋘⋙⋚⋛⋜⋝⋞⋟⋠⋡⋢⋣⋤⋥⋦⋧⋨⋩⋪⋫⋬⋭⋮⋯⋰⋱⋲⋳⋴⋵⋶⋷⋸⋹⋺⋻⋼⋽⋾⋿⌠⌡⍼⎛⎜⎝⎞⎟⎠⎡⎢⎣⎤⎥⎦⎧⎨⎩⎪⎫⎬⎭⎮⎯⎰⎱⎲⎳⏜⏝⏞⏟⏠⏡▷◁◸◹◺◻◼◽◾◿♯⟀⟁⟂⟃⟄⟇⟈⟉⟊⟋⟌⟍⟎⟏⟐⟑⟒⟓⟔⟕⟖⟗⟘⟙⟚⟛⟜⟝⟞⟟⟠⟡⟢⟣⟤⟥⟰⟱⟲⟳⟴⟵⟶⟷⟸⟹⟺⟻⟼⟽⟾⟿⤀⤁⤂⤃⤄⤅⤆⤇⤈⤉⤊⤋⤌⤍⤎⤏⤐⤑⤒⤓⤔⤕⤖⤗⤘⤙⤚⤛⤜⤝⤞⤟⤠⤡⤢⤣⤤⤥⤦⤧⤨⤩⤪⤫⤬⤭⤮⤯⤰⤱⤲⤳⤴⤵⤶⤷⤸⤹⤺⤻⤼⤽⤾⤿⥀⥁⥂⥃⥄⥅⥆⥇⥈⥉⥊⥋⥌⥍⥎⥏⥐⥑⥒⥓⥔⥕⥖⥗⥘⥙⥚⥛⥜⥝⥞⥟⥠⥡⥢⥣⥤⥥⥦⥧⥨⥩⥪⥫⥬⥭⥮⥯⥰⥱⥲⥳⥴⥵⥶⥷⥸⥹⥺⥻⥼⥽⥾⥿⦀⦁⦂⦙⦚⦛⦜⦝⦞⦟⦠⦡⦢⦣⦤⦥⦦⦧⦨⦩⦪⦫⦬⦭⦮⦯⦰⦱⦲⦳⦴⦵⦶⦷⦸⦹⦺⦻⦼⦽⦾⦿⧀⧁⧂⧃⧄⧅⧆⧇⧈⧉⧊⧋⧌⧍⧎⧏⧐⧑⧒⧓⧔⧕⧖⧗⧜⧝⧞⧟⧠⧡⧢⧣⧤⧥⧦⧧⧨⧩⧪⧫⧬⧭⧮⧯⧰⧱⧲⧳⧴⧵⧶⧷⧸⧹⧺⧻⧾⧿⨀⨁⨂⨃⨄⨅⨆⨇⨈⨉⨊⨋⨌⨍⨎⨏⨐⨑⨒⨓⨔⨕⨖⨗⨘⨙⨚⨛⨜⨝⨞⨟⨠⨡⨢⨣⨤⨥⨦⨧⨨⨩⨪⨫⨬⨭⨮⨯⨰⨱⨲⨳⨴⨵⨶⨷⨸⨹⨺⨻⨼⨽⨾⨿⩀⩁⩂⩃⩄⩅⩆⩇⩈⩉⩊⩋⩌⩍⩎⩏⩐⩑⩒⩓⩔⩕⩖⩗⩘⩙⩚⩛⩜⩝⩞⩟⩠⩡⩢⩣⩤⩥⩦⩧⩨⩩⩪⩫⩬⩭⩮⩯⩰⩱⩲⩳⩴⩵⩶⩷⩸⩹⩺⩻⩼⩽⩾⩿⪀⪁⪂⪃⪄⪅⪆⪇⪈⪉⪊⪋⪌⪍⪎⪏⪐⪑⪒⪓⪔⪕⪖⪗⪘⪙⪚⪛⪜⪝⪞⪟⪠⪡⪢⪣⪤⪥⪦⪧⪨⪩⪪⪫⪬⪭⪮⪯⪰⪱⪲⪳⪴⪵⪶⪷⪸⪹⪺⪻⪼⪽⪾⪿⫀⫁⫂⫃⫄⫅⫆⫇⫈⫉⫊⫋⫌⫍⫎⫏⫐⫑⫒⫓⫔⫕⫖⫗⫘⫙⫚⫛⫝̸⫝⫞⫟⫠⫡⫢⫣⫤⫥⫦⫧⫨⫩⫪⫫⫬⫭⫮⫯⫰⫱⫲⫳⫴⫵⫶⫷⫸⫹⫺⫻⫼⫽⫾⫿⬰⬱⬲⬳⬴⬵⬶⬷⬸⬹⬺⬻⬼⬽⬾⬿⭀⭁⭂⭃⭄⭇⭈⭉⭊⭋⭌﬩﹢﹤﹥﹦＋＜＝＞｜～￢￩￪￫￬𝛁𝛛𝛻𝜕𝜵𝝏𝝯𝞉𝞩𝟃𞻰𞻱";
    
    while (*s)
    {
        a_cp c = a_next_cp_cstr(&s);
        ASSERT_TRUE(a_is_symbol(c));
        ASSERT_TRUE(a_is_math(c));
        ASSERT_TRUE(a_is_graphical(c));
        ASSERT_EQUAL(0, strcmp(a_category_to_str(a_category(c)), "Sm"));
        ASSERT_EQUAL(0, strcmp(a_category_to_description(a_category(c)), "Symbol, math"));
        ASSERT_EQUAL(a_category(c), a_category_from_str(a_category_to_str(a_category(c))));
    }
}