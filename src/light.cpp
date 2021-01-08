#include "light.hpp"
#include "triangles.hpp"
//#include ""

void VertexLight::interpolate(VertexLight* result, const VertexLight* a, const VertexLight* b, float f) {
    result->ambient = INTERPOLATE(a->ambient, b->ambient, f);
    result->diffuse = INTERPOLATE(a->diffuse, b->diffuse, f);
    result->specular = INTERPOLATE(a->specular, b->specular, f);
}

void VertexLight::init(const Light* light, const glm::vec3* viewPos, Vertex* vertex) {
    // ambient
    this->ambient = light->color * 0.2f;
    
    // diffuse
    glm::vec3 lightDir = glm::normalize(light->position - (glm::vec3)vertex->position);
    float dot = glm::dot(lightDir, (glm::vec3)vertex->normal);
    float diff = glm::max(dot, 0.0f);
    this->diffuse = diff * light->color;

    // specular
    glm::vec3 viewDir = glm::normalize(*viewPos - (glm::vec3)vertex->position);
    glm::vec3 halfwayDir  = glm::normalize(lightDir + viewDir);
    //glm::vec3 halfwayDir  = glm::reflect(-lightDir, *normal);
    float spec = glm::pow(glm::max(glm::dot(halfwayDir, (glm::vec3)vertex->normal), 0.0f), 16.0f);
    this->specular = light->color * 0.5f * spec;
    this->ambient *= vertex->rhw;
    this->diffuse *= vertex->rhw;
    this->specular *= vertex->rhw;
}
