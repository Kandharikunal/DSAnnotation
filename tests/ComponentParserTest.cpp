// tests/ComponentParserTest.cpp
#include <gtest/gtest.h>
#include "ComponentParser.h"
#include "ErrorCollector.h"

class ComponentParserTest : public ::testing::Test {
protected:
    ErrorCollector errorCollector;
    ComponentParser parser;

    ComponentParserTest() : errorCollector(nullptr), parser(errorCollector) {}
};

TEST_F(ComponentParserTest, CreatesComponentWithCorrectName) {
    // This is a simplified test and may need adjustment based on your actual implementation
    clang::ASTContext* dummyContext = nullptr; // You might need to mock this
    clang::CXXRecordDecl* dummyDecl = nullptr; // You might need to mock this

    Component result = parser.parse(dummyDecl, dummyContext);
    EXPECT_EQ(result.getClassName(), "DummyClass");
}