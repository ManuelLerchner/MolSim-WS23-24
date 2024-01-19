#pragma once

#include <string>

/**
 * @brief Formats the given seconds into a string of the form "HH:MM:SS"
 *
 * @param total_seconds Seconds to be formatted
 * @return std::string Formatted string
 *
 * If the given seconds are negative, "N/A" is returned.
 */
std::string format_seconds_eta(int total_seconds);

/**
 * @brief Formats the given mup/s into a string
 *
 * @param mup_s mup/s to be formatted
 * @return std::string Formatted string
 *
 * If the given mup/s are negative, "N/A" is returned.
 * If the given mup/s are greater than 1000, the value is divided by 1000 and a "k" is appended.
 * If the given mup/s are greater than 1000000, the value is divided by 1000000 and a "M" is appended.
 */
std::string format_mup_s(double mup_s);

/**
 * @brief Formats the given seconds into a string of the form "HHh MMm SSs MMMms"
 *
 * @param total_seconds Seconds to be formatted
 * @return std::string Formatted string
 *
 * If the given seconds are negative, "N/A" is returned.
 */
std::string format_seconds_total(double total_seconds);
