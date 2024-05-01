#pragma once
#include <memory>
#include "./../memory/memory.h"
#include "./../utils/Vector3.h"
#include "./../Entity.h"
#include "./../memory/Offsets.h"
#include <thread>

class LocalPlayerManager
{
public:
    LocalPlayerManager(std::shared_ptr<Memory> mem, std::shared_ptr<ModuleImage> image) : memory(mem), client(image)
    {
        GetLocalPlayerEntity();
    }

    uintptr_t GetLocalPlayerBaseAddress() const ;
    Vector3 GetOrigin() const;
    int GetTeam() const;
    int GetHealth() const;
    int GetShotsFired();
    int GetEntIndex() const;
    Vector3 GetView() const;
    
    void UpdateLocalPlayer() const;
    void SetViewAngles(Vector3 to) const;

    void Shoot() const;

    std::shared_ptr<Entity> GetLocalPlayerEntity();

private:
    std::shared_ptr<Entity> localPlayerEntity = std::make_shared<Entity>();
    std::shared_ptr<Memory> memory;
    std::shared_ptr<ModuleImage> client;
};
