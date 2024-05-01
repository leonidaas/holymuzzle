#include "EntityManager.h"

#include <algorithm>

uintptr_t EntityManager::GetEntityBaseAddress(int index)
{
   return 0; 
}

uintptr_t EntityManager::GetListEntry() const
{
   return memory->Read<uintptr_t>(GetEntityListBaseAddress() + 0x10);
}


uintptr_t EntityManager::GetCurrentController(uintptr_t listEntry, int index) const
{
   return  memory->Read<uintptr_t>(listEntry + ( index * 0x78 ));
}

int EntityManager::GetPawnHandleFromController(uintptr_t controllerAddress) const
{
   return memory->Read<int>(controllerAddress + offsets::m_hPlayerPawn);
}

uintptr_t EntityManager::GetCurrentPawn(uintptr_t entityList, const int pawnHandle) const
{
   intptr_t listEntry = memory->Read<uintptr_t>(entityList + (0x8 * ((pawnHandle & 0x7FFF) >> 9) + 0x10));
   intptr_t currentPawn = memory->Read<uintptr_t>(listEntry + (0x78 * (pawnHandle & 0x1FF)));

   return currentPawn;
}


uintptr_t EntityManager::GetEntityListBaseAddress() const
{
    return memory->Read<uintptr_t>(client->m_Base + offsets::dwEntityList);
}

uintptr_t EntityManager::GetEntityInCrosshair(int entIndex) const
{
    std::uintptr_t listEntry = memory->Read<uintptr_t>(entityList + (0x8 * ((entIndex & 0x7FFF) >> 9) + 0x10));
    std::uintptr_t currentPawn = memory->Read<uintptr_t>(listEntry + (0x78 * (entIndex & 0x1FF)));
    return currentPawn;
}

std::shared_ptr<Entity> EntityManager::CreateEntity(const uintptr_t pawnAddress, const uintptr_t controllerAddress,
                                                    const Vector3 localPlayerOrigin) const
{
   const auto entity = std::make_shared<Entity>();
   entity->pawnAddress = pawnAddress;
   entity->controllerAddress = controllerAddress;
   entity->health = GetHealth(pawnAddress);
   entity->lifeState = GetLifeState(pawnAddress);
   entity->origin = memory->Read<Vector3>(pawnAddress + offsets::m_vOldOrigin);
   entity->view = memory->Read<Vector3>(pawnAddress + offsets::m_vecViewOffset);
   entity->distance = Vector3::getDistance(entity->origin, localPlayerOrigin); 
   entity->head = memory->Read<Vector3>(GetBoneMatrix(pawnAddress) + (6 * 32)); // 6 bone id, 32 step between bones

   return entity;
}

int EntityManager::GetTeam(uintptr_t pawnAddress) const
{
   return memory->Read<int>(pawnAddress + offsets::m_iTeamNum); 
}


int EntityManager::GetHealth(uintptr_t pawnAddress) const
{
   return memory->Read<int>(pawnAddress + offsets::m_iHealth); 
}

unsigned int EntityManager::GetLifeState(uintptr_t pawnAddress) const
{
   return memory->Read<unsigned int>(pawnAddress + offsets::m_lifeState);
}

bool EntityManager::GetDormant(int index)
{
   return true; 
}

uintptr_t EntityManager::GetBoneMatrix(uintptr_t pawnAddress) const
{
   uintptr_t sceneNode =  memory->Read<uintptr_t>(pawnAddress + offsets::m_pGameSceneNode);
   return memory->Read<uintptr_t>(sceneNode + offsets::m_modelState + 0x80);
}

uintptr_t EntityManager::GetSceneNodeFromPawn(uintptr_t pawn) const
{
   return memory->Read<uintptr_t>(pawn + offsets::m_pGameSceneNode);
}

int EntityManager::GetHealthFromEntity(uintptr_t pawnAddress) const
{
   return memory->Read<int>(pawnAddress + offsets::m_iTeamNum);
}

int EntityManager::GetTeamFromEntity(uintptr_t pawnAddress) const
{
   return memory->Read<int>(pawnAddress + offsets::m_iTeamNum);
}


float EntityManager::GetDistanceFromEntity(int index)
{
   return 0.f;
}

uintptr_t EntityManager::GetBoneBase(int index)
{
   return 0; 
}

bool EntityManager::GetAliveState(int index)
{
   return true; 
}

void EntityManager::AddToEntities(std::shared_ptr<Entity> entity)
{
   entities.push_back(entity);
}

void EntityManager::SortEntities()
{
   std::sort(entities.begin(), entities.end(), CompareDistance());
   
}

void EntityManager::UpdateEntityList()
{
   entityList = GetEntityListBaseAddress(); 
}

void EntityManager::ClearEntities()
{
   entities.clear();
}


bool EntityManager::HasEntities() const
{
   return entities.size() > 0;
}

std::shared_ptr<Entity>EntityManager::GetClosestEntity()
{
   return GetEntityAt(0);
}


std::shared_ptr<Entity> EntityManager::GetEntityAt(int index)
{
   return entities.at(index);
}
