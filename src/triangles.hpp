#ifndef __TRIANGLES_HPP__
#define __TRIANGLES_HPP__

#include <glm/glm.hpp>
#include "light.hpp"

#define INTERPOLATE(A, B, F) A + ((B - A) * F)
#define SWAP(A, B) {auto temp = A; A = B; B = temp;}
int CMID(int x, int min, int max);
float interpolate(float a, float b, float f);

typedef struct Vertex { 
    glm::vec4 position;
    glm::vec2 texCoord;
    glm::vec3 color;
    glm::vec4 normal;
    float rhw;
    VertexLight light;

    void initRhw();
    void add(const Vertex* v);
    static void interpolate(Vertex* result, const Vertex* a, const Vertex* b, float f);
    static void division(Vertex* result, const Vertex* a, const Vertex* b, float w);
    
} Vertex;

typedef struct Triangle {
    Vertex* vertices[3];
} Triangle;

typedef struct Edge {
    Vertex v, v1, v2;
} Edge;
typedef struct Trapezoid {
    float top, bottom;
    Edge left, right;
    void edgeInterpolate(float y);
    static int generateTrapzoidWithTriangle(Trapezoid* traps, Triangle* triangle);
} Trapezoid;

typedef struct ScanLine {
    Vertex left, right;
    glm::vec3* normal;
    void init(const Trapezoid* trapzoid, int y);
} ScanLine;

typedef struct Camera {
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;
} Camera;

// enum LIGHT_TYPE {
//     LIGHT_PARALLEL = 1,
//     LIGHT_POINT
// };

// typedef struct Light {
//     LIGHT_TYPE type;
//     union {
//         glm::vec3 direction; // parallel
//         glm::vec3 position; // point
//     };
//     glm::vec3 color;
// } Light;

// typedef struct VertexLight {
//     glm::vec3 ambient;
//     glm::vec3 diffuse;
//     glm::vec3 specular;
//     void init(const Light* light, const glm::vec3* viewPos, const glm::vec3* position, const glm::vec3* normal, float rhw);
//     static void interpolate(VertexLight* result, const VertexLight* a, const VertexLight* b, float f);
// } VertexLight;

// typedef struct Scene {
//     Mesh* meshes;
//     uint32_t meshNum;
// } Mesh;

#endif
