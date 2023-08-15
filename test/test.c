#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Unity/src/unity.h"
#include "../wordcount.h"

void setUp() {}

void tearDown() {}

void is_multi_wordTest() {
	TEST_ASSERT_EQUAL_INT(1, is_multi_word("test multi should return 1 "));
	TEST_ASSERT_EQUAL_INT(0, is_multi_word("test"));
}

void is_line_only_spacesTest() {
	TEST_ASSERT_TRUE(is_line_only_spaces("    "));
	TEST_ASSERT_FALSE(is_line_only_spaces("   t "));
}

void starts_with_hashTest() {
	TEST_ASSERT_EQUAL_INT(1, starts_with_hash("#test"));
	TEST_ASSERT_EQUAL_INT(1, starts_with_hash(" #test"));
	TEST_ASSERT_EQUAL_INT(0, starts_with_hash("test"));
}

int main() {
	UNITY_BEGIN();
	RUN_TEST(is_multi_wordTest);
	RUN_TEST(is_line_only_spacesTest);
	RUN_TEST(starts_with_hashTest);
	UNITY_END();
}
