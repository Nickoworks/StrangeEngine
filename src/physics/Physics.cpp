#include "Physics.h"

Vector2Df Physics::gravity = Vector2Df(0.0, 9.81);

std::unordered_map<int, std::unordered_map<std::string, std::unique_ptr<StaticBody> > > Physics::layersStaticBodies;
std::unordered_map<int, std::unordered_map<std::string, std::unique_ptr<RigidBody> > > Physics::layersRigidBodies;
std::unordered_map<int, std::unordered_map<std::string, std::unique_ptr<KinematicBody> > > Physics::layersKinematicBodies;

PhysicBody::PhysicBody(Vector2Df position_, Vector2Df size, Vector2Df velocity_, Vector2Df acceleration_, float mass_, float restitution) : 
position(position_), velocity(velocity_), acceleration(acceleration_), mass(mass_), size(size), restitution(restitution){
    rect = {static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size.x), static_cast<int>(size.y)};
}

void PhysicBody::applyForce(Vector2Df force){
    acceleration = acceleration + force;
}

void PhysicBody::update(float deltaTime){
    rect = {static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size.x), static_cast<int>(size.y)};
    applyForce(Physics::gravity * mass);
    velocity = velocity + (acceleration * deltaTime);
    position = position + (velocity * deltaTime);
    acceleration = Vector2Df(0, 0);
}

bool PhysicBody::checkCollisionPhysicBody(PhysicBody& body){
    return position.x < body.position.x + body.size.x &&
           position.x + size.x > body.position.x &&
           position.y < body.position.y + body.size.y &&
           position.y + size.y > body.position.y;
}

void PhysicBody::handleCollisionStaticBodyX(StaticBody& body){
    if(checkCollisionPhysicBody(body)){
        Vector2Df normalizedVelocity = velocity.normalized();

        float staticBodyTop = body.position.y;
        float staticBodyBottom = body.position.y + body.size.y;

        float physicBodyTop = position.y;
        float physicBodyBottom = position.y + body.size.y;

        if(normalizedVelocity.x > 0){
            if(physicBodyTop < staticBodyBottom && physicBodyBottom > staticBodyTop){
                if(velocity.x > 0){
                    velocity.x = -velocity.x;
                }
                velocity.x = velocity.x * restitution;
                position.x = body.position.x - body.size.x;
            }
        }
        else if(normalizedVelocity.x < 0){
            if(physicBodyTop < staticBodyBottom && physicBodyBottom > staticBodyTop){
                if(velocity.x < 0){
                    velocity.x = -velocity.x;
                }
                velocity.x = velocity.x * restitution;
                position.x = body.position.x + body.size.x;
            }      
        }
    }    
}

void PhysicBody::handleCollisionStaticBodyY(StaticBody& body){
    if(checkCollisionPhysicBody(body)){
        Vector2Df normalizedVelocity = velocity.normalized();

        float staticBodyTop = body.position.y;
        float staticBodyBottom = body.position.y + body.size.y;

        float physicBodyTop = position.y;
        float physicBodyBottom = position.y + size.y;

        if(normalizedVelocity.y > 0){
            if(physicBodyBottom > staticBodyTop && physicBodyTop < staticBodyTop){
                velocity.y = -velocity.y * restitution;
                position.y = body.position.y - size.y;
            }
        }
        else if(normalizedVelocity.y < 0){
            if(physicBodyTop < staticBodyBottom && physicBodyBottom > staticBodyBottom){
                velocity.y = -velocity.y * restitution;
                position.y = body.position.y + body.size.y;
            }
        }
    }    
}

void PhysicBody::handleCollisionStaticBody(StaticBody& body){
    if (position.y > body.position.y + body.size.y - (body.size.y/10) || position.y + size.y < body.position.y + (body.size.y/10)) {
        handleCollisionStaticBodyY(body);
    } else if(position.x > body.position.x + body.size.x - (body.size.x/10) || position.x + size.x < body.position.x + (body.size.x/10)){
        handleCollisionStaticBodyX(body);
    } else {
        handleCollisionStaticBodyY(body);
        handleCollisionStaticBodyX(body);
    }    
}

