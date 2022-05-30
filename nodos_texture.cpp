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
    printf("in constructor\n");
    printf("oringal object address: %x\n", this);
    printf("----------------------------------------------\n");
}

// nodos texture destructor
nodos_texture::~nodos_texture() 
{
    printf("in destructor of object: % x\n", this);
    printf("----------------------------------------------\n");
    if (data != nullptr) {
         stbi_image_free(data);
    }
}

nodos_texture::nodos_texture(nodos_texture&& donor)
{
    printf("in copy assign ctor\n");
    printf("address of donor: %x\n", &donor);
    printf("address of recipient: %x\n", this);
    printf("----------------------------------------------\n");
    dim_x = donor.dim_x;
    dim_y = donor.dim_y;
    channel_count = donor.channel_count;
    data = donor.data;
    donor.data = nullptr;
}

nodos_texture& nodos_texture::operator=(const nodos_texture& donor)
{
    
    printf("inside the move assignemnt operator\n");
    printf("address of donor: %x\n", &donor);
    printf("address of recipient: %x\n", this);
    printf("----------------------------------------------\n");
    return *this;
}


