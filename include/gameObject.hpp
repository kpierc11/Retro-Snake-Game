#include "math.hpp"

class GameObject
{
public:
    GameObject(class game *game);
    ~GameObject();

private:
    GameMath::Vector transform;

};