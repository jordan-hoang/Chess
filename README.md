# Chess

A simple program that lets one play chess through the shell/openGL window.

Prevents users from placing there own king in Check/Checkmate.
Can undo moves, (command for it not implemented in actual game but is used for other functions)

Doesn't detect stalemate yet.  

-Textbased version works, Graphical version works with mouse input.
  
For text-based ver.  
REQ:  
   cmake  
   boost >= 1.68  
   C++17  



Note: A good amount of the openGL code came from https://learnopengl.com/

For openGL ver.  
  glfw3.3  
  SOIL  
  glm  
  glew  
  glut  
  
  You can get SOIL from google or from here https://github.com/kbranigan/Simple-OpenGL-Image-Library
  just make and install
  
  *Only has been tested on linux.
  
