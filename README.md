# OpenGL MVP Demo

A modular **OpenGL 3.3** project implementing a clean **Model–View–Projection (MVP)** rendering pipeline.  
Renders a **textured, rotating 3D pyramid** with a structured C++ design.

This implementation is based on concepts from the excellent resource [LearnOpenGL](https://learnopengl.com/), extended and refactored into a more reusable design.

![Demo](demo.gif)

## Features
- MVP transformation pipeline  
- Custom GLSL shaders  
- Textured 3D object  
- Reusable abstractions (VAO, VBO, EBO, Shader, Texture)  
- Minimal dependencies (GLFW, GLAD, GLM, stb_image)  

## Structure
- `Main.cpp` — render loop & MVP logic  
- `Shader` — shader compilation & uniforms  
- `VAO / VBO / EBO` — buffer abstractions  
- `Texture` — image loading & binding  

## Run
- Open `MVP Demo.vcxproj` in Visual Studio  
- Build & run (x64)

## Notes
This repository serves as a foundational layer. To maintain a clean architectural history further developments will be continued in a future repository.
