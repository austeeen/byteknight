#include "backdrop_layer.hpp"

BackdropLayer::BackdropLayer(const std::string& name, bt::SceneContext* scene_context, const LayerAsset &lyr_ast) :
LayerBase(name, scene_context, lyr_ast)
{
    bt::warnForBadValue<std::string>(lyr_ast.img_src, GETNAME(lyr_ast.img_src), "BackdropLayer");
    bt::warnForBadValue<std::string>(lyr_ast.gid_str, GETNAME(lyr_ast.gid_str), "BackdropLayer");
    bt::warnForBadValue<int>(lyr_ast.img_cols, GETNAME(lyr_ast.img_cols), "BackdropLayer");
    bt::warnForBadValue<int>(lyr_ast.lyr_cols, GETNAME(lyr_ast.lyr_cols), "BackdropLayer");
}
void BackdropLayer::build()
{
    Meta::gamedata scenedata = this->getSceneData();
    render_texture = sf::RenderStates(&lyr_ast.img_texture);

    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(scenedata.total_tiles * 4);

    std::vector<int> all_gids = {};
    bt::split(lyr_ast.gid_str, ',', all_gids);

    if (scenedata.total_tiles != all_gids.size())
        bt::warn("BackdropLayer::build()", "%d (num gids) != %d (total tiles)", (int) scenedata.total_tiles, (int) all_gids.size());
    if (all_gids.size() == 0)
        bt::warn("BackdropLayer::build()", "all_gids is empty but expected to contain values.");

    for (size_t i = 0; i < all_gids.size(); i++)
    {
        bt::coord img_i(all_gids[i], lyr_ast.img_cols);
        bt::coord tile_i((int)i, lyr_ast.lyr_cols);
        bt::rect img_rect = img_i.torect(scenedata.tile_size);
        bt::rect tile_rect = tile_i.torect(scenedata.tile_size);

        sf::Vertex *quad = &vertices[i * 4];
        quad[0].position = sf::Vector2f(tile_rect.left,  tile_rect.top);
        quad[1].position = sf::Vector2f(tile_rect.right, tile_rect.top);
        quad[2].position = sf::Vector2f(tile_rect.right, tile_rect.bottom);
        quad[3].position = sf::Vector2f(tile_rect.left,  tile_rect.bottom);

        quad[0].texCoords = sf::Vector2f(img_rect.left,  img_rect.top);
        quad[1].texCoords = sf::Vector2f(img_rect.right, img_rect.top);
        quad[2].texCoords = sf::Vector2f(img_rect.right, img_rect.bottom);
        quad[3].texCoords = sf::Vector2f(img_rect.left,  img_rect.bottom);
    }
}
