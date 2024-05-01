#include "Trigger.h"
#include <thread>

void Trigger::shoot() const
{
    localPlayerManager->Shoot();
}

void Trigger::Run() const
{
    localPlayerManager->UpdateLocalPlayer();
    entityManager->UpdateEntityList();
    
    if (!GetAsyncKeyState(VK_XBUTTON1)) return; //extract to config file
    
    int entIndex = localPlayerManager->GetEntIndex();
    if (entIndex != -1)
    {
        const uintptr_t currentPawn = entityManager->GetEntityInCrosshair(entIndex);
        const int entityTeam = entityManager->GetTeamFromEntity(currentPawn);
        const int entityHealth =entityManager->GetHealthFromEntity(currentPawn);

        constexpr bool SHOOT_SAME_TEAM = true; // extract config file

        if (entityHealth > 0 && (localPlayerManager->GetTeam() != entityTeam || SHOOT_SAME_TEAM)) {
            shoot();
        }
    }
}
