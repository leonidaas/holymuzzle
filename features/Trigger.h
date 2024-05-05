#pragma once
#ifndef TRIGGER_H
#define TRIGGER_H

#include <memory>

#include "./../manager/EntityManager.h"
#include "./../manager/LocalPlayerManager.h"

class Trigger
{
public:
    Trigger(const LocalPlayerManager* lpm, const EntityManager* em) : localPlayerManager(lpm), entityManager(em) {}
    void Run() const;
    void Stop();

private:
    void shoot() const;

    bool isRunning = true;
    
    const LocalPlayerManager* localPlayerManager;
    const EntityManager* entityManager;
};

#endif
