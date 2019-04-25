#include "Settings.h"

Settings* Settings::_settings = 0;

Settings::Settings(){}

Settings* Settings::getSettings(){
    if(!(_settings)){
        _settings = new Settings();
    }
    return _settings;
}

void Settings::addSetting(std::string key, std::string value){
    _strings[key] = value;
}

std::string Settings::getSetting(std::string key){
    if(_strings.count(key) == 1){
        return _strings[key];
    }
    return "";
}
