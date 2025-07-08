    // Copyright 2025 goat5ucker
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "databus.hpp"
#include "font.hpp"

namespace sf_colors
{

}

namespace sfml_markup
{
    inline sf::Font harmonia_sans;
    inline sf::Text big_ass_title(harmonia_sans);
    inline sf::Text error_text(harmonia_sans);
    inline unsigned int error_text_fade_speed = 1; // multiplies by time in milliseconds, stands for alpha-fading;

    inline sf::Texture _throbber; // texture for throbber
    inline sf::Sprite throbber(_throbber, sf::IntRect({0,0},{128,128})); // sprite for throbber;

    inline const unsigned int throbber_frame_count = 32; // how many frames in throbber;
    /* 8 coloumns, 4 rows*/
    inline unsigned int throbber_time = 0; // for runtime definition of current frame;
    inline unsigned int throbber_speed = 40; // change frame in N milliseconds;
    inline unsigned int throbber_time_max = throbber_frame_count * throbber_speed; // do not change declaration - it's for easier counting the current throbber frame; 
    
    inline sf::Clock anim_clock; // a clock/timer for animations
    inline unsigned int anim_time = 0;  // loop time, as milliseconds

    inline void sub_update_throbber(int frame)
    {
        int x = frame % 8;
        int y = frame / 8;

        throbber.setTextureRect(sf::IntRect({x*128,y*128},{128,128}));
    }
    inline void update_throbber()
    {
        throbber_time += anim_time;
        if(throbber_time >= throbber_time_max)
        {
            throbber_time = 0;
        }
        sub_update_throbber(throbber_time / throbber_speed);
    }

    inline int init(sf::RenderWindow *window)
    {
        int ret = 0;
        anim_time = anim_clock.restart().asMilliseconds();
        throbber.setOrigin({64,64});
        

        ret = (! harmonia_sans.openFromMemory(&__sans_ttf, __sans_ttf_len));
        
        //big_ass_title.setStyle(sf::Text::Bold);
        big_ass_title.setString(L"\n\n\n\nредактор готов...");
        big_ass_title.setCharacterSize(64);
        

        error_text.setStyle(sf::Text::Italic);
        error_text.setFillColor(sf::Color(255,0,0,0));
        error_text.setString(L"тип файла не распознан или неправильный.");
        error_text.setCharacterSize(32);
        
        ret = !(_throbber.loadFromMemory(__throbber, __throbber_len));

        return 0;
    }

    inline void calc_loop(sf::RenderWindow *window)
    {
        update_throbber();
        big_ass_title.setOrigin(big_ass_title.getLocalBounds().getCenter());
        big_ass_title.setPosition(window->getView().getCenter());
        error_text.setOrigin({error_text.getLocalBounds().getCenter().x, error_text.getLocalBounds().size.y * 2});
        error_text.setPosition({(float)window->getSize().x / 2.f, (float)window->getSize().y});
        throbber.setPosition(window->getView().getCenter());

        unsigned int* error_text_alpha = &databus::sfml_error_msg_display;
        if (*error_text_alpha > 0)
        {
            *error_text_alpha = *error_text_alpha - std::min((unsigned int)(anim_time * error_text_fade_speed), (unsigned int)(*error_text_alpha));
            error_text.setFillColor(sf::Color(255,0,0,(std::min((unsigned int)(255),*error_text_alpha))));
        }

        anim_time = anim_clock.restart().asMilliseconds();
    }

    inline void draw_loop(sf::RenderWindow* window)
    {
        window->draw(big_ass_title);
        window->draw(throbber);
        window->draw(error_text);
    }
}