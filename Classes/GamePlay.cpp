#include "GamePlay.h"
#include "Defines.h"
#include "ManagerAnimations.h"
#include <time.h>

USING_NS_CC;

GamePlay::GamePlay():
	_currenLevel(LEVEL2),
	_numberSquares(LEVEL2),
	_time(TIME2),
	_winLabel(nullptr),
	_loseLabel(nullptr),
	_resetLabel(nullptr),
	_isEndGame(false),
	_isPlay(false)
{
}

GamePlay::~GamePlay()
{
	for (int i = 0; i < _listSquares.size(); i++)
	{
		CC_SAFE_DELETE(_listSquares[i]);
	}
	_listSquares.clear();
	CC_SAFE_DELETE(_defaultAnimation);
	CC_SAFE_DELETE(_winLabel);
	CC_SAFE_DELETE(_loseLabel);
	CC_SAFE_DELETE(_resetLabel);

	//ManagerAnimation::getInstance()->release();
}

Scene* GamePlay::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = GamePlay::create();
	scene->addChild(layer);
	return scene;
}

bool GamePlay::init()
{
	if (!Layer::init())
		return false;
	srand(time(NULL));
	createGame();

	//listener touch
	auto listenerTouch = EventListenerTouchOneByOne::create();
	listenerTouch->onTouchBegan = [](Touch*, Event*) {return true; };
	listenerTouch->onTouchEnded = CC_CALLBACK_2(GamePlay::OnTouchRelease, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouch, this);

	this->schedule(schedule_selector(GamePlay::updateTime), 1.f);
	startGame();

	return true;
}

void GamePlay::updateTime(float dt)
{
	if(!_isEndGame)
	if (_time < 0)
	{
		if (_numberSquares > 0)
		{
			lose();
		}
	}
	else
	{
		if (_isPlay)
		{
			char time[10];
			sprintf(time, "Time: %d", _time);
			_timeLabel->setString(time);
			_time -= dt;
		}
	}
}

void GamePlay::createGame()
{
	_screenSize = Director::getInstance()->getVisibleSize();
	
	//create grid
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(FRAME_SPRITE_PLIST);

	//calculate size of each square, ranger between them.
	float lessSide = _screenSize.width < _screenSize.height ? _screenSize.height : _screenSize.width;
	float spriteSide = lessSide / (_currenLevel * 0.5f + 2);

	float posStartX = 0 + spriteSide;
	float posStartY = _screenSize.height * 0.5f + spriteSide;
	float ranger2Shape = spriteSide + spriteSide / (float)(_currenLevel * 0.5f - 1);

	//create default square - white
	char defaultSquare[20];
	sprintf(defaultSquare, PRE_NAME_FRAME_SQUARE, COLOR_DEFAULT);
	auto frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(defaultSquare);
	frame1->retain();
	_defaultAnimation = Animate::create(Animation::createWithSpriteFrames(Vector<SpriteFrame*>{frame1}, 0.5f));
	_defaultAnimation->retain();

	//create postions
	std::vector<Vec2> listPositions;
	for (int i = 0; i < _currenLevel; i++)
	{
		listPositions.push_back(Vec2(posStartX, posStartY));
		
		if (posStartX + ranger2Shape >= _screenSize.width)
		{
			posStartX = spriteSide;
			posStartY -= ranger2Shape;
		}
		else
		{
			posStartX += ranger2Shape;
		}
	}

	//create Square
	int index = 2;
	for (int i = 0; i < _currenLevel >> 1; i++)
	{
		Animate* animate;
		if (index == COLOR_DEFAULT)index++;

		char frameName[30];
		sprintf(frameName, PRE_NAME_FRAME_SQUARE, index);
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
		frame->retain();
		animate = Animate::create(Animation::createWithSpriteFrames(Vector<SpriteFrame*>{frame}, 0.0001f));
		ManagerAnimation::getInstance()->addAnimate(animate);

		_listSquares.push_back(Square::createSquare(defaultSquare, i+1));
		_listSquares.push_back(Square::createSquare(defaultSquare, i+1));

		index++;
	}

	//set position for each Square
	for (auto x : _listSquares)
	{
		int indexPos = rand() % listPositions.size();
		x->setPosition(listPositions[indexPos]);
		x->setScale(spriteSide / (float)(x->getContentSize().width));
		this->addChild(x);
		listPositions.erase(listPositions.begin() + indexPos);

#if SHOWALL
		x->flip();
#endif
	}
	//time
	char text[10];
	sprintf(text, "Time: %d", _time);
	_timeLabel = Label::createWithTTF(text, FONT_TEXT, _screenSize.height * 0.1);
	_timeLabel->setPosition(
		//_timeLabel->getBoundingBox().size.width + 10,
		_screenSize.width * 0.5,
		_screenSize.height - _timeLabel->getBoundingBox().size.height);
	this->addChild(_timeLabel);
}

