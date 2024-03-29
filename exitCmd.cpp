// exitCmd.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <string>
#include <tlhelp32.h>

using namespace std;

static DWORD getParentProcessId(DWORD processId) {
   HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
   if (hSnapshot == INVALID_HANDLE_VALUE) {
      return 0;
   }

   PROCESSENTRY32 pe32;
   pe32.dwSize = sizeof(pe32);

   if (!Process32First(hSnapshot, &pe32)) {
      CloseHandle(hSnapshot);
      return 0;
   }

   do {
      if (pe32.th32ProcessID == processId) {
         CloseHandle(hSnapshot);
         return pe32.th32ParentProcessID;
      }
   } while (Process32Next(hSnapshot, &pe32));

   CloseHandle(hSnapshot);
   return 0;
}

string getProcessExePath(DWORD processId) {
   HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
   if (hProcess == NULL) {
      return "";
   }

   char exePath[MAX_PATH];
   if (GetModuleFileNameExA(hProcess, NULL, exePath, sizeof(exePath) / sizeof(char)) == 0) {
      CloseHandle(hProcess);
      return "";
   }

   CloseHandle(hProcess);
   return exePath;
}

static void pressKey(WORD key, bool up) {
   INPUT input = { 0 };
   input.type = INPUT_KEYBOARD;
   input.ki.wVk = key;
   if (up) {
      input.ki.dwFlags = KEYEVENTF_KEYUP;
   }
   SendInput(1, &input, sizeof(INPUT));
}

int main()
{
   DWORD processId = GetCurrentProcessId();
   DWORD parentProcessId = getParentProcessId(processId);
   string parentProcessExePath = getProcessExePath(parentProcessId);

   cout << "Parent process ID: " << parentProcessId << endl;
   cout << "Parent process exe path: " << parentProcessExePath << endl;

   if (parentProcessExePath.find("cmd.exe") != string::npos) {
      pressKey('E', false);
      pressKey('E', true);
      pressKey('X', false);
      pressKey('X', true);
      pressKey('I', false);
      pressKey('I', true);
      pressKey('T', false);
      pressKey(VK_RETURN, false);
      pressKey(VK_RETURN, true);
   }

   return 0;
}
