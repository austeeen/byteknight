#include "object_assets.hpp"
#include "factory/asset_factory.hpp"

void ObjectAsset::loadFromJson(Json::Value &root, bt::ResourceFactory *rsrc_factory)
{
    DATA::get(id, root, "id");
    BaseJsonAsset::loadFromJson(root, rsrc_factory);
    DATA::get(class_type, root, "class");
    type_id = Object::IDMAP.at(type);

    DATA::get(group_name, root, "group");
    if (group_name != "") {
        group_id = Groups::IDMAP.at(group_name);
    } else {
        bt::warn("ObjectAsset::loadFromJson", "object %s unknown group %s", this->name, this->group_name);
        group_id = Groups::NO_TEAM;
    }
    DATA::xycoord(start_coord, root, "start_coord", lyr_cols);

    Json::Value table;
    rsrc_factory->getTable(table, "game_objects");

    Json::Value class_entry = table["class"][class_type];
    DATA::get(move_set, class_entry, "move_set");
    DATA::get(speed, class_entry, "speed");
    DATA::get(acl, class_entry, "acl");
    DATA::get(img_src, class_entry, "img_src");

    Json::Value team_entry = table["team"][group_name][class_type];
    DATA::get(texture_rect, team_entry, "texture_rect");
    DATA::get(collision_rect, team_entry, "collision_rect");

    rsrc_factory->getImage(img_texture, img_cols, img_src);
    nametag = rsrc_factory->getFont()->asText(this->name);
}
