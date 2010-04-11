#include "SylphTest.h"
#include <Sylph/Core/String.h>
#include <Sylph/Core/Debug.h>

// for strcmp
#include <cstring>

using namespace Sylph;

namespace {

    class TestString : public ::testing::Test {
    };

    TEST_F(TestString, testFromAscii) {
        String s = "foobar";
        Array<uchar> a = s.utf16();
        ASSERT_EQ(6, a.length);
        EXPECT_EQ('f', a[0]);
        EXPECT_EQ('o', a[1]);
        EXPECT_EQ('o', a[2]);
        EXPECT_EQ('b', a[3]);
        EXPECT_EQ('a', a[4]);
        EXPECT_EQ('r', a[5]);
    }

    TEST_F(TestString, testFromUtf8) {
        String s = "éèçàŒù£";
        Array<uchar> a = s.utf16();
        ASSERT_EQ(8, a.length);
        EXPECT_EQ(0x00E9, a[0]);
        EXPECT_EQ(0x00E8, a[1]);
        EXPECT_EQ(0x00E7, a[2]);
        EXPECT_EQ(0x00E0, a[3]);
        EXPECT_EQ(0x008C, a[4]);
        EXPECT_EQ(0x00F9, a[5]);
        EXPECT_EQ(0x00A3, a[6]);
        EXPECT_EQ(0xF8FF, a[7]);
    }

    TEST_F(TestString, testRealEquality) {
        String s = "foobar";
        String t = "foobar";
        String u = "barfoo";
        EXPECT_TRUE(s == t);
        EXPECT_TRUE(t == s);
        EXPECT_TRUE(s != u);
        EXPECT_TRUE(u != s);
        EXPECT_TRUE(t != u);
        EXPECT_TRUE(u != t);
    }

    TEST_F(TestString, testUnicodeRealEquality) {
        String s = "éèçàŒù£";
        String t = "éèçàŒù£";
        String u = "Œù£éèçà";
        EXPECT_TRUE(s == t);
        EXPECT_TRUE(t == s);
        EXPECT_TRUE(s != u);
        EXPECT_TRUE(u != s);
        EXPECT_TRUE(t != u);
        EXPECT_TRUE(u != t);
    }

    TEST_F(TestString, testCopyEquality) {
        String s = "foobar";
        String t = s.copy();
        EXPECT_TRUE(s == t);
        EXPECT_TRUE(t == s);
    }

    TEST_F(TestString, testUnicodeCopyEquality) {
        String s = "éèçàŒù£";
        String t = s.copy();
        EXPECT_TRUE(s == t);
        EXPECT_TRUE(t == s);
    }

    TEST_F(TestString, testRefcountEquality) {
        String s = "foobar";
        String t = s;
        EXPECT_TRUE(s == t);
        EXPECT_TRUE(t == s);
    }

    TEST_F(TestString, testSelfEquality) {
        String s = "foobar";
        EXPECT_TRUE(s == s);
    }

    TEST_F(TestString, testUnicodeSelfEquality) {
        String s = "éèçàŒù£";
        EXPECT_TRUE(s == s);
    }

    TEST_F(TestString, testBoolConstructor) {
        String s = true;
        EXPECT_EQ("true", s);
        String t = false;
        EXPECT_EQ("false", t);
    }

    TEST_F(TestString, testIntConstructor) {
        String s = 12345678;
        EXPECT_EQ("12345678", s);
        String t = 12345678901234LL;
        EXPECT_EQ("12345678901234", t);
    }

    TEST_F(TestString, testFloatConstructorSimple) {
        String s = 3.14f;
        EXPECT_EQ("3.14", s);
        String t = 3.14;
        EXPECT_EQ("3.14", t);
    }

    TEST_F(TestString, testLength) {
        String s = "foobar";
        EXPECT_EQ(6, s.length());
        String t = "éèçàŒù£";
        EXPECT_EQ(8, t.length());
    }

    TEST_F(TestString, testCharAt) {
        String s = "foobar";
        ASSERT_EQ(6, s.length());
        EXPECT_EQ('f', s.at(0));
        EXPECT_EQ('o', s.at(1));
        EXPECT_EQ('o', s.at(2));
        EXPECT_EQ('b', s.at(3));
        EXPECT_EQ('a', s.at(4));
        EXPECT_EQ('r', s.at(5));
    }

    TEST_F(TestString, testUnicodeCharAt) {
        String s = "éèçàŒù£";
        EXPECT_EQ(0x00E9, s.at(0));
        EXPECT_EQ(0x00E8, s.at(1));
        EXPECT_EQ(0x00E7, s.at(2));
        EXPECT_EQ(0x00E0, s.at(3));
        EXPECT_EQ(0x008C, s.at(4));
        EXPECT_EQ(0x00F9, s.at(5));
        EXPECT_EQ(0x00A3, s.at(6));
        EXPECT_EQ(0xF8FF, s.at(7));
    }

    TEST_F(TestString, testInvalidUnicode) {
        //SYLPH_STUB_TEST;
    }

