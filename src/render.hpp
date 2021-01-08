#ifndef __RENDER_HPP__
#define __RENDER_HPP__

#include <glm/glm.hpp>
#include "triangles.hpp"
#include <assimp/scene.h>

//=====================================================================
// 坐标变换
//=====================================================================
typedef struct Transform { 
    glm::vec3 camera;
    glm::mat4 world;         // 世界坐标变换
    glm::mat4 view;          // 摄影机坐标变换
    glm::mat4 projection;    // 投影变换
    glm::mat4 transform;     // transform = world * view * projection
    int width, height;             // 屏幕大小
    void update();
    void init(int width, int height);
    int checkCvv(glm::vec4* v);
    glm::vec4 homogenize(glm::vec4* v);
} Transform;

//=====================================================================
// 渲染设备
//=====================================================================
typedef struct RenderDevice {
    Transform transform;      // 坐标变换器
    int width;                  // 窗口宽度
    int height;                 // 窗口高度
    uint32_t **framebuffer;      // 像素缓存：framebuffer[y] 代表第 y行
    float **zbuffer;            // 深度缓存：zbuffer[y] 为第 y行指针
    uint32_t **texture;          // 纹理：同样是每行索引
    int tex_width;              // 纹理宽度
    int tex_height;             // 纹理高度
    float max_u;                // 纹理最大宽度：tex_width - 1
    float max_v;                // 纹理最大高度：tex_height - 1
    int render_state;           // 渲染状态
    uint32_t background;         // 背景颜色
    uint32_t foreground;         // 线框颜色

    void init(int width, int height, void* fb);
    void destroy();
    void setTexture(void *bits, long pitch, int w, int h);
    void clear(int mode);
    void pixel(int x, int y, uint32_t color);
    void line(int x1, int y1, int x2, int y2, uint32_t c);
    uint32_t textureRead(float u, float v);
    void drawScanline(ScanLine *scanline, glm::vec3* lightPos);
    void renderTrap(Trapezoid *trap, glm::vec3* lightPos);
    void transformTriangle(Triangle* triangle);
    void drawPrimitive(const Vertex *v1, const Vertex *v2, const Vertex *v3);
    void drawPlane(Vertex* mesh, int a, int b, int c, int d);
    void drawBox(Vertex* mesh, float theta);
    void drawScene(const aiScene* scene);
    void cameraAtZero(float x, float y, float z);
    void initTexture();
} RenderDevice;

#define RENDER_STATE_WIREFRAME      1		// 渲染线框
#define RENDER_STATE_TEXTURE        2		// 渲染纹理
#define RENDER_STATE_COLOR          4		// 渲染颜色

#endif
