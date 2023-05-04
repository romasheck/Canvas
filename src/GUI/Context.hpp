#pragma once
#include "AssetManager.hpp"
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

    private:
        std::unique_ptr<sf::RenderWindow> window_ptr;
        std::unique_ptr<AssetManager> asset_manager_ptr;
    };

    extern Context* context_ptr;
}
