//
// Created by felix on 22/11/2021.
//

#pragma once

struct Font;

void initFontCache();
Font* createFont(const char* file);
void freeFont(Font* font);
void cacheCodePoint(const Font* font, int glyph);

struct Image;
Image* getCacheTexture();