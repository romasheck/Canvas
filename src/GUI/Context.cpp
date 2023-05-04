#include "Context.hpp"
#include "AssetManager.hpp"

namespace gui {
    Context::Context() {
        window_ptr = std::make_unique<sf::RenderWindow>();
        asset_manager_ptr = std::make_unique<AssetManager>();
    }

    bool Context::addFont(const FONT_ID font_id, const std::string& path_to_font)
    {
        return asset_manager_ptr->add_font(font_id, path_to_font);
    }

    const sf::Font& Context::getFont(const FONT_ID font_id) const
    {
        return asset_manager_ptr->get_font(font_id);
    }

    bool Context::addTexture(const TEXTURE_ID texture_id, const std::string& path_to_texture)
    {
        return asset_manager_ptr->add_texture(texture_id, path_to_texture);
    }
   
    const sf::Texture& Context::getTexture(const TEXTURE_ID texture_id) const
    {
        return asset_manager_ptr->get_texture(texture_id);
    }
    sf::RenderWindow& Context::window()
    {
        return *window_ptr;
    }

    Context* context_ptr;
} // namecpace game