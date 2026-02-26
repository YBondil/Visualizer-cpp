#pragma once
#include <string>
#include "Obj_visu.h"

namespace VISU {
    OBJ_VISU::Object_3D* load_stl(const std::string& filepath, SDL_Color color);
}