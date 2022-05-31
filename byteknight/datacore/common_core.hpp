#ifndef CORE_COMMON_HPP
#define CORE_COMMON_HPP

#include "common.hpp"
#include "math/math.hpp"
#include "object_core.hpp"


namespace Render {
    typedef unsigned int Order;
    const Order First = 2147483647; // -1
    const Order Last = 2147483646;  // -2
    struct OrderedObject { Object::ID id; Order order; };
    struct RenderOrder
    {
        bool operator()(const OrderedObject& lhs, const OrderedObject& rhs) const {
            switch(rhs.order) {
                // todo -- i might have this backwards
                case First: return false;
                case Last: return true;
                default: break;
            }
            if (lhs.order == rhs.order)
                return lhs.id < rhs.id;
            return lhs.order < rhs.order;
        }
    };

    typedef std::priority_queue<OrderedObject, std::vector<OrderedObject>, RenderOrder> Queue;
}

namespace Meta
{
    struct gamedata {
        SQ::rect board_size, tile_size, pxl_size;
        unsigned int total_tiles;
    };
}

#endif // CORE_COMMON_HPP
