#include <nodos_texture.h> // For class header

#define STB_IMAGE_IMPLEMENTATION // image loader needs this...
#include <stb_image.h> // image loader

nodos_texture::nodos_texture()
{
    data = nullptr;
    dim_x = 0;
    dim_y = 0;
    channel_count = 0;
}

// Nodos texture constructor
nodos_texture::nodos_texture(const char* filename) 
{
    data = stbi_load(filename, &dim_x, &dim_y, &channel_count, 0);
}

// nodos texture destructor
nodos_texture::~nodos_texture() 
{
    if (data != nullptr) {
         stbi_image_free(data);
    }
}
