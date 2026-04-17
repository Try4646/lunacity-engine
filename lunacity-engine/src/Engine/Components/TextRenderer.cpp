#include "TextRenderer.h"
#include "..//GameObject.h"
#include "..//Transform.h"
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>

#define STB_TRUETYPE_IMPLEMENTATION
#include "../../includes/stb_truetype.h"  

struct FontData {
    unsigned char* buffer;
    stbtt_bakedchar chars[96];
    GLuint texture;
    bool initialized;

    FontData() : buffer(nullptr), texture(0), initialized(false) {
        memset(chars, 0, sizeof(chars));
    }

    ~FontData() {
        if (buffer) delete[] buffer;
        if (texture) glDeleteTextures(1, &texture);
    }
};


static bool LoadFont(FontData* data, float fontSize) {
    const char* paths[] = {
        "Roboto-Italic-VariableFont_wdth,wght.ttf",
        "../Roboto-Italic-VariableFont_wdth,wght.ttf",
        "../../Roboto-Italic-VariableFont_wdth,wght.ttf",
        "src/Font/Roboto-Italic-VariableFont_wdth,wght.ttf",
    };

    std::ifstream file;
    for (const char* path : paths) {
        file.open(path, std::ios::binary | std::ios::ate);
        if (file.is_open()) break;
    }

    if (!file.is_open()) return false;

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    data->buffer = new unsigned char[size];
    file.read((char*)data->buffer, size);
    file.close();

    glGenTextures(1, &data->texture);
    glBindTexture(GL_TEXTURE_2D, data->texture);

    unsigned char* bitmap = new unsigned char[512 * 512];
    stbtt_BakeFontBitmap(data->buffer, 0, fontSize, bitmap, 512, 512, 32, 96, data->chars);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512, 512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, bitmap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    delete[] bitmap;
    data->initialized = true;
    return true;
}

TextRenderer::TextRenderer()
    : text(""), r(1), g(1), b(1), a(1), fontSize(24), fontData(nullptr) {
    fontData = new FontData();
    LoadFont(fontData, fontSize);
}

TextRenderer::~TextRenderer() {
    delete fontData;
}

void TextRenderer::SetText(const std::string& newText) {
    text = newText;
}

void TextRenderer::SetColor(float red, float green, float blue, float alpha) {
    r = red; g = green; b = blue; a = alpha;
}

void TextRenderer::SetFontSize(float size) {
    fontSize = size;
}

void TextRenderer::Render() {
    if (!fontData || !fontData->initialized || !owner) return;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, fontData->texture);
    glColor4f(r, g, b, a);

    float startX = owner->x;
    float startY = owner->y;
    float currentX = startX;
    float currentY = startY;

    for (char c : text) {
        if (c >= 32 && c <= 127) {
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(fontData->chars, 512, 512, c - 32, &currentX, &currentY, &q, 1);

            glBegin(GL_QUADS);
            glTexCoord2f(q.s0, q.t0); glVertex2f(q.x0, q.y0);
            glTexCoord2f(q.s1, q.t0); glVertex2f(q.x1, q.y0);
            glTexCoord2f(q.s1, q.t1); glVertex2f(q.x1, q.y1);
            glTexCoord2f(q.s0, q.t1); glVertex2f(q.x0, q.y1);
            glEnd();
        }
    }

    glDisable(GL_TEXTURE_2D);
}