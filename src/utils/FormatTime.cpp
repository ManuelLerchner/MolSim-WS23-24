#include "FormatTime.h"

#include "io/logger/Logger.h"

std::string format_seconds_eta(int total_seconds) {
    if (total_seconds < 0) {
        return "N/A";
    }

    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    return fmt::format("{:02d}:{:02d}:{:02d}", hours, minutes, seconds);
}

std::string format_mup_s(double mup_s) {
    if (mup_s < 0) {
        return "N/A";
    }

    std::string suffix = "";
    if (mup_s > 1000000) {
        mup_s /= 1000000;
        suffix = "M";
    } else if (mup_s > 1000) {
        mup_s /= 1000;
        suffix = "k";
    }

    return fmt::format("{:.2f}{}", mup_s, suffix);
}

std::string format_seconds_total(double total_seconds) {
    if (total_seconds < 0) {
        return "N/A";
    }

    int hours = static_cast<int>(total_seconds) / 3600;
    int minutes = (static_cast<int>(total_seconds) % 3600) / 60;
    int seconds = static_cast<int>(total_seconds) % 60;
    int millis = static_cast<int>(total_seconds * 1000) % 1000;

    return fmt::format("{}h {}m {}s {}ms", hours, minutes, seconds, millis);
}