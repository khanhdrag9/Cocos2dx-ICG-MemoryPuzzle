#include "GameEnd.h"

USING_NS_CC;

GameEnd::GameEnd()
{

}
GameEnd::~GameEnd()
{

}

Scene* GameEnd::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = GameEnd::create();
	scene->addChild(layer);
	return scene;
}

bool GameEnd::init()
{
	if (!Layer::init())
		return false;


	return true;
}
