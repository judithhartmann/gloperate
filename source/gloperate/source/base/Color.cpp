
#include <cassert>
#include <sstream>
#include <iomanip>

#include <glm/glm.hpp>

#include <cppassist/string/regex.h>

#include <gloperate/base/Color.h>


namespace gloperate
{


Color::Color()
: m_bgra{0u, 0u, 0u, 255u}
{
}

Color::Color(unsigned int bgra)
: m_v{bgra}
{
}

Color::Color(int red, int green, int blue, int alpha)
{
    m_bgra[0] = static_cast<unsigned char>(blue);
    m_bgra[1] = static_cast<unsigned char>(green);
    m_bgra[2] = static_cast<unsigned char>(red);
    m_bgra[3] = static_cast<unsigned char>(alpha);
}

Color::Color(float red, float green, float blue, float alpha)
{
    m_bgra[0] = static_cast<unsigned char>(blue  * 255.0f);
    m_bgra[1] = static_cast<unsigned char>(green * 255.0f);
    m_bgra[2] = static_cast<unsigned char>(red   * 255.0f);
    m_bgra[3] = static_cast<unsigned char>(alpha * 255.0f);
}

Color::Color(glm::tvec4<unsigned char> bgra)
{
    m_bgra = bgra;
}

bool Color::operator==(const Color & rhs) const
{
    return m_v == rhs.m_v;
}

bool Color::operator!=(const Color & rhs) const
{
    return !(*this == rhs);
}

unsigned int Color::bgra() const
{
    return m_v;
}

void Color::setBgra(unsigned int bgra)
{
    m_v = bgra;
}

int Color::red() const
{
    return m_bgra[2];
}

void Color::setRed(int value)
{
    assert(0 <= value && value <= 255);
    m_bgra[2] = static_cast<unsigned char>(value);
}

int Color::green() const
{
    return m_bgra[1];
}

void Color::setGreen(int value)
{
    assert(0 <= value && value <= 255);
    m_bgra[1] = static_cast<unsigned char>(value);
}

int Color::blue() const
{
    return m_bgra[0];
}

void Color::setBlue(int value)
{
    assert(0 <= value && value <= 255);
    m_bgra[0] = static_cast<unsigned char>(value);
}

int Color::alpha() const
{
    return m_bgra[3];
}

void Color::setAlpha(int value)
{
    assert(0 <= value && value <= 255);
    m_bgra[3] = static_cast<unsigned char>(value);
}

float Color::redf() const
{
    return m_bgra[2] / 255.0f;
}

void Color::setRedf(float value)
{
    assert(0.0f <= value && value <= 1.0f);
    m_bgra[2] = static_cast<unsigned char>(value * 255.0f);
}

float Color::greenf() const
{
    return m_bgra[1] / 255.0f;
}

void Color::setGreenf(float value)
{
    assert(0.0f <= value && value <= 1.0f);
    m_bgra[1] = static_cast<unsigned char>(value * 255.0f);
}

float Color::bluef() const
{
    return m_bgra[0] / 255.0f;
}

void Color::setBluef(float value)
{
    assert(0.0f <= value && value <= 1.0f);
    m_bgra[0] = static_cast<unsigned char>(value * 255.0f);
}

float Color::alphaf() const
{
    return m_bgra[3] / 255.0f;
}

void Color::setAlphaf(float value)
{
    assert(0.0f <= value && value <= 1.0f);
    m_bgra[3] = static_cast<unsigned char>(value * 255.0f);
}

glm::vec3 Color::toVec3() const
{
    return glm::vec3(redf(), greenf(), bluef());
}

glm::vec4 Color::toVec4() const
{
    return glm::vec4(redf(), greenf(), bluef(), alphaf());
}

std::string Color::toHexString() const
{
    std::stringstream stream;

    stream << "#";
    stream << std::hex << std::uppercase;

    stream << std::setw(2) << std::setfill('0') << alpha();
    stream << std::setw(2) << std::setfill('0') << red();
    stream << std::setw(2) << std::setfill('0') << green();
    stream << std::setw(2) << std::setfill('0') << blue();

    return stream.str();
}

bool Color::fromHexString(const std::string & str)
{
    // Check if string is a color
    if (str.size() < 1 || str[0] != '#')
    {
        return false;
    }

    // Convert string to canonical form
    std::string hex = str.substr(1);

    if (hex.size() == 3) // #RGB -> #ARGB
    {
        hex = "F" + hex;
    }

    if (hex.size() == 4) // #ARGB -> #AARRGGBB
    {
        hex = hex.substr(0, 1) + hex.substr(0, 1)
            + hex.substr(1, 1) + hex.substr(1, 1)
            + hex.substr(2, 1) + hex.substr(2, 1)
            + hex.substr(3, 1) + hex.substr(3, 1);
    }

    if (hex.size() == 6) // #RRGGBB -> #AARRGGBB
    {
        hex = "FF" + hex;
    }

    // Check string format
    if (!cppassist::matchesRegex(hex, "([0-9A-Fa-f]{8}|[0-9A-Fa-f]{6})"))
    {
        return false;
    }

    // Convert hex string to ARGB integer value
    auto argb = 0u;
    std::stringstream stream(hex);
    stream >> std::hex;
    stream >> argb;

    // Set color
    setBlue(argb & 0xff);
    argb = argb >> 8;
    setGreen(argb & 0xff);
    argb = argb >> 8;
    setRed(argb & 0xff);
    argb = argb >> 8;
    setAlpha(argb & 0xff);

    return true;
}

Color Color::interpolate(const Color & other, float interpolationValue) const
{
    return Color(glm::mix(m_bgra, other.m_bgra, interpolationValue));
}


} // namespace gloperate
