#include <Life.hpp>

int main(int argc, char* argv[]){
    Life universityLife;
    universityLife.service_player_commands();
    return 0;
}

// That's all the main program does. Basically, this program I created is made to be like a text based game where life entity is created,
// and then then it makes a terminal like environment where it keeps listening for player commands and services those commands. It
// should be able to guide you on how to use if you type "help" as the command, it will give you a list of available commands to use.