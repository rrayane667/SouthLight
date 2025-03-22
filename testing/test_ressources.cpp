#define CATCH_CONFIG_MAIN
#include "catch.h"
#include "ressources/data.h"
#include "ressources/ressource.h"
#include "ressources/ressourcemanager.h"
#include <sstream>
#include <fstream>



TEST_CASE("MeshData default constructor initializes members", "[MeshData]") {
    RESSOURCES::MeshData md;
    REQUIRE(md.vertices != nullptr);
    REQUIRE(md.UV != nullptr);
    REQUIRE(md.normals != nullptr);
    REQUIRE(md.vertices->len() == 0);
    REQUIRE(md.UV->len() == 0);
    REQUIRE(md.normals->len() == 0);
    // Note: faces is not initialized in constructor, so accessing it would crash
}

TEST_CASE("MeshData copy constructor creates deep copy", "[MeshData]") {
    RESSOURCES::MeshData original;
    
    original.vertices->append(MATH::vec3(1, 2, 3));

    RESSOURCES::MeshData copied(original);

    REQUIRE(copied.vertices->len() == 1);
    original.vertices->append(MATH::vec3(4, 5, 6)); // Modify original

    REQUIRE(copied.vertices->len() == 1); // Should remain unchanged

}

TEST_CASE("MeshData clone method creates deep copy", "[MeshData]") {
    RESSOURCES::MeshData original;
    original.UV->append(MATH::vec2(0.5, 0.5));
    
    auto cloned = original.clone();
    REQUIRE(cloned->UV->len() == 1);
  
    delete cloned;
}

TEST_CASE("Ressource load/unload sets flags correctly", "[Ressource]") {

    RESSOURCES::Ressource res("C:/Users/ORDI/Desktop/openGL/RessourceDirectory/mesh/teapot.obj", new RESSOURCES::MeshLoader(), 0, "a");
    REQUIRE_FALSE(res.isLoaded());
    
    res.load();
    REQUIRE(res.isLoaded());
   
    
    res.unload();
    REQUIRE_FALSE(res.isLoaded());
    
   
    
}

TEST_CASE("MeshLoader parses OBJ vertices correctly", "[MeshLoader]") {
    
    // Create test OBJ file
    std::ofstream("test.obj") << "v 1.0 2.0 3.0\nv 4.0 5.0 6.0\n";
    
    RESSOURCES::MeshData data;
    // WARNING: data.faces is uninitialized and will cause crashes if used
    RESSOURCES::MeshLoader::_objLoader("test.obj", data);
    
    REQUIRE(data.vertices->len() == 2);
    REQUIRE((*data.vertices)[0] == MATH::vec3(1.0f, 2.0f, 3.0f));
    REQUIRE((*data.vertices)[1] == MATH::vec3(4.0f, 5.0f, 6.0f));
}

TEST_CASE("RessourceManager creates and loads resources", "[RessourceManager]") {

    
    RESSOURCES::RessourceManager rm;
    auto* res = rm.get(0); 
    
    REQUIRE(res != nullptr);
    REQUIRE(res->isLoaded());
}
TEST_CASE("RessourceFactory creates resources", "[Factory]") {
    RESSOURCES::RessourceFactoryTypeA factory;
    std::string testPath = "test.obj";
    
    SECTION("Create mesh resource") {
        auto* res = factory.createMeshData(testPath, 0);
        REQUIRE(res->getId() == 0);
        REQUIRE(res->isLoaded() == false);
        delete res;
    }
}

TEST_CASE("MeshLoader face parsing", "[MeshLoader]") {
    std::ofstream("face_test.obj") << "f 1/2/3 4/5/6 7/8/9\n";
    
    RESSOURCES::MeshData data;
    data.faces = new DynamicList<paire<float, float>>; // Fix for uninitialized member
    
    RESSOURCES::MeshLoader::_objLoader("face_test.obj", data);
    
    REQUIRE(data.faces->len() == 3);
    REQUIRE(data.faces->get(0).first == 1);
    REQUIRE(data.faces->get(0).second == 2);
    delete data.faces;
}

TEST_CASE("Resource memory management", "[Memory]") {
    RESSOURCES::MeshData* md = new RESSOURCES::MeshData();
    
    SECTION("Destructor cleans up") {
        md->vertices->append(MATH::vec3(1,2,3));
        delete md;
        // Should validate with valgrind/memory sanitizer
    }

    SECTION("Clone doesn't share pointers") {
        auto* clone = md->clone();
        md->vertices->append(MATH::vec3(4,5,6));
        REQUIRE(clone->vertices->len() == 0);
        delete clone;
        delete md;
    }
}

TEST_CASE("ResourceManager edge cases", "[ResourceManager]") {
    RESSOURCES::RessourceManager rm;

    SECTION("Invalid resource index") {
        REQUIRE_THROWS_AS(rm.get(999), std::runtime_error);
    }

    SECTION("Double unload") {
        rm.unload(0);  // Should handle gracefully
        rm.unload(0);  // No crash
    }
}