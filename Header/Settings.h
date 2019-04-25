#ifndef SETTINGS_H
#define SETTINGS_H

#include <map>
#include <string>

/**
 * Settings is a singleton that contains all the basic setting of the program
 */
class Settings{

private:
    //Singleton
    static Settings* _settings;

    //map of setting
    std::map<std::string, std::string> _strings;

public:
    /**
     * Constructor
     */
    Settings();

    /**
     * This function is used to get the singleton
     */
    static Settings* getSettings();

    /**
     * Add a setting to the list
     */
    void addSetting(std::string key, std::string value);

    /**
     * Remove a setting from the list
     */
    std::string getSetting(std::string key);
};

#endif
