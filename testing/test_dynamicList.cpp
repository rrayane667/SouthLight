#define CATCH_CONFIG_MAIN
#include "catch.h"
#include "utilite/datastruct.h"
#include <iostream>

using namespace DATASTRUCT;

TEST_CASE("DynamicList: Default Construction", "[DynamicList]") {
    DynamicList<int> list;
    // Initially, the list should be empty.
    REQUIRE(list.len() == 0);
    // You might also want to check that capacity() returns a nonzero value,
    // assuming the constructor initializes a minimum capacity.
    REQUIRE(list.capacity() > 0);
}

TEST_CASE("DynamicList: Append Elements", "[DynamicList]") {
    DynamicList<int> list;
    list.append(10);
    list.append(20);
    REQUIRE(list.len() == 2);
    REQUIRE(list[0] == 10);
    REQUIRE(list[1] == 20);
}

TEST_CASE("DynamicList: Remove Element", "[DynamicList]") {
    DynamicList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    
    // Remove the element at index 1 (the value 2).
    list.remove(1);
    
    // After removal, the list should contain 1 and 3.
    REQUIRE(list.len() == 2);
    REQUIRE(list[0] == 1);
    REQUIRE(list[1] == 3);
}



TEST_CASE("DynamicList: Pop Element", "[DynamicList]") {
    DynamicList<int> list;
    list.append(100);
    list.append(200);
    
    // Pop should remove and return the last element.
    int popped = list.pop();
    REQUIRE(popped == 200);
    REQUIRE(list.len() == 1);
    REQUIRE(list[0] == 100);
}

TEST_CASE("DynamicList: Reserve Capacity", "[DynamicList]") {
    DynamicList<int> list;
    int initialCapacity = list.capacity();
    
    // Increase the capacity.
    list.reserve(initialCapacity + 10);
    
    // After reserving, capacity should be at least as large as requested.
    REQUIRE(list.capacity() >= initialCapacity + 10);
}

TEST_CASE("DynamicList: Iterators", "[DynamicList]") {
    DynamicList<int> list;
    list.append(5);
    list.append(10);
    list.append(15);
    
    int sum = 0;
    // Using begin() and end() to iterate through the list.
    for(auto it = list.begin(); it != list.end(); ++it){
        sum += *it;
    }
    REQUIRE(sum == 30);  // 5 + 10 + 15 should equal 30.
}

TEST_CASE("DynamicList: aff (Print Method)", "[DynamicList]") {
    DynamicList<int> list;
    list.append(7);
    list.append(8);
    list.append(9);
    
    std::stringstream ss;
    list.aff(ss);
    std::string output = ss.str();
    
    // The output should start with "Dynamic list : " and include all the numbers.
    REQUIRE(output.find("Dynamic list : ") == 0);
    REQUIRE(output.find("7") != std::string::npos);
    REQUIRE(output.find("8") != std::string::npos);
    REQUIRE(output.find("9") != std::string::npos);
}
TEST_CASE("List operator= by reference tests", "[List][assignment]")
{
    SECTION("Assigning a non-empty list to an empty list")
    {
        // Create a source list with some elements
        List<int>* src = new DynamicList<int>();
        src->append(10);
        src->append(20);

        // Create an empty destination
        List<int>* dst = new DynamicList<int>();

        // Use operator= to copy *src into *dst
        *dst = *src;  // calls operator=(const List<int>&)

        REQUIRE(dst->len() == src->len());
        REQUIRE((*dst)[0] == (*src)[0]);
        REQUIRE((*dst)[1] == (*src)[1]);

        delete src;
        delete dst;
    }

    SECTION("Self-assignment should not break the list")
    {
        List<int>* myList = new DynamicList<int>();
        myList->append(1);
        myList->append(2);

        // Assign the list to itself
        *myList = *myList;  // operator=(const List<int>&) with the same object

        REQUIRE(myList->len() == 2);
        REQUIRE((*myList)[0] == 1);
        REQUIRE((*myList)[1] == 2);

        delete myList;
    }

    SECTION("Assigning one list to another non-empty list (overwriting contents)")
    {
        List<int>* listA = new DynamicList<int>();
        listA->append(5);
        listA->append(6);

        List<int>* listB = new DynamicList<int>();
        listB->append(100);
        listB->append(200);
        listB->append(300);

        // Overwrite *listB with *listA
        *listB = *listA;

        REQUIRE(listB->len() == listA->len());
        REQUIRE((*listB)[0] == 5);
        REQUIRE((*listB)[1] == 6);

        delete listA;
        delete listB;
    }

    SECTION("Chained assignment: (listB = listA), then (listC = listB)")
    {
        List<int>* listA = new DynamicList<int>();
        List<int>* listB = new DynamicList<int>();
        List<int>* listC = new DynamicList<int>();

        listA->append(42);
        listA->append(43);

        // Assign contents of A to B, then B to C
        *listB = *listA;
        *listC = *listB;

        // Check final contents
        REQUIRE(listC->len() == 2);
        REQUIRE((*listC)[0] == 42);
        REQUIRE((*listC)[1] == 43);

        delete listA;
        delete listB;
        delete listC;
    }
}