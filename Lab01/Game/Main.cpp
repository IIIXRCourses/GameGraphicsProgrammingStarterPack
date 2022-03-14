/*+===================================================================
  File:      MAIN.CPP

  Summary:   This application demonstrates creating a Direct3D 11 device

  Origin:    http://msdn.microsoft.com/en-us/library/windows/apps/ff729718.aspx

  Originally created by Microsoft Corporation under MIT License
  © 2022 Kyung Hee University
===================================================================+*/

#include "Common.h"

#include "Game/Game.h"

/*F+F+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: wWinMain

  Summary:  Entry point to the program. Initializes everything and 
            goes into a message processing loop. Idle time is used to 
            render the scene.

  Args:     HINSTANCE hInstance
              Handle to an instance.
            HINSTANCE hPrevInstance
              Has no meaning.
            LPWSTR lpCmdLine
              Contains the command-line arguments as a Unicode 
              string
            INT nCmdShow
              Flag that says whether the main application window 
              will be minimized, maximized, or shown normally

  Returns:  INT
              Status code.
-----------------------------------------------------------------F-F*/
INT WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ INT nCmdShow)
{
    /*--------------------------------------------------------------------
      TODO: Unreferenced parameters (remove the comment)
    --------------------------------------------------------------------*/

    /*--------------------------------------------------------------------
      TODO: Initialization (remove the comment)
    --------------------------------------------------------------------*/

    // Main message loop
    MSG msg = { 0 };

    /*--------------------------------------------------------------------
      TODO: Main message loop (remove the comment)
    --------------------------------------------------------------------*/

    /*--------------------------------------------------------------------
      TODO: Destroy (remove the comment)
    --------------------------------------------------------------------*/

    return static_cast<INT>(msg.wParam);
}
