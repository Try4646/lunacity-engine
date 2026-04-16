#pragma once

class Renderer {
public:
    static void Init(int width, int height);
    static void Clear(float r, float g, float b, float a);
    static void DrawRect(float x, float y, float w, float h, float r, float g, float b);
    static void Present();
};