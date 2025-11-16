#ifndef ABSTRACTION_H
#define ABSTRACTION_H

// Window
#define WIDTH CP_System_GetWindowWidth()
#define HEIGHT CP_System_GetWindowHeight()

// Colors
#define Color CP_Color_Create
#define BLACK CP_Color_Create(0, 0, 0, 255)
#define WHITE CP_Color_Create(255, 255, 255, 255)

#define RED CP_Color_Create(255, 0, 0, 255)
#define GREEN CP_Color_Create(0, 255, 0, 255)
#define BLUE CP_Color_Create(0, 0, 255, 255)

#define YELLOW CP_Color_Create(255, 255, 0, 255)

// Shapes and background
#define background CP_Graphics_ClearBackground
#define fill CP_Settings_Fill

#define ellipse CP_Graphics_DrawEllipse
#define rect CP_Graphics_DrawRect

// Input
#define mouseX CP_Input_GetMouseX()
#define mouseY CP_Input_GetMouseY()

// Text
#define text CP_Font_DrawText

#endif // ABSTRACTION_H
