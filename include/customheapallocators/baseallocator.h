#pragma once
#include "stackallocator.h"
#include "poolallocator.h"
#include <unordered_map>
namespace ALLOC {
    template <typename T>
    class BasePool{
        inline static PoolAllocator<T, 512> pool_allocator;
        public : 
        template <typename... Args>
        static T* alloc(Args&&... args){
            return pool_allocator.allocate(std::forward<Args>(args)...);
        }

        static void dealloc(T* ptr){
            pool_allocator.deallocate(ptr);
        }
    };
    class BaseStack {
        
        inline static StackAllocator<4096> stack_alloc; 

    public:
        template <typename T, typename... Args>
        static T* alloc(Args&&... args) {
           
            return stack_alloc.allocate<T>(std::forward<Args>(args)...);
        }

        static void deallocate() {
            stack_alloc.deallocate();
        }

        
        static void rewind(Marker&& _m) {
            stack_alloc.rewindToMarker(std::move(_m));
        }

        static Marker setMarker() {
            return stack_alloc.setMarker();
        }
    };
}