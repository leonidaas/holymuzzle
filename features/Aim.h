#pragma once
#include "./../memory/Memory.h"
#include "./../memory/Offsets.h"
#include "./../manager/EntityManager.h"
#include "./../manager/LocalPlayerManager.h"

class Aim 
{
public:
    void Run() const;
    Aim(const std::shared_ptr<LocalPlayerManager>& lpm,
        const std::shared_ptr<EntityManager>& em
        )
    : localPlayerManager(lpm), entityManager(em) {}
    
    std::shared_ptr<LocalPlayerManager> localPlayerManager;
    std::shared_ptr<EntityManager> entityManager;
};
