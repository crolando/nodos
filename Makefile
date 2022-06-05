#
# Cross Platform Makefile
# Compatible with MSYS2/MINGW, Ubuntu 14.04.1 and Mac OS X
#
# You will need SDL2 (http://www.libsdl.org):
# Linux:
#   apt-get install libsdl2-dev
# Mac OS X:
#   brew install sdl2
# MSYS2:
#   pacman -S mingw-w64-i686-SDL2
#

#CXX = g++
#CXX = clang++

EXE = nodos
PLANO_DIR = ../plano
IGNE_DIR = ../imgui-node-editor
IMGUI_DIR = ../imgui-node-editor/external/imgui
STBI_DIR = ../imgui-node-editor/external/stb_image
UTIL_DIR= ../imgui-node-editor/examples/blueprints-example/utilities
SOURCES += main.cpp imgui_impl_opengl3.cpp imgui_impl_sdl.cpp
SOURCES += $(PLANO_DIR)/attribute.cpp $(PLANO_DIR)/builders.cpp $(PLANO_DIR)/drawing.cpp
SOURCES += $(IGNE_DIR)/imgui_canvas.cpp $(IGNE_DIR)/imgui_node_editor.cpp $(IGNE_DIR)/imgui_node_editor_api.cpp
SOURCES += $(PLANO_DIR)/example_property_im_draw.cpp $(PLANO_DIR)/imgui_stdlib.cpp $(PLANO_DIR)/node_registry.cpp
SOURCES += $(PLANO_DIR)/node_turnkey_api.cpp $(PLANO_DIR)/node_turnkey_draw_nodes.cpp $(PLANO_DIR)/node_turnkey_frame.cpp
SOURCES += $(PLANO_DIR)/node_turnkey_handle_interactions.cpp $(PLANO_DIR)/node_turnkey_internal.cpp $(PLANO_DIR)/widgets.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(UTIL_DIR)/builders.cpp $(UTIL_DIR)/drawing.cpp $(UTIL_DIR)/widgets.cpp $(IGNE_DIR)/crude_json.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
UNAME_S := $(shell uname -s)
LINUX_GL_LIBS = -lGL -lGLEW

CXXFLAGS = -std=c++14 -I$(PLANO_DIR) -I$(IGNE_DIR) -I$(IMGUI_DIR) -I$(STBI_DIR) -I$(UTIL_DIR) -I./
CXXFLAGS += -g -Wall -Wformat -fpermissive -DIMGUI_IMPL_OPENGL_ES2
LIBS =

##---------------------------------------------------------------------
## OPENGL ES
##---------------------------------------------------------------------

## This assumes a GL ES library available in the system, e.g. libGLESv2.so
# CXXFLAGS += -DIMGUI_IMPL_OPENGL_ES2
LINUX_GL_LIBS = -lGLESv2
## If you're on a Raspberry Pi and want to use the legacy drivers,
## use the following instead:
# LINUX_GL_LIBS = -L/opt/vc/lib -lbrcmGLESv2

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LIBS += $(LINUX_GL_LIBS) -ldl `sdl2-config --libs`

	CXXFLAGS += `sdl2-config --cflags`
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "Mac OS X"
	LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo `sdl2-config --libs`
	LIBS += -L/usr/local/lib -L/opt/local/lib

	CXXFLAGS += `sdl2-config --cflags`
	CXXFLAGS += -I/usr/local/include -I/opt/local/include
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(OS), Windows_NT)
    ECHO_MESSAGE = "MinGW"
    LIBS += -lgdi32 -lopengl32 -limm32 `pkg-config --static --libs sdl2`

    CXXFLAGS += `pkg-config --cflags sdl2`
    CFLAGS = $(CXXFLAGS)
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(PLANO_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IGNE_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(STBI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(UTIL_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(EXE) $(OBJS)
