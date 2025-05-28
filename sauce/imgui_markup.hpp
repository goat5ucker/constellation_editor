    // Copyright 2025 goat5ucker
#pragma once

namespace imgui_markup
{
    ImFontConfig _font_sans_cfg;
    ImFontConfig _font_sans_bold_cfg;

    void init()
    {
    _font_sans_cfg.FontDataOwnedByAtlas = false;
    _font_sans_cfg.GlyphRanges = ImGui::GetIO().Fonts->GetGlyphRangesCyrillic();
    ImGui::GetIO().Fonts->AddFontFromMemoryTTF(__sans_ttf, __sans_ttf_len, 24.f, &_font_sans_cfg);

    _font_sans_bold_cfg.FontDataOwnedByAtlas = false;
    _font_sans_bold_cfg.GlyphRanges = ImGui::GetIO().Fonts->GetGlyphRangesCyrillic();
    ImGui::GetIO().Fonts->AddFontFromMemoryTTF(__sans_ttf, __sans_ttf_len, 24.f, &_font_sans_bold_cfg);
    
    std::cout << ImGui::SFML::UpdateFontTexture();
    }

    void calc_loop()
    {
        ImGui::Begin("Панель Управления", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove 
                                                    | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Button("Новый Файл (НЕ РАБОТАЕТ)");
        ImGui::Dummy(ImVec2(0,10));
        ImGui::Button("Открыть Файл (НЕ РАБОТАЕТ)");
        ImGui::SeparatorText("");
        ImGui::Button("Настройки (НЕ РАБОТАЕТ)");
        ImGui::Dummy(ImVec2(0,10));
        databus::quit_call = ImGui::Button("Закрыть Программу");
        ImGui::SetWindowPos({5,5});
        ImGui::End();
    }
}