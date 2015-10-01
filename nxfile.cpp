//////////////////////////////////////////////////////////////////////////////
// NoLifeNx - Part of the NoLifeStory project                               //
// Copyright © 2013 Peter Atashian                                          //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//////////////////////////////////////////////////////////////////////////////
#include "nxfile.h"

namespace nl {
	namespace nx {
		std::vector<std::unique_ptr<file>> files;
		bool exists(std::string name) {
			return std::ifstream(name).is_open();
		}
		node add_file(std::string name) {
			if (!exists(name))
				return{};
			files.emplace_back(new file(name));
			return *files.back();
		}
		node base, back, bgm, character, effect, etc, item, map, mob, morph, npc, obj, quest, reactor, skill, sound, string, tamingmob, tile, ui;
		std::map<std::string, node> nodes;
		bool load_all() {
			if (exists("UI.nx")) {
				nodes["Character"] = add_file("Character.nx");
				nodes["Effect"] = add_file("Effect.nx");
				nodes["Etc"] = add_file("Etc.nx");
				nodes["Item"] = add_file("Item.nx");
				nodes["Map"] = add_file("Map.nx");
				nodes["Mob"] = add_file("Mob.nx");
				nodes["Morph"] = add_file("Morph.nx");
				nodes["Npc"] = add_file("Npc.nx");
				nodes["Quest"] = add_file("Quest.nx");
				nodes["Reactor"] = add_file("Reactor.nx");
				nodes["Skill"] = add_file("Skill.nx");
				nodes["Sound"] = add_file("Sound.nx");
				nodes["String"] = add_file("String.nx");
				nodes["TamingMob"] = add_file("TamingMob.nx");
				nodes["UI"] = add_file("UI.nx");
				return true;
			}
			else if (exists("Data.nx")) {
				base = add_file("Data.nx");
				character = base["Character"];
				effect = base["Effect"];
				etc = base["Etc"];
				item = base["Item"];
				map = base["Map"];
				mob = base["Mob"];
				morph = base["Morph"];
				npc = base["Npc"];
				quest = base["Quest"];
				reactor = base["Reactor"];
				skill = base["Skill"];
				sound = base["Sound"];
				string = base["String"];
				tamingmob = base["TamingMob"];
				ui = base["UI"];
				return false;
			}
			else {
				return false;
			}
		}
	}
}
