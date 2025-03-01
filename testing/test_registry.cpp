#define CATCH_CONFIG_MAIN
#include "catch.h"
#include "registry/registry.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace REG;
TEST_CASE("Registry: Create and Destroy Entity", "[Registry]") {
    Registry reg;
    
    // Initially, there are no entities.
    REQUIRE(reg.entitiesCount() == 0);
    
    // Create an entity.
    reg.createEntity();
    REQUIRE(reg.entitiesCount() == 1);
    
    // Check that the entity has both a Visibilite and a Transform component.
    Visibilite* vis = reg.getComponent<Visibilite>(0);
    REQUIRE(vis != nullptr);
    {
        std::stringstream ss;
        vis->aff(ss);
        std::string visStr = ss.str();
        // Expect the output for the Visibilite component.
        REQUIRE(visStr == "Visibilité");
    }
    
    Transform* trans = reg.getComponent<Transform>(0);
    REQUIRE(trans != nullptr);
    {
        std::stringstream ss;
        trans->aff(ss);
        std::string transStr = ss.str();
        // Expect the output for the Transform component.
        REQUIRE(transStr == "Transform");
    }
    
    // Destroy the entity.
    reg.destroyEntity(0);
    REQUIRE(reg.entitiesCount() == 0);
    
    // After destruction, attempts to get components should throw.
    REQUIRE_THROWS_AS(reg.getComponent<Visibilite>(0), std::out_of_range);
    REQUIRE_THROWS_AS(reg.getComponent<Transform>(0), std::out_of_range);
}

TEST_CASE("Registry: Remove Component", "[Registry]") {
    Registry reg;
    reg.createEntity();
    
    // Remove the Visibilite component from the entity.
    reg.removeComponent<Visibilite>(0);
    
    // After removal, accessing the Visibilite component should throw.
    REQUIRE_THROWS_AS(reg.getComponent<Visibilite>(0), std::out_of_range);
    
    // The Transform component should still exist.
    Transform* trans = reg.getComponent<Transform>(0);
    REQUIRE(trans != nullptr);
}

TEST_CASE("Registry: Output Operator", "[Registry]") {
    Registry reg;
    reg.createEntity();
    
    std::stringstream ss;
    ss << reg;
    std::string output = ss.str();
    
    // The output should contain information about the hierarchy and the component registry.
    REQUIRE(output.find("hierarchy :") != std::string::npos);
    REQUIRE(output.find("component") != std::string::npos);
    // Also check that the component names appear.
    REQUIRE(output.find("Visibilité") != std::string::npos);
    REQUIRE(output.find("Transform") != std::string::npos);
}