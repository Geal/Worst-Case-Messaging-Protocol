#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/config/SourcePrefix.h>

class PackageTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( PackageTestCase );
  CPPUNIT_TEST( testPackage );
  CPPUNIT_TEST_SUITE_END();


public:
  void setUp();

protected:

  void testPackage();

};

CPPUNIT_TEST_SUITE_REGISTRATION( PackageTestCase );

