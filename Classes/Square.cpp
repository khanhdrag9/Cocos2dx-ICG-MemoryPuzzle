#include "Square.h"
#include "ManagerAnimations.h"

Square::Square()
{

}

Square::~Square()
{
}

Square* Square::createSquare(char* frameName, int iflag)
{
	Square* square = new Square();
	if (square && square->initWithSpriteFrameName(frameName))
	{
		square->_flag = iflag;
		square->autorelease();
		return square;
	}
	CC_SAFE_DELETE(square);
	return nullptr;
}

void Square::flip(cocos2d::Animate* iAnimate)
{
	if (iAnimate == nullptr)iAnimate = ManagerAnimation::getInstance()->getAnimateByIndex(_flag - 1);
	this->runAction(iAnimate->clone());
}