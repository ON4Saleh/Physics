#include "Renderer.h"

void Renderer::AddDrawable(Drawable* drawable)
{
    drawables.push_back(drawable);
}

void Renderer::Render(sf::RenderWindow* window)
{
    for (Drawable* drawable : drawables)
    {
        window->draw(*drawable);
    }
}
