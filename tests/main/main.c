#include "unity_fixture.h"
#include "viswtimer.h"

static void runAllTests(void)
{
  RUN_TEST_GROUP(TST_VISWTIMER);
}

int main(int argc, const char* argv[])
{
  return UnityMain(argc, argv, runAllTests);
}