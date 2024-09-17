#pragma once

#include <cstdint>
#include <string>
#include <filesystem>
#include "integrater.hh"
#include "spliter.hh"

namespace fsi::argparse {

enum class ParseRetCode {
  OK = 0,
  Help,
  Version,
  Exception,
};

struct ParseResult {
    ParseRetCode retcode;
    ::std::string msg{};
};

inline ParseResult parse(int const argc, char const* const* argv) noexcept {
    if (argc < 2) {
        return {.retcode=ParseRetCode::Exception, .msg="Error: no arguments provided"};
    }

    auto split_size = uintmax_t{1024 * 1024};
    auto inputfilepath = ::std::filesystem::path{};
    auto outputdirpath = ::std::filesystem::path{"FileSpliterOut"};
    auto integratepath = ::std::filesystem::path{};

    for (int i{1}; i < argc; ++i) {
        if (argv[i] == nullptr) [[unlikely]] {
            continue;
        }

        auto arg = ::std::string{argv[i]};
        if (arg == "-h" || arg == "--help") {
            return {.retcode=ParseRetCode::Help};
        }
        else if (arg == "--version") {
            return {.retcode=ParseRetCode::Version};
        }
        else if (arg == "-o") {
            if (i + 1 >= argc) {
                return {.retcode=ParseRetCode::Exception, .msg="Error: -o takes no argument\n"};
            }
            outputdirpath = ::std::filesystem::absolute(::std::filesystem::path{argv[++i]});
        }
        else if (arg == "--integrate") {
            if (i + 1 >= argc) {
                return {.retcode=ParseRetCode::Exception, .msg="Error: --integrate takes no argument\n"};
            }
            integratepath = ::std::filesystem::absolute(::std::filesystem::path{argv[++i]});

            if (!::std::filesystem::exists(integratepath)
                || !::std::filesystem::is_directory(integratepath))
            {
                return {.retcode=ParseRetCode::Exception,
                        .msg="Error: path "+integratepath.string()+" not found or is not dir"};
            }
        }
        else if (arg == "--split-size") {
            if (i + 1 >= argc) {
                return {.retcode=ParseRetCode::Exception, .msg="Error: --split-size requires an positive integer"};
            }
            auto str_num = argv[++i];
            for (int j{}; str_num[j] != '\0'; ++j) {
                if (str_num[j] < '0' || str_num[j] > '9') {
                    return {.retcode=ParseRetCode::Exception, .msg="Error: --split-size requires an positive integer"};
                }
            }
            auto _split_size = atoi(str_num);
            if (_split_size <= 0) {
                return {.retcode=ParseRetCode::Exception, .msg="Error: --split-size requires an positive integer"};
            }
            split_size = static_cast<uintmax_t>(_split_size) * 1024;
        }
        else {
            if (::std::filesystem::exists(arg) && ::std::filesystem::is_regular_file(arg)) {
                inputfilepath =::std::filesystem::absolute(::std::filesystem::path{arg});
            } else if (arg.starts_with("-")) {
                return {.retcode=ParseRetCode::Exception, .msg="Error: no argument names "+arg};
            } else {
                return {.retcode=ParseRetCode::Exception, .msg="Error: path "+arg+" not found or is not a file"};
            }
        }
    }

    if (!inputfilepath.empty() && !outputdirpath.empty()) {
        spliter(inputfilepath, outputdirpath, split_size);
    }
    if (!integratepath.empty()) {
        integrater(integratepath);
    }

    return {.retcode=ParseRetCode::OK};
}

} // namespace fsi::argparse
