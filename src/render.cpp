#include "render.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static int a = 0, b = 0, c = 0;
void Transform::update() {
    glm::quat q = glm::quat(glm::radians(glm::vec3(45 + a++, 30, 30)));
    this->world = glm::mat4_cast(q);

    glm::mat4 m = this->view * this->world;
    this->transform = this->projection * m;
}

void Transform::init(int width, int height) {
    float aspect = (float)width / ((float)height);
    this->world = glm::mat4(1.0f);
    this->view = glm::mat4(1.0f);
    this->projection = glm::perspective(3.1415926f * 0.5f, aspect, 1.0f, 500.0f);
    this->width = width;
    this->height = height;
    this->update();
}

glm::vec4 Transform::homogenize(glm::vec4* v) {
    glm::vec4 y;
    float rhw = 1.0f / v->w;
    y.x = (v->x * rhw + 1.0f) * 0.5f * this->width;
    y.y = (1.0f - v->y * rhw) * 0.5f * this->height;
    y.z = v->z * rhw;
    y.w = 1.0f  ;
    return y;
}

int Transform::checkCvv(glm::vec4* v) {
    float width = v->w;	
    int check = 0;
    if (v->z < 0.0f) check |= 1;
    if (v->z >  width) check |= 2;
    if (v->x < -width) check |= 4;
    if (v->x >  width) check |= 8;
    if (v->y < -width) check |= 16;
    if (v->y >  width) check |= 32;
    return check;
}

void RenderDevice::init(int width, int height, void *fb) {
    int need = sizeof(void*) * (height * 2 + 1024) + width * height * 8;
    char *ptr = (char*)malloc(need + 64);
    char *framebuf, *zbuf;
    int j;
    assert(ptr);
    this->framebuffer = (uint32_t**)ptr;
    this->zbuffer = (float**)(ptr + sizeof(void*) * height);
    ptr += sizeof(void*) * height * 2;
    this->texture = (uint32_t**)ptr;
    ptr += sizeof(void*) * 1024;
    framebuf = (char*)ptr;
    zbuf = (char*)ptr + width * height * 4;
    ptr += width * height * 8;
    if (fb != NULL) framebuf = (char*)fb;
    for (j = 0; j < height; j++) {
	this->framebuffer[j] = (uint32_t*)(framebuf + width * 4 * j);
	this->zbuffer[j] = (float*)(zbuf + width * 4 * j);
    }
    this->texture[0] = (uint32_t*)ptr;
    this->texture[1] = (uint32_t*)(ptr + 16);
    memset(this->texture[0], 0, 64);
    this->tex_width = 2;
    this->tex_height = 2;
    this->max_u = 1.0f;
    this->max_v = 1.0f;
    this->width = width;
    this->height = height;
    this->background = 0xc0c0c0;
    this->foreground = 0;
    this->transform.init(width, height);
    this->render_state = RENDER_STATE_WIREFRAME;
}

void RenderDevice::destroy() {
    if (this->framebuffer) 
	free(this->framebuffer);
    this->framebuffer = NULL;
    this->zbuffer = NULL;
    this->texture = NULL;
}

void RenderDevice::setTexture(void *bits, long pitch, int w, int h) {
    char *ptr = (char*)bits;
    int j;
    assert(w <= 1024 && h <= 1024);
    for (j = 0; j < h; ptr += pitch, j++) 	// 重新计算每行纹理的指针
	this->texture[j] = (uint32_t*)ptr;
    this->tex_width = w;
    this->tex_height = h;
    this->max_u = (float)(w - 1);
    this->max_v = (float)(h - 1);
}

void RenderDevice::clear(int mode) {
    int y, x, height = this->height;
    // fb
    for (y = 0; y < this->height; y++) {
	uint32_t *dst = this->framebuffer[y];
	uint32_t cc = (height - 1 - y) * 230 / (height - 1);
	cc = (cc << 16) | (cc << 8) | cc;
	if (mode == 0) cc = this->background;
	for (x = this->width; x > 0; dst++, x--) dst[0] = cc;
    }
    // zb
    for (y = 0; y < this->height; y++) {
	float *dst = this->zbuffer[y];
	for (x = this->width; x > 0; dst++, x--) dst[0] = 0.0f;
    }
}

void RenderDevice::pixel(int x, int y, uint32_t color) {
    if (((uint32_t)x) < (uint32_t) this->width && ((uint32_t)y) < (uint32_t) this->height) {
	this->framebuffer[y][x] = color;
    }
}

