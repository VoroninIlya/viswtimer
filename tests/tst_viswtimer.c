#include "unity.h"
#include "unity_fixture.h"
#include "viswtimer.h"
#include "stdio.h"

TEST_GROUP(TST_VISWTIMER);

TEST_GROUP_RUNNER(TST_VISWTIMER) {
  RUN_TEST_CASE(TST_VISWTIMER, VISWTIM_SomeFunc);
}

TEST_SETUP(TST_VISWTIMER) {
}

TEST_TEAR_DOWN(TST_VISWTIMER) {
}

TEST(TST_VISWTIMER, VISWTIM_SomeFunc)
{
  printf("Test: VISWTIM_SomeFunc");
  //TEST_ASSERT_EQUAL(0, VISWTIM_SomeFunc());
}