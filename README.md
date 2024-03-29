# exitCmd

Exits the current Windows batch file by simulating the user typing "exit" and hitting the Enter key. It does not kill the process or do anything "nasty", as I wanted a simple and safe way of doing this. I'm tired of having to do it manually everytime I run a batch file in a dedicated Command window.

It does a simplistic check to see that its immediate parent is "cmd.exe" and, if not, it displays its PID ad the parent's PID and pathname, so that you can see why it's backing out (safety. again).

Usage:

Run it at the end of your batch file:

```
@echo off
... do stuff
exitCmd
```
 and the command window will disappear as soon as the batch file ends.
 
## Troubleshooting

 1. If you put other commands after this one, then those commands may "eat" the keystrokes and the results may be undesirable / unexpected.
 2. If you find it doesn't work very well, add a sleep of a few seconds before the exitCmd:
 ```
    sleep 3
    exitCmd
 ```
3. Try to put the exitCmd.exe on the PATH or in the current dirctory, or give it a full pathname in the batch file. If you use a batch file to invoke the exitCmd.exe, it sometimes fails.
