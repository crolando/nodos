// NODOS
// SDL2-implementation-specific main loop
// Mostly code copied from:
// Dear ImGui: standalone example application for SDL2 + OpenGL
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>

// Glew is not used during ES use
#ifdef IMGUI_IMPL_OPENGL_ES2
    #include <SDL_opengles2.h>
#else
    #include "GL/glew.h" // must be included before opengl
    #include <SDL_opengl.h>
#endif

#include "draw_triangle.h"

#include <plano_api.h>
#include "save_load_file.h"
#define STB_IMAGE_IMPLEMENTATION // image loader needs this...
#include "internal/stb_image.h"

// We use fopen and Visual Studio doesn't like that. so we tell VS to relax
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

// Texture Handling Stuff
#include <unordered_map>
#include "nodos_texture.h"
std::unordered_map<GLuint, nodos_texture> texture_owner;

// Node definitions
#include "node_defs/import_animal.h"
#include "node_defs/blueprint_demo.h"
#include "node_defs/widget_demo.h"


// Implement Callbacks
ImTextureID NodosLoadTexture(const char* path)
{   
    // Texture metadata like height/width & layer count.
    nodos_texture meta_tex; 

    // Load pixel data into ram
    unsigned char* pixels = stbi_load(path, &meta_tex.dim_x, &meta_tex.dim_y, &meta_tex.channel_count, 0);
    if (pixels == nullptr) {
        exit(-1);
    }

    // Ask OpenGl to reserve a space in vram for a "texture object", and store that object's Id number into the 2nd argument.
    GLuint GlTextureId;    
    glGenTextures(1, &GlTextureId);

    // Tell opengl to "plug in" the "texture object ID" into "the GL_TEXTURE_2D Slot of the state machine".
    glBindTexture(GL_TEXTURE_2D, GlTextureId);
    
    // Upload pixels to GPU, construct texture object, store result in "whatever ID is plugged into the GL_TEXTURE_2D slot".  
    int mip_map_level = 0;
    auto channel_arrangement = GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, channel_arrangement, meta_tex.dim_x, meta_tex.dim_y, 0, channel_arrangement, GL_UNSIGNED_BYTE, pixels);

    // Destroy the ram copy of pixel data, now that it is in vram.
    stbi_image_free(pixels);

    // Configure the texture properties
    glGenerateMipmap(GL_TEXTURE_2D);
    
    // Store the texture metadata into a list accessed by an ID so we can service the other callbacks.
    texture_owner[GlTextureId] = meta_tex;
    return (ImTextureID)GlTextureId;
}

void NodosDestroyTexture(ImTextureID texture)
{
    //restore our GLuint from our void*
    GLuint gid = (GLuint)(size_t)texture;

    //delete the texture on the graphics card side.
    glDeleteTextures(0, &gid);

    // destroy the nodos_texture and key-value-pair in the map
    texture_owner.erase(gid);
}

unsigned int NodosGetTextureWidth(ImTextureID texture)
{
    //restore our GLuint from our void*
    GLuint gid = (GLuint)(size_t)texture;

    // use hash table to lookup the metadata
    return texture_owner[gid].dim_x;

}

unsigned int NodosGetTextureHeight(ImTextureID texture)
{
    //restore our GLuint from our void*
    GLuint gid = (GLuint)(size_t)texture;

    // use hash table to lookup the metadata
    return texture_owner[gid].dim_y;
}

