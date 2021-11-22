//
// Created by felix on 20/11/2021.
//

#include <glad/gl.h>
#include <glm/vec2.hpp>
#include <vec.h>
#include <image.h>
#include <span>
#include <stb_truetype.h>
#include "font.h"
#include <cstdio>
#include <cstdlib>
#include "rect_pack.h"
#include <unordered_map>

struct Font
{
    stbtt_fontinfo fontinfo {};
};


struct FontCacheData
{
    RectPack pack;
    Image* cacheImage {};
    std::unordered_map<int, uint32_t> glyphMap {};
};

static FontCacheData fontCache;

void initFontCache()
{
    glm::ivec2 size = {1024, 1024};
    fontCache.cacheImage = createImage(size.x, size.y, ImageFiltering::Linear, 1, nullptr);
    fontCache.pack.size = size;
    fontCache.pack.nodes[0].rect.size = size;
}

void cacheCodePoint(const Font* font, int glyph)
{

    if (fontCache.glyphMap.find(glyph) != fontCache.glyphMap.end())
    {
        return;
    }

    float scale = 0.2;

    int boxLeft, boxTop, boxRight, boxBottom;
    stbtt_GetGlyphBitmapBox(&font->fontinfo, glyph, scale, scale, &boxLeft, &boxTop, &boxRight, &boxBottom);

    glm::ivec2 glyphSize(boxRight - boxLeft, boxBottom - boxTop);

    auto r = fontCache.pack.insert(glyphSize);
    assert(r.has_value());

    fontCache.glyphMap[glyph] = *r;

    RectPack::Rect rect = fontCache.pack.nodes[*r].rect;

    int width, height, xoff, yoff;
    auto bmp = stbtt_GetGlyphBitmap(&font->fontinfo, scale, scale, glyph, &width, &height, &xoff, &yoff);

    assert(rect.size.x >= width);
    assert(rect.size.y >= height);

    glBindTexture(GL_TEXTURE_2D, fontCache.cacheImage->handle);
    glTexSubImage2D(GL_TEXTURE_2D, 0, rect.pos.x, rect.pos.y, width, height, GL_RED, GL_UNSIGNED_BYTE, bmp);

    stbtt_FreeBitmap(bmp, nullptr);
}

Font *createFont(const char *file)
{
    Font* fnt = new Font{};

    FILE* fp = fopen(file, "r");
    fseek(fp, 0, SEEK_END);
    size_t fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* buffer = (char*)malloc(fileSize);
    fread(buffer, 1, fileSize, fp);
    fclose(fp);

    stbtt_InitFont(&fnt->fontinfo, reinterpret_cast<const unsigned char *>(buffer), 0);

    return fnt;
}

void freeFont(Font *font)
{
    free(font->fontinfo.data);
    delete font;
}

Image *getCacheTexture() {
    return fontCache.cacheImage;
}
