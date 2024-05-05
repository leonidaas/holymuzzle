#include <memory>

#include "Memory.h"
#include <thread>

#include "features/Aim.h"
#include "features/Trigger.h"
#include "memory/Memory.h"

int main() {

    const auto memory = std::make_unique<Memory>("cs2.exe");

    std::cout << "Trying to attach to process..";
    while (!memory->IsAttached()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << ".";
        memory->attach("cs2.exe");
    }	
    std::cout << '\n' << "Attached to process: " << memory->GetProcessId() << '\n';
    memory->BuildImageOfModule("client.dll");
    const std::shared_ptr<ModuleImage> client = memory->GetModuleImage("client.dll");

    const auto localPlayerManager = std::make_unique<LocalPlayerManager>(memory.get(), client.get());
    const auto entityManager = std::make_unique<EntityManager>(memory.get(), client.get());

    const auto trigger = std::make_shared<Trigger>(localPlayerManager.get(), entityManager.get());
    const auto aim = std::make_shared<Aim>(localPlayerManager.get(), entityManager.get());

    std::thread triggerThread(&Trigger::Run, trigger);
    std::thread aimThread(&Aim::Run, aim);

    //Exit Button Mouse 5
    while (!GetAsyncKeyState(VK_XBUTTON2)) {
       // Could catch UserInput here
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    
    trigger->Stop();
    aim->Stop();
    
    triggerThread.join();
    aimThread.join();

    return 0;
}
