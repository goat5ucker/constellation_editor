    // Copyright 2025 goat5ucker
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>
/* WOO WINDOWS PLATFORM CORNER */ // #include <windows.h>

#include "databus.hpp"
#include "imgui_markup.hpp"
#include "sfml_markup.hpp"

sf::View _sfview_flat;
sf::Time _sftime_loop;

void update_on_resize(sf::RenderWindow *window)
{
    sf::Vector2f _ws = sf::Vector2f((float)window->getSize().x, (float)window->getSize().y);
    
    std::cout << _ws.x << " " << _ws.y << std::endl;
    
    _sfview_flat = {sf::Vector2f(_ws.x / 2.f,_ws.y / 2.f), _ws};
    window->setView(_sfview_flat);
}

void init(sf::RenderWindow *window)
{
    sfml_markup::init(window);
    imgui_markup::init();
}

int main()
{
    /* WOO WINDOWS PLATFORM CORNER */ // ShowWindow( GetConsoleWindow(), SW_HIDE );

    auto window = sf::RenderWindow(sf::VideoMode({1280u, 720u}), "Constellation Editor");
    window.setMinimumSize(sf::Vector2u(800u,600u));
    window.setFramerateLimit(90);

    if (!ImGui::SFML::Init(window, true))
        return -1;
    init(&window);

    _sfview_flat = window.getDefaultView();
    window.setView(_sfview_flat);

    sf::Clock _sfclock_update;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            if (event->is<sf::Event::Closed>()) goto editor_quit; 
            if (event->is<sf::Event::Resized>()) update_on_resize(&window);
        }
        
        _sftime_loop = _sfclock_update.restart();
        ImGui::SFML::Update(window, _sftime_loop);
        imgui_markup::calc_loop();
        sfml_markup::calc_loop(&window);

        window.clear();
        window.draw(sfml_markup::big_ass_title);
        ImGui::SFML::Render(window);
        window.display();

        if(databus::quit_call) goto editor_quit;
    }

editor_quit:
    ImGui::SFML::Shutdown(window);
    window.close();
}