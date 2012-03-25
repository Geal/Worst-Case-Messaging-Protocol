#include "packageTest.h"

#include "package.h"

void PackageTestCase::setUp()
{

}

void PackageTestCase::testPackage()
{
	WCMP::Package a("plaintext");
	CPPUNIT_ASSERT_MESSAGE("plaintext message should be different from prepared package", a.prepared() != "plaintext"); 
}
