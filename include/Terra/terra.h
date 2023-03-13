// Define once
#ifndef H_TERRA
#define H_TERRA

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

// Functions
std::string openFile(const char* filepath);
void writeFile(const char* filepath, std::string data);

// Endif
#endif