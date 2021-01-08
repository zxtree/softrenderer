#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

#include <glm/glm.hpp>

enum LIGHT_TYPE {
    LIGHT_PARALLEL = 1,
    LIGHT_POINT
};

typedef struct Light {
    LIGHT_TYPE type;
    union {
        glm::vec3 direction; // parallel
        glm::vec3 position; // point
    };
    glm::vec3 color;
} Light;

struct Vertex;

typedef struct VertexLight {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    void init(const Light* light, const glm::vec3* viewPos, Vertex* vertex);
    static void interpolate(VertexLight* result, const VertexLight* a, const VertexLight* b, float f);
} VertexLight;

/**
    // ambient
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // 
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - fragPos);
    //vec3 reflectDir = reflect(-lightDir, norm);

    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 16.0);


    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

            
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
*/
#endif 
