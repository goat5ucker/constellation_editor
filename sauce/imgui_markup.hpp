    // Copyright 2025 goat5ucker
#pragma once

#include <iostream>
#include <imgui-SFML.h>
#include <imgui.h>
#include "font.hpp"
#include "databus.hpp"

namespace imgui_subfns
{

}

namespace imgui_markup
{
    enum class _conpan_state{ greeter, newfile, files, convert, settings };
    inline _conpan_state conpan_state = _conpan_state::greeter; 
    inline bool quitprompt = false;

    
    namespace menus_conpan
    {
        inline void(*current)();

        inline void greeter()
        {
            ImGui::Dummy(ImVec2(375,0));
            
            if(quitprompt)
                ImGui::BeginDisabled();
            
            if (ImGui::Button("Новый Файл (TODO)")) conpan_state = _conpan_state::newfile;
            ImGui::Dummy(ImVec2(0,10));

            if(ImGui::Button("Конвертировать из SVG (TODO)")) conpan_state = _conpan_state::convert;
            ImGui::Dummy(ImVec2(0,10));

            if (ImGui::Button("Открыть Файл (IN-DEV)")) conpan_state = _conpan_state::files;
            
            if(quitprompt)
                ImGui::EndDisabled();
            
            if(!quitprompt)
                { ImGui::SeparatorText(""); }
            else
                { ImGui::SeparatorText("Вы уверены? "); }

            if(!quitprompt)
                { if (ImGui::Button("Настройки (TODO)")) conpan_state = _conpan_state::settings; }
            else
                { if (ImGui::Button("Нет")) quitprompt = false; }
            ImGui::Dummy(ImVec2(0,10));
            
            if (ImGui::Button("Закрыть Редактор"))
            {
                if(quitprompt)
                    databus::quit_call = true;
                quitprompt = true;
            }
            ImGui::Dummy(ImVec2(0,10));

            ImGui::SetWindowPos({5,5});
        }

        inline void newfile() // TODO
        {
            ImGui::Dummy(ImVec2(375,0));
            
            if (ImGui::Button("Назад..."))
                conpan_state = _conpan_state::greeter;

            ImGui::SeparatorText("Новый файл: ");

            ImGui::Text("ну тут типа менюшка \nсоздания нового файла...");
            ImGui::Dummy(ImVec2(0,10));

            ImGui::SetWindowPos({5,5});
        }

        inline void convert() // TODO
        {
            ImGui::Dummy(ImVec2(375,0));
            
            if (ImGui::Button("Назад..."))
                conpan_state = _conpan_state::greeter;

            ImGui::SeparatorText("Конвертировать из SVG: ");

            ImGui::Text("вы знаете, что такое безумие?");
            ImGui::Dummy(ImVec2(0,10));

            ImGui::SetWindowPos({5,5});
        }

        inline void files() // TODO
        {
            ImGui::Dummy(ImVec2(375,0));
            
            if (ImGui::Button("Назад..."))
                conpan_state = _conpan_state::greeter;
            ImGui::SeparatorText("Открыть файл: ");

            ImGui::Dummy(ImVec2(0,10));

            

            ImGui::SetWindowPos({5,5});
        }

        inline void settings() // TODO
        {
            ImGui::Dummy(ImVec2(375,0));
            
            if (ImGui::Button("Назад..."))
                conpan_state = _conpan_state::greeter;

            ImGui::SeparatorText("Настройки: ");

            ImGui::Text("beep boop boop beep");
            ImGui::Dummy(ImVec2(0,10));

            ImGui::SetWindowPos({5,5});

        }
    }

    
    inline ImFont* _font_sans = NULL;
    inline ImFont* _font_sans_bold = NULL;

    inline void init()
    {
        menus_conpan::current = &menus_conpan::greeter;

        ImFontConfig _font_sans_cfg;
        ImFontConfig _font_sans_bold_cfg;

        _font_sans_cfg.FontDataOwnedByAtlas = false;
        _font_sans_cfg.GlyphRanges = ImGui::GetIO().Fonts->GetGlyphRangesCyrillic();
        _font_sans_bold_cfg.FontDataOwnedByAtlas = false;
        _font_sans_bold_cfg.GlyphRanges = ImGui::GetIO().Fonts->GetGlyphRangesCyrillic();
        
        _font_sans_bold = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(__sans_bold_ttf, __sans_bold_ttf_len, 24.f, &_font_sans_bold_cfg);
        _font_sans = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(__sans_ttf, __sans_ttf_len, 24.f, &_font_sans_cfg);
        
        std::cout << ImGui::SFML::UpdateFontTexture() << std::endl;
        std::cout << _font_sans << std::endl;
    }

    inline void calc_loop()
    {
        switch(conpan_state)
        {
        case (_conpan_state::newfile):
            menus_conpan::current = menus_conpan::newfile; break;
        case (_conpan_state::convert):
            menus_conpan::current = menus_conpan::convert; break;
        case (_conpan_state::files):
            menus_conpan::current = menus_conpan::files; break;
        case (_conpan_state::settings):
            menus_conpan::current = menus_conpan::settings; break;
        default:
            menus_conpan::current = menus_conpan::greeter; break;
        }

        ImGui::PushFont(_font_sans_bold);
        ImGui::Begin("Панель Управления", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove 
                                                    | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::PopFont();
        ImGui::PushFont(_font_sans);
        ImGui::Dummy(ImVec2(0,10));
        menus_conpan::current();
        ImGui::PopFont();
        ImGui::End();
    }
}