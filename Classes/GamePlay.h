#pragma once
#include "cocos2d.h"
#include "Square.h"
#include <vector>
#include <queue>

enum LEVELS {
	LEVEL1 = 8,
	LEVEL2 = 12,
	LEVEL3 = 16
};

enum LEVELS_TIME {
	TIME1 = 40,
	TIME2 = 30,
	TIME3 = 25,
};

class GamePlay : public cocos2d::Layer
{
	int _currenLevel;
	int _numberSquares;
	int _time;
	bool _isEndGame;
	bool _isPlay;
	cocos2d::Size _screenSize;

	std::queue<Square*> _pressedSquares;

	cocos2d::Animate* _defaultAnimation;
	std::vector<Square*> _listSquares;

	//win-lose
	cocos2d::Label* _winLabel;
	cocos2d::Label* _loseLabel;
	cocos2d::Label* _resetLabel;
	cocos2d::Label* _timeLabel;

	void createGame();
	void startGame();
	void showAll();
	void hideAll(float = 0.0);

	void check2Square();
	void flipDown2Square(Square* s1, Square* s2);
	void Remove2Square(Square* s1, Square* s2);
	void dvisiable(Square* s);

	void updateTime(float);
	void disvisiableAll();
	void win();
	void lose();
public:
	GamePlay();
	virtual ~GamePlay();

	static cocos2d::Scene* createScene();
	bool init();

	CREATE_FUNC(GamePlay);

	void OnTouchRelease(cocos2d::Touch* i_touch, cocos2d::Event* i_event);
};