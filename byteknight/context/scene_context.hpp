#ifndef CTX_SCENE_CONTEXT_HPP
#define CTX_SCENE_CONTEXT_HPP

#include "common.hpp"
#include "datacore/common_core.hpp"
#include "gui/font.hpp"

namespace bt
{

class Scene;
class GameContext;
class Controller;

class SceneContext
{
public:
    SceneContext(GameContext* game_context, const std::string& scene_group_name);
    ~SceneContext();
    void build();
    const std::vector<std::string>& getSceneNames() const;
    const sf::View getWindowView() const;
    const sf::FloatRect getWindowViewport() const;
    Controller* getController();
    void setSceneData(Meta::gamedata data);
    Meta::gamedata& getSceneData();

    gui::Font* font;

private:
    GameContext* __game_context;
    const std::string __group_name;
    std::vector<std::string> __scene_names;
    Meta::gamedata __scene_data;
};

}
#endif // CTX_SCENE_CONTEXT_HPP