void RenderDevice::line(int x1, int y1, int x2, int y2, uint32_t c) {
    int x, y, rem = 0;
    if (x1 == x2 && y1 == y2) {
	pixel(x1, y1, c);
    }	else if (x1 == x2) {
	int inc = (y1 <= y2)? 1 : -1;
	for (y = y1; y != y2; y += inc)
	    pixel(x1, y, c);
	pixel(x2, y2, c);
    }	else if (y1 == y2) {
	int inc = (x1 <= x2)? 1 : -1;
	for (x = x1; x != x2; x += inc)
	    pixel(x, y1, c);
	pixel(x2, y2, c);
    }	else {
	int dx = (x1 < x2)? x2 - x1 : x1 - x2;
	int dy = (y1 < y2)? y2 - y1 : y1 - y2;
	if (dx >= dy) {
	    if (x2 < x1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
	    for (x = x1, y = y1; x <= x2; x++) {
		pixel(x, y, c);
		rem += dy;
		if (rem >= dx) {
		    rem -= dx;
		    y += (y2 >= y1)? 1 : -1;
		    pixel(x, y, c);
		}
	    }
	    pixel(x2, y2, c);
	}	else {
	    if (y2 < y1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
	    for (x = x1, y = y1; y <= y2; y++) {
		pixel(x, y, c);
		rem += dx;
		if (rem >= dy) {
		    rem -= dy;
		    x += (x2 >= x1)? 1 : -1;
		    pixel(x, y, c);
		}
	    }
	    pixel(x2, y2, c);
	}
    }
}

uint32_t RenderDevice::textureRead(float u, float v) {
    int x, y;
    u = u * this->max_u;
    v = v * this->max_v;
    x = (int)(u + 0.5f);
    y = (int)(v + 0.5f);
    x = CMID(x, 0, this->tex_width - 1);
    y = CMID(y, 0, this->tex_height - 1);
    return this->texture[y][x];
}

uint32_t RGB(glm::vec3 color) {
    float r = color.r;
    float g = color.g;
    float b = color.b;
    int R = (int)(r * 255.0f);
    int G = (int)(g * 255.0f);
    int B = (int)(b * 255.0f);
    R = CMID(R, 0, 255);
    G = CMID(G, 0, 255);
    B = CMID(B, 0, 255);
    return (R << 16) | (G << 8) | (B);
}

glm::vec3 RGB(uint32_t color) {
    glm::vec3 vec;
    vec.r = (int) (color >> 16) / 255.0f;
    vec.g = (int) ((color >> 8) % 256) / 255.0f; 
    vec.b = (int) (color % 256) / 255.0f;
    return vec;
}

void RenderDevice::drawScanline(ScanLine *scanline, glm::vec3* lightPos) {
    uint32_t *framebuffer = this->framebuffer[(int)scanline->left.position.y];
    float *zbuffer = this->zbuffer[(int)scanline->left.position.y];
    int render_state = this->render_state;

    int x = scanline->left.position.x, w = scanline->right.position.x;
    float leftx = scanline->left.position.x;
    float lineWidth = scanline->right.position.x - scanline->left.position.x;    

    for(int i = 0; i < lineWidth; i++) {
        x++;    
        if(x >= 0 && x < width) {
            Vertex vt;
            Vertex::interpolate(&vt, &scanline->left, &scanline->right, ((float)i/lineWidth));
            float z = 1.0f / vt.position.z;
	    if (z >= zbuffer[x]) {
		zbuffer[x] = z;
                float vtw = 1.0f / vt.rhw;
		if (render_state & RENDER_STATE_COLOR) {
		    framebuffer[x] = RGB(vt.color);
		}
		if (render_state & RENDER_STATE_TEXTURE) {
                    float u = vt.texCoord.x * vtw;
                    float v = vt.texCoord.y * vtw;
		    //uint32_t cc = textureRead(u, v);
		    glm::vec3 color = vt.color * vtw;
					
		    glm::vec3 l =  (vt.light.ambient + vt.light.diffuse + vt.light.specular) * vtw;
		    //glm::vec3 c = l * textureColor;
		    //uint32_t color = RGB(c);
		    //framebuffer[x] = color;
		    framebuffer[x] = RGB(color * l);
		}
	    }
	}

	if (x >= width) break;
    }
}

// 主渲染函数
void RenderDevice::renderTrap(Trapezoid *trap, glm::vec3* lightPos) {
    ScanLine scanline;
    int j, top, bottom;
    float x = 0.5f;
    top = (int)(trap->top + x);
    bottom = (int)(trap->bottom + x);
    for (j = top; j < bottom; j++) {
	if (j >= 0 && j < this->height) {
	    trap->edgeInterpolate((float)j + x);
	    scanline.init(trap, j);
	    drawScanline(&scanline, lightPos);
	}
	if (j >= this->height) 
	    break;
    }
}

// 根据 render_state 绘制原始三角形
void RenderDevice::drawPrimitive(const Vertex *v1, const Vertex *v2, const Vertex *v3) {
    glm::vec4 p1, p2, p3;
    int render_state = this->render_state;

    glm::vec4 lightPos = glm::vec4(4.0f, 0.0f, 0.0f, 1.0f);
    // 按照 Transform 变化
    glm::vec4 c1 = this->transform.transform * v1->position;
    glm::vec4 c2 = this->transform.transform * v2->position;
    glm::vec4 c3 = this->transform.transform * v3->position;
    glm::vec4 cn1 = this->transform.transform * v1->normal;
    glm::vec4 cn2 = this->transform.transform * v2->normal;
    glm::vec4 cn3 = this->transform.transform * v3->normal;
    glm::vec4 l = this->transform.transform * lightPos;
    glm::vec4 c = this->transform.transform * glm::vec4(this->transform.camera, 1.0f);
    // 裁剪，注意此处可以完善为具体判断几个点在 cvv内以及同cvv相交平面的坐标比例
    // 进行进一步精细裁剪，将一个分解为几个完全处在 cvv内的三角形
    if (this->transform.checkCvv(&c1) != 0) return;
    if (this->transform.checkCvv(&c2) != 0) return;
    if (this->transform.checkCvv(&c3) != 0) return;

    // 归一化
    p1 = this->transform.homogenize(&c1);
    p2 = this->transform.homogenize(&c2);
    p3 = this->transform.homogenize(&c3);
    glm::vec3 ll = this->transform.homogenize(&l);
    glm::vec3 cc = this->transform.homogenize(&c);
    //glm::vec3

    Light light;
    light.position = ll;
    light.color = glm::vec3(1.0f, 0.5, 0.5f);
    // 纹理或者色彩绘制
    if (render_state & (RENDER_STATE_TEXTURE | RENDER_STATE_COLOR)) {
	Vertex t1 = *v1, t2 = *v2, t3 = *v3;
	Trapezoid traps[2];
	int n;

	t1.position = p1; 
	t2.position = p2;
	t3.position = p3;
	t1.position.w = c1.w;
	t2.position.w = c2.w;
	t3.position.w = c3.w;
	t1.normal = cn1;
	t2.normal = cn2;
	t3.normal = cn3;
	//tri.calcNormal();
        t1.initRhw();
        t2.initRhw();
        t3.initRhw();
	t1.light.init(&light, &cc, &t1);
	t2.light.init(&light, &cc, &t2);
	t3.light.init(&light, &cc, &t3);
	//tri.calcLight(&cc, &light);
	Triangle tri = {&t1, &t2, &t3};	    

	// 拆分三角形为0-2个梯形，并且返回可用梯形数量
	n = Trapezoid::generateTrapzoidWithTriangle(traps, &tri);

	if (n >= 1) renderTrap(&traps[0], &ll);
	if (n >= 2) renderTrap(&traps[1], &ll);
    }
}

// void RenderDevice::drawPlane(Vertex* mesh, int a, int b, int c, int d) {
//     Vertex p1 = mesh[a], p2 = mesh[b], p3 = mesh[c], p4 = mesh[d];
//     p1.texCoord.x = 0, p1.texCoord.y = 0, p2.texCoord.x = 0, p2.texCoord.y = 1;
//     p3.texCoord.x = 1, p3.texCoord.y = 1, p4.texCoord.x = 1, p4.texCoord.y = 0;
//     drawPrimitive(&p1, &p2, &p3);
//     drawPrimitive(&p3, &p4, &p1);
// }

// void RenderDevice::drawBox(Vertex* mesh, float theta) {
//     //a = !a;
//     drawPlane(mesh, 0, 1, 2, 3);
//     drawPlane(mesh, 7, 6, 5, 4);
//     drawPlane(mesh, 0, 4, 5, 1);
//     drawPlane(mesh, 1, 5, 6, 2);
//     drawPlane(mesh, 2, 6, 7, 3);
//     drawPlane(mesh, 3, 7, 4, 0);
// }

void RenderDevice::drawScene(const aiScene* scene) {
    for(int m = 0; m < scene->mNumMeshes; m++) {
	aiMesh* mesh = scene->mMeshes[m];
	for(int f = 0; f < mesh->mNumFaces; f++) {
	    aiFace* face = &mesh->mFaces[f];
	    Vertex vertexes[face->mNumIndices];
	    for(int i = 0; i < face->mNumIndices; i++) {
		unsigned int indice = face->mIndices[i];

		aiVector3D* v = &mesh->mVertices[indice];
		aiVector3D* n = &mesh->mNormals[indice];
		aiColor4D* c = mesh->mColors[indice];
		vertexes[i].position = {v->x, v->y, v->z, 1.0f};
		vertexes[i].normal = {n->x, n->y, n->z, 1.0f};
		vertexes[i].color = {1.0f, 0.0f, 0.0f};
	    }
	    this->drawPrimitive(&vertexes[0], &vertexes[1], &vertexes[2]);
	}
    }
}

void RenderDevice::cameraAtZero(float x, float y, float z) {
    glm::vec3 eye = {x, y, z}, center = {0.0f, 0.0f, 0.0f}, up = {0.0f, 0.0f, 1.0f};
    this->transform.camera = eye;
    this->transform.view = glm::lookAt(eye, center, up);
    this->transform.update();
}

void RenderDevice::initTexture() {
    static uint32_t texture[256][256];
    int i, j;
    for (j = 0; j < 256; j++) {
	for (i = 0; i < 256; i++) {
	    int x = i / 32, y = j / 32;
	    texture[j][i] = ((x + y) & 1)? 0xffffff : 0x3fbcef;
	}
    }
    setTexture(texture, 256 * 4, 256, 256);
}
