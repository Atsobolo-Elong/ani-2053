# C3 — Démo 1 

## 1. Nombre de fichiers et de lignes du module

Module étudié :

`Kernel/Runtime/NKWindow`

La mesure a été réalisée directement dans l'arborescence du module.

Résultat mesuré :

Commande utilisée :
```
```powershell
$NKWindow = "C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow"

$allFiles = Get-ChildItem -Path $NKWindow -Recurse -File

$sourceFiles = $allFiles | Where-Object {
    $_.Extension -in ".h", ".hpp", ".c", ".cpp"
}

"Nombre total de fichiers : $($allFiles.Count)"
"Nombre de fichiers C/C++ : $($sourceFiles.Count)"

$totalLines = 0

foreach ($file in $sourceFiles) {
    $totalLines += (Get-Content $file.FullName).Count
}

"Nombre total de lignes C/C++ : $totalLines"
Résultat :
Nombre total de fichiers : 122
Nombre de fichiers C/C++ : 108
Nombre total de lignes C/C++ : 24026

```


2. Les backends de plateforme
Dans :
```
Kernel/Runtime/NKWindow/src/NKWindow/Platform
```
j’ai trouvé les répertoires suivants :
```
Android
Cocoa
Common
Emscripten
HarmonyOS
Linux
Noop
UIKit
UWP
Wayland
Win32
Xbox
XCB
XLib
Common 
```
correspond au code partagé et n’est pas compté comme backend.
Les 13 backends/répertoires de plateforme comptés sont donc :
```
Android
Cocoa
Emscripten
HarmonyOS
Linux
Noop
UIKit
UWP
Wayland
Win32
Xbox
XCB
XLib
Total : 13.
```
Commande utilisée pour les identifier :
```
Get-ChildItem "$NKWindow\src\NKWindow\Platform" -Directory |
    Select-Object -ExpandProperty Name
```


3. Suivi d’un appel public dans deux backends
Appel choisi : 
```
NkWindow::SetTitle()
```
L’appel public étudié est :
```
void NkWindow::SetTitle(const NkString &title);
```
Il permet de modifier le titre de la fenêtre.
J’ai suivi cette même fonction dans deux backends différents :
```
Win32
XCB
Implémentation Win32
```
Fichier :
```
Platform/Win32/NkWin32Window.cpp
void NkWindow::SetTitle(const NkString &t) {
        mConfig.title = t;
        if (mData.mHwnd) {
                SetWindowTextW(mData.mHwnd, NkUtf8ToWide(t).CStr());
                // La synchronisation est déjà faite via la modification de mConfig
        }
}
Implémentation XCB
```
Fichier :
```
Platform/XCB/NkXCBWindow.cpp
void NkWindow::SetTitle(const NkString &title) {
        mConfig.title = title;
        if (!mData.mConnection || !mData.mWindow)
                return;

        xcb_change_property(mData.mConnection, XCB_PROP_MODE_REPLACE, mData.mWindow, XCB_ATOM_WM_NAME, XCB_ATOM_STRING,
                                                8, static_cast<uint32_t>(title.Size()), title.CStr());
        xcb_change_property(mData.mConnection, XCB_PROP_MODE_REPLACE, mData.mWindow, sAtomNetWmName, sAtomUtf8String, 8,
                                                static_cast<uint32_t>(title.Size()), title.CStr());
        xcb_flush(mData.mConnection);
}
```
Ce qui est identique
Dans les deux implémentations, mConfig.title est d’abord mis à jour avec le nouveau titre.
L’interface publique reste la même : le programme appelant utilise NkWindow::SetTitle() sans avoir à connaître le backend.
Ce qui change
Sous Win32, le titre est appliqué à la fenêtre native avec SetWindowTextW() et le texte NkString est converti avant d’être transmis à l’API Windows.
Sous XCB, le titre est appliqué en modifiant les propriétés X11 avec xcb_change_property(), puis les modifications sont envoyées avec xcb_flush().
 Les trois phrases demandées
L’interface publique de NkWindow masque les différences entre les systèmes de fenêtres.
Chaque backend traduit le même appel SetTitle() vers l’API native de sa plateforme : Win32 utilise l’API Windows tandis que XCB utilise les propriétés X11.
Le module NKWindow absorbe donc la différence d’implémentation entre les plateformes tout en conservant une interface publique commune.

## VOICI le resultat conforme de powershell :

```
PS C:\Users\missa> cd C:\Users\missa\Nkentseu\Nkentseu
PS C:\Users\missa\Nkentseu\Nkentseu> pwd