void PhysicBody::handleCollisionRigidBodyX(RigidBody& body){
    if(checkCollisionPhysicBody(body)){
        Vector2Df normalizedVelocity = velocity.normalized();

        float rigidBodyTop = body.position.y;
        float rigidBodyBottom = body.position.y + body.size.y;

        float physicBodyTop = position.y;
        float physicBodyBottom = position.y + size.y;

        if(normalizedVelocity.x > 0){
            if(physicBodyTop < rigidBodyBottom && physicBodyBottom > rigidBodyTop){
                if(velocity.x > 0){
                    velocity.x = -velocity.x;
                }
                velocity.x = velocity.x * restitution;
                position.x = body.position.x - body.size.x;
            }
        }
        else if(normalizedVelocity.x < 0){
            if(physicBodyTop < rigidBodyBottom && physicBodyBottom > rigidBodyTop){
                if(velocity.x < 0){
                    velocity.x = -velocity.x;
                }
                velocity.x = velocity.x * restitution;
                position.x = body.position.x + body.size.x;
            }      
        }
    }
}

void PhysicBody::handleCollisionRigidBodyY(RigidBody& body){
    if(checkCollisionPhysicBody(body)){
        Vector2Df normalizedVelocity = velocity.normalized();

        float rigidBodyTop = body.position.y;
        float rigidBodyBottom = body.position.y + body.size.y;

        float physicBodyTop = position.y;
        float physicBodyBottom = position.y + size.y;

        if(normalizedVelocity.y > 0){
            if(physicBodyBottom > rigidBodyTop && physicBodyTop < rigidBodyTop){
                velocity.y = -velocity.y * restitution;
                position.y = body.position.y - size.y;
            }
        }
        else if(normalizedVelocity.y < 0){
            if(physicBodyTop < rigidBodyBottom && physicBodyBottom > rigidBodyBottom){
                velocity.y = -velocity.y * restitution;
                position.y = body.position.y + body.size.y;
            }
        }
    }    
}

void PhysicBody::handleCollisionRigidBody(RigidBody& body){
    if (position.y > body.position.y + body.size.y - (body.size.y/10) || position.y + size.y < body.position.y + (body.size.y/10)) {
        handleCollisionRigidBodyY(body);
    } else if(position.x > body.position.x + body.size.x - (body.size.x/10) || position.x + size.x < body.position.x + (body.size.x/10)){
        handleCollisionRigidBodyX(body);
    } else {
        handleCollisionRigidBodyY(body);
        handleCollisionRigidBodyX(body);
    }    
}

void PhysicBody::handleCollisionKinematicBodyX(KinematicBody& body){
    if(checkCollisionPhysicBody(body)){
        Vector2Df normalizedVelocity = velocity.normalized();

        float kinematicBodyTop = body.position.y;
        float kinematicBodyBottom = body.position.y + body.size.y;

        float physicBodyTop = position.y;
        float physicBodyBottom = position.y + size.y;

        if(normalizedVelocity.x > 0){
            if(physicBodyTop < kinematicBodyBottom && physicBodyBottom > kinematicBodyTop){
                if(velocity.x > 0){
                    velocity.x = -velocity.x;
                }
                velocity.x = velocity.x * restitution;
                position.x = body.position.x - size.x;
            }
        }
        else if(normalizedVelocity.x < 0){
            if(physicBodyTop < kinematicBodyBottom && physicBodyBottom > kinematicBodyTop){
                if(velocity.x < 0){
                    velocity.x = -velocity.x;
                }
                velocity.x = velocity.x * restitution;
                position.x = body.position.x + body.size.x;
            }      
        }
    } 
}

