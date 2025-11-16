// Important note for future reference: this program assumes rects are corner rendered and ellipses are cemter remdered

#include <stdio.h>
#include "cprocessing.h"
#include "abstraction.h"
#include "ui_elements.h"

// Globals
#define gridWidth 533.33f
#define gridHeight 450.0f;

// Assets
CP_Font font;
CP_Sound buttonSound;


float health = 100.0f; // Used by progress bar demo
float volume = 100.0f; // Used by slider demo

void game_init(void)
{
	// Basic config
	CP_System_SetWindowSize(1600, 900);
	CP_Settings_RectMode(CP_POSITION_CORNER);

	// Initialize font
	font = CP_Font_Load("Assets/Fonts/Roboto-Regular.ttf");
	CP_Font_Set(font);

	// Initialize sound
	buttonSound = CP_Sound_Load("Assets/Sounds/Retro Impact Punch 07.wav");
}

// BUTTON
void demoButtonClick(void) {
	CP_Sound_PlayAdvanced(buttonSound, volume / 100.0f, 1.0f, 0, CP_SOUND_GROUP_0);
}
void drawButtonDemo(Point topleft) {
	Button testButton = (Button){
		(Quad) {
			.position = (Point) { 266.66f - 50.0f, 225.0f - 25.0f },
			.width = 100.0f,
			.height = 50.0f,
		},
		"test button",
		(UI_Style) {
			.defaultColor = BLACK,
			.hoverColor = WHITE,
			.strokeColor = RED,
			.strokeWeight = 3.0f,
		},
		(Font_Style) {
			.fontSize = 20.0f,
			.primaryColor = RED,
			.secondaryColor = RED,
		},
		demoButtonClick
	};

	drawButton(testButton);
}

// CHECKBOX
int isAlive = 0;
void drawCheckboxDemo(void) {
	Checkbox testCheckbox = (Checkbox){
		(Quad) {
			.position.x = 266.66f - 7.5f,
			.position.y = 675.0f - 7.5f,
			.width = 15,
			.height = 15,
		},
		.value = &isAlive,
		.onClick = NULL,
	};

	drawCheckbox(testCheckbox);
}

// PROGRESS BAR
void randomizeHealth(void) {
	health = CP_Random_GetFloat() * 100.0f;
}
void heal(void) {
	health += 5.0f;
}
void hurt(void) {
	health -= 5.0f;
}
void drawProgressBarDemo(void) {
	ProgressBar testProgressBar = (ProgressBar){
		(Quad) {700, 200, 200, 25},
		0.0f, 100.0f,
		&health,
		RED, WHITE,
	};

	Button randomizeButton = (Button){
		{750, 260, 100, 50},
		"randomize",
		(UI_Style) {
			.defaultColor = BLACK,
			.hoverColor = WHITE,
			.strokeColor = YELLOW,
			.strokeWeight = 3.0f,
		},
		(Font_Style) {
			.fontSize = 20.0f,
			.primaryColor = YELLOW,
			.secondaryColor = YELLOW,
		},
		randomizeHealth,
	};
	Button healButton = (Button) {
		{675, 320, 100, 50},
		"heal (+5hp)",
		(UI_Style) {
			.defaultColor = BLACK,
			.hoverColor = WHITE,
			.strokeColor = GREEN,
			.strokeWeight = 3.0f,
		},
		(Font_Style) {
			.fontSize = 20.0f,
			.primaryColor = GREEN,
			.secondaryColor = GREEN,
		},
		heal,
	};
	Button hurtButton = (Button) {
		{825, 320, 100, 50},
		"hurt (-5hp)",
		(UI_Style) {
			.defaultColor = BLACK,
			.hoverColor = WHITE,
			.strokeColor = RED,
			.strokeWeight = 3.0f,
		},
		(Font_Style) {
			.fontSize = 20.0f,
			.primaryColor = RED,
			.secondaryColor = RED,
		},
		hurt,
	};

	// Text and elements
	fill(RED);
	char printHP[32];
	sprintf_s(printHP, sizeof(printHP), "HP: %.2f", health);
	text(printHP, 800, 180);
	drawProgressBar(testProgressBar);
	drawButton(randomizeButton);
	drawButton(healButton);
	drawButton(hurtButton);
}

// SLIDER
void drawSliderDemo(void) {
	Slider testSlider = (Slider){
		.properties = {700, 650, 200, 50},
		0.0f, 100.0f,
		&volume,
		RED, GREEN, BLACK,
		NULL
	};

	fill(RED);
	char printVolume[32];
	sprintf_s(printVolume, sizeof(printVolume), "Volume: %.2f", volume);
	text(printVolume, 800, 630);
	drawSlider(testSlider);
}

// TEXTBOX
char testInput[32] = "Sample text";
void drawTextBoxDemo(void) {
	TextBox testBox = (TextBox){
		.properties = {1333.33f - 100.0f, 175.0f, 200.0f, 100.0f},
		.value = &testInput[0],
		.uiStyle = (UI_Style) {
			.defaultColor = BLACK,
			.hoverColor = WHITE,
			.strokeColor = RED,
			.strokeWeight = 3.0f,
		},
		.fontStyle = (Font_Style) {
			.fontSize = 20.0f,
			.primaryColor = RED,
			.secondaryColor = RED,
		},
	};

	drawTextBox(testBox, 32);
}

// ALL
void drawGrid(void) {
	fill(BLACK);
	CP_Settings_Stroke(WHITE);
	CP_Settings_StrokeWeight(5.0f);
	CP_Settings_TextSize(24.0f);

	float rectWidth = WIDTH / 3.0f;
	float rectHeight = HEIGHT / 2.0f;

	char ui_elements[6][32] = {
		"Button",
		"Checkbox",
		"Progress bar",
		"Slider",
		"Text box",
		"Dropdown"
	};

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			fill(BLACK);
			rect(i * rectWidth, j * rectHeight, rectWidth, rectHeight);
			fill(WHITE);
			text(ui_elements[2 * i + j], rectWidth * i + 0.5f * rectWidth, 50 + rectHeight * j);
		}
	}

}

void drawDemoes(void) {
	drawButtonDemo((Point) {0.0f, 0.0f});
	drawCheckboxDemo();
	drawProgressBarDemo();
	drawSliderDemo();
	drawTextBoxDemo();
}

void game_update(void)
{
	// Reset background
	background(WHITE);

	// Draw grid
	drawGrid();

	// Draw demoes
	drawDemoes();
}

void game_exit(void)
{
	CP_Font_Free(font);
	CP_Sound_Free(buttonSound);
}

int main(void)
{
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_System_SetFrameRate(60.0f);
	CP_Engine_Run(0);
	return 0;
}
