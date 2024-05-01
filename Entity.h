#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include "Memory.h"
#include <DirectXMath.h>

#include "utils/Vector3.h"

class Entity {
public:
    std::uintptr_t pawnAddress = 0;
    std::uintptr_t controllerAddress = 0;
	
    Vector3 origin = Vector3(0,0,0);
    Vector3 view = Vector3(0,0,0);
    Vector3 head = Vector3(0,0,0);

    int health = 0;
    unsigned int lifeState = 0;
    int team = 0;

    float distance = 0;

public:
    Entity() = default;
};

struct CompareDistance {
    bool operator()(const std::shared_ptr<Entity>& e1, const std::shared_ptr<Entity>& e2) const {
        return e1->distance < e2->distance;
    }
};