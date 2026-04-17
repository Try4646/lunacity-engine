#pragma once
#include "../Component.h"
#include <string>


struct FontData;

class TextRenderer : public Component {
private:
    std::string text;
    float r, g, b, a;
    float fontSize;
    FontData* fontData; 

public:
    TextRenderer();
    ~TextRenderer();

    void SetText(const std::string& newText);
    void SetColor(float red, float green, float blue, float alpha = 1.0f);
    void SetFontSize(float size);
    void Render() override;
};