void PhysicBody::handleCollisionKinematicBodyY(KinematicBody& body){
    if(checkCollisionPhysicBody(body)){
        Vector2Df normalizedVelocity = velocity.normalized();

        float kinematicBodyTop = body.position.y;
        float kinematicBodyBottom = body.position.y + body.size.y;

        float physicBodyTop = position.y;
        float physicBodyBottom = position.y + size.y;

        if(normalizedVelocity.y > 0){
            if(physicBodyBottom > kinematicBodyTop && physicBodyTop < kinematicBodyTop){
                velocity.y = -velocity.y * restitution;
                position.y = body.position.y - size.y;
            }
        }
        else if(normalizedVelocity.y < 0){
            if(physicBodyTop < kinematicBodyBottom && physicBodyBottom > kinematicBodyBottom){
                velocity.y = -velocity.y * restitution;
                position.y = body.position.y + body.size.y;
            }
        }
    }
}

void PhysicBody::handleCollisionKinematicBody(KinematicBody& body){
    if (position.y > body.position.y + body.size.y - (body.size.y/10) || position.y + size.y < body.position.y + (body.size.y/10)) {
        handleCollisionKinematicBodyY(body);
    } else if(position.x > body.position.x + body.size.x - (body.size.x/10) || position.x + size.x < body.position.x + (body.size.x/10)){
        handleCollisionKinematicBodyX(body);
    } else {
        handleCollisionKinematicBodyY(body);
        handleCollisionKinematicBodyX(body);
    }
}

void PhysicBody::handleCollisionPhysicBodyX(PhysicBody& body){
    if(checkCollisionPhysicBody(body)){
        Vector2Df normalizedVelocity = velocity.normalized();

        float otherBodyTop = body.position.y;
        float otherBodyBottom = body.position.y + body.size.y;

        float physicBodyTop = position.y;
        float physicBodyBottom = position.y + size.y;

        if(normalizedVelocity.x > 0){
            if(physicBodyTop < otherBodyBottom && physicBodyBottom > otherBodyTop){
                if(velocity.x > 0){
                    velocity.x = -velocity.x;
                }
                velocity.x = velocity.x * restitution;
                position.x = body.position.x - size.x;
            }
        }
        else if(normalizedVelocity.x < 0){
            if(physicBodyTop < otherBodyBottom && physicBodyBottom > otherBodyTop){
                if(velocity.x < 0){
                    velocity.x = -velocity.x;
                }
                velocity.x = velocity.x * restitution;
                position.x = body.position.x + body.size.x;
            }      
        }
    }
}

void PhysicBody::handleCollisionPhysicBodyY(PhysicBody& body){
    if(checkCollisionPhysicBody(body)){
        Vector2Df normalizedVelocity = velocity.normalized();

        float otherBodyTop = body.position.y;
        float otherBodyBottom = body.position.y + body.size.y;

        float physicBodyTop = position.y;
        float physicBodyBottom = position.y + size.y;

        if(normalizedVelocity.y > 0){
            if(physicBodyBottom > otherBodyTop && physicBodyTop < otherBodyTop){
                velocity.y = -velocity.y * restitution;
                position.y = body.position.y - size.y;
            }
        }
        else if(normalizedVelocity.y < 0){
            if(physicBodyTop < otherBodyBottom && physicBodyBottom > otherBodyBottom){
                velocity.y = -velocity.y * restitution;
                position.y = body.position.y + body.size.y;
            }
        }
    }
}

void PhysicBody::handleCollisionPhysicBody(PhysicBody& body){
    if (position.y > body.position.y + body.size.y - (body.size.y/10) || position.y + size.y < body.position.y + (body.size.y/10)) {
        handleCollisionPhysicBodyY(body);
    } else if(position.x > body.position.x + body.size.x - (body.size.x/10) || position.x + size.x < body.position.x + (body.size.x/10)){
        handleCollisionPhysicBodyX(body);
    } else {
        handleCollisionPhysicBodyY(body);
        handleCollisionPhysicBodyX(body);
    }
}

RigidBody::RigidBody(Vector2Df position_, Vector2Df size_, Vector2Df velocity_, Vector2Df acceleration_, float mass_ = 1.f, float restitution_ = 1.f) : 
PhysicBody(position_, size_, velocity_, acceleration_, mass_, restitution_){
    type = "RigidBody";
    rect = {static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size.x), static_cast<int>(size.y)};
}

