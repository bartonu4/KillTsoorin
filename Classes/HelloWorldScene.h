#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#define COCOS2D_DEBUG 1

#include "cocos2d.h"
#include <math.h>

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuEnter(cocos2d::Ref* psender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	bool someSpriteOn;
	cocos2d::Sprite *someSprite;

	cocos2d::PhysicsWorld *world;

	void setPhysicsWorld(cocos2d::PhysicsWorld *physWorld);
	bool onContactBegin(cocos2d::PhysicsContact& contact);


};

#endif // __HELLOWORLD_SCENE_H__
