#pragma once

#include <map>
#include <string>

/**
 * @brief Enum class to specify the output format
 */
enum class OutputFormat { VTU, XYZ, CHKPT, NONE };

/**
 * @brief Returns a mappping of supported output formats
 *
 * @return std::map<std::string,OutputFormat> Mapping of supported output formats
 */
std::map<std::string, OutputFormat> get_supported_output_formats();