Path
----
C:\Users\missa\Nkentseu\Nkentseu


PS C:\Users\missa\Nkentseu\Nkentseu> git status
Refresh index: 100% (7019/7019), done.
On branch main
Your branch is behind 'origin/main' by 1314 commits, and can be fast-forwarded.
  (use "git pull" to update your local branch)

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   .vscode/settings.json
        modified:   CONSOLIDATION_TODO.md
        modified:   Nkentseu.jenga
        modified:   pyrightconfig.json

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   .vscode/settings.json
        modified:   Applications/NKViewportDemo/src/NKViewportDemo/main.cpp
        modified:   Applications/NkVideoPlayer/NkVideoPlayer.jenga
        modified:   Externals/Libs/NKGLSlang (new commits)
        modified:   Externals/Libs/NKGlad (new commits)
        modified:   Kernel/Foundation/NKMath/src/NKMath/NkRandom.h
        modified:   Nkentseu.jenga
        modified:   Tutoriels3D/Tutoriels3D.jenga
        modified:   pyrightconfig.json

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        Applications/ChatChat-Kongossa/
        Applications/Frog/
        Applications/Nyeck/
        Applications/Pworkspace/
        Applications/viewport_capture.mp4
        NkUIHudDemo_hud.png
        conv_seq.mp4
        conv_src.avi
        conv_trans.mp4
        cvframe_001.png
        cvframe_002.png
        cvframe_003.png
        cvframe_004.png
        cvframe_005.png
        cvframe_006.png
        cvframe_007.png
        cvframe_008.png
        cvframe_009.png
        cvframe_010.png
        engine_capture.mp4
        h264_recon.yuv
        h264_test.h264
        h264_test.mp4
        nkframe_0001.png
        nkframe_0002.png
        nkframe_0003.png
        nkframe_0004.png
        nkframe_0005.png
        nknetwork_demo.cpp
        nkvideo_mjpeg.avi
        nkvideo_mjpeg.mov
        nkvideo_mpeg1.m1v
        nkvideo_mpeg1_screen.m1v
        nkvideo_raw.avi
        nkvideoreader_selftest.avi
        nkwebmwriter_selftest.webm
        settings.cfg

