#include <cassert>
#include <cstdio>
#include <csignal>
#include <string_view>
#include <fast_io/fast_io.h>
#include "outinfo.hh"
#include "parse.hh"

int main(int argc, char **argv) noexcept {
    ::std::signal(SIGINT, [](int sig){
        if (sig == SIGINT) {
            ::std::exit(0);
        }
    });

    auto arg_parse_result = fsi::argparse::parse(argc, argv);
    if (arg_parse_result.retcode == fsi::argparse::ParseRetCode::Version) {
        fprintf(stderr, "%s\n", fsi::outinfo::version.data());
    }
    else if (arg_parse_result.retcode == fsi::argparse::ParseRetCode::Help) {
        fprintf(stderr, "%s\n", fsi::outinfo::usage.data());
    }
    else if (arg_parse_result.retcode == fsi::argparse::ParseRetCode::OK) {}
    else if (arg_parse_result.retcode == fsi::argparse::ParseRetCode::Exception) {
        assert(!arg_parse_result.msg.empty());
        fprintf(stderr, "%s\n", arg_parse_result.msg.c_str());
    }
#ifndef NDEBUG
    else {
        fprintf(stderr, "InternalError: parse returned an unknown code\n");
        fast_io::fast_terminate();
    }
#endif

    return 0;
}
