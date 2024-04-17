//
// Data structure/algorithm testing
//

#include <catch2/catch_test_macros.hpp>
#include "nodemap.hpp"

TEST_CASE("Compile Test", "[flag]"){
    REQUIRE(true);
}

TEST_CASE("Simple 3x3 grid generation", "[flag]"){
    nodeMap testMap(3, 3);
    std::string generatedString = testMap.getMapString();
    std::string expectedString = R"(XXX
XXX
XXX
)";


    REQUIRE(generatedString == expectedString);
}