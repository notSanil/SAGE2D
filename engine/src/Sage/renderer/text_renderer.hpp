#if 0

#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "Sage/transform/point.hpp"
#include "Sage/transform/Vec4.h"
#include "Sage/renderer/font.hpp"

class TextRenderer{
public:
    void renderText(const Font *font, std::string const &text, Sage::Vec4<int> col, Point const pos);
    static TextRenderer* get();

private:
    TextRenderer();
};
#endif