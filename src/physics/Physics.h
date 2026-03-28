#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <memory>
#include "SDL_include.h"
#include <sstream>
#include <string>
#include "Vector2D.h"
#include "Logger.h"

typedef SDL_Rect Rect;

class StaticBody;
class RigidBody;
class KinematicBody;


using Vector2Df = Vector2D<float>;

class PhysicBody{
public:
    /* 
        Abstract class for physic bodies
    */
    Vector2Df position;
    Vector2Df velocity;
    Vector2Df size;
    Vector2Df acceleration;
    Rect rect;
    std::string type;
    //Vector2Df forces;
    float mass;
    float restitution;

    PhysicBody(Vector2Df position_, Vector2Df size, Vector2Df velocity_, Vector2Df acceleration_, float mass_, float restitution);

    void applyForce(Vector2Df force);
    virtual void update(float deltaTime);

    void handleCollisionStaticBodyX(StaticBody& body);
    void handleCollisionStaticBodyY(StaticBody& body);
    void handleCollisionStaticBody(StaticBody& body);

    void handleCollisionRigidBodyX(RigidBody& body);
    void handleCollisionRigidBodyY(RigidBody& body);
    void handleCollisionRigidBody(RigidBody& body);

    void handleCollisionKinematicBodyX(KinematicBody& body);
    void handleCollisionKinematicBodyY(KinematicBody& body);
    void handleCollisionKinematicBody(KinematicBody& body);

    void handleCollisionPhysicBodyX(PhysicBody& body);
    void handleCollisionPhysicBodyY(PhysicBody& body);
    void handleCollisionPhysicBody(PhysicBody& body);

    bool checkCollisionPhysicBody(PhysicBody& body);
};

class RigidBody : public PhysicBody{
public:
    RigidBody(Vector2Df position_, Vector2Df size_, Vector2Df velocity_, Vector2Df acceleration_, float mass_, float restitution_);
    void update(float deltaTime) override;
};

class StaticBody : public PhysicBody{
public:
    StaticBody(Vector2Df pos, Vector2Df size);
    void update(float deltaTime) override;
};

class KinematicBody : public PhysicBody{
public:
    KinematicBody(Vector2Df position_, Vector2Df size_, Vector2Df velocity_, Vector2Df acceleration_, float mass_, float restitution_);
    KinematicBody(Vector2Df position_, Vector2Df size_, Vector2Df velocity_);
    KinematicBody(Vector2Df position_, Vector2Df size_);
    void update(float deltaTime) override;
};

class Physics{
public:
    static Vector2Df gravity;
    static std::unordered_map<int, std::unordered_map<std::string, std::unique_ptr<StaticBody> > > layersStaticBodies;
    static std::unordered_map<int, std::unordered_map<std::string, std::unique_ptr<RigidBody> > > layersRigidBodies;
    static std::unordered_map<int, std::unordered_map<std::string, std::unique_ptr<KinematicBody> > > layersKinematicBodies;

    static void trimSpaces(std::string& str);
    static void setPhysicsBodiesFromFile(std::string data);

    static void update(float deltaTime);

    static void createKinematicBody(Vector2Df position_, Vector2Df size_, Vector2Df velocity_, Vector2Df acceleration_, float mass_, float restitution_, int layerID, std::string name);
    static void createKinematicBody(Vector2Df position_, Vector2Df size_, Vector2Df velocity_, Vector2Df acceleration_, int layerID, std::string name);
    static void createKinematicBody(Vector2Df position_, Vector2Df size_, Vector2Df velocity_, int layerID, std::string name);
    static void createKinematicBody(Vector2Df position_, Vector2Df size_, int layerID, std::string name);
    static void createStaticBody(Vector2Df pos, Vector2Df size, int layerID, std::string name);
    static void createRigidBody(Vector2Df position_, Vector2Df size_, Vector2Df velocity_, Vector2Df acceleration_, int layerID, std::string name, float mass_, float restitution_);

    static void handleCollisionWithOnePhysicBody(PhysicBody* currBody, int layer);

    static StaticBody* getStaticBody(int layerID, std::string name);
    static RigidBody* getRigidBody(int layerID, std::string name);
    static KinematicBody* getKinematicBody(int layerID, std::string name);
};
