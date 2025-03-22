#include "data.h"


namespace RESSOURCES{

    MeshData::MeshData(const MeshData& m_data){

        vertices = new DynamicList<MATH::vec3>(dynamic_cast<DynamicList<MATH::vec3>*>(m_data.vertices));
        UV = new DynamicList<MATH::vec2>(dynamic_cast<DynamicList<MATH::vec2>*>(m_data.UV));
        normals = new DynamicList<MATH::vec3>(dynamic_cast<DynamicList<MATH::vec3>*>(m_data.normals));
        faces = new DynamicList<paire<float, float>>(dynamic_cast<DynamicList<paire<float, float>>*>(m_data.faces));
    }

    MeshData::MeshData() {

        vertices = new DynamicList<MATH::vec3>;
        UV = new DynamicList<MATH::vec2>;
        normals = new DynamicList<MATH::vec3>;
        faces = new DynamicList<paire<float, float>>;
    }

    MeshData* MeshData::clone() const{
        
        MeshData* d = new MeshData(*this);
        return d;
    }
}