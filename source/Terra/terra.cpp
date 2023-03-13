// Header
#include <Terra/terra.h>

// Functions
std::string openFile(const char* filepath){
    std::ifstream in(filepath, std::ios::binary);
    if(in){
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return contents;
    }
    else{
        std::cout << "ERROR(READ): COULDN'T LOAD FILE!\n";
        exit(EXIT_FAILURE);
        return "ERROR";
    }
}
void writeFile(const char* filepath, std::string data){
    std::ofstream out(filepath, std::ios::binary);
    if(out){
        out.write(&data[0], data.size());
        out.close();
    }
    else{
        std::cout << "ERROR(WRITE): COULDN'T START WRITING TO FILE!\n" << "FILE: " << filepath << "\n";
        exit(EXIT_FAILURE);
        return;
    }
}