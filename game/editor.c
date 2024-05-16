#include "editor.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"
#include "render.h"

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
    
    // body 
    ncEditorData.BodyTypeEditMode = false;
    ncEditorData.BodyTypeActive = 0;
    ncEditorData.MassValue = 2.0f;
    ncEditorData.DampingValue = 0.0f;
    ncEditorData.GravityScaleValue = 1.0f;
    ncEditorData.StiffnessValue = 10.0f;

    // world 
    ncEditorData.GravityValue = 0.0f;
    ncEditorData.GravitationValue = 0.0f;
}

void UpdateEditor(Vector2 position)
{
    //
}

void DrawEditor(Vector2 position)
{
    if (ncEditorData.BodyTypeEditMode) GuiLock();

    if (EditorBoxActive)
    {
        EditorBoxActive = !GuiWindowBox((Rectangle) { anchor01.x + 0, anchor01.y + 0, 304, 616 }, "Editor");
        if (GuiDropdownBox((Rectangle) { anchor01.x + 80, anchor01.y + 80, 120, 16 }, "DYNAMIC;KINEMATIC;STATIC", & ncEditorData.BodyTypeActive, ncEditorData.BodyTypeEditMode)) ncEditorData.BodyTypeEditMode = !ncEditorData.BodyTypeEditMode;
        GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 160, 120, 16 }, "Mass Max", TextFormat("%0.2f", ncEditorData.MassValue), & ncEditorData.MassValue, 0, 5);
        GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 200, 120, 16 }, "Gravitation", TextFormat("%0.2f", ncEditorData.GravitationValue), & ncEditorData.GravitationValue, 0, 100);
        GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 240, 120, 16 }, "Gravity Scale", TextFormat("%0.2f", ncEditorData.GravityScaleValue), & ncEditorData.GravityScaleValue, 0, 10);
        GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 280, 120, 16 }, "Damping", TextFormat("%0.2f", ncEditorData.DampingValue), & ncEditorData.DampingValue, 0, 10);
        GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 320, 120, 16 }, "Stiffness", TextFormat("%0.2f", ncEditorData.StiffnessValue), & ncEditorData.StiffnessValue, 0, 10);
    }

    DrawTexture(cursorTexture, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, (Color) { 255, 255, 255, 255 });

    GuiUnlock();
}

ncBody* GetBodyIntersect(ncBody* bodies, Vector2 position)
{
    for (ncBody* body = bodies; body; body = body->next)
    {
        Vector2 screen = ConvertWorldToScreen(body->position);
        if (CheckCollisionPointCircle(position, screen, ConvertWorldToPixel(body->mass)))
        {
            return body;
        }
    }

    return NULL;
}

void DrawLineBodyToPosition(ncBody* body, Vector2 position)
{
    Vector2 screen = ConvertWorldToScreen(body->position);
    DrawLine((int)screen.x, (int)screen.y, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, YELLOW);
}