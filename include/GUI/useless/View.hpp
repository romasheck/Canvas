#ifndef VIEW_HPP
#define VIEW_HPP

#include "gui_lib.hpp"
#include "coordinate.hpp"

namespace gui
{
    class View
    {
    private:
        //sf::Sprite sprite_;
        sf::Texture texture_;
        sf::Texture text_;

    public:
        View();
        View(const std::string& textur_path, const std::string& text);

    public:
        void draw() const;

    public:
        void setSize        (const coordinate size);
        void setPosition    (const coordinate pos);

    public:
        void setFont        (const std::string& font_path);
        void setTexture     (const std::string& texture_path);
        void setText        (const std::string& text);
    };
}

#endif