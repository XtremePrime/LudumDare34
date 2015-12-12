#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <iostream>
#include <fstream>
#include "skill.hpp"
#include "player.h"

class SaveFile
{
private:
public:
	void init(Player& p)
	{
		if(!fexists("save.pcsav")){
			std::cout << "ERROR: Save doesn't exist.\n";
			std::cout << "Creating savefile...";
			if(create_file()){
				std::cout << "Created successfully!\n";
			}else{
				std::cout << "FAILED!\n";
			}
		}else{
			std::cout << "Save exists.\n";
			std::cout << "Loading...\n";
			load_file(p);
		}
	}

	int create_file()
	{
		std::ofstream file;
		file.open("save.pcsav", std::ios::out | std::ios::app);
		for(int i = 0; i < 6; ++i){
			file << 0;
			file << " ";
		}
	}

	void load_file(Player& p)
	{
		std::ifstream file;
		file.open("save.pcsav", std::ios::in);
		int i; float f;
		file >> i;	p.set_lvl(SkillEnum::MINING, i);
		file >> i; 	p.set_lvl(SkillEnum::FISHING, i);
		file >> i;	p.set_lvl(SkillEnum::WOODCUTTING, i);
		file >> f;	p.set_xp(SkillEnum::MINING, f);
		file >> f;	p.set_xp(SkillEnum::FISHING, f);
		file >> f;	p.set_xp(SkillEnum::WOODCUTTING, f);
		file.close();
	}

	void save_file(Player& p)
	{
		std::ofstream file;
		file.open("save.pcsav", std::ios::out | std::ios::trunc);
		int i; float f;
		i = p.get_lvl(SkillEnum::MINING); 		file << i;	file << " ";
		i = p.get_lvl(SkillEnum::FISHING); 		file << i;	file << " ";
		i = p.get_lvl(SkillEnum::WOODCUTTING); 	file << i;	file << " ";
		f = p.get_xp(SkillEnum::MINING); 		file << f;	file << " ";
		f = p.get_xp(SkillEnum::FISHING); 		file << f;	file << " ";
		f = p.get_xp(SkillEnum::WOODCUTTING); 	file << f;	file << " ";
		file.close();
	}

	bool fexists(std::string filename)
	{
		std::ifstream file(filename);
		return file;
	}
};

#endif // SAVEFILE_H
