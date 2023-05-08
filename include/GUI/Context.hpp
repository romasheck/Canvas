#pragma once
#include "../../include/GUI/AssetManager.hpp"
#include "../../include/GUI/Mouse.hpp"
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

namespace gui {
    class WidgetMaster;
    class Context final {
        friend WidgetMaster;
    private:
        Context();

    public:
        bool addFont(const FONT_ID font_id, const std::string& path_to_font);
        const sf::Font& getFont(const FONT_ID font_id) const;

        bool addTexture(const TEXTURE_ID texture_id, const std::string& path_to_texture);
        const sf::Texture& getTexture(const TEXTURE_ID texture_id) const;

        sf::RenderWindow& window(); 

        const Mouse& mouse() const;

        sf::Time getTime() const;

    private:
        std::unique_ptr<sf::RenderWindow> window_ptr;
        std::unique_ptr<AssetManager> asset_manager_ptr;
        std::unique_ptr<Mouse> mouse_ptr;
        std::unique_ptr<sf::Clock> sf_clock_ptr;
    };

    extern Context* context_ptr;
}
