#include "Aim.h"

#include <memory>
#include <thread>

#include "./../Entity.h"
#include "./../utils/Math.h"
#include "./../utils/Vector2.h"

void Aim::Run() const
{
    entityManager->ClearEntities();
    localPlayerManager->UpdateLocalPlayer();
    
    const auto entityList = entityManager->GetEntityListBaseAddress();
    const auto listEntry = entityManager->GetListEntry();

    for(int i = 0; i < 64; i++) 
    {
        if(listEntry == 0) continue;

        const auto currentController = entityManager->GetCurrentController(listEntry, i);
        if(currentController == 0) continue;

        const int pawnHandle = entityManager->GetPawnHandleFromController(currentController);
        if(pawnHandle == 0) continue;

        uintptr_t currentPawn = entityManager->GetCurrentPawn(entityList, pawnHandle);
        if(currentPawn == localPlayerManager->GetLocalPlayerEntity()->pawnAddress) continue;

        if(entityManager->GetLifeState(currentPawn) != 256) continue;
        if(localPlayerManager->GetTeam() == entityManager->GetTeam(currentPawn)) continue;

        const auto entity = entityManager->CreateEntity(
            currentPawn,
            currentController,
            localPlayerManager->GetLocalPlayerEntity()->origin
            );

        entityManager->AddToEntities(entity);
        entityManager->SortEntities();
    }
    
    if(GetAsyncKeyState(VK_SHIFT)) // extract to config file
    {
        if(entityManager->HasEntities()) 
        {
            Vector3 playerView = localPlayerManager->GetOrigin() + localPlayerManager->GetView();
            Vector3 entityHead = entityManager->GetClosestEntity()->head;
            
            Vector2 newAngles = Math::CalculateAngles(playerView, entityHead);
            Vector3 newAnglesVec3 = Vector3(newAngles.y, newAngles.x, 0.0f);

            localPlayerManager->SetViewAngles(newAnglesVec3);
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }
}
#include "Aim.h"
