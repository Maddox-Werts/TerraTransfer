/*
    This simplistic application will give the user the ability to SAFELY transfer
    data from the Video Game Terraria.
*/

// Includes
/// System
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
/// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
/// Terra
#include <Terra/terra.h>
#include <Terra/app.h>

// Window
Application window;

// Variables
GUI::Text* m_errmsg;
GUI::Button* r_erryes;
GUI::Button* r_errno;
bool errvis = false;

std::string _global_file_path;
std::string _global_world_name;
std::string _global_player_name;


// Functions
/// Saving
void finalizeTransfer(){
    // String -> Const Character List
    std::string _worldPath = (_global_file_path + "Worlds/" + _global_world_name + ".wld");
    std::string _playerPath = (_global_file_path + "Players/" + _global_player_name + ".plr");
    const char* worldPath = _worldPath.c_str();
    const char* playerPath = _playerPath.c_str();

    // Reading new data
    std::string newWorld = openFile("./custom/World.wld");
    std::string newPlayer = openFile("./custom/Player.plr");

    // Writing new data
    writeFile(worldPath, newWorld);
    writeFile(playerPath, newPlayer);
}
void initTransfer(){
    // String -> Const Character List
    std::string _worldPath = (_global_file_path + "Worlds/" + _global_world_name + ".wld");
    std::string _playerPath = (_global_file_path + "Players/" + _global_player_name + ".plr");
    const char* worldPath = _worldPath.c_str();
    const char* playerPath = _playerPath.c_str();
    int erroCNT = 0;

    // Does our data already exist?
    struct stat worldDat, playerDat;
    if(stat(worldPath, &worldDat) == 0){
        // File already exists
        // Get new file
        struct stat newWorld;
        stat("./custom/World.wld", &newWorld);

        // Which is newer?
        double oldWorldDifference = difftime(worldDat.st_mtime, newWorld.st_mtime);

        // Giving a statement
        if(oldWorldDifference > 0){
           erroCNT++;
        }
    }
    if(stat(playerPath, &playerDat) == 0){
        // File already exists
        // Get new file
        struct stat newPlayer;
        stat("./custom/Player.plr", &newPlayer);

        // Which is newer?
        double oldPlayerDifference = difftime(playerDat.st_mtime, newPlayer.st_mtime);

        // Giving a statement
        if(oldPlayerDifference > 0){
            erroCNT++;
        }
    }

    if(erroCNT == 0){
        finalizeTransfer();
    }
    else if(!errvis){
        m_errmsg = new GUI::Text(window.renderer, 30,100, 16, "Your world in your Terraria Data is newer than it's replacement.");
        r_erryes = new GUI::Button(window.renderer, 380, 180, "Yes");
        r_errno = new GUI::Button(window.renderer, 440, 180, "No");
        errvis = true;
        std::cout << "NEW\n";
    }
}

// Entry Point
int main(int argc, char* argv[]){
    // Failing to grab info
    if(argc < 2){
        std::ofstream out("log.txt");
        if(out){
            out << "This app requires 2 arguments in order to work.\n";
            out << "First, you must supply your Worlds Name.\n";
            out << "Secondly, you must supply your Player name.\n";
            out << "In your application's CUSTOM directory, You must have two files:\n";
            out << "1) World.wld\n";
            out << "2) Player.plr\n";
            out.close();
        }
        else{
            std::cout << "Failed to Write Error log";
        }

        return 0;
    }

    // Get username and SavePath
    std::string username = getlogin();
    int platform = 0;

    // Screen Objects
    GUI::Texture home_background(window.renderer, "data/homeback.png", 0,0, 800,600);
    GUI::Texture err_background(window.renderer, "data/errback.png", 0,0, 800,600);

    GUI::Text helloMSG_1(window.renderer, 30,20, 24, "Hello, Welcome to TerraTransfer.");
    GUI::Text helloMSG_2(window.renderer, 30,60, 24, "The simplistic app to safely");
    GUI::Text helloMSG_3(window.renderer, 30,100, 24, "transfer your game data from");
    GUI::Text helloMSG_4(window.renderer, 30,140, 24, "one device to another.");

    GUI::Text errorMSG_2(window.renderer, 30, 130, 16, "Proceed?");

    GUI::Text platMSG_1(window.renderer, 30,300, 16, "What platform are you currently using?");

    GUI::Button macBTN(window.renderer, 30,340, "MacOS");
    GUI::Button linuxBTN(window.renderer, 100,340, "Linux");

    GUI::Button submitBTN(window.renderer, 100, 500, "Transfer");
    bool submit_clicked = false;

    // App loop
    while(window.running){
        // Update
        window.Update();

        // Clear
        window.Clear();

        // Pages
        if(errvis){
            // Errors
            r_erryes->Update(&window);
            r_errno->Update(&window);
            if(r_erryes->clicked){
                finalizeTransfer();
                window.running = false;
            }
            else if(r_errno->clicked){
                errvis = false;
            }

            // Render code..
            err_background.Draw(window.renderer);
            m_errmsg->Draw(window.renderer);
            errorMSG_2.Draw(window.renderer);
            r_erryes->Draw(window.renderer);
            r_errno->Draw(window.renderer);
        }
        else{
            // App code..
            macBTN.Update(&window);
            linuxBTN.Update(&window);
            if(macBTN.clicked){
                platform = 0;
                submit_clicked = false;
            }
            else if(linuxBTN.clicked){
                platform = 1;
                submit_clicked = false;
            }
            
            submitBTN.Update(&window);
            if(submitBTN.clicked && !submit_clicked){
                submit_clicked = true;
                submitBTN.clicked = false;
                _global_world_name = argv[1];
                _global_player_name = argv[2];

                switch(platform){
                case 0:         // MACOS
                    _global_file_path = "/Users/" + username + MACOS_PATH;
                    initTransfer();
                    break;
                case 1:         // LINUX
                    _global_file_path = LINUX_PATH;
                    initTransfer();
                    break;
                case 2:         // WINDOWS
                    break;
                }
            }
            else if(!submitBTN.clicked){
                submit_clicked = false;
            }

            // Render code..
            home_background.Draw(window.renderer);
            
            helloMSG_1.Draw(window.renderer);
            helloMSG_2.Draw(window.renderer);
            helloMSG_3.Draw(window.renderer);
            helloMSG_4.Draw(window.renderer);

            platMSG_1.Draw(window.renderer);

            macBTN.Draw(window.renderer);
            linuxBTN.Draw(window.renderer);

            submitBTN.Draw(window.renderer);
        }

        // Display
        window.Display();
    }

    // Cleanup
    window.Delete();

    // Exit
    return 0;
}