// Main 
int main(int, char**)
{
    // Setup SDL
    // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
    // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // Decide GL+GLSL versions
    #if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    #elif defined(__APPLE__)
    // GL 3.2 Core + GLSL 150
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    #else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    #endif

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL3 example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
    #if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    bool err = gl3wInit() != 0;
    #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    bool err = glewInit() != GLEW_OK;
    #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    bool err = gladLoadGL() == 0;
    #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
    bool err = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress) == 0; // glad2 recommend using the windowing library loader instead of the (optionally) bundled one.
    #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
    bool err = false;
    glbinding::Binding::initialize();
    #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
    bool err = false;
    glbinding::initialize([](const char* name) { return (glbinding::ProcAddress)SDL_GL_GetProcAddress(name); });
    #else
    bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
    #endif
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark(); // Setup Dear ImGui style
    
    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Plano Initialization
    plano::types::ContextCallbacks cbk;           // Callback Setup
    cbk.LoadTexture = NodosLoadTexture;           // Fill in the function pointers with our callbacks defined before main().
    cbk.DestroyTexture = NodosDestroyTexture;     // This fills in the address of NodosDestroyTexture()
    cbk.GetTextureHeight = NodosGetTextureHeight; // ...
    cbk.GetTextureWidth = NodosGetTextureWidth;
    
    // Create a plano context
    plano::types::ContextData* context_a;
    context_a = plano::api::CreateContext(cbk, "../plano/data/");
    
    // Make context_a the "active context"
    // Note: you can have multple contexts. All plano::api calls after a "SetContext" affect that "active" context.
    plano::api::SetContext(context_a);
    
    // Register node types to the context that is "active"
    plano::api::RegisterNewNode(node_defs::blueprint_demo::InputActionFire::ConstructDefinition());
    plano::api::RegisterNewNode(node_defs::blueprint_demo::OutputAction::ConstructDefinition());
    plano::api::RegisterNewNode(node_defs::blueprint_demo::Branch::ConstructDefinition());
    plano::api::RegisterNewNode(node_defs::blueprint_demo::DoN::ConstructDefinition());
    plano::api::RegisterNewNode(node_defs::blueprint_demo::SetTimer::ConstructDefinition());
    plano::api::RegisterNewNode(node_defs::blueprint_demo::SingleLineTraceByChannel::ConstructDefinition());
    plano::api::RegisterNewNode(node_defs::blueprint_demo::PrintString::ConstructDefinition());
    plano::api::RegisterNewNode(node_defs::import_animal::ConstructDefinition());
    plano::api::RegisterNewNode(node_defs::widget_demo::BasicWidgets::ConstructDefinition());
    plano::api::RegisterNewNode(node_defs::widget_demo::TreeDemo::ConstructDefinition());
    plano::api::RegisterNewNode(node_defs::widget_demo::PlotDemo::ConstructDefinition());
    load_project_file("nodos_project_a.txt"); // deserialize a project into this context (uses the nodes that were registered)
    
    // Variables to track sample window behaviors
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // setup for off-screen triangle rasterization
    GLint attribute_coord2d;
    GLuint program, vbo, fbo, render_texture;
    draw_triangle_setup(program, attribute_coord2d, vbo); // shader & buffer setup.
    glGenFramebuffers(1, &fbo); // stack allocation of fbo
    glBindFramebuffer(GL_FRAMEBUFFER, fbo); // attach to state machine    
    glGenTextures(1, &render_texture); // stack allocation of render_texture
    glBindTexture(GL_TEXTURE_2D, render_texture); // attach to state machine

    // instantiate object & assign to GL_TEXTURE_2D
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // filtering

    // Configure framebuffer.  Important: Render textures and FBOs are not the same.
    // This command says "given the state, attach render_texture to fbo's GL_Color_Attachament0 slot"
    // First argument: render_texture is read/write
    // Second argument: render_texture attaches to attachment0 point
    // third arguement: render_texture's variable
    // fourth argument: mip map level
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, render_texture, 0); 
    glDrawBuffer(GL_COLOR_ATTACHMENT0);  // Says which attachment point to render to (later)

    // Always check that our framebuffer is ok
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        printf("something went wrong with framebuffer setup");
        return -1;
    }

    // Main draw loop
    bool done = false;
    while (!done)
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        // Render Triangle ~~~~
        
        // Render to our framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glViewport(0, 0, 256, 256);                 
        glClear(GL_COLOR_BUFFER_BIT);
        glEnableVertexAttribArray(attribute_coord2d);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(attribute_coord2d);
        
        
        // render to screen from here on...
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();


        // 1. Show the active plano node graph window context
        plano::api::Frame();
        
        // 2. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 3. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Image((ImTextureID)render_texture, ImVec2(256, 256));
            ImGui::End();
        }

        // 4. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering 
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    } // End of draw loop.  Shutdown requested beyond here...

    // Write save file from active context
    save_project_file("nodos_project_a.txt");
    

    // Cleanup
    plano::api::DestroyContext(context_a);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