PS C:\Users\missa\Nkentseu\Nkentseu> Get-ChildItem -Path . -Directory -Recurse -Filter "NKWindow" | Select-Object -ExpandProperty FullName
C:\Users\missa\Nkentseu\Nkentseu\Build\Obj\Debug-Windows\NKWindow
C:\Users\missa\Nkentseu\Nkentseu\Build\Obj\Release-Windows\NKWindow
C:\Users\missa\Nkentseu\Nkentseu\docs\NKWindow
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow
C:\Users\missa\Nkentseu\Nkentseu\wiki\Runtime\NKWindow
PS C:\Users\missa\Nkentseu\Nkentseu> $NKWindow = "C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow"
PS C:\Users\missa\Nkentseu\Nkentseu> (Get-ChildItem -Path $NKWindow -File -Recurse | Measure-Object).Count
122
PS C:\Users\missa\Nkentseu\Nkentseu> $SourceFiles = Get-ChildItem -Path $NKWindow -File -Recurse |
>>     Where-Object { $_.Extension -in ".h", ".hpp", ".c", ".cpp" }
PS C:\Users\missa\Nkentseu\Nkentseu> $SourceFiles.Count
108
PS C:\Users\missa\Nkentseu\Nkentseu> $totalLines = 0
PS C:\Users\missa\Nkentseu\Nkentseu> $totalLines = 0
PS C:\Users\missa\Nkentseu\Nkentseu>
PS C:\Users\missa\Nkentseu\Nkentseu> foreach ($file in $SourceFiles) {
>>     $totalLines += (Get-Content -LiteralPath $file.FullName | Measure-Object -Line).Lines
>> }
PS C:\Users\missa\Nkentseu\Nkentseu>
PS C:\Users\missa\Nkentseu\Nkentseu> $totalLines
24026
PS C:\Users\missa\Nkentseu\Nkentseu> Get-ChildItem -Path $NKWindow -Directory -Recurse |
>>     Select-Object -ExpandProperty FullName
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\pch
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\tests
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\EntryPoints
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Cocoa
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Common
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Emscripten
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\HarmonyOS
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Linux
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Noop
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\UIKit
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\UWP
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Wayland
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Win32
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Xbox
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\XCB
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\XLib
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android\java
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android\java\com
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android\java\com\nkentseu
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android\java\com\nkentseu\window
PS C:\Users\missa\Nkentseu\Nkentseu> Get-ChildItem -Path $NKWindow -File -Recurse |
>>     Where-Object { $_.Extension -in ".h", ".hpp", ".c", ".cpp" } |
>>     Select-Object -ExpandProperty FullName
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\pch\pch.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\pch\pch.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\NKMain.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\NKWindow.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core\NkContext.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core\NkContext.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core\NkDialogs.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core\NkDialogs.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core\NkEntry.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core\NkEvent.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core\NkEventSystem.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core\NkLauncher.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core\NkLauncher.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core\NkMain.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core\NkSurface.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core\NkSurfaceHint.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core\NkTypes.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core\NkWESystem.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core\NkWESystem.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core\NkWindow.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core\NkWindowClipboard.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core\NkWindowConfig.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core\NkWindowCursor.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\EntryPoints\NkAndroid.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\EntryPoints\NkAppleMobile.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\EntryPoints\NkCocoa.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\EntryPoints\NkEmscripten.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\EntryPoints\NkHarmonyOS.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\EntryPoints\NkNoob.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\EntryPoints\NkUikit.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\EntryPoints\NkUWP.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\EntryPoints\NkWatchOS.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\EntryPoints\NkWayland.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\EntryPoints\NkWindowsDesktop.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\EntryPoints\NkXbox.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\EntryPoints\NkXCB.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\EntryPoints\NkXLib.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android\NkAndroidDropTarget.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android\NkAndroidEventSystem.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android\NkAndroidEventSystem.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android\NkAndroidGamepad.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android\NkAndroidTextInputJNI.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android\NkAndroidWindow.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android\NkAndroidWindow.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Cocoa\NkCocoaEventSystem.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Cocoa\NkCocoaGamepad.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Cocoa\NkCocoaWindow.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Common\NkSystemMemory.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Emscripten\NkEmscriptenDropTarget.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Emscripten\NkEmscriptenEventSystem.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Emscripten\NkEmscriptenEventSystem.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Emscripten\NkEmscriptenGamepad.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Emscripten\NkEmscriptenWindow.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Emscripten\NkEmscriptenWindow.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\HarmonyOS\NkHarmonyEventSystem.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\HarmonyOS\NkHarmonyEventSystem.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\HarmonyOS\NkHarmonyGamepad.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\HarmonyOS\NkHarmonyGamepad.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\HarmonyOS\NkHarmonyWindow.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\HarmonyOS\NkHarmonyWindow.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Linux\NkLinuxGamepadBackend.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Noop\NkNoopEventSystem.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Noop\NkNoopEventSystem.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Noop\NkNoopGamepad.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Noop\NkNoopWindow.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Noop\NkNoopWindow.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\UIKit\NkUIKitEventSystem.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\UIKit\NkUIKitGamepad.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\UIKit\NkUIKitWindow.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\UWP\NkUWPEventSystem.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\UWP\NkUWPEventSystem.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\UWP\NkUWPGamepad.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\UWP\NkUWPWindow.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\UWP\NkUWPWindow.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Wayland\NkWaylandDropTarget.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Wayland\NkWaylandEventSystem.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Wayland\NkWaylandEventSystem.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Wayland\NkWaylandWindow.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Wayland\NkWaylandWindow.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Wayland\NkXdgDecorationProtocol.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Wayland\NkXdgShellProtocol.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Wayland\xdg-decoration-client-protocol.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Wayland\xdg-decoration-protocol.c
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Wayland\xdg-shell-client-protocol.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Wayland\xdg-shell-protocol.c
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Win32\NkWin32DropTarget.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Win32\NkWin32EventSystem.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Win32\NkWin32EventSystem.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Win32\NkWin32Gamepad.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Win32\NkWin32Window.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Win32\NkWin32Window.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Xbox\NkXboxEventSystem.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Xbox\NkXboxEventSystem.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Xbox\NkXboxGamepad.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Xbox\NkXboxWindow.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Xbox\NkXboxWindow.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\XCB\NkXCBDropTarget.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\XCB\NkXCBEventSystem.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\XCB\NkXCBEventSystem.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\XCB\NkXCBWindow.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\XCB\NkXCBWindow.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\XLib\NkXLibDropTarget.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\XLib\NkXLibEventSystem.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\XLib\NkXLibEventSystem.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\XLib\NkXLibWindow.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\XLib\NkXLibWindow.h
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\tests\benchmark_smoke.cpp
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\tests\test_smoke.cpp
PS C:\Users\missa\Nkentseu\Nkentseu>
PS C:\Users\missa\Nkentseu\Nkentseu>
PS C:\Users\missa\Nkentseu\Nkentseu> $NKWindow = "C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow"
PS C:\Users\missa\Nkentseu\Nkentseu>
PS C:\Users\missa\Nkentseu\Nkentseu> (Get-ChildItem -Path $NKWindow -File -Recurse | Measure-Object).Count
122
PS C:\Users\missa\Nkentseu\Nkentseu>
PS C:\Users\missa\Nkentseu\Nkentseu> $SourceFiles = Get-ChildItem -Path $NKWindow -File -Recurse |
>>     Where-Object { $_.Extension -in ".h", ".hpp", ".c", ".cpp" }
PS C:\Users\missa\Nkentseu\Nkentseu>
PS C:\Users\missa\Nkentseu\Nkentseu> $totalLines = 0
PS C:\Users\missa\Nkentseu\Nkentseu> foreach ($file in $SourceFiles) {
>>     $totalLines += (Get-Content -LiteralPath $file.FullName | Measure-Object -Line).Lines
>> }
PS C:\Users\missa\Nkentseu\Nkentseu> $totalLines
24026
PS C:\Users\missa\Nkentseu\Nkentseu>
PS C:\Users\missa\Nkentseu\Nkentseu> Get-ChildItem -Path $NKWindow -Directory -Recurse |
>>     Select-Object -ExpandProperty FullName
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\pch
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\tests
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\EntryPoints
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Cocoa
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Common
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Emscripten
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\HarmonyOS
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Linux
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Noop
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\UIKit
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\UWP
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Wayland
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Win32
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Xbox
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\XCB
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\XLib
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android\java
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android\java\com
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android\java\com\nkentseu
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android\java\com\nkentseu\window
PS C:\Users\missa\Nkentseu\Nkentseu> $NKWindow = "C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow"
PS C:\Users\missa\Nkentseu\Nkentseu>
PS C:\Users\missa\Nkentseu\Nkentseu> Get-ChildItem -Path "$NKWindow\src\NKWindow\Platform" -Recurse -Filter "*.cpp" |
>>     Select-String -Pattern "SetTitle" |
>>     Select-Object Path, LineNumber, Line

