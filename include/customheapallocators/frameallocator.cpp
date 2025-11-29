#include "stackallocator.h"

namespace ALLOC{
    template <unsigned int block_size=4096>
    class FrameAllocator : StackAllocator<block_size>{
        void rewindToMarker(Marker&& _m) = delete;
        Marker setMarker() = delete;
    };
}