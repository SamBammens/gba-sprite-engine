# voor notities

# klasse blokje
# spel = main
# score
# achtergrond (extra)
# sound (extra)
# startscherm (extra)
# Moeilijkheid instellen? (extra)

project(Tetris)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp src/TetrisMenu.cpp src/TetrisMenu.h
        src/SpelFase.cpp src/SpelFase.h src/bg.h src/StartScene.cpp src/StartScene.h
        src/Sound.h src/random.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
