#include <cassert>
#include <cstdio>
#include <string_view>
#include "outinfo.hh"
#include "terminate.hh"
#include "parse.hh"

int main(int argc, char **argv) noexcept {
    auto arg_parse_result = fs::argparse::parse(argc, argv);
    if (arg_parse_result.retcode == fs::argparse::ParseRetCode::VERSION_REQUESTED) {
        fprintf(stderr, fs::outinfo::version.data());
    }
    else if (arg_parse_result.retcode == fs::argparse::ParseRetCode::HELP_REQUESTED) {
        fprintf(stderr, fs::outinfo::usage.data());
    }
    else if (arg_parse_result.retcode == fs::argparse::ParseRetCode::OK) {}
    else if (arg_parse_result.retcode == fs::argparse::ParseRetCode::NO_ARG_ERROR) {
        fprintf(stderr, "%s", "ValueError: no argument provided");
    }
    else if (arg_parse_result.retcode == fs::argparse::ParseRetCode::INVALID_ARG_ERROR) {
        fprintf(stderr, "ValueError: invalid argument provided");
    }
    else if (arg_parse_result.retcode == fs::argparse::ParseRetCode::FILE_NOT_FOUND_ERROR) {
        assert(!arg_parse_result.msg.empty());
        fprintf(stderr, "%s", arg_parse_result.msg.c_str());
    }
    else {
#ifdef NDEBUG
        fast_io::unreachable();
#else
        fprintf(stderr, "InternalError: parse returned an unknown code");
        fast_io::fast_terminate();
#endif
    }

    return 0;
}
