#include "cprocessing.h"
#include "abstraction.h"
#include "ui_elements.h"
#include "collision_utils.h"

#include <stdio.h>

void drawButton(Button button) {
	Quad properties = button.properties;
	Point mousePointer = (Point){ .x = mouseX, .y = mouseY, };

	int isHovering = pointInRect(mousePointer, properties);

	// Draw rectangle
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_Stroke(button.uiStyle.strokeColor);
	CP_Settings_StrokeWeight(button.uiStyle.strokeWeight);
	if (isHovering) fill(button.uiStyle.hoverColor);
	else fill(button.uiStyle.defaultColor);
	rect(properties.position.x, properties.position.y, properties.width, properties.height);


	// Draw text
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	if (isHovering) fill(button.fontStyle.secondaryColor);
	else fill(button.fontStyle.primaryColor);
	CP_Settings_TextSize(button.fontStyle.fontSize);
	text(button.value, properties.position.x + 0.5f * properties.width, properties.position.y + 0.5f * properties.height);

	// Handle click
	if (isHovering) {
		if (CP_Input_MouseClicked() && button.onClick != NULL) {
			button.onClick();
		}
	}
}

void drawCheckbox(Checkbox checkbox) {
	Quad properties = checkbox.properties;
	Point mousePointer = (Point){ .x = mouseX, .y = mouseY, };

	int isChecked = checkbox.value ? *checkbox.value : 0;
	int isHovering = pointInRect(mousePointer, properties);

	// Draw rectangle
	CP_Settings_RectMode(CP_POSITION_CORNER);
	fill(WHITE);
	CP_Settings_Stroke(BLACK);
	CP_Settings_StrokeWeight(1.0f);
	rect(properties.position.x, properties.position.y, properties.width, properties.height);
	if (isChecked) {
		fill(BLACK);
		CP_Graphics_DrawLine(properties.position.x, properties.position.y, properties.position.x + properties.width, properties.position.y + properties.height);
		CP_Graphics_DrawLine(properties.position.x + properties.width, properties.position.y, properties.position.x, properties.position.y + properties.height);
	}

	// Handle click
	if (isHovering) {
		if (CP_Input_MouseClicked()) {
			(*checkbox.value) = !(*checkbox.value);
		}
	}
}

void drawProgressBar(ProgressBar bar) {
	Quad prop = bar.properties;

	float currentValue = bar.value ? *bar.value : bar.min;

	if (currentValue < bar.min) currentValue = bar.min;
	if (currentValue > bar.max) currentValue = bar.max;

	float range = bar.max - bar.min;
	float percentage = (range > 0.0f) ? ((currentValue - bar.min) / range) : 0.0f;
	float fillWidth = bar.properties.width * percentage;

	// Draw actual bar
	CP_Settings_RectMode(CP_POSITION_CORNER);

	fill(bar.backgroundColor);
	rect(prop.position.x, prop.position.y, prop.width, prop.height);
	
	fill(bar.color);
	rect(prop.position.x, prop.position.y, fillWidth, prop.height);
}

void drawSlider(Slider slider) {
	//basic config
	CP_Settings_RectMode(CP_POSITION_CORNER);
	
	
	Quad prop = slider.properties;
	Point mousePointer = { mouseX, mouseY };
	
	int isFocused = 0;
	float percentage = *slider.value / slider.max;
	Quad pointer = { prop.position.x + prop.width * percentage, prop.position.y, 10, prop.height };

	//background
	fill(slider.backgroundColor);
	rect(prop.position.x, prop.position.y, prop.width, prop.height);

	fill(slider.primaryColor);
	if (pointInRect(mousePointer, prop)) {
		fill(slider.secondaryColor);
		if (CP_Input_MouseDown(MOUSE_BUTTON_1)) {
			isFocused = 1;
		}
	}
	else {
		isFocused = 0;
	}

	if (isFocused) {
		float newValue = (mouseX - slider.properties.position.x) / slider.properties.width;
		*(slider.value) = newValue * slider.max;
	}

	// Draw pointer
	rect(pointer.position.x, pointer.position.y, pointer.width, pointer.height);
};

void drawTextBox(TextBox box, int strLength) {
	Quad prop = box.properties;
	Point mousePointer = { mouseX, mouseY };
	int maxLength = (strLength >= 2) ? strLength - 1 : 1;

	int isHovering = pointInRect(mousePointer, prop);
	int isActive = 0;

	// modifiers
	int shiftModifier = CP_Input_KeyDown(KEY_LEFT_SHIFT) || CP_Input_KeyDown(KEY_RIGHT_SHIFT);

	if (isHovering) {
		isActive = 1;
	}
	else isActive = 0;


	// Draw rectangle
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_Stroke(box.uiStyle.strokeColor);
	CP_Settings_StrokeWeight(box.uiStyle.strokeWeight);
	if(isHovering) fill(box.uiStyle.hoverColor);
	else fill(box.uiStyle.defaultColor);
	rect(prop.position.x, prop.position.y, prop.width, prop.height);

	// Draw text
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_TOP);
	CP_Settings_TextSize(box.fontStyle.fontSize);
	fill(box.fontStyle.primaryColor);
	text(box.value, prop.position.x + 5.0f, prop.position.y + 5.0f);

	// Handle input
	if (isActive) {
		if (CP_Input_KeyTriggered(KEY_BACKSPACE)) {
			// Remove last character
			int len = strlen(box.value);
			if (len > 0) {
				box.value[len - 1] = '\0';
			}
		}
		else {
			// Add character
			for (int key = KEY_A; key <= KEY_Z; key++) {
				if (CP_Input_KeyTriggered((CP_KEY)key)) {
					int len = strlen(box.value);
					if (len < maxLength) { // Ensure we don't exceed buffer
						box.value[len] = (char)(key - KEY_A + (shiftModifier? 'A' : 'a'));
						box.value[len + 1] = '\0';
					}
				}
			}
			for (int key = KEY_0; key <= KEY_9; key++) {
				if (CP_Input_KeyTriggered((CP_KEY)key)) {
					int len = strlen(box.value);
					if (len < maxLength) { // Ensure we don't exceed buffer
						box.value[len] = (char)(key - KEY_0 + '0');
						box.value[len + 1] = '\0';
					}
				}
			}
			if (CP_Input_KeyTriggered(KEY_SPACE)) {
				int len = strlen(box.value);
				if (len < maxLength) { // Ensure we don't exceed buffer
					box.value[len] = ' ';
					box.value[len + 1] = '\0';
				}
			}
		}
	}
}
