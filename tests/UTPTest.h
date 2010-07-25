#ifndef __UTPTEST_H__
#define __UTPTEST_H__

#include <iostream>
#include <cmath>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "utp.h"
#include "mpreal.h"
#include "common.h"

class UTPTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE (UTPTest);
    CPPUNIT_TEST (expTest);
    CPPUNIT_TEST (logTest);
    CPPUNIT_TEST (log10Test);
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
        void fabsTest(void);
        void ceilTest(void);
        void floorTest(void);

    private:
		tada::utp::UTP<double> *a, *b, *u, *v;
};

#endif /* __UTPTEST_H__ */
