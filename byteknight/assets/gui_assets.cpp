#include "gui_assets.hpp"
#include "factory/asset_factory.hpp"

/**************************************************************************************************/
/* DATA */
/*
void DATA::get(AnchoredPosition& dst, const Json::Value &val, const std::string& key) {
    std::string anchor_str;
    DATA::get(anchor_str, val, key);
    if (anchor_str == "NULL") {
        dst = AnchoredPosition{"", "", ""};
        return;
    }
    std::vector<std::string> keywrds;
    SQ::split(anchor_str, '_', keywrds);
    dst.target = keywrds[0];
    dst.x_anchor = keywrds[1];
    dst.y_anchor = keywrds[2];
}
void DATA::get(AnimationInfo& dst, const Json::Value &val, const std::string& key) {
    Json::Value root = val.get(key, Json::nullValue);
    if (root.isNull()) {
        dst = AnimationInfo{"", false, false};
        return;
    }
    DATA::get(dst.anim_type, root, "type");
    DATA::get(dst.horizontal, root, "horizontal");
    DATA::get(dst.vertical, root, "vertical");
}
*/

/**************************************************************************************************/

WidgetAsset::WidgetAsset(Json::Value &root, const int id, ResourceFactory *rsrc_factory)
{
    this->id = id;
    this->loadFromJson(root, rsrc_factory);
}
void WidgetAsset::loadFromJson(Json::Value &root, ResourceFactory *rsrc_factory)
{
    BaseJsonAsset::loadFromJson(root, rsrc_factory);
    type_id = Widgets::IDMAP.at(type);
    DATA::get(render_order, root, "render_order");
    DATA::get(img_src, root, "img_src");
    Json::Value table;
    rsrc_factory->getTable(table, "widgets");
    if (!table.empty()) {
        Json::Value widget_entry = table["type"][type];
        if (!widget_entry.empty()) {
            DATA::get(img_src, widget_entry, "img_src");
            DATA::get(texture_rect, widget_entry, "texture_rect");
            rsrc_factory->getImage(img_texture, img_src);
            DATA::get(flip_sprite, widget_entry, "flip_sprite");
        }
    }

    if (img_src != "") {
        rsrc_factory->getImage(img_texture, img_src);
    }

    DATA::get(position_rect, root, "position_rect");
    if (!position_rect.exists()) {
        if (texture_rect.exists()) {
            position_rect = texture_rect;
            position_rect.left = 0.f;
            position_rect.top = 0.f;
        } else {
            position_rect = SQ::rect(sf::Sprite(img_texture).getLocalBounds());
        }
    }

    DATA::get(anchor_str, root, "anchor");
    if (anchor_str != "") {
        anchor = Widgets::ANCHORTBL.at(anchor_str);
    } else {
        anchor = Widgets::NONE;
    }

    // DATA::get(anim_info, root, "animation");
    DATA::get(action_msg, root, "action");
}
