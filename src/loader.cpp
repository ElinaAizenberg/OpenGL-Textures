
#include <iostream>

#include "../include/loader.h"


void ObjectLoader::loadObjFileData(const std::string &filepath,
                                   std::vector<float> &object_vertices,
                                   std::vector<float> &object_normals,
                                   std::vector<float> &object_texture_coordinates)
{
    tinyobj::ObjReaderConfig reader_config;
    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(filepath, reader_config))
    {
        if (!reader.Error().empty())
        {
            std::cerr << "TinyObjReader: " << reader.Error();
            throw reader.Error();
        }
        exit(1);
    }

    if (!reader.Warning().empty() && reader.Warning().find("Material") == std::string::npos)
    {
        std::cout << "TinyObjReader: " << reader.Warning();
        throw reader.Warning();
    }

    tinyobj::attrib_t attrib    = reader.GetAttrib();
    std::vector<tinyobj::shape_t> shapes    = reader.GetShapes();

    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                tinyobj::real_t vx = attrib.vertices[3*size_t(idx.vertex_index)+0];
                tinyobj::real_t vy = attrib.vertices[3*size_t(idx.vertex_index)+1];
                tinyobj::real_t vz = attrib.vertices[3*size_t(idx.vertex_index)+2];
                object_vertices.push_back(vx);
                object_vertices.push_back(vy);
                object_vertices.push_back(vz);


                // Check if `normal_index` is zero or positive. negative = no normal data
                if (idx.normal_index >= 0) {
                    tinyobj::real_t nx = attrib.normals[3*size_t(idx.normal_index)+0];
                    tinyobj::real_t ny = attrib.normals[3*size_t(idx.normal_index)+1];
                    tinyobj::real_t nz = attrib.normals[3*size_t(idx.normal_index)+2];
                    object_normals.push_back(nx);
                    object_normals.push_back(ny);
                    object_normals.push_back(nz);

                }

                // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                if (idx.texcoord_index >= 0) {
                    tinyobj::real_t tx = attrib.texcoords[2*size_t(idx.texcoord_index)+0];
                    tinyobj::real_t ty = attrib.texcoords[2*size_t(idx.texcoord_index)+1];
                    object_texture_coordinates.push_back(tx);
                    object_texture_coordinates.push_back(ty);

                }
            }
            index_offset += fv;
        }
    }
}
