#pragma once
#include "../Component.h"
#include <string>


struct FontData;

class TextRenderer : public Component {
public:
    TextRenderer();
    explicit TextRenderer(const std::string& fontPath, float fontSize = 24.0f);
    ~TextRenderer();

    void SetText(const std::string& newText);
    void SetColor(float red, float green, float blue, float alpha);
    void SetFontSize(float size);
    void SetFont(const std::string& fontPath, float fontSize);
    void Render();

private:
    std::string text;
    float r, g, b, a;
    float fontSize;
    FontData* fontData;
};