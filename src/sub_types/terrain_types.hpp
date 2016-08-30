#ifndef TERRAIN_TYPES_HPP
#define TERRAIN_TYPES_HPP

enum terrain_type_e {STONE, SNOW};
static std::map< terrain_type_e, double> g_terrain_speed_modifier = {{STONE, 0.0}, {SNOW, 0.5}};
#endif

