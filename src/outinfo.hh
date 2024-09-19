#pragma once

#include <string_view>

namespace fsi::outinfo {

constexpr auto version = ::std::string_view{
  "FileSpliter version 0.1.1 ("
#ifdef NDEBUG
  "release mode"
#else
  "debug mode"
#endif
  ")"
};

constexpr auto usage = ::std::string_view{
R"(usage: FileSpliter [option] ...
Options:
  <file>                 Input file.
  -h, --help             Print this help message and exit.
  --version              Print version information and exit.
  -o <dir>               Output dir.
  --split-size <size>    Split size.
  --integrate <dir>      Integrate files that -o generated in <dir>.
)"
};

} // namespace fsi::outinfo