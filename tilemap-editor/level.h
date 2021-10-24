#pragma once
#include <vector>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace level {
	struct level_data  {
		std::vector<int> tile_ids;
		int tile_size_x;
		int tile_size_y;
		int map_width;
		int map_height;
	};

	json to_json(level_data& level) {
		json j;
		j["tile_ids"] = level.tile_ids;
		j["tile_size_x"] = level.tile_size_x;
		j["tile_size_y"] = level.tile_size_y;
		j["map_width"] = level.map_width;
		j["map_height"] = level.map_height;

		return j;
	}

	level_data from_json(json& j) {
		level_data from;
		j.at("tile_ids").get_to(from.tile_ids);
		j.at("tile_size_x").get_to(from.tile_size_x);
		j.at("tile_size_y").get_to(from.tile_size_y);
		j.at("map_width").get_to(from.map_width);
		j.at("map_height").get_to(from.map_height);

		return from;
	}
}