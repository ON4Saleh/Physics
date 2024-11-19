#include <SFML/Graphics.hpp>
#include <list>

using namespace sf;
using namespace std;

class Renderer
{
private:
    list<sf::Drawable*> drawables;  
public:
    void AddDrawable(sf::Drawable* drawable); 
    void Render(RenderWindow* window);       
};
