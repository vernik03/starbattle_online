#pragma once
#include "MapCreator.h"
#include "boost_asio.h"

class InfoToSend
{
public:
	InfoToSend();
	~InfoToSend();

	void AddID() {

	}

	void Update() {
		to_send.clear();
		to_send += std::to_string(PERSONAL_ID);
	}

	void SetCoords(int x, int y) {
		to_send += " mm"; // mouse move
		to_send += std::to_string(x);
		to_send += "_";
		to_send += std::to_string(y);
		
	}

	void SetKey(FRKey k) {
		to_send += " kb"; //keyboard buttom
		switch (k)
		{
		case FRKey::RIGHT:
			to_send += "r";
			break;
		case FRKey::LEFT:
			to_send += "l";
			break;
		case FRKey::DOWN:
			to_send += "d";
			break;
		case FRKey::UP:
			to_send += "u";
			break;
		default:
			break;
		}
	}

	void SetClick(FRMouseButton button, bool isReleased) {
		to_send += " mb"; //mouse buttom
		switch (button)
		{
		case FRMouseButton::LEFT:
			to_send += "l";
			break;
		case FRMouseButton::MIDDLE:
			to_send += "m";
			break;
		case FRMouseButton::RIGHT:
			to_send += "r";
			break;
		default:
			break;
		}
	}

	std::string GetResult() {
		return to_send;
	}
private:
	std::string to_send;

};
