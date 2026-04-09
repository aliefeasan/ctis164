CTIS164 - Technical Mathematics with Programming
Homework #1: Interactive 2D Scene with OpenGL/GLUT
This project is a C-based graphical application developed as part of the CTIS164 course at Bilkent University. It demonstrates basic 2D computer graphics concepts, coordinate transformations, and user interactivity using the OpenGL Utility Toolkit (GLUT).

👨‍💻 Author
Name: Ali Efe Asan

Academic Year: 2025-2026 Spring

🚀 Features
1. Interactive Menu System
The application starts with three main interactive circular buttons at the top:

TITLE: Displays student and course information.

SCENE: Transitions to an animated 2D landscape.

EXIT: Safely terminates the application.

2. Dynamic Visuals & Animations
Animated Police Car: A custom-drawn police car that moves across the screen.

Cloud Movement: Procedural cloud animation moving in the opposite direction of the car.

Environment Design: A detailed 2D scene featuring mountains, a house with windows/doors, and a highway.

3. User Interaction
Hover Effects: Buttons change color and text style when the mouse cursor hovers over them (Passive Motion).

Mouse Clicking: Navigation between screens is handled via precise distance-based collision detection for the circular buttons.

🛠️ Technical Details
Language: C

Library: OpenGL / GLUT

Shapes: Implementation of circles, polygons, lines, and rectangles using glBegin() and glEnd() primitives.

Mathematics: * Trigonometric functions (sin, cos) for circle rendering.

Euclidean distance formula for mouse-click detection.

Coordinate mapping for window resizing.

📸 How to Run
Prerequisites: Ensure you have an IDE (like Visual Studio) configured with the GLUT library.

Compilation: Compile the source code. The project includes #ifdef _MSC_VER to handle secure warnings in Windows environments.

Controls:

Move Mouse: Hover over buttons to see interactions.

Left Click: Click "TITLE" or "SCENE" to switch views.

📜 Academic Integrity
This repository is for educational purposes. If you are a student currently taking the CTIS164 course, please refer to the university's academic integrity policy before using this code.

Bilkent University - CTIS 2026
