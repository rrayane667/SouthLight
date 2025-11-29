#pragma once
#include "utilite/dataStruct.h"
using namespace DATASTRUCT;
namespace ALLOC{
    struct Marker{
        void* marker = nullptr;
        int marker_block = -1;
    };
    template <unsigned int block_size=4096>
    class StackAllocator{
        void* current_ptr = nullptr;
        void* current_block = nullptr;

        Stack<void*> blocks;
        void expand(){
            
            if(current_block)blocks.append(current_block);
            current_block = new char[block_size];
            
            current_ptr = current_block;
        }

        inline void align(){

            if(((static_cast<char*>(current_ptr))-(static_cast<char*>(current_block)))%16) current_ptr =(static_cast<char*>(current_ptr))+ 16 - ((static_cast<char*>(current_ptr))-(static_cast<char*>(current_block)))%16;
            
        }

        public:
        StackAllocator() = default;

        Marker setMarker(){
            Marker _m;
            _m.marker = current_ptr;
            _m.marker_block = blocks.len();
            return _m;
        }

        void rewindToMarker(Marker&& _m){
            if(!current_ptr || _m.marker_block > blocks.len()) return;
            current_ptr = _m.marker;
            if(_m.marker_block == blocks.len()) return;
            while(_m.marker_block != blocks.len()){
                delete[] static_cast<char*>(current_block);
                current_block = blocks.pop();
            }


        }
        template <typename T, typename... Args>
        T* allocate(Args&&... args){
            align();
            if(!current_ptr || (static_cast<char*>(current_ptr)) + sizeof(T)>(static_cast<char*>(current_block))+block_size ) {expand();align();}
            
            T* _ptr = new (static_cast<T*>(current_ptr)) T(std::forward<Args>(args)...);
            current_ptr = (static_cast<char*>(current_ptr)) + sizeof(T);
            
            return _ptr;
        }

        void deallocate(){
            if(!current_ptr) return;

            delete[] (static_cast<char*>(current_block));
            for(auto& _bck : blocks){
                delete[] (static_cast<char*>(_bck));
            }
            blocks.releaseOwnership();
            current_ptr = nullptr;
            current_block = nullptr;
            return;
            
 
        }

        ~StackAllocator(){
            delete[] (static_cast<char*>(current_block));
            for(auto& _bck : blocks){
                delete[] (static_cast<char*>(_bck));
            }
            blocks.releaseOwnership();
        }
    };
}