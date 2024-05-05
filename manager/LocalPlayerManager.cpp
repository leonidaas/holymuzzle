#include "LocalPlayerManager.h"

uintptr_t LocalPlayerManager::GetLocalPlayerBaseAddress() const
{
   return memory->Read<uintptr_t>(client->m_Base + offsets::dwLocalPlayerPawn);
}

Vector3 LocalPlayerManager::GetOrigin() const
{
   return memory->Read<Vector3>(localPlayerEntity->pawnAddress + offsets::m_vOldOrigin);
}

int LocalPlayerManager::GetTeam() const
{
   return memory->Read<int>(localPlayerEntity->pawnAddress + offsets::m_iTeamNum);
}

int LocalPlayerManager::GetHealth() const
{
   return memory->Read<int>(localPlayerEntity->pawnAddress + offsets::m_iHealth);
}

int LocalPlayerManager::GetShotsFired()
{
   return 0; 
}

int LocalPlayerManager::GetEntIndex() const
{
   return memory->Read<int>(localPlayerEntity->pawnAddress + offsets::m_iIDEntIndex);
}


Vector3 LocalPlayerManager::GetView() const
{
   return memory->Read<Vector3>(localPlayerEntity->pawnAddress + offsets::m_vecViewOffset);
}

void LocalPlayerManager::SetViewAngles(Vector3 to) const
{
   memory->Write(client->m_Base + offsets::dwViewAngles, Vector3(0,0,0));
}

void LocalPlayerManager::Shoot() const
{
   std::this_thread::sleep_for(std::chrono::milliseconds(20)); // extract to config file
   memory->Write<int>(client->m_Base + offsets::dwForceAttack, 65537);
   std::this_thread::sleep_for(std::chrono::milliseconds(10));
   memory->Write<int>(client->m_Base + offsets::dwForceAttack, 256);
}


std::shared_ptr<Entity> LocalPlayerManager::GetLocalPlayerEntity()
{
   return localPlayerEntity;
}


void LocalPlayerManager::UpdateLocalPlayer() const
{
   localPlayerEntity->health = GetHealth();
   localPlayerEntity->team = GetTeam();
   localPlayerEntity->pawnAddress = GetLocalPlayerBaseAddress();
   localPlayerEntity->origin = GetOrigin();
   localPlayerEntity->view = GetView();
}


