#pragma once

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include "terminate.hh"

namespace fsi::details {

struct integrate_data {
    uintmax_t index;
    ::std::vector<char> data;
};

} // namespace fsi::details

namespace fsi {

inline void integrater(::std::filesystem::path const dirpath) noexcept {
    assert(::std::filesystem::exists(dirpath) && ::std::filesystem::is_directory(dirpath));

    ::std::vector<details::integrate_data> data{};
    ::std::string output_filename = "integrate.bin";

    for (auto const& entry : ::std::filesystem::directory_iterator(dirpath)) {
        auto const& path = entry.path();

        if (path.filename() == "filename.fsi.txt") {
            auto temp = ::std::ifstream(path);
            temp >> output_filename;
            temp.close();
            continue;
        }

        if (!::std::filesystem::is_regular_file(path) || !path.string().ends_with(".fsi.bin")) {
            continue;
        }

        auto filesize = ::std::filesystem::file_size(path);

        ::std::ifstream inputfile(path, ::std::ios::in | ::std::ios::binary);
        if (!inputfile.is_open()) [[unlikely]] {
            fprintf(stderr, "fail to open file %s\n", path.string().c_str());
            fast_io::fast_terminate();
        }
        auto readed_data = ::std::vector<char>(filesize);
        inputfile.read(readed_data.data(), filesize);
        auto name = path.filename().string();
        name.resize(name.size() - 8);
        data.push_back({
            .index=static_cast<decltype(details::integrate_data::index)>(atoi(name.c_str())),
            .data=readed_data
        });
        inputfile.close();
    }

    ::std::ranges::sort(data, [](auto const& lhs, auto const& rhs) {
        return lhs.index < rhs.index;
    });

    auto output_file = ::std::ofstream(dirpath / output_filename, ::std::ios::out | ::std::ios::binary);
    ::std::ranges::for_each(data, [&output_file](auto const& data) {
        output_file.write(data.data.data(), data.data.size());
    });
    output_file.close();
}

} // namespace fsi
