#pragma once
#include "GlobalVariables.h"
#include "Framework.h"

class InfoToSend
{
public:
	InfoToSend(){};
	~InfoToSend(){};

	void AddID() {
		request += " ";
		request += std::to_string(personal_id_public);
	}

	void Update() {
		request.clear();
		request += "TICK";
		AddID();		
	}

	void SetCoords(int x, int y, Rotation rot) {
		request += " MM "; // mouse move
		request += std::to_string(int(x + window_x));
		request += " ";
		request += std::to_string(int(y + window_y));
		request += " ";
		switch (rot)
		{
		case Rotation::Top:
			request += 'T';
			break;
		case Rotation::Left:
			request += 'L';			
			break;
		case Rotation::Bottom:
			request += 'B';
			break;
		case Rotation::Right:
			request += 'R';
			break;
		default:
			break;
		}
		
		request += " " + std::to_string(personal_id_public) + " ";
		request += std::to_string(personal_id_private);
	}

	void SetKey(FRKey k) {
		request += " KB "; //keyboard buttom
		switch (k)
		{
		case FRKey::RIGHT:
			request += "R";
			break;
		case FRKey::LEFT:
			request += "L";
			break;
		case FRKey::DOWN:
			request += "D";
			break;
		case FRKey::UP:
			request += "U";
			break;
		default:
			break;
		}
		request += " " + std::to_string(personal_id_public) + " ";
		request += std::to_string(personal_id_private);
	}

	void SetClick(FRMouseButton button, bool isReleased) {
		request += " MB "; //mouse buttom
		switch (button)
		{
		case FRMouseButton::LEFT:
			request += "L";
			break;
		case FRMouseButton::MIDDLE:
			request += "M";
			break;
		case FRMouseButton::RIGHT:
			request += "R";
			break;
		default:
			break;
		}
		request += " " + std::to_string(personal_id_public) + " ";
		request += std::to_string(personal_id_private);
	}

	void SetClose() {
		request += " CLOSE"; 
		request += " " + std::to_string(personal_id_public) + " ";
		request += std::to_string(personal_id_private);
	}

};
