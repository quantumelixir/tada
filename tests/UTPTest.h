#ifndef __UTPTEST_H__
#define __UTPTEST_H__

#include <iostream>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "utp.h"
#include "common.h"

class UTPTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE (UTPTest);
    CPPUNIT_TEST (expTest);
    CPPUNIT_TEST (logTest);
    CPPUNIT_TEST (log10Test);

    CPPUNIT_TEST (sinTest);
    CPPUNIT_TEST (cosTest);
    CPPUNIT_TEST (tanTest);
    CPPUNIT_TEST (asinTest);
    CPPUNIT_TEST (acosTest);
    CPPUNIT_TEST (atanTest);
    CPPUNIT_TEST (sinhTest);
    CPPUNIT_TEST (coshTest);
    CPPUNIT_TEST (tanhTest);
    CPPUNIT_TEST (asinhTest);
    CPPUNIT_TEST (acoshTest);
    CPPUNIT_TEST (atanhTest);

    CPPUNIT_TEST (fabsTest);
    CPPUNIT_TEST (ceilTest);
    CPPUNIT_TEST (floorTest);
    CPPUNIT_TEST_SUITE_END ();

    public:
        void setUp (void);
        void tearDown (void);

    protected:
        void expTest(void);
        void logTest(void);
        void log10Test(void);

        void sinTest(void);
        void cosTest(void);
        void tanTest(void);
        void asinTest(void);
        void acosTest(void);
        void atanTest(void);
        void sinhTest(void);
        void coshTest(void);
        void tanhTest(void);
        void asinhTest(void);
        void acoshTest(void);
        void atanhTest(void);

        void fabsTest(void);
        void ceilTest(void);
        void floorTest(void);

    private:
		tada::utp::UTP<double> *a, *b, *c, *u, *v;
};

#endif /* __UTPTEST_H__ */