void RigidBody::update(float deltaTime){
    rect = {static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size.x), static_cast<int>(size.y)};
    applyForce(Physics::gravity * mass);
    velocity = velocity + (acceleration * deltaTime);
    position = position + (velocity * deltaTime);
    acceleration = Vector2Df(0, 0);
}

StaticBody::StaticBody(Vector2Df pos, Vector2Df size) : 
PhysicBody(pos, size, Vector2Df(0, 0), Vector2Df(0, 0), 0.f, 0.f){
    type = "StaticBody";
    rect = {static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size.x), static_cast<int>(size.y)};
}

void StaticBody::update(float deltaTime){
    rect = {static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size.x), static_cast<int>(size.y)};
}

KinematicBody::KinematicBody(Vector2Df position_, Vector2Df size_, Vector2Df velocity_, Vector2Df acceleration_, float mass_ = 0.f, float restitution_ = 0.f) : 
PhysicBody(position_, size_, velocity_, acceleration_, mass_, restitution_){
    type = "KinematicBody";
    rect = {static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size.x), static_cast<int>(size.y)};
}

KinematicBody::KinematicBody(Vector2Df position_, Vector2Df size_, Vector2Df velocity_) : 
PhysicBody(position_, size_, velocity_, Vector2Df(0, 0), 0.f, 0.f){
    type = "KinematicBody";
    rect = {static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size.x), static_cast<int>(size.y)};
}

KinematicBody::KinematicBody(Vector2Df position_, Vector2Df size_) : 
PhysicBody(position_, size_, Vector2Df(0, 0), Vector2Df(0, 0), 0.f, 0.f){
    type = "KinematicBody";
    rect = {static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size.x), static_cast<int>(size.y)};
}

void KinematicBody::update(float deltaTime){
    rect = {static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(size.x), static_cast<int>(size.y)};
    velocity = velocity + (acceleration * deltaTime);
    position = position + (velocity * deltaTime);
    acceleration = Vector2Df(0, 0);
    
}

// make more methods and make collision detection in all this objects
// and make collision mask

void Physics::trimSpaces(std::string& str) {
    size_t start = str.find_first_not_of(" ");
    size_t end = str.find_last_not_of(" ");
    if(start == std::string::npos){
        str = "";
    } else {
        str = str.substr(start, end - start + 1);
    }
}

