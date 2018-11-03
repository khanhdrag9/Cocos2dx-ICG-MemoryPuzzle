#include "ManagerAnimations.h"

ManagerAnimation* ManagerAnimation::_instance = new ManagerAnimation();

ManagerAnimation* ManagerAnimation::getInstance()
{
	return _instance;
}

cocos2d::Animate* ManagerAnimation::getAnimateByIndex(int index)
{
	if (index < _listAnimates.size())
		return _listAnimates[index];
	return nullptr;
}

void ManagerAnimation::addAnimate(cocos2d::Animate* iani)
{
	iani->retain();
	_listAnimates.push_back(iani);
}

void ManagerAnimation::release()
{
	for (auto x : _listAnimates)
	{
		CC_SAFE_DELETE(x);
	}
	_listAnimates.clear();
}