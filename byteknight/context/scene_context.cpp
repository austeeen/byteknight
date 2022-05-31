#include "scene_context.hpp"
#include "context/game_context.hpp"
#include "scene/instance.hpp"
#include "factory/asset_factory.hpp"

SceneContext::SceneContext(GameContext *game_context, const std::string& scene_group_name) :
font(nullptr), __group_name(scene_group_name)
{
    SQ::throwForNullPtr(game_context, GETNAME(game_context));
    this->__game_context = game_context;
    this->font = this->__game_context->rsrc_factory->getFont();
    game_context->ast_factory->loadSceneGroup(this->__group_name, this->__scene_names);
}
SceneContext::~SceneContext()
{
    __game_context = nullptr;
    font = nullptr;
}
const std::vector<std::string>& SceneContext::getSceneNames() const
{
    return __scene_names;
}
const sf::View SceneContext::getWindowView() const
{
    SQ::throwForNullPtr(__game_context, GETNAME(__game_context));
    return __game_context->getWindow().getView();
}
const sf::FloatRect SceneContext::getWindowViewport() const
{
    SQ::throwForNullPtr(__game_context, GETNAME(__game_context));
    return __game_context->getWindow().getView().getViewport();
}
Controller* SceneContext::getController() {
    return __game_context->controller();
}
void SceneContext::setSceneData(Meta::gamedata data)
{
    SQ::warnForBadValue<SQ::rect>(data.board_size, GETNAME(data.board_size), "SceneContext::setSceneData");
    SQ::warnForBadValue<SQ::rect>(data.tile_size, GETNAME(data.tile_size), "SceneContext::setSceneData");
    SQ::warnForBadValue<SQ::rect>(data.pxl_size, GETNAME(data.pxl_size), "SceneContext::setSceneData");
    SQ::warnForBadValue<int>(data.total_tiles, GETNAME(data.total_tiles), "SceneContext::setSceneData");
    __scene_data = data;
}
Meta::gamedata& SceneContext::getSceneData()
{
    return __scene_data;
}
