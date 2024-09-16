#pragma once

#include <string>
#include <filesystem>
#include "run.hh"

namespace fs::argparse {

enum class ParseRetCode {
  OK = 0,
  NO_ARG_ERROR,
  INVALID_ARG_ERROR,
  HELP_REQUESTED,
  VERSION_REQUESTED,
  FILE_NOT_FOUND_ERROR,
};

struct ParseResult {
    ParseRetCode retcode;
    ::std::string msg{};
};

inline ParseResult parse(int const argc, char const* const* argv) noexcept {
    if (argc < 2) {
        return {.retcode=ParseRetCode::NO_ARG_ERROR};
    }

    auto inputfilepath = ::std::filesystem::path{};
    auto outputdirpath = ::std::filesystem::path{"FileSpliterOut"};

    for (int i{1}; i < argc; ++i) {
        if (argv[i] == nullptr) [[unlikely]] {
            continue;
        }

        auto arg = ::std::string{argv[i]};
        if (arg == "-h" || arg == "--help") {
            return {.retcode=ParseRetCode::HELP_REQUESTED};
        }
        else if (arg == "--version") {
            return {.retcode=ParseRetCode::VERSION_REQUESTED};
        }
        else if (arg == "-o") {
            if (i + 1 >= argc) {
                return {.retcode=ParseRetCode::INVALID_ARG_ERROR};
            }
            outputdirpath = ::std::filesystem::absolute(::std::filesystem::path{argv[++i]});
        }
        else {
            if (::std::filesystem::exists(arg) && ::std::filesystem::is_regular_file(arg)) {
                inputfilepath =::std::filesystem::absolute(::std::filesystem::path{arg});
            } else if (arg.starts_with("-")) {
                return {.retcode=ParseRetCode::INVALID_ARG_ERROR};
            } else {
                return {.retcode=ParseRetCode::FILE_NOT_FOUND_ERROR, .msg="path "+arg+" not found or is not file"};
            }
        }
    }

    run(inputfilepath, outputdirpath);

    return {.retcode=ParseRetCode::OK};
}

} // namespace fs::argparse
