#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
// 'scene' is an autorelease object
auto scene = Scene::createWithPhysics();
scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);


// 'layer' is an autorelease object
auto layer = HelloWorld::create();
layer->setPhysicsWorld(scene->getPhysicsWorld());

// add layer as a child to scene
scene->addChild(layer);

// return the scene
return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
//////////////////////////////
// 1. super init first
if (!Layer::init())
{
return false;
}

Size visibleSize = Director::getInstance()->getVisibleSize();
Vec2 origin = Director::getInstance()->getVisibleOrigin();

/////////////////////////////
// 2. add a menu item with "X" image, which is clicked to quit the program
// you may modify it.

// add a "close" icon to exit the progress. it's an autorelease object

auto closeItem = MenuItemImage::create(
"CloseNormal.png",
"CloseSelected.png",
CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
origin.y + closeItem->getContentSize().height / 2));
auto menuItem = MenuItemImage::create("play.png",
"CloseNormal.png",
CC_CALLBACK_1(HelloWorld::menuEnter, this));
menuItem->setPosition(Vec2(visibleSize.width / 2 - closeItem->getContentSize().width / 2,
visibleSize.height / 2));
menuItem->setScale(0.4);

// create menu, it's an autorelease object
auto menu = Menu::create(closeItem, NULL);
menu->addChild(menuItem);
menu->setPosition(Vec2::ZERO);
this->addChild(menu, 1);

/////////////////////////////
// 3. add your codes below...

// add a label shows "Hello World"
// create and initialize a label

auto label = Label::createWithTTF("Hello defdsg nu4", "fonts/Marker Felt.ttf", 24);

// position the label on the center of the screen
label->setPosition(Vec2(origin.x + visibleSize.width / 2,
origin.y + visibleSize.height - label->getContentSize().height));

// add the label as a child to this layer
this->addChild(label, 1);

// add "HelloWorld" splash screen"
auto backSprite = Sprite::create();
backSprite->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height));
backSprite->setColor(Color3B::GRAY);



// position the sprite on the center of the screen
backSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

// add the sprite as a child to this layer
this->addChild(backSprite, 0);
////////////

{
someSpriteOn = false;
someSprite = Sprite::create();
someSprite->setTextureRect(Rect(0, 0, 100, 100));
someSprite->setColor(Color3B::MAGENTA);
someSprite->setOpacity(255);


auto someBody = PhysicsBody::createBox(someSprite->getContentSize(), PhysicsMaterial(1, 1, 1));

someBody->setMass(19);
someBody->setVelocity(Vect(200, 0));

someBody->setCollisionBitmask(1);
someBody->setCategoryBitmask(0x01);
someBody->applyImpulse(Vect(500, 100));
someBody->setContactTestBitmask(true);

CCLOG("sy4");

someSprite->setPhysicsBody(someBody);


someSprite->setPosition(Vec2(100, 400));
this->addChild(someSprite, 1);
}

{
someSpriteOn = false;
someSprite = Sprite::create();
someSprite->setTextureRect(Rect(0, 0, 100, 100));
someSprite->setColor(Color3B::WHITE);
someSprite->setOpacity(255);

auto someBody = PhysicsBody::createBox(someSprite->getContentSize(), PhysicsMaterial(1, 1, 0));
someSprite->setPhysicsBody(someBody);
someBody->setMass(199);
//someBody->applyForce(Vect(6000, 700));
someBody->setCollisionBitmask(2);
//someBody->setCategoryBitmask(0x00);
someBody->setContactTestBitmask(true);
CCLOG("nu4");



someSprite->setPosition(Vec2(400, 500));
this->addChild(someSprite, 1);
}
auto contactListener = EventListenerPhysicsContact::create();
contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

///////////////
//Creating edge

auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
auto edgeSprite = Sprite::create();
edgeSprite->setPosition(visibleSize.width / 2+origin.x, visibleSize.height / 2+origin.y);
edgeSprite->setPhysicsBody(edgeBody);
this->addChild(edgeSprite);



return true;
}

void HelloWorld::setPhysicsWorld(cocos2d::PhysicsWorld *physWorld){
world = physWorld;

}
bool HelloWorld::onContactBegin(cocos2d::PhysicsContact& contact)
{
auto nodeA = contact.getShapeA()->getBody()->getCollisionBitmask();
auto nodeB = contact.getShapeB()->getBody()->getCollisionBitmask();
auto shapeA = contact.getShapeA();
CCLOG("kayato huyna");
if ((1==nodeA && nodeB == 2)||(2==nodeA&&nodeB==1))
{

	shapeA->getBody()->getNode()->removeFromParent();
CCLOG("per%d + vt%d", nodeA, nodeB);

}




//bodies can collide
return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
return;
#endif

Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
exit(0);
#endif
}
void HelloWorld::menuEnter(cocos2d::Ref* psender)
{


if (!someSpriteOn){
this->removeChild(someSprite, false);

someSpriteOn = true;
}
else{
someSpriteOn = false;
someSprite = Sprite::create();
someSprite->setTextureRect(Rect(0, 0, 100, 100));
someSprite->setColor(Color3B::MAGENTA);
someSprite->setOpacity(255);


someSprite->setPosition(Vec2(50, 239));
this->addChild(someSprite, 1);

}

}