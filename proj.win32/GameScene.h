#pragma once
#include "cocos2d.h"
#define COCOS2D_DEBUG 1
#define CUSTOM_CREATE_FUNC(__TYPE__) \
	static __TYPE__* create(PhysicsWorld* world) \
{ \
	__TYPE__ *pRet = new __TYPE__(); \
if (pRet && pRet->init(world)) \
	{ \
	pRet->autorelease(); \
	return pRet; \
	} \
	 else \
	 { \
	 delete pRet; \
	 pRet = NULL; \
	 return NULL; \
	 } \
}
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
	
	void createSprite(float scale, int tag);
	void tick(float dt);
	bool onContactBegin(PhysicsContact &contact);
	CUSTOM_CREATE_FUNC(GameScene);
	virtual bool init(PhysicsWorld * phyWorld);
	void setPhysicsWorld(cocos2d::PhysicsWorld *physWorld);
private:
	cocos2d::PhysicsWorld *world;
};

