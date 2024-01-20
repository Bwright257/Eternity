#include <filesystem>
#include <fstream>
#include "Saver.h"

Saver::Saver() : _maxSlots(3){
    loadSave(meta().saveID());

    
    return;
}

Saver& Saver::instance(){
    static Saver instance;
    return instance;
}

void Saver::save(std::string saveID){
    std::ofstream outFile;
    outFile.open(pathToSave(saveID), std::ostream::trunc);

    

    outFile.close();
    return;
}

void Saver::loadSave(std::string saveID){
    std::string path = pathToSave(saveID);

    if (saveExists(saveID)){
        std::ifstream inFile;
        inFile.open(path);

        while (inFile.good()){

        }

        inFile.close();
    }

    return;
}

void Saver::deleteSave(std::string saveID){
    std::filesystem::remove(pathToSave(saveID));
    return;
}

bool Saver::saveExists(std::string saveID){
    return std::filesystem::exists(pathToSave(saveID));
}

std::string Saver::pathToSave(std::string saveID){
    return "Data/Saves/" + saveID;
}