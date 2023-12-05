#pragma once

#include "memory/allocator.h"

namespace nk {
    class MallocAllocator : public Allocator {
    public:
        MallocAllocator();

        MallocAllocator(const MallocAllocator&) = delete;
        MallocAllocator& operator=(MallocAllocator&) = delete;

        MallocAllocator(MallocAllocator&&);
        MallocAllocator& operator=(MallocAllocator&&);

        virtual ~MallocAllocator() override;

        virtual void* allocate(const u64 size_bytes, [[maybe_unused]] const u64 alignment) override;
        virtual void free(void* const ptr, [[maybe_unused]] const u64 size_bytes) override;
    };
}
