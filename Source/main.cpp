#include "galba.h"
#include "raylib.h"

typedef struct MenuButton {
    const char* text;
    Vector2 position;
    bool isSelected;
} MenuButton;

#define NUM_BUTTONS 3
MenuButton buttons[NUM_BUTTONS];
int selectedButton = 0;  // Index of the selected button

Texture2D texture;
Font customFont;

void init_buttons()
{
    buttons[0].text = "Play";
    buttons[0].position = { 600, 300 };
    buttons[0].isSelected = false;

    buttons[1].text = "Settings";
    buttons[1].position = { 600, 400 };
    buttons[1].isSelected = false;

    buttons[2].text = "Exit";
    buttons[2].position = { 600, 500 };
    buttons[2].isSelected = false;
}


void handle_input()
{
    // Keyboard navigation (up/down arrows)
    if (IsKeyPressed(KEY_DOWN)) {
        selectedButton = (selectedButton + 1) % NUM_BUTTONS;  // Move down
    }
    if (IsKeyPressed(KEY_UP)) {
        selectedButton = (selectedButton - 1 + NUM_BUTTONS) % NUM_BUTTONS;  // Move up
    }

    // Mouse hover and click detection in one loop
    for (int i = 0; i < NUM_BUTTONS; i++) {
        Rectangle buttonRect = { buttons[i].position.x, buttons[i].position.y, 200, 50 };  // Define button area
        if (CheckCollisionPointRec(GetMousePosition(), buttonRect)) {
            selectedButton = i;  // Mouse hover selects the button
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                // Handle mouse click on the hovered button
                if (i == 0) {
                    printf("Play button clicked\n");
                }
                else if (i == 1) {
                    printf("Settings button clicked\n");
                }
                else if (i == 2) {
                    CloseWindow();
                }
            }
        }
    }

    // Action when "Enter" is pressed
    if (IsKeyPressed(KEY_ENTER)) {
        if (selectedButton == 0) {
            printf("Play button clicked\n");
        }
        else if (selectedButton == 1) {
            printf("Settings button clicked\n");
        }
        else if (selectedButton == 2) {
            CloseWindow();  // Close the game for "Exit"
        }
    }
}


void draw_buttons()
{
    for (int i = 0; i < NUM_BUTTONS; i++) {
        if (i == selectedButton) {
            DrawTextEx(customFont, buttons[i].text, buttons[i].position, 50, 2, YELLOW);
            DrawLine((int)buttons[i].position.x - 10, (int)buttons[i].position.y - 5, (int)buttons[i].position.x + 200, (int)buttons[i].position.y - 5, YELLOW); 
            DrawLine((int)buttons[i].position.x - 10, (int)buttons[i].position.y + 50, (int)buttons[i].position.x + 200, (int)buttons[i].position.y + 50, YELLOW);
        }
        else {
            DrawTextEx(customFont, buttons[i].text, buttons[i].position, 50, 2, WHITE);
        }
    }
}


void render()
{
    int windowWidth = GetScreenWidth();
    int windowHeight = GetScreenHeight();

    Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    Rectangle destRec = { 0.0f, 0.0f, (float)windowWidth, (float)windowHeight };
    Vector2 origin = { 0.0f, 0.0f };

    // Draw the background texture
    DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, WHITE);

    // Draw text and other UI elements
    Vector2 textPosition = { 550, 45 };
    DrawTextEx(customFont, "MAIN MENU", textPosition, 55, 2, WHITE);

    // Draw buttons
    draw_buttons();
}

int main()
{
    initialize(1420, 920, "Window");

    Image img = LoadImage("C:/Users/ibtis/OneDrive - Uppsala universitet/Desktop/cppAssignments/GameMenu/Source/bg.png");
    if (img.width > 0 && img.height > 0) {
        texture = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    else {
        printf("Failed to load image 'images.png'\n");
        return -1;
    }

    customFont = LoadFont("C:/Users/ibtis/OneDrive - Uppsala universitet/Desktop/cppAssignments/GameMenu/Source/GolosText - VariableFont_wght.ttf");
    if (customFont.baseSize == 0) {
        printf("Failed to load custom font\n");
        return -1;
    }

    init_buttons();  // Initialize buttons

    while (is_window_open())
    {
        handle_input();  // Handle keyboard and mouse input
        clear_window();
        render();
        display();
    }

    UnloadTexture(texture);
    UnloadFont(customFont);

    return 0;
}
