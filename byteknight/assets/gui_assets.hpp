#ifndef AST_GUI_HPP
#define AST_GUI_HPP

#include "asset_bases.hpp"
#include "datacore/widget_core.hpp"

/*
struct AnchoredPosition {
    std::string target, x_anchor, y_anchor;
};

struct AnimationInfo {
    std::string anim_type;
    bool horizontal, vertical;
};


namespace DATA
{
    // void get(AnchoredPosition& dst, const Json::Value &val, const std::string& key);
    // void get(AnimationInfo& dst, const Json::Value &val, const std::string& key);
}

*/


struct WidgetAsset: BaseJsonAsset
{
    WidgetAsset(Json::Value& root, const int id, ResourceFactory *rsrc_factory);
    void loadFromJson(Json::Value& root, ResourceFactory *rsrc_factory) override;
    Widgets::ID id, type_id;
    Widgets::anchor anchor;
    sf::Texture img_texture;
    bool flip_sprite;
    std::string img_src, anchor_str;
    // todo -- Render::Order render_order;
    int render_order;
    SQ::rect position_rect, texture_rect;
    // AnimationInfo anim_info;
    MSG action_msg;
};

#endif // AST_GUI_HPP
