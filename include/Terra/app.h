// Define once
#ifndef H_APP
#define H_APP

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
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
/// Terra
#include <Terra/terra.h>

// Constants
#define MACOS_PATH "/Library/Application Support/Terraria/"
#define LINUX_PATH "~/.local/Terraria/"

// Classes
class Application{
public:
    // Variables
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;

    int mx, my;
    bool clicked;

    // Constructor
    Application();

    // Functions
    void Update();

    void Clear();
    void Display();

    void Delete();
};

namespace GUI{
    class Text{
    private:
        // Variables
        SDL_Texture* tex;
    public:
        // Variables
        float x,y;
        float w,h;
        float fontSize;
        std::string value;

        // Constructor
        Text(SDL_Renderer* renderer, float x, float y, float fontSize, std::string value);

        // Functions
        void Change(SDL_Renderer* renderer);
        void Draw(SDL_Renderer* renderer);
    };

    class Button{
    private:
        // Variables
        Text text;
    
    public:
        // Variables
        bool clicked;
        float x,y;
        float w,h;

        // Constructor
        Button(SDL_Renderer* renderer, float x, float y, std::string value);

        // Functions
        void Update(Application* app);
        void Draw(SDL_Renderer* renderer);
    };

    class Texture{
    private:
        // Variables
        SDL_Texture* tex;
    public:
        // Variables
        float x,y;
        float w,h;

        // Constructors
        Texture(SDL_Renderer* renderer, const char* filepath, float x, float y, float w, float h);

        // Functions
        void Draw(SDL_Renderer* renderer);
    };
}

// End definition
#endif