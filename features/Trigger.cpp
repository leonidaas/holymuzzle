#include "Trigger.h"
#include <thread>

void Trigger::shoot() const
{
    localPlayerManager->Shoot();
}

void Trigger::Stop()
{
    isRunning = false;
}

void Trigger::Run() const
{
    while(isRunning)
    {
        localPlayerManager->UpdateLocalPlayer();

        // Hardcoded Mouse 4 Button
        if (!GetAsyncKeyState(VK_XBUTTON1)) continue;
        
        int entIndex = localPlayerManager->GetEntIndex();
        if (entIndex != -1)
        {
            const uintptr_t currentPawn = entityManager->GetEntityInCrosshair(entIndex);
            const int entityTeam = entityManager->GetTeamFromEntity(currentPawn);
            const int entityHealth =entityManager->GetHealthFromEntity(currentPawn);

            constexpr bool SHOOT_SAME_TEAM = true; 

            if (entityHealth > 0 && (localPlayerManager->GetTeam() != entityTeam || SHOOT_SAME_TEAM)) {
                shoot();
            }
        }
    }
}