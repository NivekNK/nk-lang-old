#pragma once

#include "core/map_macro.h"

#define ENUM(Name, Values) \
    enum class Name { \
        MAP_LIST(NK_SIMPLE_VALUE, NK_EXPAND_ARGUMENTS Values) \
        ,MaxValues \
    }; \
    struct Name##Impl { \
        static inline constexpr nk::cstr values[static_cast<nk::u64>(Name::MaxValues)] = { \
            MAP_LIST(NK_STRING, NK_EXPAND_ARGUMENTS Values) \
        }; \
        static inline constexpr nk::cstr string(const Name value) { \
            return values[static_cast<nk::u64>(value)]; \
        } \
    }
