#define CATCH_CONFIG_MAIN
#include "catch.h"
#include "utilite/datastruct.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace DATASTRUCT;

TEST_CASE("SparseSet: Set and Retrieve", "[SparseSet]") {
    SparseSet<int> s;
    // Set elements at different sparse indices.
    s.set(5, 100);
    s.set(2, 200);
    
    // Retrieve via operator[] which uses the sparse-to-dense mapping.
    REQUIRE(s[5] == 100);
    REQUIRE(s[2] == 200);
}

TEST_CASE("SparseSet: Out-of-range Access", "[SparseSet]") {
    SparseSet<int> s;
    // Without any element set, accessing any index should throw.
    REQUIRE_THROWS_AS(s[0], std::out_of_range);
    
    // After setting an element at index 3.
    s.set(3, 300);
    // Accessing an index that hasn't been set (e.g. index 4) should throw.
    REQUIRE_THROWS_AS(s[4], std::out_of_range);
}

TEST_CASE("SparseSet: Remove Element", "[SparseSet]") {
    SparseSet<int> s;
    s.set(1, 111);
    s.set(4, 444);
    
    // Verify that elements are properly set.
    REQUIRE(s[1] == 111);
    REQUIRE(s[4] == 444);
    
    // Remove the element at sparse index 1.
    s.remove(1);
    
    // Accessing the removed element should now throw an exception.
    REQUIRE_THROWS_AS(s[1], std::out_of_range);
    
    // The other element remains intact.
    REQUIRE(s[4] == 444);
}

TEST_CASE("SparseSet: Iterators", "[SparseSet]") {
    SparseSet<int> s;
    // Set several elements.
    s.set(0, 10);
    s.set(2, 20);
    s.set(5, 50);
    
    // Iterate through the dense storage using begin() and end().
    int sum = 0;
    for(auto it = s.begin(); it != s.end(); ++it) {
        sum += *it;
    }
    // The sum should be 10 + 20 + 50 = 80.
    REQUIRE(sum == 80);
}

TEST_CASE("SparseSet: aff Method (Output)", "[SparseSet]") {
    SparseSet<int> s;
    s.set(1, 101);
    s.set(3, 303);
    
    std::stringstream ss;
    s.aff(ss);
    std::string output = ss.str();
    
    // Check that the output contains expected section headers.
    REQUIRE(output.find("Sparse set :") != std::string::npos);
    REQUIRE(output.find("Sparse :") != std::string::npos);
    REQUIRE(output.find("Dense :") != std::string::npos);
    
    // Verify that the values are printed.
    REQUIRE(output.find("101") != std::string::npos);
    REQUIRE(output.find("303") != std::string::npos);
}
// Helper function to verify contents of a SparseSet
template <typename T>
void verifySparseSet(SparseSet<T>& s, const std::vector<int>& indices, const std::vector<T>& values)
{
    REQUIRE(indices.size() == values.size());

    for (size_t i = 0; i < indices.size(); i++) {
        int idx = indices[i];
        // Check that getIndex(...) returns the "dense index", not -1
        REQUIRE(s.getIndex(idx) != -1);

        // Check that operator[] returns the correct value
        REQUIRE(s[idx] == values[i]);
    }
}

TEST_CASE("SparseSet<T> operator= (assignment) tests", "[SparseSet][assignment]")
{
    SECTION("Assigning a non-empty SparseSet to an empty one")
    {
        SparseSet<int> s1;  // Source
        SparseSet<int> s2;  // Destination

        // Populate s1 with a few elements
        s1.set(0, 10);
        s1.set(5, 50);
        s1.set(2, 20);

        // Now assign s2 = s1
        s2 = s1;

        // Verify that s2 has the same elements
        verifySparseSet(s2, {0, 5, 2}, {10, 50, 20});
    }

    SECTION("Self-assignment does not break the SparseSet")
    {
        SparseSet<int> s1;
        s1.set(3, 33);
        s1.set(7, 77);

        // Self-assignment
        s1 = s1;

        // Verify it's still intact
        verifySparseSet(s1, {3, 7}, {33, 77});
    }

    SECTION("Assigning one non-empty SparseSet to another non-empty one (overwriting)")
    {
        SparseSet<int> s1;
        s1.set(1, 100);
        s1.set(10, 1000);

        SparseSet<int> s2;
        s2.set(2, 200);
        s2.set(3, 300);
        s2.set(4, 400);

        // Overwrite s2 with s1
        s2 = s1;

        // Verify that s2 now matches s1
        verifySparseSet(s2, {1, 10}, {100, 1000});

        // Check that old s2 elements are no longer present
        REQUIRE(s2.getIndex(2) == -1);
        REQUIRE(s2.getIndex(3) == -1);
        REQUIRE(s2.getIndex(4) == -1);
    }

    SECTION("Chained assignment: s3 = s2 = s1")
    {
        SparseSet<int> s1;
        s1.set(0, 42);
        s1.set(5, 555);

        SparseSet<int> s2;
        SparseSet<int> s3;

        // Chained assignment
        s3 = s2 = s1;

        // Verify both s2 and s3 match s1
        verifySparseSet(s2, {0, 5}, {42, 555});
        verifySparseSet(s3, {0, 5}, {42, 555});
    }
}