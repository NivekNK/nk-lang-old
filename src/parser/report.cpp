#include "nkpch.h"

#include "parser/report.h"

namespace nk {
#if defined(NK_PLATFORM_WINDOWS)
    void Report::activate_virtual_terminal() {
        HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD console_mode;
        GetConsoleMode(handle_out, &console_mode);
        console_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(handle_out, console_mode);
    }
#endif

    cstr Report::colorize(i8 font, i8 background, i8 style) {
        static char code[20];

        if (font >= 0)
            font += 30;
        else
            font = 0;

        if (background >= 0)
            background += 40;
        else
            background = 0;

        if (background > 0 && style > 0) {
            sprintf(code, "\033[%d;%d;%dm", font, background, style);
        } else if (background > 0) {
            sprintf(code, "\033[%d;%dm", font, background);
        } else if (style > 0) {
            sprintf(code, "\033[%d;%dm", style, font);
        } else {
            sprintf(code, "\033[%dm", font);
        }

        return code;
    }

    void Report::report(bool error, const cstr message, const u64 line_number, const cstr line, const u64 column_number) {
        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);
        std::tm time_info;
        localtime_s(&time_info, &time_t_now);

        u64 digits = 0;
        u64 aux_line_number = line_number;
        while (aux_line_number != 0) {
            aux_line_number /= 10;
            digits++;
        }

        std::scoped_lock lock{m_mutex};
        std::cout << colorize(error ? 1 : 3, -1, 1)
                  << std::format("[{:02}:{:02}:{:02}] {}: {}\n\n",
                                 time_info.tm_hour,
                                 time_info.tm_min,
                                 time_info.tm_sec,
                                 error ? "Error" : "Warning",
                                 message)
                  << "\033[0m"
                  << std::format("    {} | {}\n{:>{}}\n",
                                 line_number,
                                 line,
                                 "^---Here",
                                 14 + digits + column_number)
                  << std::flush;
    }
}
