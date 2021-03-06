#pragma once
#include "cocos2d.h"
#define COCOS2D_DEBUG 1

#include "cocos2d.h"
#include <math.h>
USING_NS_CC;
class GameScene :
	public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	CREATE_FUNC(GameScene);
};

