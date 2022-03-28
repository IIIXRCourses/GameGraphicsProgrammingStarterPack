/*+===================================================================
  File:      GAME.H

  Summary:   Game header file that contains declarations of functinos
			 used for the lab samples of Game Graphics Programming 
             course.

  Classes: Game

  © 2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Renderer/Renderer.h"
#include "Window/MainWindow.h"

namespace library
{
    /*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
      Class:    Game

      Summary:  Main game engine class

      Methods:  Initialize
                  Initializes the components of the game
                Run
                  Runs the game loop
                GetGameName
                  Returns the name of the game
                Game
                  Constructor.
                ~Game
                  Destructor.
    C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
    class Game final
    {
    public:
        Game(PCWSTR pszGameName);
        Game(const Game& other) = delete;
        Game(Game&& other) = delete;
        Game& operator=(const Game& other) = delete;
        Game& operator=(Game&& other) = delete;
        ~Game() = default;

        HRESULT Initialize(_In_ HINSTANCE hInstance, _In_ INT nCmdShow);

        INT Run();

        PCWSTR GetGameName() const;
    private:
        PCWSTR m_pszGameName;
        std::unique_ptr<MainWindow> m_mainWindow;
        std::unique_ptr<Renderer> m_renderer;
    };
}