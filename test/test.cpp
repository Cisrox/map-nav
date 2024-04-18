//
// Data structure/algorithm testing
//

#include <catch2/catch_test_macros.hpp>
#include "nodemap.hpp"

TEST_CASE("Compile Test", "[flag]"){
    REQUIRE(true);
}

TEST_CASE("Large 1000x1000 grid generation test", "[flag]"){
    nodeMap testMap(1000, 1000);
    std::string generatedString = testMap.getMapString();
    std::string expectedString;

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            expectedString += "X";
        }
        expectedString += "\n";
    }

    REQUIRE(generatedString == expectedString);
}

TEST_CASE("Check corner detection", "[flag]"){
    // array boundaries
    int xMax = 2;
    int yMax = 2;

    // Generate a 3x3 board
    nodeMap testMap(3, 3);


    // check top left corner
    REQUIRE(testMap.getNode(0,0)->isCorner(xMax, yMax));

    // check top right corner
    REQUIRE(testMap.getNode(xMax,0)->isCorner(xMax, yMax));

    // check bottom left corner
    REQUIRE(testMap.getNode(0,yMax)->isCorner(xMax, yMax));

    // check bottom right corner
    REQUIRE(testMap.getNode(xMax,yMax)->isCorner(xMax, yMax));
}

TEST_CASE("Check border detection", "[flag]"){
    // array boundaries
    int xMax = 2;
    int yMax = 2;
    nodeMap testMap(3, 3);


    // Check a non corner in top row
    REQUIRE(testMap.getNode(1, 0)->isBorder(xMax, yMax));

    // Check a non corner in bottom row
    REQUIRE(testMap.getNode(1, yMax)->isBorder(xMax, yMax));

    // Check a non corner in left column
    REQUIRE(testMap.getNode(0, 1)->isBorder(xMax, yMax));

    // Check a non corner in right column
    REQUIRE(testMap.getNode(xMax, 1)->isBorder(xMax, yMax));
}

TEST_CASE("Check corners have 3 edges with max outdegree 8", "[flag]"){
    // array boundaries
    int xMax = 2;
    int yMax = 2;

    nodeMap testMap(3, 3, 8, false);

    // check top left corner
    REQUIRE(testMap.getNode(0,0)->getOutdegree() == 3);

    // check top right corner
    REQUIRE(testMap.getNode(xMax,0)->getOutdegree() == 3);

    // check bottom left corner
    REQUIRE(testMap.getNode(0,yMax)->getOutdegree() == 3);

    // check bottom right corner
    REQUIRE(testMap.getNode(xMax,yMax)->getOutdegree() == 3);
}

TEST_CASE("Check borders have 5 edges with max outdegree 8", "[flag]"){
    // array boundaries
    int xMax = 2;
    int yMax = 2;

    nodeMap testMap(3, 3, 8, false);

    // Check a non corner in top row
    REQUIRE(testMap.getNode(1, 0)->getOutdegree() == 5);

    // Check a non corner in bottom row
    REQUIRE(testMap.getNode(1, yMax)->getOutdegree() == 5);

    // Check a non corner in left column
    REQUIRE(testMap.getNode(0, 1)->getOutdegree() == 5);

    // Check a non corner in right column
    REQUIRE(testMap.getNode(xMax, 1)->getOutdegree() == 5);
}