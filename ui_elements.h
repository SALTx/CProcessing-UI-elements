#ifndef UI_ELEMENTS_H
#define UI_ELEMENTS_H

#include "shape_utils.h"

typedef struct {
	CP_Color defaultColor;
	CP_Color hoverColor;
	CP_Color strokeColor;
	float strokeWeight;
} UI_Style;

typedef struct {
	CP_Color primaryColor;
	CP_Color secondaryColor;
	float fontSize;
} Font_Style;

typedef struct {
	Quad properties;
	char value[32];
	UI_Style uiStyle;
	Font_Style fontStyle;
	FunctionPtr onClick;
} Button;

typedef struct {
	Quad properties;
	int* value;
	FunctionPtr onClick;
} Checkbox;

typedef struct {
	Quad properties;
	float min, max;
	float* value;
	CP_Color color;
	CP_Color backgroundColor;
} ProgressBar;

typedef struct {
	Quad properties;
	float min, max;
	float* value;
	CP_Color primaryColor;
	CP_Color secondaryColor;
	CP_Color backgroundColor;
	FunctionPtr onChange;
} Slider;

typedef struct {
	Quad properties;
	char* value;
	UI_Style uiStyle;
	Font_Style fontStyle;
} TextBox;


void drawButton(Button button);
void drawCheckbox(Checkbox checkbox);
void drawProgressBar(ProgressBar progressBar);
void drawSlider(Slider slider);
void drawTextBox(TextBox box, int strLength);

#endif // UI_ELEMENTS_H
