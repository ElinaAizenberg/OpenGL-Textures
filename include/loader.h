#ifndef PROJECT_4_LOADER_H
#define PROJECT_4_LOADER_H

#include <string>
#include <vector>
#include "tiny_obj_loader.h"

class ObjectLoader
{
public:

    static void loadObjFileData(const std::string &filepath,
                                std::vector<float> &object_vertices,
                                std::vector<float> &object_normals,
                                std::vector<float> &object_texture_coordinates);
};

#endif //PROJECT_4_LOADER_H
