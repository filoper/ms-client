cmake_minimum_required(VERSION 3.14)

project(msclient)

# Set project options
include(cmake/StandardSettings.cmake)
include(cmake/Utils.cmake)
include(cmake/Doxygen.cmake)
include(cmake/CompilerWarnings.cmake)
include(cmake/StaticAnalyzers.cmake)

if (APPLE)
  if (CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
    set(CMAKE_CXX_FLAGS "-Wno-c++11-narrowing -mlinker-version=505")
    set(CMAKE_C_FLAGS "-Wno-c++11-narrowing -mlinker-version=505")
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "-Wno-c++11-narrowing -mlinker-version=450")
    set(CMAKE_C_FLAGS "-Wno-c++11-narrowing -mlinker-version=450")
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-isystem  /usr/local/Cellar/gcc/9.3.0_1/lib/gcc/9/gcc/x86_64-apple-darwin18/9.3.0/../../../../../../include/c++/9.3.0 -isystem  /usr/local/Cellar/gcc/9.3.0_1/lib/gcc/9/gcc/x86_64-apple-darwin18/9.3.0/../../../../../../include/c++/9.3.0/x86_64-apple-darwin18 -isystem  /usr/local/Cellar/gcc/9.3.0_1/lib/gcc/9/gcc/x86_64-apple-darwin18/9.3.0/../../../../../../include/c++/9.3.0/backward -isystem  /usr/local/Cellar/gcc/9.3.0_1/lib/gcc/9/gcc/x86_64-apple-darwin18/9.3.0/include -isystem  /usr/local/Cellar/gcc/9.3.0_1/lib/gcc/9/gcc/x86_64-apple-darwin18/9.3.0/include-fixed -isystem /Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/usr/include -isystem /Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/System/Library/Frameworks")
  else()
    message(AUTHOR_WARNING "No compiler flags set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
  endif()

elseif (UNIX AND NOT APPLE)
  if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "-Wno-c++11-narrowing")
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  else()
    message(AUTHOR_WARNING "No compiler flags set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
  endif()
endif()

include_directories(.)
include_directories(Audio)
include_directories(Character)
include_directories(Character/Inventory)
include_directories(Character/Look)
include_directories(Data)
include_directories(Gameplay)
include_directories(Gameplay/Combat)
include_directories(Gameplay/MapleMap)
include_directories(Gameplay/Physics)
include_directories(Graphics)
include_directories(IO)
include_directories(IO/Components)
include_directories(IO/UITypes)
include_directories(IO/UITypes/Login)
include_directories(Net)
include_directories(Net/Handlers)
include_directories(Net/Handlers/Helpers)
include_directories(Net/Packets)
include_directories(Template)
include_directories(Util)

add_executable(msclient
    Audio/Audio.cpp
    Character/Inventory/Equip.cpp
    Character/Inventory/EquipQuality.cpp
    Character/Inventory/Inventory.cpp
    Character/Inventory/InventoryType.cpp
    Character/Inventory/Item.cpp
    Character/Inventory/Pet.cpp
    Character/Inventory/Weapon.cpp
    Character/Look/Afterimage.cpp
    Character/Look/Body.cpp
    Character/Look/BodyDrawInfo.cpp
    Character/Look/CharEquips.cpp
    Character/Look/CharLook.cpp
    Character/Look/Clothing.cpp
    Character/Look/EquipSlot.cpp
    Character/Look/Face.cpp
    Character/Look/Hair.cpp
    Character/Look/PetLook.cpp
    Character/Look/Stance.cpp
    Character/ActiveBuffs.cpp
    Character/Buff.cpp
    Character/Char.cpp
    Character/CharEffect.cpp
    Character/CharStats.cpp
    Character/EquipStat.cpp
    Character/ExpTable.cpp
    Character/Job.cpp
    Character/MapleStat.cpp
    Character/MonsterBook.cpp
    Character/OtherChar.cpp
    Character/PassiveBuffs.cpp
    Character/Player.cpp
    Character/PlayerStates.cpp
    Character/QuestLog.cpp
    Character/SkillBook.cpp
    Character/TeleportRock.cpp
    Data/BulletData.cpp
    Data/EquipData.cpp
    Data/ItemData.cpp
    Data/JobData.cpp
    Data/SkillData.cpp
    Data/WeaponData.cpp
    Gameplay/Combat/Bullet.cpp
    Gameplay/Combat/Combat.cpp
    Gameplay/Combat/MobCombat.cpp
    Gameplay/Combat/MobSkill.cpp
    Gameplay/Combat/MobSkillHitEffect.cpp
    Gameplay/Combat/MobSkillUseEffect.cpp
    Gameplay/Combat/DamageNumber.cpp
    Gameplay/Combat/RegularAttack.cpp
    Gameplay/Combat/Skill.cpp
    Gameplay/Combat/SkillAction.cpp
    Gameplay/Combat/SkillBullet.cpp
    Gameplay/Combat/SkillHitEffect.cpp
    Gameplay/Combat/SkillSound.cpp
    Gameplay/Combat/SkillUseEffect.cpp
    Gameplay/Combat/MobCombat.cpp 
    Gameplay/Combat/MobSkill.cpp
    Gameplay/Combat/MobSkillHitEffect.cpp
    Gameplay/Combat/MobSkillUseEffect.cpp
    Gameplay/Combat/MobSpecialAttack.cpp
    Gameplay/Combat/SkillAffectedEffect.cpp
    Gameplay/MapleMap/Drop.cpp
    Gameplay/MapleMap/ItemDrop.cpp
    Gameplay/MapleMap/MapBackgrounds.cpp
    Gameplay/MapleMap/MapChars.cpp
    Gameplay/MapleMap/MapDrops.cpp
    Gameplay/MapleMap/MapEffect.cpp
    Gameplay/MapleMap/MapInfo.cpp
    Gameplay/MapleMap/MapMobs.cpp
    Gameplay/MapleMap/MapNpcs.cpp
    Gameplay/MapleMap/MapObject.cpp
    Gameplay/MapleMap/MapObjects.cpp
    Gameplay/MapleMap/MapPortals.cpp
    Gameplay/MapleMap/MapReactors.cpp
    Gameplay/MapleMap/MapTilesObjs.cpp
    Gameplay/MapleMap/MesoDrop.cpp
    Gameplay/MapleMap/Mob.cpp
    Gameplay/MapleMap/Npc.cpp
    Gameplay/MapleMap/Obj.cpp
    Gameplay/MapleMap/Portal.cpp
    Gameplay/MapleMap/Reactor.cpp
    Gameplay/MapleMap/Tile.cpp
    Gameplay/Physics/Foothold.cpp
    Gameplay/Physics/FootholdTree.cpp
    Gameplay/Physics/Physics.cpp
    Gameplay/Camera.cpp
    Gameplay/Spawn.cpp
    Gameplay/Stage.cpp
    Graphics/Animation.cpp
    Graphics/Color.cpp
    Graphics/EffectLayer.cpp
    Graphics/Geometry.cpp
    Graphics/GraphicsGL.cpp
    Graphics/Sprite.cpp
    Graphics/Text.cpp
    Graphics/Texture.cpp
    Graphics/RecurringEffect.cpp
    IO/Components/AreaButton.cpp
    IO/Components/Button.cpp
    IO/Components/Charset.cpp
    IO/Components/ChatBalloon.cpp
    IO/Components/EquipTooltip.cpp
    IO/Components/Gauge.cpp
    IO/Components/Icon.cpp
    IO/Components/IconCover.cpp
    IO/Components/ItemTooltip.cpp
    IO/Components/MapleButton.cpp
    IO/Components/MapleComboBox.cpp
    IO/Components/MapleFrame.cpp
    IO/Components/MapTooltip.cpp
    IO/Components/NameTag.cpp
    IO/Components/NpcText.cpp
    IO/Components/ScrollingNotice.cpp
    IO/Components/SkillTooltip.cpp
    IO/Components/Slider.cpp
    IO/Components/StatefulIcon.cpp
    IO/Components/Textfield.cpp
    IO/Components/TextTooltip.cpp
    IO/Components/TwoSpriteButton.cpp
    IO/UITypes/UIBuffList.cpp
    IO/UITypes/UICashShop.cpp
    IO/UITypes/UIChannel.cpp
    IO/UITypes/UICharInfo.cpp
    IO/UITypes/UIChat.cpp
    IO/UITypes/UIChatBar.cpp
    IO/UITypes/UIEquipInventory.cpp
    IO/UITypes/UIEvent.cpp
    IO/UITypes/UIItemInventory.cpp
    IO/UITypes/UIJoypad.cpp
    IO/UITypes/UIKeyConfig.cpp
    IO/UITypes/UIMiniMap.cpp
    IO/UITypes/UINotice.cpp
    IO/UITypes/UINpcTalk.cpp
    IO/UITypes/UIOptionMenu.cpp
    IO/UITypes/UIQuestLog.cpp
    IO/UITypes/UIQuit.cpp
    IO/UITypes/UIShop.cpp
    IO/UITypes/UISkillBook.cpp
    IO/UITypes/UIStatsInfo.cpp
    IO/UITypes/UIStatusBar.cpp
    IO/UITypes/UIStatusMessenger.cpp
    IO/UITypes/UIUserList.cpp
    IO/UITypes/UIWorldMap.cpp
    IO/UITypes/UIGaugeBoss.cpp
    IO/UITypes/UINotification.cpp
    IO/UITypes/Login/UILogo.cpp
    IO/UITypes/Login/UILogin.cpp
    IO/UITypes/Login/UILoginWait.cpp
    IO/UITypes/Login/UILoginNotice.cpp
    IO/UITypes/Login/UICharSelect.cpp
    IO/UITypes/Login/UIGender.cpp
    IO/UITypes/Login/UIRaceSelect.cpp
    IO/UITypes/Login/UITermsOfService.cpp
    IO/UITypes/Login/UIWorldSelect.cpp
    IO/UITypes/Login/UIAranCreation.cpp
    IO/UITypes/Login/UICygnusCreation.cpp
    IO/UITypes/Login/UIExplorerCreation.cpp
    IO/UITypes/Login/UIRegion.cpp
    IO/UITypes/Login/UISoftKey.cpp
    IO/Cursor.cpp
    IO/Keyboard.cpp
    IO/Messages.cpp
    IO/UI.cpp
    IO/UIElement.cpp
    IO/UIStateCashShop.cpp
    IO/UIStateGame.cpp
    IO/UIStateLogin.cpp
    IO/Window.cpp
    Net/Handlers/Helpers/CashShopParser.cpp
    Net/Handlers/Helpers/CharacterParser.cpp
    Net/Handlers/Helpers/ItemParser.cpp
    Net/Handlers/Helpers/LoginParser.cpp
    Net/Handlers/Helpers/MovementParser.cpp
    Net/Handlers/AttackHandlers.cpp
    Net/Handlers/CashShopHandlers.cpp
    Net/Handlers/CommonHandlers.cpp
    Net/Handlers/InventoryHandlers.cpp
    Net/Handlers/LoginHandlers.cpp
    Net/Handlers/MapObjectHandlers.cpp
    Net/Handlers/MessagingHandlers.cpp
    Net/Handlers/NpcInteractionHandlers.cpp
    Net/Handlers/PlayerHandlers.cpp
    Net/Handlers/PlayerInteractionHandlers.cpp
    Net/Handlers/SetFieldHandlers.cpp
    Net/Handlers/TestingHandlers.cpp
    Net/Cryptography.cpp
    Net/InPacket.cpp
    Net/OutPacket.cpp
    Net/PacketSwitch.cpp
    Net/Session.cpp
    Net/SocketAsio.cpp
    Net/SocketWinsock.cpp
    Util/Misc.cpp
    Util/NxFiles.cpp
    Configuration.cpp
    MSClient.cpp
    Game.cpp
)

IF (WIN32)
    target_sources(msclient PUBLIC MSClient.rc)
ENDIF()

set_property(TARGET msclient PROPERTY CXX_STANDARD 20)
set_property(TARGET msclient PROPERTY CXX_STANDARD_REQUIRED ON)

set_project_warnings(${PROJECT_NAME})

# Format the project using the `clang-format` target (i.e: cmake --build build --target clang-format)
add_clang_format_target()

TARGET_INCLUDE_DIRECTORIES(msclient 
  SYSTEM PRIVATE
    ${PROJECT_SOURCE_DIR}/thirdparty/NoLifeNx
    ${PROJECT_SOURCE_DIR}/thirdparty/asio/asio/include
    ${PROJECT_SOURCE_DIR}/thirdparty/stb
    ${PROJECT_SOURCE_DIR}/thirdparty/glad/build/include
)

IF (UNIX)
    INCLUDE(FindFreetype)
    TARGET_INCLUDE_DIRECTORIES(msclient 
      SYSTEM PRIVATE
        ${FREETYPE_INCLUDE_DIRS}
    )

    TARGET_LINK_LIBRARIES(msclient 
      ${FREETYPE_LIBRARIES}
      ${PROJECT_SOURCE_DIR}/thirdparty/glad/build/libglad.a
      ${PROJECT_SOURCE_DIR}/thirdparty/NoLifeNx/nlnx/build/libNoLifeNx.a
    )
ENDIF()

IF (APPLE)
    TARGET_INCLUDE_DIRECTORIES(msclient 
      SYSTEM PRIVATE
        ${PROJECT_SOURCE_DIR}/thirdparty/bass24-osx
        /usr/local/Cellar/glfw/3.3.2/include
    )

    TARGET_LINK_LIBRARIES(msclient 
      ${PROJECT_SOURCE_DIR}/thirdparty/bass24-osx/libbass.dylib
      /usr/local/Cellar/lz4/1.9.2/lib/liblz4.a
      /usr/local/Cellar/glfw/3.3.2/lib/libglfw.dylib
    )
ELSEIF (UNIX AND NOT APPLE)
    TARGET_INCLUDE_DIRECTORIES(msclient 
      SYSTEM PRIVATE
        ${PROJECT_SOURCE_DIR}/thirdparty/bass24-linux
    )

    TARGET_LINK_LIBRARIES(msclient 
      ${PROJECT_SOURCE_DIR}/thirdparty/bass24-linux/x64/libbass.so
      /usr/lib/x86_64-linux-gnu/libglfw.so
      /usr/lib/x86_64-linux-gnu/liblz4.a
      dl
      pthread
    )
ELSEIF (WIN32)
    TARGET_INCLUDE_DIRECTORIES(msclient 
      SYSTEM PRIVATE
        ${PROJECT_SOURCE_DIR}/thirdparty/bass24/c
        ${PROJECT_SOURCE_DIR}/thirdparty/glfw/include
        ${PROJECT_SOURCE_DIR}/thirdparty/freetype/freetype-windows-binaries-2.10.2/include
    )

    TARGET_LINK_LIBRARIES(msclient 
      ${PROJECT_SOURCE_DIR}/thirdparty/bass24/c/x64/bass.lib
      wsock32
      ws2_32
    )

    IF (MSVC)
        TARGET_LINK_LIBRARIES(msclient 
          ${PROJECT_SOURCE_DIR}/thirdparty/glad/build/glad.lib
          ${PROJECT_SOURCE_DIR}/thirdparty/glfw/build/src/glfw3.lib
          ${PROJECT_SOURCE_DIR}/thirdparty/NoLifeNx/nlnx/build/NoLifeNx.lib
          ${PROJECT_SOURCE_DIR}/thirdparty/freetype/freetype-windows-binaries-2.10.2/win64/freetype.lib
          ${PROJECT_SOURCE_DIR}/thirdparty/lz4/dll/liblz4.dll.a
        )
    ELSE()
        TARGET_LINK_LIBRARIES(msclient 
          ${PROJECT_SOURCE_DIR}/thirdparty/glad/build/libglad.a
          ${PROJECT_SOURCE_DIR}/thirdparty/glfw/build/src/libglfw3.a
          ${PROJECT_SOURCE_DIR}/thirdparty/NoLifeNx/nlnx/build/libNoLifeNx.a
          ${PROJECT_SOURCE_DIR}/thirdparty/freetype/freetype-windows-binaries-2.10.2/win64/freetype.lib
          ${PROJECT_SOURCE_DIR}/thirdparty/lz4/dll/liblz4.dll.a
        )
    ENDIF()
ELSE()
    message(FATAL_ERROR "Error: Unknown platform.")
ENDIF()

include(GNUInstallDirs)
install(
  TARGETS
    msclient
  LIBRARY DESTINATION
    ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION
    ${CMAKE_INSTALL_BINDIR}
  ARCHIVE DESTINATION
    ${CMAKE_INSTALL_LIBDIR}
)

install(
  DIRECTORY
    fonts
  DESTINATION
    ${CMAKE_INSTALL_BINDIR}
)

install(
  FILES
    Icon.png
  DESTINATION
    ${CMAKE_INSTALL_BINDIR}
)