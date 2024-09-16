#pragma once

#include <cstdint>
#include <ios>
#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <filesystem>
#include <string_view>
#include "terminate.hh"

namespace fs::details {

inline std::string file_get_content(std::filesystem::path const& path) {
    std::ifstream ifs(path, std::ios::in | std::ios::binary);
    std::istreambuf_iterator<char> iit(ifs), iite;
    std::string content(iit, iite);
    return content;
}

inline void file_put_content(std::filesystem::path const& path, std::string_view const& content) {
    std::ofstream ofs(path, std::ios::out | std::ios::binary);
    ofs << content;
}

} // namespace details

namespace fs {

inline void run(
        ::std::filesystem::path const input_filepath,
        ::std::filesystem::path const output_dirpath,
        uintmax_t const split_bytes = 1024 * 1024
) noexcept {
    assert(!input_filepath.empty() && !output_dirpath.empty()
            && ::std::filesystem::exists(input_filepath)
            && ::std::filesystem::is_regular_file(input_filepath));

    if (!::std::filesystem::exists(output_dirpath) && !::std::filesystem::is_directory(output_dirpath)) {
        ::std::filesystem::create_directories(output_dirpath);
    }

    auto inputfile = ::std::ifstream(input_filepath, std::ios::in | std::ios::binary);
    if (!inputfile.is_open()) [[unlikely]] {
        ::std::cerr << "InternalError: failed to open input file " << input_filepath << std::endl;
        fast_io::fast_terminate();
    }

    ::std::vector<char> buffer(split_bytes);
    ::std::streamsize bytes_count{};
    uintmax_t file_index{};
    do {
        inputfile.read(buffer.data(), split_bytes);
        bytes_count = inputfile.gcount();

        auto const output_filepath = output_dirpath / ("file_"+::std::to_string(file_index++)+".bin");
        ::std::ofstream outputfile(output_filepath, ::std::ios::out | ::std::ios::binary);
        if (!outputfile.is_open()) [[unlikely]] {
            ::std::cerr << "InternalError: failed to open output file " << output_filepath << "\n";
            fast_io::fast_terminate();
        }

        outputfile.write(buffer.data(), bytes_count);
        outputfile.close();
    } while (bytes_count >= split_bytes);
}

} // namespace fs
