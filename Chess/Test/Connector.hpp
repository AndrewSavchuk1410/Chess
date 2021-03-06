#pragma once

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>

STARTUPINFO sti = { 0 };
SECURITY_ATTRIBUTES sats = { 0 };
PROCESS_INFORMATION pi = { 0 };
HANDLE pipin_w, pipin_r, pipout_w, pipout_r;
BYTE buffer[10240];
DWORD writ, excode, read, available;


void ConnectToEngine(char* path)
{
    pipin_w = pipin_r = pipout_w = pipout_r = NULL;
    sats.nLength = sizeof(sats);
    sats.bInheritHandle = TRUE;
    sats.lpSecurityDescriptor = NULL;

    CreatePipe(&pipout_r, &pipout_w, &sats, 0);
    CreatePipe(&pipin_r, &pipin_w, &sats, 0);

    sti.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    sti.wShowWindow = SW_HIDE;
    sti.hStdInput = pipin_r;
    sti.hStdOutput = pipout_w;
    sti.hStdError = pipout_w;

    CreateProcess(NULL, path, NULL, NULL, TRUE, 0, NULL, NULL, &sti, &pi);
}


std::string getNextMove(std::string position)
{
    std::string str, ans;
    position = "position startpos moves " + position + "\ngo\n";

    WriteFile(pipin_w, position.c_str(), position.length(), &writ, NULL);
    Sleep(500);

    PeekNamedPipe(pipout_r, buffer, sizeof(buffer), &read, &available, NULL);
    do
    {
        ZeroMemory(buffer, sizeof(buffer));
        if (!ReadFile(pipout_r, buffer, sizeof(buffer), &read, NULL) || !read) break;
        buffer[read] = 0;
        str += (char*)buffer;
    } while (read >= sizeof(buffer));

    int n = str.find("bestmove");
    std::cout << str << "\n";

    n = str.find(" pv ");
    if (n != -1) {
        ans = str.substr(n + 4, 5);
        std::cout << std::endl << "ANS "<< ans << std::endl;
        return ans;
    }
    
    return "error";
    
}

void CloseConnection()
{
    WriteFile(pipin_w, "quit\n", 5, &writ, NULL);
    if (pipin_w != NULL) CloseHandle(pipin_w);
    if (pipin_r != NULL) CloseHandle(pipin_r);
    if (pipout_w != NULL) CloseHandle(pipout_w);
    if (pipout_r != NULL) CloseHandle(pipout_r);
    if (pi.hProcess != NULL) CloseHandle(pi.hProcess);
    if (pi.hThread != NULL) CloseHandle(pi.hThread);
}