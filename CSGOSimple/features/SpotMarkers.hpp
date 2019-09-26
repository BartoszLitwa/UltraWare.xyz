#pragma once
#include "../Includes.h"

class CSpotMarkers //https://www.youtube.com/watch?v=GeO4jt0R5k4 and https://www.youtube.com/watch?v=CutMdeJ3aZE
{
public:
	void Update();
	void WalkBot(CUserCmd* cmd); 
	bool button_clicked = false;
	int marker = 0; //current spot
private:
	void Refresh(std::string levelName, std::vector<Vector>& spots, bool save);
	bool button_down = false;
	
	int Team;
	std::string levelName;
	std::vector<Vector> spots;
};

extern CSpotMarkers* spotmarkers;