#ifndef texture_manager_H
#define texture_manager_H
#include <memory>
#include <unordered_map>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

class nodos_texture {
public:
    nodos_texture(const char* filename) {
        data = stbi_load(filename, &dim_x, &dim_y, &channel_count, 0);
    }
    ~nodos_texture() {
        if (data != nullptr) {
            stbi_image_free(data);
        }
    }
    int dim_x, dim_y, channel_count;
    unsigned char* data;
};

class texture_manager {

public:
    static void* LoadTexture(char const*);
    static void DestroyTexture(void*);
    static int GetTextureWidth(void*);
    static int GetTextureHeight(void*);

private:
    static std::unordered_map<GLuint, std::unique_ptr<nodos_texture>> texture_owner;
};

#endif // texture_manager_H
