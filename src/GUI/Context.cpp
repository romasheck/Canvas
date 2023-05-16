#include "../../include/GUI/Context.hpp"

namespace gui {
    Context::Context():
                        window_ptr(std::make_unique<sf::RenderWindow>()),
                        asset_manager_ptr(std::make_unique<AssetManager>()),
                        mouse_ptr(std::make_unique<Mouse>()),
                        sf_clock_ptr(std::make_unique<sf::Clock>())
                        {}


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

    sf::Time Context::getTime() const
    {
        return sf_clock_ptr->getElapsedTime();
    }

    const Mouse& Context::mouse() const
    {
        return *mouse_ptr;
    }

    //Context* context_ptr;
} // namecpace game