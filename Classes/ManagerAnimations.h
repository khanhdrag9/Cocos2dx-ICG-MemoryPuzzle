#pragma once
#include "cocos2d.h"
#include <vector>

class ManagerAnimation : public cocos2d::Sprite
{
	ManagerAnimation(){}
	~ManagerAnimation() { }
	std::vector<cocos2d::Animate*> _listAnimates;

	static ManagerAnimation* _instance;
public:
	static ManagerAnimation* getInstance();
	cocos2d::Animate* getAnimateByIndex(int index);

	void addAnimate(cocos2d::Animate* iani);
	void release();
};