# nodos
Example application using the [plano library](https://github.com/crolando/plano)
Plano is designed to be platform agnostic. Nodos is where I develop plano, and Nodos serves to illustrate its use.

## Dependency Description and Windows Binary Links
Nodos builds on Visual Studio 2019

Nodos depends on these packages: 
- [SDL2-2.0.22](https://github.com/libsdl-org/SDL/releases/download/release-2.0.22/SDL2-devel-2.0.22-VC.zip) - the windows 64 binaries and headers - you'll want the zip called "SDL2-devel-2.0.22-VC.zip"
- [glew-2.1.0](https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip/download) - windows x64 binaries and headers -0 you'll want the zip called "glew-2.1.0-win32.zip"
- [imgui-node-editor](https://github.com/thedmd/imgui-node-editor) - sources from github
- [plano](https://github.com/crolando/plano) - sources from github

## Windows Installation Instructions
1. Manually ownload the four dependencies, and unzip them into sibling folders named and positioned like this:
![example_node_siblings](https://user-images.githubusercontent.com/1946494/201411014-c34ffe25-7da4-421c-9b61-fd9ed1ba3216.jpg)
2. Open the nodos/nodos.vcxproj in Visual Studio 2019
3. Open the nodos project, and set the Coniguration Properties > Debugging > Environment line to read like this:
   `PATH=%PATH%;$(ProjectDir)..\glew-2.1.0\bin\Release\x64;$(ProjectDir)..\SDL2-2.0.22\lib\x64`
![example_env_setup](https://user-images.githubusercontent.com/1946494/201411944-7d4e9217-e1ae-406a-80ae-b973ae7fb342.jpg)
4. Now it should compile and run without any issues. 

