#pragma once
#include "cocos2d.h"

class Square : public cocos2d::Sprite
{
	int _flag;
public:
	Square();
	virtual ~Square();
	static Square* createSquare(char* frameName, int iflag);
	void flip(cocos2d::Animate* iAnimate = nullptr);

	inline bool operator == (Square& square);
};

inline bool Square::operator == (Square& square)
{
	return this->_flag == square._flag;
}