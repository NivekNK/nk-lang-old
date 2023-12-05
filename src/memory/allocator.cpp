#include "nkpch.h"

#include "memory/allocator.h"

namespace nk {
    Allocator::Allocator(const u64 size_bytes, void* const start)
        : m_size_bytes{size_bytes},
          m_used_bytes{0},
          m_allocation_count{0},
          m_start{start}
    {
    }

    Allocator::Allocator(Allocator&& other)
        : m_size_bytes{other.m_size_bytes},
          m_used_bytes{other.m_used_bytes},
          m_allocation_count{other.m_allocation_count},
          m_start{other.m_start}
    {
        other.m_size_bytes = 0;
        other.m_used_bytes = 0;
        other.m_allocation_count = 0;
        other.m_start = nullptr;
    }

    Allocator& Allocator::operator=(Allocator&& rhs) {
        m_size_bytes = rhs.m_size_bytes;
        m_used_bytes = rhs.m_used_bytes;
        m_allocation_count = rhs.m_allocation_count;
        m_start = rhs.m_start;

        rhs.m_size_bytes = 0;
        rhs.m_used_bytes = 0;
        rhs.m_allocation_count = 0;
        rhs.m_start = nullptr;

        return *this;
    }

    Allocator::~Allocator() {
        Assert(m_allocation_count == 0 && m_used_bytes == 0);
    }
}
