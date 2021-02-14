#include <unity.h>
#include "../src/main.h"

void test_convert_seconds_to_time(void) {
    //GIVEN
    int seconds = 4321; // 01:12:01 (HH:MM:SS)
    //WHEN
    int time = convertSecondsToTime(seconds); //TODO fix this! does not work for whatever reason °_°
    //THEN
    TEST_ASSERT_EQUAL_INT16(112, time);
}

void test_failure(void) {
    TEST_ASSERT(false);
}

void test_success(void) {
    TEST_ASSERT(true);
}


void setup()
{
    delay(2000); // service delay
    UNITY_BEGIN();

    RUN_TEST(test_failure);
    RUN_TEST(test_success);
    RUN_TEST(test_convert_seconds_to_time);

    UNITY_END(); // stop unit testing
}

void loop()
{
}