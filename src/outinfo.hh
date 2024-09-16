#pragma once

#include <string_view>

namespace fs::outinfo {

constexpr auto version = ::std::string_view{"0.0.0"};

constexpr auto usage = ::std::string_view{
    "usage: FileSpliter [options] <input> <output>"
};

} // namespace fs::outinfo