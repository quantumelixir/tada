#include "UTPTest.h"

using namespace tada::utp;
using namespace std;
using mpfr::mpreal;

CPPUNIT_TEST_SUITE_REGISTRATION (UTPTest);

void UTPTest::setUp(void)
{
	a = new UTP<double>(5); b = new UTP<double>(5);
	u = new UTP<double>(5); v = new UTP<double>(5);

	(*a)[0] =  1.3 ; (*a)[1] = -4 ; (*a)[2] =  2 ; (*a)[3] =  4 ; (*a)[4] =  3 ;
	(*b)[0] = -2.6 ; (*b)[1] =  3 ; (*b)[2] =  4 ; (*b)[3] = -3 ; (*b)[4] = -1 ;

	(*v)[0] =  0 ; (*v)[1] = 0 ; (*v)[2] = 0 ; (*v)[3] = 0 ; (*v)[4] = 0 ;
	(*u)[0] =  0 ; (*u)[1] = 0 ; (*u)[2] = 0 ; (*u)[3] = 0 ; (*u)[4] = 0 ;
}

void UTPTest::tearDown(void)
{
	delete a; delete b;
	delete u; delete v;
}

void UTPTest::expTest(void)
{
}

void UTPTest::logTest(void)
{
}

void UTPTest::log10Test(void)
{
}

void UTPTest::fabsTest(void)
{
	(*u) = fabs((*a));
	CPPUNIT_ASSERT_EQUAL ((*u), (*a));
	(*u) = fabs((*b));
	CPPUNIT_ASSERT_EQUAL ((*u), -((*b)));
}

void UTPTest::ceilTest(void)
{
	(*u) = ceil((*a));
	CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[0], 2.0);
	CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[1], 0.);
	CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[2], 0.);
	CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[3], 0.);
	CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[4], 0.);
}

void UTPTest::floorTest(void)
{
	(*u) = floor((*b));
	CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[0], -3.0);
	CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[1], 0.);
	CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[2], 0.);
	CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[3], 0.);
	CPPUNIT_ASSERT_ALMOST_EQUAL ((*u)[4], 0.);
}
