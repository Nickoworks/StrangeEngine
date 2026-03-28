#include "ShaderManager.h"

std::string ShaderManager::currUseShader;
std::unordered_map<std::string, std::shared_ptr<ShaderProgram> > ShaderManager::shaders;

void ShaderManager::init(std::string shaderDirPath){
    std::unordered_map<std::string, std::string> fragSrc;
    std::unordered_map<std::string, std::string> vertSrc;

    for(const auto& entry_file : std::filesystem::directory_iterator(shaderDirPath)){
        std::filesystem::path filePath(entry_file.path());
        std::string file_name = filePath.stem().string();
        std::string file_type = filePath.extension().string();

        if(file_type == ".frag"){
            fragSrc[file_name] = entry_file.path().string();
        } else if(file_type == ".vert"){
            vertSrc[file_name] = entry_file.path().string();
        } else if(file_type == ""){ 
            continue;
        } else {
            LOG("SHADER MANAGER", "invalid file extension!" + file_type, RED_CODE);
            LOG("DEBUG", entry_file.path().string());
        }
    }

    for(auto pair : fragSrc){
        auto it = vertSrc.find(pair.first);
        if(it != vertSrc.end()){
            if(shaders.empty()){
                // shaders[pair.first] = ShaderProgram(fragSrc[pair.first], vertSrc[pair.first]);
                shaders[pair.first] = std::make_shared<ShaderProgram>(fragSrc[pair.first], vertSrc[pair.first]);
                // shaders.emplace(pair.first, ShaderProgram(
                //     fragSrc[pair.first],
                //     vertSrc[pair.first]
                // ));
                LOG("SHADER MANAGER", "PROGRAM IS COMPILED WITH " + std::to_string(shaders[pair.first]->shaderProgram) + " ID");
                continue;
            }

            if(!shaders.empty()){
                // shaders[pair.first] = ShaderProgram(fragSrc[pair.first], vertSrc[pair.first]);
                shaders[pair.first] = std::make_shared<ShaderProgram>(fragSrc[pair.first], vertSrc[pair.first]);

                // shaders.emplace(pair.first, ShaderProgram(
                //     fragSrc[pair.first],
                //     vertSrc[pair.first]
                // ));
                LOG("SHADER MANAGER", "PROGRAM IS COMPILED WITH " + std::to_string(shaders[pair.first]->shaderProgram) + " ID");
            } else {
                LOG("SHADER MANAGER", "this shader is already has " + pair.first, YELLOW_CODE);
            }
        } else {
            LOG("SHADER MANAGER", "second shader not found!", RED_CODE);
        }     
    }
    
    // for(auto pair : shaders){
    //     LOG("DEBUG", pair.first);
    //     std::cout << pair.second->shaderProgram << std::endl;
    // }

}

void ShaderManager::useShader(std::string shaderName){
    currUseShader = shaderName;
    shaders[shaderName]->use();
}

// make more safe returns and etc

ShaderProgram* ShaderManager::getCurrShader(){
    // return &shaders[currUseShader];
}

ShaderProgram* ShaderManager::getShader(std::string shaderName){
    if(shaders.find(shaderName) != shaders.end()){
        return shaders[shaderName].get();
    }
    return nullptr;
}

void ShaderManager::deleteAllShaders(){
    for(auto pair : shaders){
        pair.second->~ShaderProgram();
    }
}
