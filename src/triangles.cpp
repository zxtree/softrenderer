#include "triangles.hpp"

#include <memory.h>

int CMID(int x, int min, int max) { 
    return (x < min)? min : ((x > max)? max : x); 
}

float interpolate(float a, float b, float f) { 
    return INTERPOLATE(a, b, f);
}

void Vertex::initRhw() {
    float rhw = 1.0f / this->position.w;
    this->rhw = rhw;
    this->texCoord *= rhw;
    this->color *= rhw;
}

void Vertex::interpolate(Vertex* result, const Vertex* a, const Vertex* b, float f) {
	result->position = INTERPOLATE(a->position, b->position, f);
	result->texCoord = INTERPOLATE(a->texCoord, b->texCoord, f);
	result->color = INTERPOLATE(a->color, b->color, f);
	VertexLight::interpolate(&result->light, &a->light, &b->light, f);
    result->rhw = INTERPOLATE(a->rhw, b->rhw, f);
}

void Vertex::division(Vertex* result, const Vertex* a, const Vertex* b, float w) {
	float inv = 1.0f / w;
	result->position = (b->position - a->position) * inv;
	result->texCoord = (b->texCoord - a->texCoord) * inv;
	result->color = (b->color - a->color) * inv;
    result->rhw = (b->rhw - a->rhw) * inv;
}

void Vertex::add(const Vertex* v) {
	this->position += v->position;
	this->texCoord += v->texCoord;
	this->color += v->color;
    this->rhw += v->rhw;
}

// void Triangle::calcNormal() {
// 	glm::vec3 e1 = glm::vec3(vertices[2]->position - vertices[0]->position);
// 	glm::vec3 e2 = glm::vec3(vertices[1]->position - vertices[0]->position);
// 	this->normal = glm::normalize(glm::cross(e1, e2));
// }

// void Triangle::calcLight(glm::vec3* camera, Light* light) {
// 	for(int i = 0; i < 3; i++) {
// 		glm::vec3 pos = glm::vec3(this->vertices[i]->position);
// 		this->vertices[i]->light.init(light, camera, &pos, &this->normal, this->vertices[i]->rhw);
// 	}
// }

// 根据三角形生成 0-2 个梯形，并且返回合法梯形的数量
int Trapezoid::generateTrapzoidWithTriangle(Trapezoid* traps, Triangle* triangle) {
	Vertex* a = (Vertex*)triangle->vertices[0];
	Vertex* b = (Vertex*)triangle->vertices[1];
	Vertex* c = (Vertex*)triangle->vertices[2];
	if(a->position.y > b->position.y) SWAP(a, b);
	if(a->position.y > c->position.y) SWAP(a, c);
	if(b->position.y > c->position.y) SWAP(b, c);
	if(a->position.y == b->position.y && a->position.y == c->position.y) return 0;
	if(a->position.x == b->position.x && a->position.x == c->position.x) return 0;

	// triangle down \-/
	if(a->position.y == b->position.y) {
		if(a->position.x > b->position.x) SWAP(a, b);
		if(a->position.y < c->position.y) return 0;
		traps[0].top = a->position.y;
		traps[0].bottom = c->position.y;
		traps[0].left.v1 = *a;
		traps[0].left.v2 = *b;
		traps[0].right.v1 = *a;
		traps[0].right.v2 = *c;
		return 1;
	}

	//triangle up /_|
	if(b->position.y == c->position.y) {
		if(b->position.x > c->position.x) SWAP(b, c);
		if(a->position.y < c->position.y) return 0;
		traps[0].top = a->position.y;
		traps[0].bottom = c->position.y;
		traps[0].left.v1 = *a;
		traps[0].left.v2 = *b;
		traps[0].right.v1 = *a;
		traps[0].right.v2 = *c;
		return 1;
	}

	traps[0].top = a->position.y;
	traps[0].bottom = b->position.y;
	traps[1].top = b->position.y;
	traps[1].bottom = c->position.y;

	float k, x;
	k = (c->position.y - a->position.y) / (b->position.y - a->position.y);
	x = a->position.x + (b->position.x - a->position.x) * k;

	// triangle left
	if(x <= c->position.x) {
		traps[0].left.v1 = *a;
		traps[0].left.v2 = *b;
		traps[0].right.v1 = *a;
		traps[0].right.v2 = *c;
		traps[1].left.v1 = *b;
		traps[1].left.v2 = *c;
		traps[1].right.v1 = *a;
		traps[1].right.v2 = *c;
	}
	// triangle right
	else {
		traps[0].left.v1 = *a;
		traps[0].left.v2 = *c;
		traps[0].right.v1 = *a;
		traps[0].right.v2 = *b;
		traps[1].left.v1 = *a;
		traps[1].left.v2 = *c;
		traps[1].right.v1 = *b;
		traps[1].right.v2 = *c;
	}

	return 2;
}

// 按照 Y 坐标计算出左右两条边纵坐标等于 Y 的顶点
void Trapezoid::edgeInterpolate(float y) {
	float leftHeight = left.v2.position.y - left.v1.position.y;
	float rightHeight = right.v2.position.y - right.v1.position.y;

	float tl = (y - left.v1.position.y) / leftHeight;
	float tr = (y - right.v1.position.y) / rightHeight;

	Vertex::interpolate(&left.v, &left.v1, &left.v2, tl);
	Vertex::interpolate(&right.v, &right.v1, &right.v2, tr);
}

void ScanLine::init(const Trapezoid* trapzoid, int y) {
    this->left = trapzoid->left.v;
    
    this->right = trapzoid->right.v;
}
