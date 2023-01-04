#ifndef save_load_file_h
#define save_load_file_h

/*
*  Functions to save and load plano graphs.
*/


#include "plano_api.h"
#include <string>
#include <fstream>

// Load project function
// This is "stateful": meaning you must first create a nodos context, and set the context
// Loading will then affect the currently set context.
void load_project_file(const char *file_address)
{
    // Load the project file
    std::ifstream inf(file_address);
    std::stringstream ssbuf;
    ssbuf << inf.rdbuf();
    std::string sbuf = ssbuf.str();
    size_t load_size = sbuf.size();
    plano::api::LoadNodesAndLinksFromBuffer(load_size, sbuf.c_str());
}

// Save project function
// This is "stateful": meaning you must first create a nodos context, and set the context
// Saving will then affect the currently set context.
int save_project_file(const char *file_address)
{
    size_t save_size;
    char* cbuffer  = plano::api::SaveNodesAndLinksToBuffer(&save_size);
    // Save "size" count characters from "cbuffer" to a file.
    FILE* bl;
    bl = fopen(file_address,"w");
    if (!bl)
    {
        printf("failed to open save-file to save project.\n");
        return -1;
    }
    fwrite(cbuffer, sizeof(char), save_size, bl);
    delete cbuffer;
    return 0;
}



#endif /* save_load_file_h */
