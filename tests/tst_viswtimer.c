#include "unity.h"
#include "unity_fixture.h"
#include "viswtimer.h"
#include "stdio.h"

#define TST_VISWTIMER_TICKS_IN_MS 10

TEST_GROUP(TST_VISWTIMER);

TEST_GROUP_RUNNER(TST_VISWTIMER) {
  RUN_TEST_CASE(TST_VISWTIMER, VISWTIM_Create);
  RUN_TEST_CASE(TST_VISWTIMER, VISWTIM_Start);
  RUN_TEST_CASE(TST_VISWTIMER, VISWTIM_isExpired);
}

TEST_SETUP(TST_VISWTIMER) {
  VISWTIM_Init(TST_VISWTIMER_TICKS_IN_MS);
}

TEST_TEAR_DOWN(TST_VISWTIMER) {
}

TEST(TST_VISWTIMER, VISWTIM_Create)
{
  // check if name == NULL
  {
    TEST_ASSERT_FALSE(VISWTIM_Create(NULL));
  }
  {
    TEST_ASSERT_TRUE(VISWTIM_Create("veryveryveryverylooooooong name of timer"));
    TEST_ASSERT_TRUE(VISWTIM_Create("test2"));
  }
  // check if timer name exists
  {
    TEST_ASSERT_FALSE(VISWTIM_Create("veryveryveryverylooooooong"));
  }
  {
    TEST_ASSERT_TRUE(VISWTIM_Create("test3"));
  }
  // number of initialized timers higher VISWTIM_MAX_TIMERS
  {
    TEST_ASSERT_FALSE(VISWTIM_Create("test4"));
  }
}

TEST(TST_VISWTIMER, VISWTIM_Start)
{
  TEST_ASSERT_TRUE(VISWTIM_Create("test1"));
  // start name == NULLq
  {
    TEST_ASSERT_FALSE(VISWTIM_Start(NULL, 10));
  }
  // start not existing timer
  {
    TEST_ASSERT_FALSE(VISWTIM_Start("noexist", 10));
  }
  // start with timeout = 0
  {
    TEST_ASSERT_FALSE(VISWTIM_Start("test1", 0));
  }
  {
    TEST_ASSERT_TRUE(VISWTIM_Start("test1", 10));
  }
  for(uint32_t i = 0; i <= 5*TST_VISWTIMER_TICKS_IN_MS; i++){
    VISWTIM_Handler();
  }
  TEST_ASSERT_FALSE(VISWTIM_isExpired("test1"));
  for(uint32_t i = 0; i <= 5*TST_VISWTIMER_TICKS_IN_MS; i++){
    VISWTIM_Handler();
  }
  TEST_ASSERT_TRUE(VISWTIM_isExpired("test1"));
}

TEST(TST_VISWTIMER, VISWTIM_isExpired)
{
  // check if timer name is NULL
  {
    TEST_ASSERT_FALSE(VISWTIM_isExpired(NULL));
  }
  // check if no timer created
  {
    TEST_ASSERT_FALSE(VISWTIM_isExpired("test1"));
  }
  TEST_ASSERT_TRUE(VISWTIM_Create("test1"));
  // check wrong timer name
  {
    TEST_ASSERT_FALSE(VISWTIM_isExpired("wrong"));
  }
}