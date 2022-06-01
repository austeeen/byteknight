#include "exceptions.hpp"
#include "utils/math.hpp"

namespace bt
{
    bool __badVal(const int v) { return v == 0; }
    bool __badVal(const rect v) { return (v.width == 0 && v.height == 0) || (v.width > VERY_LARGE_NUM || v.height > VERY_LARGE_NUM); }
    bool __badVal(const std::string &v) { return v == ""; }
}
