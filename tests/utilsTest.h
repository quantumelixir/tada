#ifndef __UTILSTEST_H__
#define __UTILSTEST_H__

#include <iostream>
#include <vector>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "utils.h"
#include "common.h"

class utilsTest : public CPPUNIT_NS :: TestFixture
{
    CPPUNIT_TEST_SUITE (utilsTest);
    CPPUNIT_TEST (convTest);
    CPPUNIT_TEST (tconvTest);
    CPPUNIT_TEST (solve_ueqvaTest);
    CPPUNIT_TEST (solve_aeqvuTest);
    CPPUNIT_TEST_SUITE_END ();

    public:
        void setUp (void);
        void tearDown (void);

    protected:
        void convTest(void);
        void tconvTest(void);
        void solve_ueqvaTest(void);
        void solve_aeqvuTest(void);

    private:
        std::vector<double> *a, *b, *u, *v;
};

#endif /* __UTILSTEST_H__ */
