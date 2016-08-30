#ifndef COMPONENT_TERRAIN_TYPE_HPP
#define COMPONENT_TERRAIN_TYPE_HPP

#include "entityx/entityx.h"
#include "../sub_types/terrain_types.hpp"

struct terrain_type : entityx::Component<terrain_type> {
    terrain_type(std::string type_name, terrain_type_e type)
        : m_type(type), m_speed_modifier(g_terrain_speed_modifier.find(type)->second) {
    }
    terrain_type_e m_type;
    double m_speed_modifier;
};

#endif

