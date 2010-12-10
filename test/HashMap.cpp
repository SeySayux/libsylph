#include "SylphTest.h"
#include <Sylph/Core/HashMap.h>
#include <Sylph/Core/Debug.h>

using namespace Sylph;

namespace {

    void testEqualityHelper(HashMap<String,String>& h,
            bool order = true) {
        if(order) {
            h["a"] = "alpha";
            h["b"] = "beta";
            h["g"] = "gamma";
            h["d"] = "delta";
        } else {
            h["g"] = "gamma";
            h["d"] = "delta";
            h["b"] = "beta";
            h["a"] = "alpha";
        }
    }

    class TestHashMap : public ::testing::Test {

    };

    TEST_F(TestHashMap, testInEqOut) {
        HashMap<String,String> h;
        h["English"] = "English";
        h["French"] = "français";
        h["Spanish"] = "español";
        h["Dutch"] = "Nederlands";
        ASSERT_EQ(4,h.size());
        EXPECT_EQ(String("English"),h["English"]);
        EXPECT_EQ(String("français"),h["French"]);
        EXPECT_EQ(String("español"),h["Spanish"]);
        EXPECT_EQ(String("Nederlands"),h["Dutch"]);
    }

    TEST_F(TestHashMap, testContainsKey) {
        HashMap<String,String> h;
        h["abc"] = "def";
        EXPECT_TRUE(h.containsKey("abc"));
        EXPECT_FALSE(h.containsKey("def"));
    }

    TEST_F(TestHashMap, testContainsValue) {
        HashMap<String,String> h;
        h["abc"] = "def";
        EXPECT_TRUE(h.containsValue(new String("def")));
        EXPECT_FALSE(h.containsValue(new String("abc")));
    }

    TEST_F(TestHashMap, testClear) {
        HashMap<String,String> h;
        h["English"] = "English";
        h["French"] = "français";
        h["Spanish"] = "español";
        h["Dutch"] = "Nederlands";
        ASSERT_EQ(4,h.size());
        h.clear();
        EXPECT_EQ(0,h.size());
    }

    TEST_F(TestHashMap, testRehash) {
        HashMap<String,String> h((size_t) 3);
        h["English"] = "English";
        h["French"] = "français";
        h["Spanish"] = "español";
        h["Dutch"] = "Nederlands";
        ASSERT_EQ(4,h.size());
        EXPECT_EQ(String("English"),h["English"]);
        EXPECT_EQ(String("français"),h["French"]);
        EXPECT_EQ(String("español"),h["Spanish"]);
        EXPECT_EQ(String("Nederlands"),h["Dutch"]);
    }

    TEST_F(TestHashMap, testIterator) {
        Array<String> keys(4);
        Array<String> values(4);

        HashMap<String,String> h;
        h["English"] = "English";
        h["French"] = "français";
        h["Spanish"] = "español";
        h["Dutch"] = "Nederlands";

        //ASSERT_NO_THROW({
            idx_t i = 0;
            for(HashMap<String,String>::iterator it = h.begin();
                it != h.end(); ++it) {
                keys[i] = it->key;
                values[i] = *(it->value);
                i++;
            }
        //});

        for(idx_t i = 0; i < 4; i++) {
            EXPECT_EQ(h[keys[i]],values[i]);
        }
    }

    TEST_F(TestHashMap, testEmptyIterator) {
        HashMap<String, String> h;

        ASSERT_NO_THROW({
           for(HashMap<String,String>::iterator it = h.begin();
                it != h.end(); ++it) {
               // hopefully not optimised out...
           }
        });
    }

    TEST_F(TestHashMap, testEmptyEquality) {
        HashMap<String,String> g;
        HashMap<String,String> h;

        ASSERT_NO_THROW(g == h);
        EXPECT_TRUE(g == h);
    }

    TEST_F(TestHashMap, testRealEquality) {
        HashMap<String, String> h;
        HashMap<String, String> g;

        testEqualityHelper(h);
        testEqualityHelper(g);

        ASSERT_NO_THROW(g == h);
        EXPECT_TRUE(g == h);
    }

    TEST_F(TestHashMap, testInequality) {
        HashMap<String, String> h;
        HashMap<String, String> g;

        testEqualityHelper(h);
        g["a"] = "aleph";

        ASSERT_NO_THROW(g == h);
        EXPECT_FALSE(g == h);
    }

    TEST_F(TestHashMap, testSequenceEquality) {
        HashMap<String, String> h;
        HashMap<String, String> g;

        testEqualityHelper(h);
        testEqualityHelper(g, false);

        ASSERT_NO_THROW(g == h);
        EXPECT_TRUE(g == h);
    }

    TEST_F(TestHashMap, testAssignExisting) {
        HashMap<String, String> h;

        s = "foo";
        ASSERT_NO_THROW(h["bar"] = s);
        ASSERT_EQ(s, h["bar"]);
        ASSERT_EQ("foo", h["bar"]);
    }

    TEST_f(TestHashMap, testStringKeyIntValue) {
        HashMap<String, int> h;

        ASSERT_NO_THROW(h["foo"] = 9);
        int i = 42;
        ASSERT_NO_THROW(h["bar"] = i);
        ASSERT_EQ(9, h["foo"]);
        ASSERT_EQ(42,h["foo"]);
        ASSERT_EQ(i, h["foo"]);
    }

    TEST_F(TestHashMap, testIntKeyStringValue) {
        HashMap<int, String> h;

        ASSERT_NO_THROW(h[4] = "foo");
        String s = "abc";
        ASSERT_NO_THROW(h[2] = s);
        ASSERT_EQ("foo",h[4]);
        ASSERT_EQ("abc",h[2]);
        ASSERT_EQ(s, h[2])
    }

    TEST_F(TestHashMap, testPointerKey) {
        class SomeClass { int i; };

        HashMap<SomeClass*, String> h;

        SomeClass sc = new SomeClass;

        ASSERT_NO_THROW(h[sc] = "foobar");

        delete sc;
    }


} // namespace
