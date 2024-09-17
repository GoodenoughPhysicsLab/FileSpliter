#pragma once

#include <string_view>

namespace fsi::outinfo {

constexpr auto version = ::std::string_view{"0.0.0"};

constexpr auto usage = ::std::string_view{
    "usage: FileSpliter [options] <input>"
};

} // namespace fsi::outinfo