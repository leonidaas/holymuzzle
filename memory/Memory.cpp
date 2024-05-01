#include "Memory.h"
#include <TlHelp32.h>

ModuleImage::ModuleImage(const std::string& name, uintptr_t base, uintptr_t size) :
	n_Name(name), m_Base(base), m_Size(size) {
}

ModuleImage::~ModuleImage(void) {
	if (!m_cBytes.empty()) {
		m_cBytes.clear();
	}
}

void ModuleImage::setup(const std::string& name, uintptr_t base, uintptr_t size) {
	n_Name = name;
	m_Base = base;
	m_Size = size;
}

Memory::Memory(const std::string& processName) {
	attach(processName);
}

Memory::~Memory(void) {
	Release();
}

bool Memory::attach(const std::string& processName) {
	if (m_attached) {
		return true;
	}

	if (processName.empty()) {
		if (m_processName.empty()) {
			return false;
		}
	}
	else {
		m_processName = processName;
	}

	auto hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		return false;
	}

	PROCESSENTRY32 ProcEntry = { sizeof(PROCESSENTRY32) };

#ifdef _UNICODE
	std::wstring processNameW(m_processName.begin(), m_processName.end());
#endif

	if (Process32First(hSnapshot, &ProcEntry)) {
		bool succeeded;

		do {
#ifdef _UNICODE
			succeeded = processNameW.compare(ProcEntry.szExeFile) == 0;
#else
			succeeded = m_processName == ProcEntry.szExeFile;
#endif
			if (succeeded) {
				m_processId = ProcEntry.th32ProcessID;
				break;
			}
		} while (Process32Next(hSnapshot, &ProcEntry));
	}

	CloseHandle(hSnapshot);

	if (!m_processId) {
		return false;
	}

	m_processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_processId);
	m_attached = m_processHandle != INVALID_HANDLE_VALUE;

	return m_attached;

}

bool Memory::IsAttached(void) const {
	return m_attached;
}

bool Memory::BuildImageOfModule(const std::string& moduleName) {
	if (moduleName.empty() || !m_attached) {
		return false;
	}

	if (!!m_moduleImages.count(moduleName)) {
		return true;
	}

	auto hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, m_processId);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		return false;
	}
	auto succeeded = false;
	MODULEENTRY32 ModEntry = { sizeof(MODULEENTRY32) };

	if (Module32First(hSnapshot, &ModEntry)) {
#ifdef _UNICODE
		std::wstring nameW(moduleName.begin(), moduleName.end());
#endif
		do {
#ifdef _UNICODE
			succeeded = nameW.compare(ModEntry.szModule) == 0;
#else 
			succeeded = moduleName == ModEntry.szModule;
#endif
			if (succeeded) {
				
				auto pModuleImage = std::make_shared< ModuleImage >(moduleName,
					reinterpret_cast<uintptr_t>(ModEntry.modBaseAddr),  
					static_cast<uintptr_t>(ModEntry.modBaseSize));     

				// Read the whole module into a buffer which is declared as a vector of bytes
				pModuleImage->m_cBytes = std::vector< byte >(pModuleImage->m_Size);
				ReadMemory(pModuleImage->m_Base, &pModuleImage->m_cBytes.at(0), pModuleImage->m_Size);

				// Insert the module in our module buffer
				m_moduleImages.insert(make_pair(moduleName, std::move(pModuleImage)));
				break;
			}
		} while (Module32Next(hSnapshot, &ModEntry));
	}
	CloseHandle(hSnapshot);
	return succeeded;
}

BOOL Memory::ReadMemory(const uintptr_t address, void* buffer, const size_t size) const
{
	if (!m_attached) {
		return false;
	}
	SIZE_T bytesRead;
	const auto result = ReadProcessMemory(m_processHandle, reinterpret_cast<const void*>(address), buffer, size, &bytesRead);
	return result && bytesRead == size;
}

BOOL Memory::WriteMemory(const uintptr_t address, const void* buffer, const size_t size) const
{
	if (!m_attached) {
		return false;
	}
	SIZE_T bytesWritten;
	auto result = WriteProcessMemory(m_processHandle, reinterpret_cast<void*>(address), buffer, size, &bytesWritten);
	return result && bytesWritten == size;
}

uint32_t Memory::GetProcessId(void) const {
	return m_processId;
}

HANDLE Memory::GetProcessHandle(void) const {
	return m_processHandle;
}

std::shared_ptr< ModuleImage > Memory::GetModuleImage(const std::string& name) const {
	if (!!m_moduleImages.count(name)) {
		return m_moduleImages.at(name);
	}
	return nullptr;
}

void Memory::Release(void) {
	m_attached = false;
	m_processId = 0;

	if (m_processHandle) {
		CloseHandle(m_processHandle);
		m_processHandle = nullptr;
	}
	m_processName.clear();

	if (!m_moduleImages.empty()) {
		m_moduleImages.clear();
	}
}
