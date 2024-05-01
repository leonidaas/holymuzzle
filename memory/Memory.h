#pragma once 
#ifndef MEMORY_H
#define MEMORY_H

#include <Windows.h>
#include <iostream> 
#include <vector>
#include <memory>
#include <map>

/* Credits to ReactiioN */
class ModuleImage {
public:
    ModuleImage(void) = default;

    ModuleImage(const std::string& name, uintptr_t base, uintptr_t size);

    ~ModuleImage(void);

    void setup(const std::string& name, uintptr_t base, uintptr_t size);

public:
    std::string n_Name = ""; // name of the module
    uintptr_t m_Base = 0; // base address of the module
    uintptr_t m_Size = 0; // size of the module
    std::vector<byte> m_cBytes; // whole module buffered as bytes
};

class Memory {
private:

public:
    Memory() = default;
    explicit Memory(const std::string& processName);
    ~Memory();

    bool attach(const std::string& processName);
    bool IsAttached() const;

    bool BuildImageOfModule(const std::string& name);

    BOOL ReadMemory(uintptr_t address, void* buffer, size_t size) const;

    BOOL WriteMemory(uintptr_t address, const void* buffer, size_t size) const;

    uint32_t GetProcessId() const;

    HANDLE GetProcessHandle() const;

    std::shared_ptr<ModuleImage> GetModuleImage(const std::string& name) const;

    template< class T > BOOL Read(std::uintptr_t base, T& buffer);

    template< class T > BOOL Write(std::uintptr_t base, T buffer);

    template< class T > T Read(std::uintptr_t base);

    void Release(void);

private:
    bool m_attached = false;
    uint32_t m_processId = 0;
    HANDLE m_processHandle = nullptr;
    std::string m_processName = "";
    std::map<std::string, std::shared_ptr<ModuleImage>> m_moduleImages;
};

template < class T >
BOOL Memory::Read(uintptr_t base, T& buffer) {
    return ReadMemory(base, &buffer, sizeof(T));
}

template < class T >
BOOL Memory::Write(uintptr_t base, T buffer) {
    return WriteMemory(base, &buffer, sizeof(T));
}

template < class T >
T Memory::Read(uintptr_t base) {
    T buffer;
    ReadMemory(base, &buffer, sizeof(T));
    return buffer;
}

#endif // !MEMORY_H