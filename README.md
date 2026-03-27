# 🔺 OpenGL MVP Demo

A modular **OpenGL 3.3+** project demonstrating a clean rendering pipeline using the **Model–View–Projection (MVP)** transformation system.
This project renders a **textured, rotating 3D pyramid** while showcasing a structured, object-oriented approach to OpenGL.

This implementation is based on concepts from the excellent resource [LearnOpenGL](https://learnopengl.com/), extended and refactored into a more reusable design.

This repository serves as a foundational layer. To maintain a clean architectural history further developments will be continued in a future repository.

---

## 🎥 Demo

![Demo](demo.gif)

---

## 🎯 Purpose

This project focuses on:

* Understanding the graphics pipeline
* Writing maintainable C++ code
* Designing reusable rendering components

---


## 🚀 Features

* Modern OpenGL (Core Profile, 3.3+)
* MVP transformation pipeline (Model, View, Projection)
* Textured 3D object (pyramid)
* Custom shader system (GLSL)
* Clean abstraction of OpenGL objects
* Minimal dependencies (GLFW, GLAD, GLM, stb_image)

---

## 🧱 Project Structure

```
MVP Demo/
│
├── Main.cpp              # Entry point and render loop
├── shaderClass.*         # Shader compilation & uniform handling
├── VAO.*                 # Vertex Array Object abstraction
├── VBO.*                 # Vertex Buffer Object abstraction
├── EBO.*                 # Element Buffer Object abstraction
├── Texture.*             # Texture loading & binding (stb_image)
│
├── default.vert          # Vertex shader
├── default.frag          # Fragment shader
├── stone.png             # Texture
│
├── Libraries/
│   ├── include/          # Header-only dependencies (GLFW, GLAD, GLM, stb)
│   └── lib/              # Precompiled libraries (glfw3.lib)
│
└── x64/                  # Build output
```

---

## 🧠 Architecture Overview

This project avoids messy OpenGL code by wrapping core functionality into reusable classes:

### Core Components

* **Shader**

  * Compiles and links GLSL shaders
  * Handles uniform uploads (matrices, textures, etc.)

* **VAO (Vertex Array Object)**

  * Stores vertex attribute configurations

* **VBO / EBO**

  * Manage vertex data and indices

* **Texture**

  * Loads images using `stb_image`
  * Binds textures for rendering

* **Main.cpp**

  * Initializes window/context
  * Handles the render loop
  * Applies MVP transformations

---


## 🛠️ Dependencies

This project includes all required libraries locally:

* GLFW (window/context)
* GLAD (OpenGL loader)
* GLM (math library)
* stb_image (image loading)

No external installation required.

---

## ▶️ How to Build & Run

### Requirements

* Windows
* Visual Studio (recommended)

### Steps

1. Open:

   ```
   MVP Demo.vcxproj
   ```

   in Visual Studio

2. Set configuration:

   * **x64**
   * **Debug** or **Release**

3. Build and run:

   ```
   Ctrl + F5
   ```

---

## 🎮 Controls

| Key | Action           |
| --- | ---------------- |
| ESC | Exit application |

---

## 📸 Output

The program displays:

* A rotating 3D pyramid
* Textured with `stone.png`
* Rendered using a perspective camera

---


## 📌 Future Improvements

* Multiple objects
* Camera movement
* Lighting
* Transparency and blending
* Anti-Aliasing

---
