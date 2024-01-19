#pragma once
#include "MetaSave.h"
#include "Save.h"

#define saver Saver::instance()

class Saver{
    public:
        Saver();
        ~Saver(){}
        Saver(Saver& other) = delete;
        void operator=(const Saver& other) = delete;

        static Saver& instance();

        void save(std::string saveID);
        void loadSave(std::string saveID);
        void deleteSave(std::string saveID);
        bool saveExists(std::string saveID);
        std::string pathToSave(std::string saveID);

        MetaSave& meta(){return _meta;}
        const MetaSave& meta() const{return _meta;}
        const int& maxSlots() const{return _maxSlots;}
    private:
        MetaSave _meta;
        const int _maxSlots;
};