#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_LEFT_HANDED

#include <SDL2/SDL.h>

#include "render.hpp"
#include <google/profiler.h>
#include "scene.hpp"

int main() {
    ProfilerStart("profile.prof");
    int windowWidth = 800;
    int windowHeight = 600;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Event e;
    SDL_Window* window;
    SDL_Surface* screen;

    window = SDL_CreateWindow(
			      "title",
			      SDL_WINDOWPOS_UNDEFINED,
			      SDL_WINDOWPOS_UNDEFINED,
			      windowWidth,
			      windowHeight,
			      SDL_WINDOW_BORDERLESS);

    screen = SDL_GetWindowSurface(window);

    RenderDevice device;
    float alpha = 1.0;
    device.init(windowWidth, windowHeight, NULL);

    device.initTexture();
    device.render_state = RENDER_STATE_TEXTURE;
    device.cameraAtZero(4.0f, 0.0f, 0.0f);

    const aiScene* scene = aiImportFile("./resources/box.dae", aiProcessPreset_TargetRealtime_MaxQuality);
    //    int a = loadAsset("./resources/box.dae", &scene);
    //printf("a: %d\n", a);

    // Vertex mesh[8] = {
    // 		      { { -1, -1,  1, 1 }, { 0, 0 }, { 1.0f, 0.2f, 0.2f } },
    // 		      { {  1, -1,  1, 1 }, { 0, 1 }, { 0.2f, 1.0f, 0.2f } },
    // 		      { {  1,  1,  1, 1 }, { 1, 1 }, { 0.2f, 0.2f, 1.0f } },
    // 		      { { -1,  1,  1, 1 }, { 1, 0 }, { 1.0f, 0.2f, 1.0f } },
    // 		      { { -1, -1, -1, 1 }, { 0, 0 }, { 1.0f, 1.0f, 0.2f } },
    // 		      { {  1, -1, -1, 1 }, { 0, 1 }, { 0.2f, 1.0f, 1.0f } },
    // 		      { {  1,  1, -1, 1 }, { 1, 1 }, { 1.0f, 0.3f, 0.3f } },
    // 		      { { -1,  1, -1, 1 }, { 1, 0 }, { 0.2f, 1.0f, 0.3f } },
    // };

    int _exit = 0;
    while(!_exit) {
	while(SDL_PollEvent(&e)) {
	    if(e.type == SDL_QUIT)
		_exit = 1;
	    if(e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_ESCAPE) {
		    _exit = 1;
                }
            }
	}

	device.clear(1);
	device.transform.update();
	//device.drawBox(mesh, alpha);
	device.drawScene(scene);

	SDL_LockSurface(screen);
	Uint32* pixels = (Uint32*)screen->pixels;
	for(int y = 0; y < windowHeight; y++) {
	    Uint32* row = device.framebuffer[y];
	    for(int x = 0; x < windowWidth; x++) {
		*(pixels + (y * windowWidth) + x ) = row[x];
	    }
	}
	SDL_UnlockSurface(screen);
	SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);

    ProfilerStop();
    return 0;
}
