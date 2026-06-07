#pragma once // Захист від подвійного включення

#include <vector>
#include <string>
#include <iostream>
#include <glm/glm.hpp>

// Підключаємо бібліотеку, але БЕЗ макросу IMPLEMENTATION!
#include "tiny_obj_loader.h"

// 1. Наша структура
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

// 2. Функція завантаження
// Додаємо слово 'inline', щоб C++ не сварився, якщо ти колись
// підключиш цей файл до кількох різних .cpp файлів
inline bool loadOBJ(const char* path, std::vector<Vertex>& out_vertices, std::vector<unsigned int>& out_indices) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path)) {
        std::cerr << "Помилка завантаження OBJ: " << warn << err << std::endl;
        return false;
    }

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex;

            vertex.Position = {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2]
            };

            if (index.normal_index >= 0) {
                vertex.Normal = {
                        attrib.normals[3 * index.normal_index + 0],
                        attrib.normals[3 * index.normal_index + 1],
                        attrib.normals[3 * index.normal_index + 2]
                };
            } else {
                vertex.Normal = {0.0f, 0.0f, 0.0f};
            }

            if (index.texcoord_index >= 0) {
                vertex.TexCoords = {
                        attrib.texcoords[2 * index.texcoord_index + 0],
                        1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
                };
            } else {
                vertex.TexCoords = {0.0f, 0.0f};
            }

            out_vertices.push_back(vertex);
            out_indices.push_back(out_indices.size());
        }
    }
    std::cout << "Successfully enchanted: " << path << " (" << out_vertices.size() << " vertex)" << std::endl;
    return true;
}