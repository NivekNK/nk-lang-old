#include "nkpch.h"

#include "core/logging.h"

namespace nk {
    void LoggingSystem::styled_log(const cstr message, i8 font, i8 background, i8 style) {
        std::scoped_lock lock(m_log_mutex);
        std::cout << colorize(font, background, style)
                  << message
                  << "\033[0m\n"
                  << std::flush;

        if (m_file_output) {
        }
    }

#if defined(NK_PLATFORM_WINDOWS)
    void LoggingSystem::activate_virtual_terminal() {
        HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD consoleMode;
        GetConsoleMode(handleOut, &consoleMode);
        consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(handleOut, consoleMode);
    }
#endif

    cstr LoggingSystem::colorize(i8 font, i8 background, i8 style) {
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

    void LoggingSystem::log(const cstr message, const cstr log_name, const Priority priority, const cstr file, const u32 line) {
        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);
        std::tm time_info;
        localtime_s(&time_info, &time_t_now);

        str formatted_message = std::format(
            "[{:02}:{:02}:{:02}] {}: {} ({}:{})",
            time_info.tm_hour,
            time_info.tm_min,
            time_info.tm_sec,
            log_name,
            message,
            file,
            line);

        styled_log(formatted_message.c_str(), m_style[priority][0], m_style[priority][1], m_style[priority][2]);
    }
}