void Physics::setPhysicsBodiesFromFile(std::string data){


    //Vector2Df position_, Vector2Df size, Vector2Df velocity_, Vector2Df acceleration_, float mass_, float restitution

    // TYPE, NAME: PARAMS 

    layersStaticBodies.clear();
    layersRigidBodies.clear();
    layersKinematicBodies.clear();

    std::istringstream file(data);
    std::string line;

    std::string physic_body_type;
    std::string name;
    std::string positionX, positionY;
    std::string sizeX, sizeY;
    std::string velocityX, velocityY;
    std::string accelerationX, accelerationY;
    std::string mass;
    std::string restitution;
    std::string layerID;

    while(std::getline(file, line)){
        if(line == ""){
            continue;
        }
        std::string line_ = line;
        size_t pos = line.find(":");
        line.erase(pos);

        std::istringstream type_name(line);
        
        std::getline(type_name, physic_body_type, ',');
        std::getline(type_name, name, ',');

        trimSpaces(physic_body_type);
        trimSpaces(name);

        if(physic_body_type == "StaticBody"){
            //Vector2Df pos, Vector2Df size
            line_.erase(0, pos+1);
            std::istringstream params(line_);
            std::getline(params, positionX, ',');
            std::getline(params, positionY, ',');
            std::getline(params, sizeX, ',');
            std::getline(params, sizeY, ',');
            std::getline(params, layerID, ',');

            trimSpaces(positionX);
            trimSpaces(positionY);
            trimSpaces(sizeX);
            trimSpaces(sizeY);


            createStaticBody(Vector2Df(std::stof(positionX), std::stof(positionY)), 
                            Vector2Df(std::stof(sizeX), std::stof(sizeY)), 
                            std::stoi(layerID), 
                            name);
            LOG("PHYSICS", "created StaticBody: " + name);
        }

        else if(physic_body_type == "RigidBody"){
            //Vector2Df position_, Vector2Df size_, Vector2Df velocity_, Vector2Df acceleration_, float mass_, float restitution_
            line_.erase(0, pos+1);

            std::istringstream params(line_);
            std::getline(params, positionX, ',');
            std::getline(params, positionY, ',');
            std::getline(params, sizeX, ',');
            std::getline(params, sizeY, ',');
            std::getline(params, velocityX, ',');
            std::getline(params, velocityY, ',');
            std::getline(params, accelerationX, ',');
            std::getline(params, accelerationY, ',');
            std::getline(params, mass, ',');
            std::getline(params, restitution, ',');
            std::getline(params, layerID, ',');

            trimSpaces(positionX);
            trimSpaces(positionY);
            trimSpaces(sizeX);
            trimSpaces(sizeY);
            trimSpaces(velocityX);
            trimSpaces(velocityY);
            trimSpaces(accelerationX);
            trimSpaces(accelerationY);
            trimSpaces(mass);
            trimSpaces(restitution);
            trimSpaces(layerID);

            createRigidBody(Vector2Df(std::stof(positionX), std::stof(positionY)),
                            Vector2Df(std::stof(sizeX), std::stof(sizeY)),
                            Vector2Df(std::stof(velocityX), std::stof(velocityY)),
                            Vector2Df(std::stof(accelerationX), std::stof(accelerationY)),
                            std::stoi(layerID), name, std::stof(mass), std::stof(restitution));
            LOG("PHYSICS", "created RigidBody: " + name);
        }

        else if(physic_body_type == "KinematicBody"){
            //Vector2Df position_, Vector2Df size_, Vector2Df velocity_, Vector2Df acceleration_, float mass_, float restitution_
            line_.erase(0, pos+1);
            
            std::istringstream params(line_);
            std::getline(params, positionX, ',');
            std::getline(params, positionY, ',');
            std::getline(params, sizeX, ',');
            std::getline(params, sizeY, ',');
            std::getline(params, velocityX, ',');
            std::getline(params, velocityY, ',');
            std::getline(params, accelerationX, ',');
            std::getline(params, accelerationY, ',');
            std::getline(params, mass, ',');
            std::getline(params, restitution, ',');
            std::getline(params, layerID, ',');

            trimSpaces(positionX);
            trimSpaces(positionY);
            trimSpaces(sizeX);
            trimSpaces(sizeY);
            trimSpaces(velocityX);
            trimSpaces(velocityY);
            trimSpaces(accelerationX);
            trimSpaces(accelerationY);
            trimSpaces(mass);
            trimSpaces(restitution);
            trimSpaces(layerID);

            createKinematicBody(Vector2Df(std::stof(positionX), std::stof(positionY)),
                                Vector2Df(std::stof(sizeX), std::stof(sizeY)),
                                Vector2Df(std::stof(velocityX), std::stof(velocityY)),
                                Vector2Df(std::stof(accelerationX), std::stof(accelerationY)),
                                std::stof(mass),
                                std::stof(restitution),
                                std::stoi(layerID),
                                name);
            LOG("PHYSICS", "created KinematicBody: " + name);
        }
    }
}

void Physics::update(float deltaTime){
    for(auto& layer : layersStaticBodies){
        for(auto& physic_body_layer : layer.second){
            auto& staticBody = physic_body_layer.second;
            staticBody->update(deltaTime);
            if(physic_body_layer.second->type != "StaticBody"){
                handleCollisionWithOnePhysicBody(physic_body_layer.second.get(), layer.first);
            }
        }
    }
    for(auto& layer : layersRigidBodies){
        for(auto& physic_body_layer : layer.second){
            auto& rigidBody = physic_body_layer.second;
            rigidBody->update(deltaTime);
            handleCollisionWithOnePhysicBody(physic_body_layer.second.get(), layer.first);
        }
    }
    for(auto& layer : layersKinematicBodies){
        for(auto& physic_body_layer : layer.second){
            auto& kinematicBody = physic_body_layer.second;
            kinematicBody->update(deltaTime);
            handleCollisionWithOnePhysicBody(physic_body_layer.second.get(), layer.first);
        }
    }
}

