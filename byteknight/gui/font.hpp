#ifndef GUI_SQFONT_HPP
#define GUI_SQFONT_HPP

#include "common.hpp"

namespace bt::gui
{
    class Font: public sf::Font
    {
    public:
        Font();
        ~Font();
        bool load(const std::string& font_fp);
        sptr<sf::Text> asText(const std::string& linestr,
            const sf::Color& color = sf::Color::Black,
            const unsigned int maxlinew = 0);

    private:
        void __createText(
            const std::size_t hash,
            const std::string& linestr,
            const sf::Color& color,
            const unsigned int maxlinew);

        sf::Font* __font;
        std::map<std::size_t, sptr<sf::Text>> __txtcache;
        const unsigned int __max_cache_size, __default_char_size;
    };

}

#endif // GUI_SQFONT_HPP
