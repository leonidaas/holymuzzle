#pragma once

/*
 * https://github.com/sezzyaep/CS2-OFFSETS
 */
 namespace offsets {
     //offsets
     constexpr std::ptrdiff_t dwEntityList = 0x18C9E78;
     constexpr std::ptrdiff_t dwLocalPlayerController = 0x1919588;
     constexpr std::ptrdiff_t dwLocalPlayerPawn = 0x173D5A8;
     constexpr std::ptrdiff_t dwViewAngles = 0x1937E50;
     constexpr std::ptrdiff_t dwViewMatrix = 0x192B2C0;
     //buttons
     constexpr std::ptrdiff_t dwForceAttack = 0x1736410;
     //client.dll 
     constexpr std::ptrdiff_t m_iHealth = 0x334;
     constexpr std::ptrdiff_t m_iTeamNum = 0x3CB;
     constexpr std::ptrdiff_t m_iIDEntIndex = 0x13B0;
     constexpr std::ptrdiff_t m_vOldOrigin = 0x127C;
     constexpr std::ptrdiff_t m_vecViewOffset = 0xC58;
     constexpr std::ptrdiff_t m_lifeState = 0x338;
     constexpr std::ptrdiff_t m_hPlayerPawn = 0x7E4;
     constexpr std::ptrdiff_t m_modelState = 0x160;
     constexpr std::ptrdiff_t m_pGameSceneNode = 0x318;
 };
