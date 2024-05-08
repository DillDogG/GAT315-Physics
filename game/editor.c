#include "editor.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

bool ncEditorActive = true;
bool ncEditorIntersect = false;
ncEditorData_t ncEditorData;

Rectangle editorRect;

Vector2 anchor01 = { 950, 50 };

bool EditorBoxActive = true;

void InitEditor()
{
    GuiLoadStyle("raygui/styles/cyber/style_cyber.rgs");
    
    ncEditorData.GravitationValue = 2;
    ncEditorData.MassMinValue = 0.1f;
    ncEditorData.MassMaxValue = 1;
}

void UpdateEditor(Vector2 position)
{
    //
}

void DrawEditor()
{
    if (EditorBoxActive)
    {
        EditorBoxActive = !GuiWindowBox((Rectangle) { anchor01.x + 0, anchor01.y + 0, 304, 616 }, "Editor");
        GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 80, 120, 16 }, "Mass Min", NULL, & ncEditorData.MassMinValue, 0, 100);
        GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 120, 120, 16 }, "Mass Max", NULL, & ncEditorData.MassMaxValue, 0, 100);
        GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 168, 120, 16 }, "Gravitation", NULL, & ncEditorData.GravitationValue, 0, 100);
    }
}