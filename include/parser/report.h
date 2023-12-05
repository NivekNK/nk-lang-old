#pragma once

namespace nk {
    class Report {
    public:
        static inline Report& get() {
            static Report instance;
            return instance;
        }

        static inline void init() {
            get();
        }

        static inline void error(const cstr message, const u64 line_number, const cstr line, const u64 column_number) {
            get().report(true, message, line_number, line, column_number);
        }

        static inline void warning(const cstr message, const u64 line_number, const cstr line, const u64 column_number) {
            get().report(false, message, line_number, line, column_number);
        }

        ~Report() = default;

    private:
        Report() = default;

#if defined(NK_PLATFORM_WINDOWS)
        void activate_virtual_terminal();
#endif
        cstr colorize(i8 font, i8 background, i8 style);
        void report(bool error, const cstr message, const u64 line_number, const cstr line, const u64 column_number);

        std::mutex m_mutex;
    };
}