Path                                                                                                             LineNumber Line
----                                                                                                             ---------- ----
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android\NkAndroidWindow.cpp              819     void...
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Emscripten\NkEmscriptenWindow.cpp        657     void...
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\HarmonyOS\NkHarmonyWindow.cpp            663     void...
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Noop\NkNoopWindow.cpp                    130     void...
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\UWP\NkUWPWindow.cpp                      143     void...
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Wayland\NkWaylandWindow.cpp               13 //   ...
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Wayland\NkWaylandWindow.cpp             1285     // S...
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Wayland\NkWaylandWindow.cpp             1288     void...
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Win32\NkWin32Window.cpp                  693     void...
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Xbox\NkXboxWindow.cpp                    270     void...
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\XCB\NkXCBWindow.cpp                      817     void...
C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\XLib\NkXLibWindow.cpp                    743     void...


PS C:\Users\missa\Nkentseu\Nkentseu> $NKWindow = "C:\Users\missa\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow"
PS C:\Users\missa\Nkentseu\Nkentseu>
PS C:\Users\missa\Nkentseu\Nkentseu> Get-Content "$NKWindow\src\NKWindow\Platform\Win32\NkWin32Window.cpp" |
>>     Select-Object -Skip 685 -First 30

                // Synchroniser mConfig
                const_cast<NkWindow *>(this)->mConfig.title = title;

                return title;
        }

        void NkWindow::SetTitle(const NkString &t) {
                mConfig.title = t;
                if (mData.mHwnd) {
                        SetWindowTextW(mData.mHwnd, NkUtf8ToWide(t).CStr());
                        // La synchronisation est déjà faite via la modification de mConfig
                }
        }

        // =============================================================================
        // Size / Position
        // =============================================================================

        NkVec2u NkWindow::GetSize() const {
                RECT rc = {};
                if (mData.mHwnd)
                        GetClientRect(mData.mHwnd, &rc);
                NkVec2u size = {(uint32)(rc.right - rc.left), (uint32)(rc.bottom - rc.top)};

                // Synchroniser mConfig
                const_cast<NkWindow *>(this)->mConfig.width = size.x;
                const_cast<NkWindow *>(this)->mConfig.height = size.y;

                return size;
PS C:\Users\missa\Nkentseu\Nkentseu>
PS C:\Users\missa\Nkentseu\Nkentseu> Write-Host "`n================ XCB ================`n"

================ XCB ================

PS C:\Users\missa\Nkentseu\Nkentseu>
PS C:\Users\missa\Nkentseu\Nkentseu> Get-Content "$NKWindow\src\NKWindow\Platform\XCB\NkXCBWindow.cpp" |
>>     Select-Object -Skip 809 -First 30
                return {0, 0};
        }

        // =============================================================================
        // Setters
        // =============================================================================

        void NkWindow::SetTitle(const NkString &title) {
                mConfig.title = title;
                if (!mData.mConnection || !mData.mWindow)
                        return;

                xcb_change_property(mData.mConnection, XCB_PROP_MODE_REPLACE, mData.mWindow, XCB_ATOM_WM_NAME, XCB_ATOM_STRING,
                                                        8, static_cast<uint32_t>(title.Size()), title.CStr());
                xcb_change_property(mData.mConnection, XCB_PROP_MODE_REPLACE, mData.mWindow, sAtomNetWmName, sAtomUtf8String, 8,
                                                        static_cast<uint32_t>(title.Size()), title.CStr());
                xcb_flush(mData.mConnection);
        }

        void NkWindow::SetSize(uint32 w, uint32 h) {
                mConfig.width = w;
                mConfig.height = h;
                if (!mData.mConnection || !mData.mWindow)
                        return;

                uint32_t values[] = {w, h};
                xcb_configure_window(mData.mConnection, mData.mWindow, XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT,
                                                         values);
                xcb_flush(mData.mConnection);
        }
PS C:\Users\missa\Nkentseu\Nkentseu> Get-Content "$NKWindow\src\NKWindow\Platform\XCB\NkXCBWindow.cpp" |
>>     Select-Object -Skip 815 -First 12

        void NkWindow::SetTitle(const NkString &title) {
                mConfig.title = title;
                if (!mData.mConnection || !mData.mWindow)
                        return;

                xcb_change_property(mData.mConnection, XCB_PROP_MODE_REPLACE, mData.mWindow, XCB_ATOM_WM_NAME, XCB_ATOM_STRING,
                                                        8, static_cast<uint32_t>(title.Size()), title.CStr());
                xcb_change_property(mData.mConnection, XCB_PROP_MODE_REPLACE, mData.mWindow, sAtomNetWmName, sAtomUtf8String, 8,
                                                        static_cast<uint32_t>(title.Size()), title.CStr());
                xcb_flush(mData.mConnection);
        }
PS C:\Users\missa\Nkentseu\Nkentseu>
```