#pragma once
#ifndef TRIGGER_H
#define TRIGGER_H

#include <memory>

#include "./../manager/EntityManager.h"
#include "./../manager/LocalPlayerManager.h"

class Trigger
{
public:
    Trigger(std::shared_ptr<LocalPlayerManager> lpm, std::shared_ptr<EntityManager> em) : localPlayerManager(lpm), entityManager(em) {}
    void Run() const;

private:
    void shoot() const;

    std::shared_ptr<LocalPlayerManager> localPlayerManager;
    std::shared_ptr<EntityManager> entityManager;
};

#endif
