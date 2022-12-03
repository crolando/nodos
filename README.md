# nodos
Example application using the [plano library](https://github.com/crolando/plano)
Plano is designed to be platform agnostic. Nodos is where I develop plano, and Nodos serves to illustrate its use.

Windows and macOS (M1) build instructions and support are available.

## Windows Dependency Description and Windows Binary Links
Nodos builds on Visual Studio 2019

Nodos depends on these binary packages: 
- [SDL2-2.0.22](https://github.com/libsdl-org/SDL/releases/download/release-2.0.22/SDL2-devel-2.0.22-VC.zip) - the windows 64 binaries and headers - you'll want the zip called "SDL2-devel-2.0.22-VC.zip"
- [glew-2.1.0](https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip/download) - windows x64 binaries and headers -0 you'll want the zip called "glew-2.1.0-win32.zip"
Nodos also depends on these source repos:
- [imgui-node-editor](https://github.com/thedmd/imgui-node-editor) - sources from github
- [plano](https://github.com/crolando/plano) - sources from github

## Windows Installation Instructions
1. Manually ownload the four dependencies and nodos, and unzip them into sibling folders named and positioned like this:
![example_node_siblings](https://user-images.githubusercontent.com/1946494/201422130-b5e0532f-9ac7-446f-b60d-7fe183df0702.jpg)
2. Open the nodos/nodos.vcxproj in Visual Studio 2019
3. Open the nodos project, and set the Coniguration Properties > Debugging > Environment line to read like this:
   `PATH=%PATH%;$(ProjectDir)..\glew-2.1.0\bin\Release\x64;$(ProjectDir)..\SDL2-2.0.22\lib\x64`
![example_env_setup](https://user-images.githubusercontent.com/1946494/201411944-7d4e9217-e1ae-406a-80ae-b973ae7fb342.jpg)
4. Now it should compile and run without any issues. 

## MacOS Dependency Description 
Nodos builds on Xcode

Nodos depends on packages from Homebrew package manager: 
- SDL2 - Install homebrew, and install SDL2
- GLEW - Install homebrew, and install GLEW
Nodos also depends on source repos:
- [imgui-node-editor](https://github.com/thedmd/imgui-node-editor) - sources from github
- [plano](https://github.com/crolando/plano) - sources from github

## macOS Installation Instructions
1. install homebrew
2. add the homebrew to your path 
    echo '# Set PATH, MANPATH, etc., for Homebrew.' >> /Users/<username>/.zprofile
    echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> /Users/<usernanme>/.zprofile
    eval "$(/opt/homebrew/bin/brew shellenv)"
3. clone or download the github repo code
4. open the Nodos.xcodeproj 
5. verify that the header search path (search paths > Header Search Paths) align with your homebrew and github folders
6. verify that your library search paths (search paths > library search paths) align with your homebrew folder.  (the github sources will be built and linked by the project)
7. verify the source files are all found.
8. you should be able to build and run nodos now. 
