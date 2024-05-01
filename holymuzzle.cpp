#include <memory>

#include "Memory.h"
#include <thread>

#include "features/Aim.h"
#include "features/Trigger.h"
#include "memory/Memory.h"

int main() {

    const auto memory = std::make_shared<Memory>("cs2.exe");

    std::cout << "Trying to attach to process..";
    while (!memory->IsAttached()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << ".";
        memory->attach("cs2.exe");
    }	
    std::cout << '\n' << "Attached to process: " << memory->GetProcessId() << '\n';
    memory->BuildImageOfModule("client.dll");
    const std::shared_ptr<ModuleImage> client = memory->GetModuleImage("client.dll");

    const auto localPlayerManager = std::make_shared<LocalPlayerManager>(memory, client);
    const auto entityManager = std::make_shared<EntityManager>(memory, client);

    const auto trigger = Trigger(localPlayerManager, entityManager);
    const auto aim = Aim(localPlayerManager, entityManager);
    
    while (memory->IsAttached()) {
        trigger.Run();
        aim.Run();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    
    std::cin.get();

    return 0;
}
