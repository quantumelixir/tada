#include "utilsTest.h"

using namespace tada::utils;
using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION (utilsTest);

void utilsTest::setUp(void)
{
    // set up test environment (initializing objects)
    a = new vector<double>(5);
    b = new vector<double>(5);
    u = new vector<double>(5);
    v = new vector<double>(5);

    (*a)[0] =  1 ; (*a)[1] = -4 ; (*a)[2] =  2 ; (*a)[3] =  4 ; (*a)[4] =  3 ;
    (*b)[0] = -2 ; (*b)[1] =  3 ; (*b)[2] =  4 ; (*b)[3] = -3 ; (*b)[4] = -1 ;
    (*v)[0] =  3 ; (*v)[1] =  1 ; (*v)[2] = -5 ; (*v)[3] = -4 ; (*v)[4] = -4 ;

    (*u)[0] =  0 ; (*u)[1] = 0 ; (*u)[2] = 0 ; (*u)[3] = 0 ; (*u)[4] = 0 ;
}

void utilsTest::tearDown(void)
{
    // finally delete objects
    delete a; delete b; delete u; delete v;
}

void utilsTest::GeneratorTest(void)
{
    Generator<double> gen;
    CPPUNIT_ASSERT_ALMOST_EQUAL (gen.next(), 0.0);
    CPPUNIT_ASSERT_ALMOST_EQUAL (gen.next(), 1.0);
    CPPUNIT_ASSERT_ALMOST_EQUAL (gen.next(), 2.0);
    CPPUNIT_ASSERT_ALMOST_EQUAL (gen.next(), 3.0);

    Generator<double> inc(2.0, 4.5);
    CPPUNIT_ASSERT_EQUAL (inc++, 2.0);
    CPPUNIT_ASSERT_EQUAL (inc++, 6.5);
    CPPUNIT_ASSERT_EQUAL (inc++, 11.0);
    CPPUNIT_ASSERT_EQUAL (++inc, 20.0);
    CPPUNIT_ASSERT_EQUAL (inc(), 20.0);
}

void utilsTest::convTest(void)
{
    CPPUNIT_ASSERT_ALMOST_EQUAL (convolve(a->begin(), b->begin(), 0, 0.0), -2.0);
    CPPUNIT_ASSERT_ALMOST_EQUAL (convolve(a->begin(), b->begin(), 1, 0.0), 11.0);
    CPPUNIT_ASSERT_ALMOST_EQUAL (convolve(a->begin(), b->begin(), 2, 0.0), -12.0);
    CPPUNIT_ASSERT_ALMOST_EQUAL (convolve(a->begin(), b->begin(), 3, 0.0), -21.0);
    CPPUNIT_ASSERT_ALMOST_EQUAL (convolve(a->begin(), b->begin(), 4, 0.0), 25.0);
}

void utilsTest::tconvTest(void)
{
    CPPUNIT_ASSERT_ALMOST_EQUAL (tconvolve(a->begin(), b->begin(), 0, 0.0), 0.0);
    CPPUNIT_ASSERT_ALMOST_EQUAL (tconvolve(a->begin(), b->begin(), 1, 0.0), 8.0);
    CPPUNIT_ASSERT_ALMOST_EQUAL (tconvolve(a->begin(), b->begin(), 2, 0.0), -20.0);
    CPPUNIT_ASSERT_ALMOST_EQUAL (tconvolve(a->begin(), b->begin(), 3, 0.0), -28.0);
    CPPUNIT_ASSERT_ALMOST_EQUAL (tconvolve(a->begin(), b->begin(), 4, 0.0), 40.0);
}

void utilsTest::solve_ueqvaTest(void)
{
    // solve u' = va'
    // a:  1 , -4  , 2  , 4  , 3
    // v:  3 , 1   , -5 , -4 , -4
    // u:  ? , -12 , 4  , 20 , 11

    solve_ueqva(u->begin(), a->begin(), v->begin(), u->size(), 0.0);
    CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[1], -12.0);
    CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[2], 4.0);
    CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[3], 20.0);
    CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[4], 11.0);
}

void utilsTest::solve_aeqvuTest(void)
{
    // solve a' = vu'
    // a:  1 , -4   , 2   , 4     , 3
    // v:  3 , 1    , -5  , -4    , -4
    // u:  0 , -4/3 , 8/9 , 32/81 , 97/81

    solve_aeqvu(u->begin(), a->begin(), v->begin(), u->size(), 0.0);
    CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[1], -4/3.0);
    CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[2], 8/9.0);
    CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[3], 32/81.0);
    CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[4], 97/81.0);
}

void utilsTest::solve_simulTest(void)
{
    // solve a' = vu'
    // a:  1 , -4   , 2   , 4     , 3
    // v:  3 , 1    , -5  , -4    , -4
    // u:  0 , -4/3 , 8/9 , 32/81 , 97/81

            /*
             *void solve_simul(IterA u1, T alpha1, IterB a1, IterB v1,
             *                 IterA u2, T alpha2, IterB a2, IterB v2,
             *                 IndexType n, int kind)
             */

    (*u)[0] = sin((*a)[0]); (*v)[0] = cos((*a)[0]);
    solve_simul(u->begin(),  1.0, a->begin(), v->begin(),
                v->begin(), -1.0, a->begin(), u->begin(),
                u->size() ,  1);

    CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[0],  0.8414709848078965);
    CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[1], -2.1612092234725591);
    CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[2], -5.6511632667268925);
    CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[3],  14.656201697862556);
    CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[4],  13.732354315642295);
}
