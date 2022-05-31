#include "square_font.hpp"

SQ::Font::Font(): __font(new sf::Font()), __max_cache_size(20), __default_char_size(32)
{}
SQ::Font::~Font()
{
    SQ::destroy(this->__font);
    this->__txtcache.clear();
}
bool SQ::Font::load(const std::string& font_fp)
{
    if (this->__font->loadFromFile(font_fp)) {
        // disable font anti-aliasing
        const_cast<sf::Texture&>(this->__font->getTexture(this->__default_char_size)).setSmooth(false);
        return true;
    }
    return false;
}
sptr<sf::Text> SQ::Font::asText(const std::string& linestr, const sf::Color& color, const unsigned int maxlinew)
{
    const std::size_t h = std::hash<std::string>{}(linestr);
    if (this->__txtcache.count(h) == 0) {
        this->__createText(h, linestr, color, maxlinew);
    }
    return this->__txtcache[h];
}
void SQ::Font::__createText(const std::size_t hash, const std::string& linestr, const sf::Color& color,
    const unsigned int maxlinew)
{
    this->__txtcache[hash] = mkptr<sf::Text>(linestr, *this->__font, this->__default_char_size);
    this->__txtcache[hash]->setFillColor(color);
    this->__txtcache[hash]->setScale(0.3f, 0.3f);
}