void GamePlay::startGame()
{
	showAll();
	this->scheduleOnce(schedule_selector(GamePlay::hideAll), TIME_SHOW_PRE_GAME);
}

void GamePlay::showAll()
{
	for (auto x : _listSquares)
		x->flip();
}

void GamePlay::hideAll(float)
{
	for (auto x : _listSquares)
		x->flip(_defaultAnimation);
	_isPlay = true;
}

void GamePlay::flipDown2Square(Square* s1, Square* s2)
{
	auto waggle = Sequence::create(
		MoveBy::create(0.1f, Vec2(5.0, 0)),
		MoveBy::create(0.2f, Vec2(-10.0, 0)),
		MoveBy::create(0.1f, Vec2(5.0, 0)),
		nullptr
	);
	auto action = Sequence::createWithTwoActions(waggle, _defaultAnimation);

	s1->runAction(action->clone());
	s2->runAction(action->clone());

	CC_SAFE_DELETE(waggle);
	CC_SAFE_DELETE(action);
}

void GamePlay::Remove2Square(Square* s1, Square* s2)
{
	auto rotateAndDel = Spawn::createWithTwoActions(
		RotateBy::create(0.5f, 360),
		ScaleTo::create(0.5f, 0.2));
	
	auto dvs1 = CallFunc::create(std::bind(&GamePlay::dvisiable, this, s1));
	auto dvs2 = CallFunc::create(std::bind(&GamePlay::dvisiable, this, s2));
	dvs1->autorelease();
	dvs2->autorelease();
	
	s1->runAction(Sequence::createWithTwoActions(rotateAndDel, dvs1)->clone());
	s2->runAction(Sequence::createWithTwoActions(rotateAndDel, dvs2)->clone());

	CC_SAFE_DELETE(rotateAndDel);
	_numberSquares -= 2;
	if (_numberSquares == 0)
	{
		win();
	}
}

void GamePlay::dvisiable(Square* s)
{
	s->setVisible(false);
}

void GamePlay::disvisiableAll()
{
	for (auto x : _listSquares)
		x->setVisible(false);
}

void GamePlay::win()
{
	if (_winLabel == nullptr)
	{
		_winLabel = Label::createWithTTF(TITLE_WIN, FONT_TEXT, _screenSize.width * 0.3);
		_winLabel->setPosition(_screenSize * 0.5);
		this->addChild(_winLabel, 3);
	}
	if (_resetLabel == nullptr)
	{

	}
	disvisiableAll();
	_isEndGame = true;
}

void GamePlay::lose()
{
	if (_loseLabel == nullptr)
	{
		_loseLabel = Label::createWithTTF(TITLE_LOSE, FONT_TEXT, _screenSize.width * 0.3);
		_loseLabel->setPosition(_screenSize * 0.5);
		this->addChild(_loseLabel, 3);
	}
	if (_resetLabel == nullptr)
	{

	}
	disvisiableAll();
	_isEndGame = true;
}

void GamePlay::OnTouchRelease(cocos2d::Touch* i_touch, cocos2d::Event* i_event)
{
	if (_isEndGame)
	{
		Scene* scene = GamePlay::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
	}
	else if(_isPlay)
	{
		for (int i = 0; i < _listSquares.size(); i++)
		{
			auto p = _listSquares[i];
			auto t = p->getBoundingBox();
			if (p->isVisible())
			{
				if (p->getBoundingBox().containsPoint(i_touch->getLocation()))
				{
					bool isContained = false;
					for (auto x : _pressedSquares._Get_container())
					{
						if (x->getPosition() == p->getPosition())
						{
							isContained = true;
							break;
						}
					}
					if (!isContained)
					{
						p->flip();
						_pressedSquares.push(p);
						check2Square();
					}
				}
			}
		}
	}
}

void GamePlay::check2Square()
{
	if (_pressedSquares.size() >= 2)
	{
		Square* square1 = _pressedSquares.front();
		_pressedSquares.pop();
		Square* square2 = _pressedSquares.front();
		_pressedSquares.pop();

		if (*square1 == *square2)
		{
			Remove2Square(square1, square2);
		}
		else
		{
			flipDown2Square(square1, square2);
		}
	}
}