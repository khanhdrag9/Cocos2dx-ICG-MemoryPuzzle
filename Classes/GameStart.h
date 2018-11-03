#pragma once
#include "cocos2d.h"

class GameStart : public cocos2d::Layer
{
	cocos2d::Label* _titleGame;
	cocos2d::Label* _labelStartGame;

public:
	GameStart();
	virtual ~GameStart();

	static cocos2d::Scene* createScene();
	bool init();

	CREATE_FUNC(GameStart);
};