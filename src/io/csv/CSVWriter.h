#pragma once

#include <array>
#include <filesystem>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#include "io/logger/Logger.h"

/**
 * @brief Writes a single element to the CSV file.
 *
 * @param file The file stream to write to.
 * @param value The value to write.
 */
template <typename T>
void write_csv_element(std::ofstream& file, const T& value) {
    file << value;
}

/**
 * @brief Escapes a string value to be written to the CSV file.
 *
 * @param file The file stream to write to.
 * @param value The value to write.
 */
template <>
void write_csv_element<std::string>(std::ofstream& file, const std::string& value) {
    file << "\"" << value << "\"";
}

class CSVWriter {
   public:
    /**
     * @brief Creates a new CSVWriter instance.
     *
     * @param file_path The path to the CSV file to write to.
     * @param cols The cols of the CSV file.
     * @param separator The separator to use between values.
     */
    CSVWriter(const std::filesystem::path& file_path, const std::vector<std::string>& cols, std::string separator = ";")
        : cols(cols), separator(std::move(separator)) {
        Logger::logger->info("Creating CSVWriter for file {}...", file_path.string());
        Logger::logger->info("Header: {}", cols.size());

        if (std::filesystem::exists(file_path)) {
            Logger::logger->warn("File {} already exists, appending to it!", file_path.string());
            file.open(file_path, std::ios_base::app);
        } else {
            Logger::logger->info("File {} does not exist, creating it!", file_path.string());
            std::filesystem::create_directories(file_path.parent_path());
            file.open(file_path, std::ios_base::out);

            writeRow({cols.begin(), cols.end()});
        }

        if (!file.is_open()) {
            Logger::logger->error("Could not open file {} for writing!", file_path.string());
            throw std::runtime_error("Could not open file for writing!");
        }
    }

    /**
     * @brief Writes a row to the CSV file.
     *
     * @param row The row to write.
     */

    using serializable_types = std::variant<size_t, int, double, std::string>;
    void writeRow(const std::vector<serializable_types>& row) {
        if (row.size() != cols.size()) {
            Logger::logger->error("Row size ({}) does not match cols size ({})!", row.size(), cols.size());
            throw std::runtime_error("Row size does not match cols size!");
        }

        for (size_t i = 0; i < row.size(); i++) {
            if (i > 0) {
                file << separator;
            }
            std::visit([&](auto&& arg) { write_csv_element(file, arg); }, row[i]);
        }
        file << std::endl;
    }

   private:
    /**
     * @brief The file stream to write to.
     */
    std::ofstream file;

    /**
     * @brief The cols of the CSV file.
     */
    const std::vector<std::string> cols;

    /**
     * @brief The separator to use between values.
     */
    const std::string separator;
};