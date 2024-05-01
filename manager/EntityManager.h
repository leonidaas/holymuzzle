#pragma once
#include <cstdint>
#include <vector>
#include "./../Entity.h"
#include "./../memory/Memory.h"
#include "./../memory/Offsets.h"

class Entity;

class EntityManager
{
public:
    EntityManager(std::shared_ptr<Memory> mem, std::shared_ptr<ModuleImage> mod) : memory(mem), client(mod)
    {
        UpdateEntityList();
    }; 
    
    uintptr_t GetEntityBaseAddress(int index);
    uintptr_t GetListEntry() const;
    uintptr_t GetCurrentController(uintptr_t listEntry, int index) const;

    uintptr_t GetCurrentPawn(uintptr_t entityList, int pawnHandle) const;

    int GetPawnHandleFromController(uintptr_t controllerAddress) const;
    uintptr_t GetEntityListBaseAddress() const;

    uintptr_t GetSceneNodeFromPawn(uintptr_t pawn) const;

    uintptr_t GetBoneMatrix(uintptr_t pawnAddress) const;
    
    uintptr_t GetEntityInCrosshair(int entIndex) const;
    int GetTeam(uintptr_t pawnAddress) const;
    int GetHealth(uintptr_t pawnAddress) const;
    unsigned int GetLifeState(uintptr_t pawnAddress) const;
    bool GetDormant(int index);

    int GetTeamFromEntity(uintptr_t base) const;
    int GetHealthFromEntity(uintptr_t base) const;
    
    float GetDistanceFromEntity(int index);
    uintptr_t GetBoneBase(int index);

    bool GetAliveState(int index);

    std::shared_ptr<Entity> CreateEntity(uintptr_t pawnAddress, uintptr_t controllerAddress, Vector3 localPlayerOrigin) const;

    void AddToEntities(std::shared_ptr<Entity> entity);
    void SortEntities();
    void UpdateEntityList();
    bool HasEntities() const;
    void ClearEntities();
    
    std::shared_ptr<Entity> GetClosestEntity();
    std::shared_ptr<Entity> GetEntityAt(int index);

private:
    uintptr_t entityList;
    std::vector<std::shared_ptr<Entity>> entities;

    std::shared_ptr<Memory> memory;
    std::shared_ptr<ModuleImage> client;
};
