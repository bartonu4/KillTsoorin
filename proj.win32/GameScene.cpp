#include "GameScene.h"


cocos2d::Scene * GameScene::createScene(){
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//scene->getPhysicsWorld()->setGravity(Vec2(0, 2));
	
	// 'layer' is an autorelease object
	auto layer = GameScene::create(scene->getPhysicsWorld());
	//layer->setPhysicsWorld(scene->getPhysicsWorld());


	// add layer as a child to scene
	scene->addChild(layer);
	
	// return the scene
	return scene;
}
bool GameScene::init(PhysicsWorld *phyWorld){
	world = phyWorld;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	CCLOG("visible height =%f width=%f, x=%f, y=%f", visibleSize.height, visibleSize.width, origin.x, origin.y);
	//TIMER 
	//schedule(CC_SCHEDULE_SELECTOR(GameScene::tick), 0.9f);

	//contacklistener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//edge sprite 
	auto sceneEdge = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(sceneEdge);
	this->addChild(edgeNode);


	auto backSprite = Sprite::create();
	backSprite->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height));
	backSprite->setColor(Color3B::WHITE);
	backSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backSprite, 0);
		
	createSprite(1, 10);
	return true;
}

void GameScene::createSprite(float scale, int tag)
{
	auto sprite = Sprite::create("f1.jpg");
	//sprite->setTextureRect(Rect(0, 0, 50, 50));
	
	//sprite->setColor(Color3B::RED);
	//sprite->setPosition(random(-visibleSize.width / 2+20, visibleSize.width / 2-20), random(-visibleSize.height / 2+20, visibleSize.height / 2-20));
	sprite->setPosition(random(10, 500), random(10, 500));
	
	
	auto physicsBody = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setGravityEnable(false);
	physicsBody->setContactTestBitmask(0xF);
	//physicsBody->setMass(2.0);
	//physicsBody->setVelocity(Vec2(cocos2d::random(-500, 500), random(-500, 500)));

	auto  rightHand = Sprite::create();
	rightHand->setTextureRect(Rect(0, 0, 20, 20));
	rightHand->setPosition(sprite->getPosition().x - sprite->getContentSize().width / 2, sprite->getPosition().y + sprite->getContentSize().height / 2);
	auto physicsHand = PhysicsBody::createCircle(20.0f,PhysicsMaterial(0.1,1,0));
	
	physicsHand->setGravityEnable(true);
	physicsHand->setDynamic(true);
	//Vec2 grB(hand->getPosition().x, hand->getPosition().y);
	//Vec2 grA(sprite->getPosition().x, sprite->getPosition().y);
	auto connection = PhysicsJointFixed::construct(physicsBody, physicsHand, Vec2(sprite->getPosition().x - sprite->getContentSize().width / 2, 
		sprite->getPosition().y + sprite->getContentSize().height / 2));
	rightHand->setPhysicsBody(physicsHand);
	
	world->addJoint(connection);




	sprite->setPhysicsBody(physicsBody);
	sprite->setScale(scale);
	sprite->setTag(tag);
	this->addChild(sprite);
	this->addChild(hand);

}
bool GameScene::onContactBegin(PhysicsContact &contact)
{
	auto spA = contact.getShapeA()->getBody()->getNode();
	auto spB = contact.getShapeB()->getBody()->getNode();
	if (spA == nullptr || spB == nullptr)
	{
		return false;
	}
	int tag = spA->getTag();
	float scale = spA->getScale();
	if (spA->getTag() == spB->getTag())
	{
		
		spA->removeFromParentAndCleanup(true);
		spB->removeFromParentAndCleanup(true);
		createSprite(scale*1.3f, tag * 2);
		return true;
	}
	else
	{
		return true;
	}
	
	
}
void GameScene::tick(float dt)
{
	createSprite(1, 10);
}

void GameScene::setPhysicsWorld(cocos2d::PhysicsWorld *physWorld){
	//world = this->getScene()->getPhysicsWorld();

}