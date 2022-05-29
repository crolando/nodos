#ifndef texture_manager_H
#define texture_manager_H

class nodos_texture {
public:
    nodos_texture();
    nodos_texture(const char* filename);
    ~nodos_texture();
    int dim_x, dim_y, channel_count;
    unsigned char* data;
};

#endif // texture_manager_H
