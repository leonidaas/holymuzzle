#pragma once
#include "./../memory/Memory.h"
#include "./../memory/Offsets.h"
#include "./../manager/EntityManager.h"
#include "./../manager/LocalPlayerManager.h"

class Aim 
{
public:
    Aim(LocalPlayerManager* lpm,
        EntityManager* em)
    : localPlayerManager(lpm), entityManager(em) {}
    
    void Run() const;
    void Stop();
private:
    LocalPlayerManager* localPlayerManager;
    EntityManager* entityManager;
    
    bool isRunning = true;
};
