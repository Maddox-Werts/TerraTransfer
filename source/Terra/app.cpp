// Header
#include <Terra/app.h>

// Constructor
Application::Application(){
    // Start SDL2
    SDL_Init(SDL_INIT_VIDEO);

    // Create a window
    window = SDL_CreateWindow(
        "TerraTransfer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    ); if(window == NULL){
        std::cout << "Failed to create a window.\n";
        return;
    }

    // Creating a renderer
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
        std::cout << "Failed to create a renderer.\n";
        return;
    }

    // Start subsystems
    TTF_Init();
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    // We're running
    running = true;
}

// Functions
void Application::Update(){
    SDL_Event event;
    clicked = false;

    while(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
            running = false;
            break;
        case SDL_MOUSEMOTION:
            mx = event.motion.x;
            my = event.motion.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT){
                clicked = true;
            }

        }
    }
}

void Application::Clear(){
    SDL_SetRenderDrawColor(renderer, 0,0,0, 255);
    SDL_RenderClear(renderer);
}
void Application::Display(){
    SDL_RenderPresent(renderer);
}

void Application::Delete(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

namespace GUI{
    // Constructor
    Text::Text(SDL_Renderer* renderer, float x, float y, float fontSize, std::string value){
        // Init Values
        this->x = x;
        this->y = y;
        this->value = value;
        this->fontSize = fontSize;

        // Create Texture
        TTF_Font* font = TTF_OpenFont("data/font.ttf", fontSize);
        SDL_Color color = {255,255,255};
        
        SDL_Surface* surface = TTF_RenderText_Solid(font, value.c_str(), color);
        tex = SDL_CreateTextureFromSurface(renderer, surface);
    
        this->w = surface->w;
        this->h = surface->h;
    }

    // Functions
    void Text::Change(SDL_Renderer* renderer){
        TTF_Font* font = TTF_OpenFont("data/font.ttf", fontSize);
        SDL_Color color = {255,255,255};
        
        SDL_Surface* surface = TTF_RenderText_Solid(font, value.c_str(), color);
        tex = SDL_CreateTextureFromSurface(renderer, surface);
    
        this->w = surface->w;
        this->h = surface->h;
    }
    void Text::Draw(SDL_Renderer* renderer){
        SDL_Rect rect;

        rect.x = x; rect.y = y;
        rect.w = w; rect.h = h;

        SDL_SetRenderDrawColor(renderer, 255,255,255, 1);
        SDL_RenderCopy(renderer, tex, NULL, &rect);
    }

    // Constructor
    Button::Button(SDL_Renderer* renderer, float x, float y, std::string value): text(renderer, x+1,y+1, 14, value){
        this->x = x;
        this->y = y;

        this->w = text.w + 2;
        this->h = text.h + 2;
    }

    // Functions
    void Button::Update(Application* app){
        // Checking if clicked:
        float lMX, lMY;
        lMX = app->mx - this->x;
        lMY = app->my - this->y;

        if(app->clicked
        && lMX > 0
        && lMY > 0
        && lMX < this->w
        && lMY < this->h){
            this->clicked = true;
        }
    }
    void Button::Draw(SDL_Renderer* renderer){
        SDL_Rect rect;

        rect.x = x; rect.y = y;
        rect.w = this->w;
        rect.h = this->h;

        SDL_SetRenderDrawColor(renderer, 80,80,80, 255);
        SDL_RenderFillRect(renderer, &rect);

        text.Draw(renderer);
    }

    // Constructors
    Texture::Texture(SDL_Renderer* renderer, const char* filepath, float x, float y, float w, float h){
        // Init Values
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;

        // Texture
        SDL_Surface* surf = IMG_Load(filepath);
        tex = SDL_CreateTextureFromSurface(renderer, surf);
    }

    // Functions
    void Texture::Draw(SDL_Renderer* renderer){
        SDL_Rect rect;

        rect.x = x; rect.y = y;
        rect.w = w; rect.h = h;

        SDL_SetRenderDrawColor(renderer, 255,255,255, 1);
        SDL_RenderCopy(renderer, tex, NULL, &rect);
    }
}