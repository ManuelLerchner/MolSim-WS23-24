#pragma once

#include <array>
#include <filesystem>
#include <fstream>
#include <string>
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

/**
 * @brief Writes a row to the CSV file.
 *
 * @param file The file stream to write to.
 * @param data The data to write.
 * @param separator The separator to use between values.
 */
template <size_t Index = 0, typename... Types>
void write_csv_row(std::ofstream& file, const std::tuple<Types...>& data, const std::string& separator) {
    if constexpr (Index < sizeof...(Types)) {
        if (Index > 0) {
            file << separator;
        }
        write_csv_element(file, std::get<Index>(data));
        write_csv_row<Index + 1>(file, data, separator);
    }
}

template <typename... DataTypes>
class CSVWriter {
   public:
    static constexpr size_t tuple_length = std::tuple_size<std::tuple<DataTypes...>>::value;
    /**
     * @brief Creates a new CSVWriter instance.
     *
     * @param file_path The path to the CSV file to write to.
     * @param header The header of the CSV file.
     * @param separator The separator to use between values.
     */
    template <typename... HeaderTypes>
    CSVWriter(const std::filesystem::path& file_path, const std::tuple<HeaderTypes...>& header, const std::string& separator = ";")
        : separator(separator) {
        static_assert(sizeof...(HeaderTypes) == tuple_length, "Tuple length does not match header length");

        if (std::filesystem::exists(file_path)) {
            Logger::logger->warn("File {} already exists, appending to it!", file_path.string());
            file.open(file_path, std::ios_base::app);
        } else {
            Logger::logger->info("File {} does not exist, creating it!", file_path.string());
            std::filesystem::create_directories(file_path.parent_path());
            file.open(file_path, std::ios_base::out);

            write_csv_row(file, header, separator);
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
    void writeRow(const std::tuple<DataTypes...>& row) {
        static_assert(sizeof...(DataTypes) == tuple_length, "Tuple length does not match header length");

        write_csv_row(file, row, separator);
        file << std::endl;
    }

   private:
    /**
     * @brief The file stream to write to.
     */
    std::ofstream file;

    /**
     * @brief The separator to use between values.
     */
    const std::string separator;
};