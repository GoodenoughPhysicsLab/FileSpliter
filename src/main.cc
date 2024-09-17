#include <cassert>
#include <cstdio>
#include <string_view>
#include "outinfo.hh"
#include "terminate.hh"
#include "parse.hh"

int main(int argc, char **argv) noexcept {
    auto arg_parse_result = fsi::argparse::parse(argc, argv);
    if (arg_parse_result.retcode == fsi::argparse::ParseRetCode::VERSION_REQUESTED) {
        fprintf(stderr, "%s\n", fsi::outinfo::version.data());
    }
    else if (arg_parse_result.retcode == fsi::argparse::ParseRetCode::HELP_REQUESTED) {
        fprintf(stderr, "%s\n", fsi::outinfo::usage.data());
    }
    else if (arg_parse_result.retcode == fsi::argparse::ParseRetCode::OK) {}
    else if (arg_parse_result.retcode == fsi::argparse::ParseRetCode::NO_ARG_ERROR) {
        fprintf(stderr,  "ValueError: no argument provided\n");
    }
    else if (arg_parse_result.retcode == fsi::argparse::ParseRetCode::INVALID_ARG_ERROR) {
        fprintf(stderr, "ValueError: invalid argument provided\n");
    }
    else if (arg_parse_result.retcode == fsi::argparse::ParseRetCode::Exception) {
        assert(!arg_parse_result.msg.empty());
        fprintf(stderr, "%s\n", arg_parse_result.msg.c_str());
    }
    else {
#ifdef NDEBUG
        fast_io::unreachable();
#else
        fprintf(stderr, "InternalError: parse returned an unknown code\n");
        fast_io::fast_terminate();
#endif
    }

    return 0;
}
