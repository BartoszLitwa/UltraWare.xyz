#pragma once
#include "../Includes.h"
#include "../options.hpp"

class SkinChanger //https://github.com/adamb70/CSGO-skin-ID-dumper/blob/master/item_index.txt
{
public:
	bool SetGlove = true;
	int SelectedKnifeCT;
	int SelectedKnifeT;
	bool SetForceFullUpdate;
	void SetSkin(ClientFrameStage_t stage);
	void ForceFullUpdate(ClientFrameStage_t stage);
};

extern SkinChanger skinchanger;