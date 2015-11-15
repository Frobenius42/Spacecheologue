#include "player.hpp"

Player::Player(b2World* world, float x, float y)
: mPos()
, mBody()
{
    b2BodyDef mBodyDef; // def du joueur
    mBodyDef.type = b2_dynamicBody; // le joueur est un corps dynamique
    mBodyDef.fixedRotation = true; // ULTRA IMPORTANT SINON LES COLLISIONS FONT ROTATER LE PLAYER !!!
	mBodyDef.position.Set(x, y);

	b2PolygonShape mBox;
	mBox.SetAsBox(0.2f, 0.3f);

	b2FixtureDef mFixtureDef;
	mFixtureDef.shape = &mBox;
	mFixtureDef.density = 0.0f;
	mFixtureDef.friction = 0.f;
	mFixtureDef.restitution = 0.f;

	mBody = world->CreateBody(&mBodyDef);
    mBody->CreateFixture(&mFixtureDef);

    mBox.SetAsBox(0.05, 0.05, b2Vec2(0,-2), 0);
    mFixtureDef.isSensor = true;
    b2Fixture* footSensorFixture = mBody->CreateFixture(&mFixtureDef);
    footSensorFixture->SetUserData( (void*)3 );
}

Player::Player()
: mPos()
, mBody()
{

}

b2Body* Player::getBody()
{
    return mBody;
}

sf::Vector2f Player::getPos()
{
    return mPos;
}
