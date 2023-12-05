#include "nkpch.h"

#include "memory/malloc_allocator.h"

namespace nk {
    MallocAllocator::MallocAllocator()
        : Allocator{0, nullptr} {
    }

    MallocAllocator::MallocAllocator(MallocAllocator&& other)
        : Allocator{std::move(other)} {
    }

    MallocAllocator& MallocAllocator::operator=(MallocAllocator&& other) {
        Allocator::operator=(std::move(other));
        return *this;
    }

    MallocAllocator::~MallocAllocator() {
    }

    void* MallocAllocator::allocate(const u64 size_bytes, const u64 alignment) {
        m_allocation_count++;
        m_size_bytes += size_bytes;
        m_used_bytes += size_bytes;
        m_start = std::malloc(size_bytes);
        return m_start;
    }

    void MallocAllocator::free(void* const ptr, const u64 size_bytes) {
        m_allocation_count--;
        m_size_bytes -= size_bytes;
        m_used_bytes -= size_bytes;
        std::free(ptr);
        m_start = nullptr;
    }
}
