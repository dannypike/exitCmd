# exitCmd

Exits the current Windows batch file by simulating the user typing "exit" and hitting the Enter key. It does not kill the process or do anything "nasty", as I wanted a simple and safe way of doing this. I'm tired of having to do it manually everytime I run a batch file in a dedicated Command window.

It does a simplistic check to see that its immediate parent is "cmd.exe" and, if not, it displays its PID ad the parent's PID and pathname, so that you can see why itt's backing out.
