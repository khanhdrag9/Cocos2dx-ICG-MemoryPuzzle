#include "GameStart.h"
#include "Defines.h"
#include "GamePlay.h"

USING_NS_CC;

GameStart::GameStart():
	_titleGame(nullptr),
	_labelStartGame(nullptr)
{

}
GameStart::~GameStart()
{
	CC_SAFE_DELETE(_titleGame);
	CC_SAFE_DELETE(_labelStartGame);
}

Scene* GameStart::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = GameStart::create();
	scene->addChild(layer);
	return scene;
}

bool GameStart::init()
{
	if (!Layer::init())
		return false;

	Size screenSize = Director::getInstance()->getVisibleSize();

	_titleGame = Label::createWithTTF(TITLE_GAME, FONT_TEXT, SIZE_TITLE_GAME);
	_titleGame->setPosition(screenSize.width * 0.5f, screenSize.height * 0.7);
	_titleGame->setColor(Color3B::GREEN);
	this->addChild(_titleGame);

	_labelStartGame = Label::createWithTTF(LABEL_STARTGAME, FONT_TEXT, SIZE_LABEL_STARTGAME);
	_labelStartGame->setPosition(screenSize.width * 0.5f, screenSize.height * 0.4f);
	this->addChild(_labelStartGame);

	auto listenerTouch = EventListenerTouchOneByOne::create();
	listenerTouch->onTouchBegan = [](Touch* touch, Event* event)
	{
		TransitionScene* trans = TransitionFade::create(1, GamePlay::createScene());
		Director::getInstance()->replaceScene(trans);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, this);

	return true;
}