void Physics::createKinematicBody(Vector2Df position_, Vector2Df size_, Vector2Df velocity_, Vector2Df acceleration_, float mass_, float restitution_, int layerID, std::string name){
    layersKinematicBodies[layerID].emplace(name, std::make_unique<KinematicBody>(
        position_, size_, velocity_, acceleration_, mass_, restitution_
    ));
}

void Physics::createKinematicBody(Vector2Df position_, Vector2Df size_, Vector2Df velocity_, Vector2Df acceleration_, int layerID, std::string name){
    layersKinematicBodies[layerID].emplace(name, std::make_unique<KinematicBody>(
        position_, size_, velocity_, acceleration_
    ));
}

void Physics::createKinematicBody(Vector2Df position_, Vector2Df size_, Vector2Df velocity_, int layerID, std::string name){
    layersKinematicBodies[layerID].emplace(name, std::make_unique<KinematicBody>(
        position_, size_, velocity_
    ));
}

void Physics::createKinematicBody(Vector2Df position_, Vector2Df size_, int layerID, std::string name){
    layersKinematicBodies[layerID].emplace(name, std::make_unique<KinematicBody>(
        position_, size_
    ));
}

void Physics::createStaticBody(Vector2Df pos, Vector2Df size, int layerID, std::string name){
    layersStaticBodies[layerID].emplace(name, std::make_unique<StaticBody>(
        pos, size
    ));
}

void Physics::createRigidBody(Vector2Df position_, Vector2Df size_, Vector2Df velocity_, Vector2Df acceleration_, int layerID, std::string name, float mass_ = 1.f, float restitution_ = 1.f){
    layersRigidBodies[layerID].emplace(name, std::make_unique<RigidBody>(
        position_, size_, velocity_, acceleration_, mass_, restitution_
    ));
}

void Physics::handleCollisionWithOnePhysicBody(PhysicBody* currBody, int layer){
    for(auto& bodyPair : layersStaticBodies[layer]){
        StaticBody* otherBody = bodyPair.second.get();

        if(currBody != otherBody){
            currBody->handleCollisionPhysicBody(*otherBody);
        }
    }
    for(auto& bodyPair : layersRigidBodies[layer]){
        RigidBody* otherBody = bodyPair.second.get();

        if(currBody != otherBody){
            currBody->handleCollisionPhysicBody(*otherBody);
        }
    }
    for(auto& bodyPair : layersKinematicBodies[layer]){
        KinematicBody* otherBody = bodyPair.second.get();

        if(currBody != otherBody){
            currBody->handleCollisionPhysicBody(*otherBody);
        }
    }
}

StaticBody* Physics::getStaticBody(int layerID, std::string name){
    auto layerIt = layersStaticBodies.find(layerID);
    if (layerIt != layersStaticBodies.end()) {
        auto bodyIt = layerIt->second.find(name);
        if (bodyIt != layerIt->second.end()) {
            return bodyIt->second.get();
        }
    }
    return nullptr;
}

RigidBody* Physics::getRigidBody(int layerID, std::string name){
    auto layerIt = layersRigidBodies.find(layerID);
    if (layerIt != layersRigidBodies.end()) {
        auto bodyIt = layerIt->second.find(name);
        if (bodyIt != layerIt->second.end()) {
            return bodyIt->second.get();
        }
    }
    return nullptr;
}

KinematicBody* Physics::getKinematicBody(int layerID, std::string name){
    auto layerIt = layersKinematicBodies.find(layerID);
    if (layerIt != layersKinematicBodies.end()) {
        auto bodyIt = layerIt->second.find(name);
        if (bodyIt != layerIt->second.end()) {
            return bodyIt->second.get();
        }
    }
    return nullptr;
}