    TEST_F(TestString, testAstralPlaneUnicode) {
        //SYLPH_STUB_TEST;
    }

    TEST_F(TestString, testToAscii) {
        String s = "foobar";
        const char * c = s.ascii();
        EXPECT_STREQ("foobar", c);
        String t = "français";
        const char * c2 = t.ascii();
        EXPECT_STREQ("fran?ais", c2);
    }

    TEST_F(TestString, testToUtf8) {
        String s = "foobar";
        const char * c = s.utf8();
        EXPECT_STREQ("foobar", c);
        String t = "français";
        const char * c2 = t.utf8();
        EXPECT_STREQ("français", c2);
    }

    TEST_F(TestString, testLowerCase) {
        String s = "foo";
        EXPECT_EQ("foo", s.toLowerCase());
        s = "FoO";
        EXPECT_EQ("foo", s.toLowerCase());
        s = "FoX";
        EXPECT_NE("foo", s.toLowerCase());
    }

    TEST_F(TestString, testUpperCase) {
        String s = "FOO";
        EXPECT_EQ("FOO", s.toUpperCase());
        s = "fOO";
        EXPECT_EQ("FOO", s.toUpperCase());
        s = "FoX";
        EXPECT_NE("FOO", s.toUpperCase());
    }

    TEST_F(TestString, testEqualsIgnoreCase) {
        String s = "foo";
        String t = "FOO";
        EXPECT_TRUE(s.equalsIgnoreCase(s));
        EXPECT_TRUE(s.equalsIgnoreCase(t));
        EXPECT_TRUE(t.equalsIgnoreCase(t));
        EXPECT_TRUE(t.equalsIgnoreCase(s));
        EXPECT_FALSE(s.equalsIgnoreCase("Fox"));
        EXPECT_FALSE(t.equalsIgnoreCase("Fox"));
    }

    TEST_F(TestString, testContainment) {
        String s = "foobar";
        EXPECT_TRUE(s.contains("oba"));
    }

    TEST_F(TestString, testTrim) {
        String s = "\t\twtf  \n";
        EXPECT_EQ("wtf",s.trim());
    }

    TEST_F(TestString, testSubstring) {
        String s = "foobar";
        EXPECT_EQ("oba",s.substring(2,4));
    }

    TEST_F(TestString, testIndexOf) {
        String s = "foobar";
        EXPECT_EQ(3,s.indexOf("b"));
        EXPECT_EQ(2,s.indexOf("ob"));
        EXPECT_EQ(-1,s.indexOf("zaz"));
        EXPECT_EQ(-1,s.indexOf("z"));
    }

    TEST_F(TestString, testLastIndexOf) {
        String s = "foobar";
        EXPECT_EQ(3,s.lastIndexOf("b"));
        EXPECT_EQ(2,s.lastIndexOf("ob"));
        EXPECT_EQ(-1,s.lastIndexOf("zaz"));
        EXPECT_EQ(-1,s.lastIndexOf("z"));
    }

    TEST_F(TestString, testMerge) {
        SYLPH_STUB_TEST;
    }

    TEST_F(TestString, testHashUniqueness) {
        String s = "foo";
        String t = "bar";
        Hash<String> hashf;
        EXPECT_NE(hashf(s),hashf(t));
    }

    TEST_F(TestString, testHashEquality) {
        String s = "foo";
        String t = "foo";
        Hash<String> hashf;
        EXPECT_EQ(hashf(s),hashf(s));
        EXPECT_EQ(hashf(s),hashf(t));
    }

    TEST_F(TestString, testToBool) {
        String s = "true";
        EXPECT_TRUE(s.boolValue());
        s = "TrUe";
        EXPECT_TRUE(s.boolValue());
        s = "";
        EXPECT_FALSE(s.boolValue());
        s = "false";
        EXPECT_FALSE(s.boolValue());
        s = "ololol";
        EXPECT_FALSE(s.boolValue());
        s = "ééé";
        EXPECT_FALSE(s.boolValue());
    }

    TEST_F(TestString, testToInt) {
        String a = "123";
        EXPECT_EQ(123, a.intValue());
        String b = "-123";
        EXPECT_EQ(-123,b.intValue());
        String c = " 333 ";
        EXPECT_EQ(333, c.intValue());
        String d = "foobar";
        EXPECT_EQ(0, d.intValue());
    }

    TEST_F(TestString, testToFloatSimple) {
        String s = "3.14";
        EXPECT_FLOAT_EQ(3.14f,s.floatValue());
    }

    TEST_F(TestString, testAppend) {
        String a = "foo";
        String b = "bar";
        String c = a + b;
        a += b;
        EXPECT_EQ("foobar",a);
        EXPECT_EQ("foobar",c);
    }

    TEST_F(TestString, testMultiply) {
        String s = "-";
        String t = s * 5;
        EXPECT_EQ("-----",t);

        String u = "é";
        String v = u * 7;
        EXPECT_EQ("ééééééé",v);
    }

    TEST_F(TestString, testInvoke) {
        SYLPH_STUB_TEST;
    }

} // namespace
