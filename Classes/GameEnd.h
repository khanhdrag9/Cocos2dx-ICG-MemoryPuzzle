#pragma once
#include "cocos2d.h"

class GameEnd : public cocos2d::Layer
{
public:
	GameEnd();
	virtual ~GameEnd();

	static cocos2d::Scene* createScene();
	bool init();

	CREATE_FUNC(GameEnd);
};