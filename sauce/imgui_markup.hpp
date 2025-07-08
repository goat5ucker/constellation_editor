    // Copyright 2025 goat5ucker
#pragma once

#include <iostream>
#include <vector>
#include <filesystem>
#include <imgui-SFML.h>
#include <imgui.h>
#include "font.hpp"
#include "databus.hpp"

namespace imgui_subfns
{
    inline std::vector<std::filesystem::path> filelist;
    inline std::vector<std::string> filenames;
    inline int current_selection = -1;
    inline std::filesystem::path current_path = ".";
    
    inline void update_filelist()
    {
        namespace fs = std::filesystem;

        filelist.clear(); filenames.clear();

        filelist.push_back(fs::absolute("../"));
        filenames.push_back("../");

        for (const fs::directory_entry& entry: fs::directory_iterator(current_path))
        {
            filelist.push_back(entry.path());
            // filenames.push_back(filelist.back().filename());
            // if(fs::is_directory(filelist.back())) filenames.back().append("/");
            if(fs::is_directory(filelist.back())) {filenames.push_back("./"); filenames.back().append(filelist.back().filename());}
            else filenames.push_back(filelist.back().filename());

        }
    }

    inline void init_filelist()
    {
        namespace fs = std::filesystem;

        // current_path = fs::absolute(current_path);
        current_path = fs::current_path();

        update_filelist();
    }

    inline void update_on_file_entry(std::filesystem::path newpath)
    {
        namespace fs = std::filesystem;
        if(fs::is_directory(newpath)) // directory handling
        {
            if(current_selection == 0) current_path = current_path.parent_path();
            else
                current_path = newpath;
            update_filelist();
            return;
        }

        switch (r_c_w_utils::file_check(newpath))
        {
        case 2: break;
        case 1: /* svg handling */ break;
        case -1:
        default: databus::sfml_error_msg_display = 4000; break;
        };
    }

    inline void filelist_selector()
    {
        ImGui::Text("%s", current_path.c_str());
        ImGui::BeginListBox("##", ImVec2(750,350));

        for(int i = 0; i<filenames.size(); i++)
        {
            bool sel = false;
            if (current_selection == i) sel = true;
            if (ImGui::Selectable(filenames[i].c_str(), sel))
            {
                if (current_selection == i)
                {
                    update_on_file_entry(filelist[i]);
                    ImGui::EndListBox();
                    current_selection = -1;
                    return;
                }
                current_selection = i;
            }
        }
        ImGui::EndListBox();
    }
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
            ImGui::SeparatorText("Открыть файл со скомпилированным созвездием: ");

            ImGui::Dummy(ImVec2(0,10));
            
            imgui_subfns::filelist_selector();

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
        imgui_subfns::init_filelist();

        menus_conpan::current = &menus_conpan::greeter;

        ImFontConfig _font_sans_cfg;
        ImFontConfig _font_sans_bold_cfg;

        _font_sans_cfg.FontDataOwnedByAtlas = false;
        _font_sans_cfg.GlyphRanges = ImGui::GetIO().Fonts->GetGlyphRangesCyrillic();
        _font_sans_bold_cfg.FontDataOwnedByAtlas = false;
        _font_sans_bold_cfg.GlyphRanges = ImGui::GetIO().Fonts->GetGlyphRangesCyrillic();
        
        _font_sans_bold = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(__sans_bold_ttf, __sans_bold_ttf_len, 24.f, &_font_sans_bold_cfg);
        _font_sans = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(__sans_ttf, __sans_ttf_len, 24.f, &_font_sans_cfg);
        
        std::cout << "Dear ImGui font initialized successfully" << ImGui::SFML::UpdateFontTexture() << std::endl;
    }

    inline void calc_loop()
    {
        if (databus::conpan_open)
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
}