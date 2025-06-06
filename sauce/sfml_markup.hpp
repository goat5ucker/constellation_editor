    // Copyright 2025 goat5ucker
#pragma once

#include <SFML/Graphics.hpp>
#include "font.hpp"

namespace sf_colors
{

}

namespace sfml_markup
{
    inline sf::Font harmonia_sans;
    inline sf::Text big_ass_title(harmonia_sans);

    inline int init(sf::RenderWindow *window)
    {
        if(! harmonia_sans.openFromMemory(&__sans_ttf, __sans_ttf_len))
            return 1;
        big_ass_title.setStyle(sf::Text::Bold);
        big_ass_title.setString(L"ОШИБКА:\nРЕДАКТОР НЕДОПИСАН");
        big_ass_title.setCharacterSize(64);
        big_ass_title.setPosition({300,100});
        return 0;
    }

    inline void calc_loop(sf::RenderWindow *window)
    {
        big_ass_title.setOrigin({big_ass_title.getLocalBounds().size.x / 2, big_ass_title.getLocalBounds().size.y / 2});
        big_ass_title.setPosition({(float)window->getSize().x / 2.f, (float)window->getSize().y / 2.f});
    }
}