#include "stdio.h"
#include "cutest/CuTest.h"
#include "standard_calc.h"

/**************** Tests for bound_to_180() *******************/
void test_bound_basic1(CuTest *tc) {
    //Test angles already between bounds
    CuAssertDblEquals(tc, 0, bound_to_180(0), 0.0001);
    CuAssertDblEquals(tc, 90, bound_to_180(90), 0.0001);
    CuAssertDblEquals(tc, -90.1, bound_to_180(-90.1), 0.0001);
    CuAssertDblEquals(tc, -180, bound_to_180(-180), 0.0001);

    //Test angles outside bounds
    CuAssertDblEquals(tc, -180, bound_to_180(180), 0.0001);
    CuAssertDblEquals(tc, -89.734985, bound_to_180(270.265), 0.0001);
    CuAssertDblEquals(tc, 90, bound_to_180(-270), 0.0001);
    CuAssertDblEquals(tc, 0, bound_to_180(360), 0.0001);
    CuAssertDblEquals(tc, 0, bound_to_180(-360), 0.0001);

    //Test angles >|360|
    CuAssertDblEquals(tc, -56, bound_to_180(1024), 0.0001);
    CuAssertDblEquals(tc, 55.9999, bound_to_180(-1024.0001), 0.0001);

    //Test passing an int still returns a flaot
    CuAssertDblEquals(tc, 60.0f, bound_to_180(static_cast<int>(420)), 0.0001);
}

/**************** Tests for is_angle_between() *******************/
void test_between_basic1(CuTest *tc) {
    //Test for middle angle between bounds
    CuAssertTrue(tc, is_angle_between(0, 1, 2));
    CuAssertTrue(tc, is_angle_between(0, 45, 90));

    //Middle angle outside bounds
    CuAssertIntEquals(tc, 0, is_angle_between(45, 90, 270)); //Since CuTest can't check false, I compared an implicit int cast of false to 0

    //Bounds are equal (ideally this would throw a separate assert in the func, but unfortunately it can't be implemented without access to <assert>)
    CuAssertIntEquals(tc, 0, is_angle_between(90, 90, 90));

    //Test for angles that are negative, >|360|, and have decimals
    CuAssertTrue(tc, is_angle_between(-112, -90, -1));
    CuAssertIntEquals(tc, 0, is_angle_between(6969, 4200, 1984));
    CuAssertTrue(tc, is_angle_between(-420, -59, 1382));
    CuAssertTrue(tc, is_angle_between(25.001, 25.002, 25.003));

}

int main(int argc, char const *argv[]) {
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, test_bound_basic1);
    SUITE_ADD_TEST(suite, test_between_basic1);

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    return suite->failCount > 0 ? 1 : 0;
}
