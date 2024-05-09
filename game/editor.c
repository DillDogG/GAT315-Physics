#include "editor.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

bool ncEditorActive = true;
bool ncEditorIntersect = false;
ncEditorData_t ncEditorData;

Rectangle editorRect;

Vector2 anchor01 = { 950, 50 };
Texture2D cursorTexture;

bool EditorBoxActive = true;

void InitEditor()
{
    GuiLoadStyle("raygui/styles/cyber/style_cyber.rgs");

    Image image = LoadImage("resources / reticle 1.png");
    cursorTexture = LoadTextureFromImage(image);
    UnloadImage(image);
    
    ncEditorData.MassMinValue = 0.1f;
    ncEditorData.MassMaxValue = 1;
    ncEditorData.GravitationValue = 2;
    ncEditorData.GravityScaleValue = 2;
    ncEditorData.DampingValue = 2;
}

void UpdateEditor(Vector2 position)
{
    //
}

void DrawEditor(Vector2 position)
{
    //if (ncEditorData.BodyTypeEditMode) GuiLock();

    if (EditorBoxActive)
    {
        EditorBoxActive = !GuiWindowBox((Rectangle) { anchor01.x + 0, anchor01.y + 0, 304, 616 }, "Editor");
        GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 80, 120, 16 }, "Mass Min", NULL, & ncEditorData.MassMinValue, 0, 100);
        GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 120, 120, 16 }, "Mass Max", NULL, & ncEditorData.MassMaxValue, 0, 100);
        GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 160, 120, 16 }, "Gravitation", NULL, & ncEditorData.GravitationValue, 0, 100);
        GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 200, 120, 16 }, "Gravity Scale", NULL, & ncEditorData.GravityScaleValue, 0, 100);
        GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 240, 120, 16 }, "Damping", NULL, & ncEditorData.DampingValue, 0, 100);
    }

    DrawTexture(cursorTexture, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, (Color) { 255, 255, 255, 255 });

    GuiUnlock();
}