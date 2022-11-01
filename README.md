# nodos
Example application using the plano library

Plano is designed to be platform agnostic. Nodos is where I develop plano, and Nodos serves to illustrate its use.

The only guaranteed working project is the visual studio project for x64 windows.

Nodos depends on these items: 
SDL2-2.0.22 - the windows 64 binaries and headers - you'll want the zip called "SDL2-devel-2.0.22-VC.zip"
glew-2.1.0 - windows x64 binaries and headers -0 you'll want the zip called "glew-2.1.0-win32.zip"
imgui-node-editor - sources from github
plano - sources from github
It does not depend on imgui.  imgui-node-editor has patches applied that plano depends on
   (the features added are springs, and fringe scale drawing).
   
Configuring software on windows is an aquired taste.  But if you toss all these dpendencies as sibling folders
to the nodos folder, the visual studio project should work.  Even the debug environment is set up to read the 
DLL files.

