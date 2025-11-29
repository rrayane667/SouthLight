#pragma once
#include "utilite/dataStruct.h"
#include <stdlib.h> 
using namespace DATASTRUCT;
namespace ALLOC{
    template <typename T, unsigned int block_size=4096>
    class PoolAllocator{
        size_t slot_size = std::max(sizeof(T), sizeof(void*));
        void* free_slot = nullptr;
        DynamicList<void*> blocks;
        void expand(){
            char* new_chunk = new char[slot_size*block_size];
            blocks.append(new_chunk);
            for(unsigned int i = 0; i < block_size - 1; ++i){
                void** ptr_ = reinterpret_cast<void**>(new_chunk + i*slot_size);
                *ptr_ = reinterpret_cast<void**>(new_chunk + (i+1)*slot_size);
            }
            void** last = reinterpret_cast<void**>(new_chunk + (block_size - 1) * slot_size);
            *last = free_slot;

            free_slot = new_chunk;
        }

        public:

        ~PoolAllocator() {
        for (void* chunk : blocks) {
            delete[] static_cast<char*>(chunk);// si objet existe encore il faut appeler explicitement destructeur ( a cause de l utilisation de placement new)
        }
    }
        template <typename... Args>
        T* allocate(Args&&... args){
            if(!free_slot) expand();
            void* temp = *reinterpret_cast<void**>(free_slot);
            T* r = new (free_slot) T(std::forward<Args>(args)...);
            free_slot = temp;

            return r;
            
        }

        void deallocate(T* ptr){
            if(!ptr) return;
            ptr->~T();
            void** _ptr = reinterpret_cast<void**>(ptr);
            *_ptr = free_slot;
            free_slot = reinterpret_cast<void*>(_ptr);

        }
    };
}