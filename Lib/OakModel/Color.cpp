/*
 * OakModelView (http://oakmodelview.com/)
 * Author: Mikkel Nøhr Løvgreen (mikkel@oakmodelview.com)
 * ------------------------------------------------------------------------
 * Licensed to Vilaversoftware IVS who licenses this file to you under the
 * Apache License, Version 2.0 (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Color.h"


namespace Oak::Model {

// =============================================================================
// (public)
Color::Color()
{
    m_red = 0;
    m_green = 0;
    m_blue = 0;
    m_alpha = -1;
}

// =============================================================================
// (public)
Color::Color(int red, int green, int blue, int alpha)
{
    m_red = red;
    m_green = green;
    m_blue = blue;
    m_alpha = alpha;
}

// =============================================================================
// (public)
Color::Color(const Color &copy)
{
    *this = copy;
}

// =============================================================================
// (public)
Color &Color::operator=(const Color &copy)
{
    m_red = copy.m_red;
    m_green = copy.m_green;
    m_blue = copy.m_blue;
    m_alpha = copy.m_alpha;

    return *this;
}

// =============================================================================
// (public)
bool Color::operator==(const Color& c) const
{
    return m_red == c.m_red &&
           m_green == c.m_green &&
           m_blue == c.m_blue &&
           m_alpha == c.m_alpha;
}

// =============================================================================
// (public)
bool Color::isValid() const
{
    return m_alpha >= 0;
}

// =============================================================================
// (public)
int Color::red() const
{
    return m_red;
}

// =============================================================================
// (public)
int Color::green() const
{
    return m_green;
}

// =============================================================================
// (public)
int Color::blue() const
{
    return m_blue;
}

// =============================================================================
// (public)
int Color::alpha() const
{
    return m_alpha;
}

// =============================================================================
// (public)
bool Color::setRed(int value)
{
    if (value == m_red || value < 0 || value > 255) { return false; }
    m_red = value;
    return true;
}

// =============================================================================
// (public)
bool Color::setGreen(int value)
{
    if (value == m_green || value < 0 || value > 255) { return false; }
    m_green = value;
    return true;
}

// =============================================================================
// (public)
bool Color::setBlue(int value)
{
    if (value == m_blue || value < 0 || value > 255) { return false; }
    m_blue = value;
    return true;
}

// =============================================================================
// (public)
bool Color::setAlpha(int value)
{
    if (value == m_alpha || value < -1 || value > 255) { return false; }
    m_alpha = value;
    return true;
}

// =============================================================================
// (public)
bool Color::set(int red, int green, int blue, int alpha)
{
    return setRed(red) &&
           setGreen(green) &&
           setBlue(blue) &&
           setAlpha(alpha);
}

} // namespace Oak::Model

