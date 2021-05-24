#ifndef util_h
#define util_h

#include <EEPROM.h>

// it is important to not just randomly change these adresses
#define SETTING0_METRIC 0
#define SETTING1_BLINDMAXDISTANCE 1
#define SETTING2_SOCIALDISTANCE 2
#define LASTADRESS 1023

class Util
{
    private:
    // value * 5 for cm. Reason: max value byte 255, max distance 500 ish cm.
    // 0: boolean, set to true. False = freedom units.
    // 1: 60 * 5 = 300 cm before its starts notifying the user
    // 2: 30 * 5 = 150 cm before its starts notifying the user
    byte settings[3] = {byte(1), byte(60), byte(30)}; // Default settings
    public:
    /**Will return true if time since last call is larger than delay.
     * This function won't call delay() so it won't stop code after it from running.*/
    static bool delayHasPassed(unsigned long &previousTime, int delay)
    {
        unsigned long currentTime = millis();

        if (currentTime - previousTime >= delay)
        {
            previousTime = currentTime;
            return true;
        }
        else
        {
            return false;
        }
    };

    /** # EEPROM functions
     * Functions need to minimize the amount of writing to EEPROM as it is rated for around 100,000 write cycles per single location.
     * Use these functions for reading and updating settings, avoid using EEPROM functions outside these functions.
    */

    // https://www.instructables.com/Arduino-EEPROM-Settings-Initialization/
    /**Initialization of settings and EEPROM.
     * If first startup it will save default settings to EEPROM.
    */
    void initEEPROM()
    {
        if (EEPROM.read(LASTADRESS) == 'I') // Already initialized at some point, read the current settings.
        {
            #ifdef VERBOSE
            Serial.println("EEPROM: Init flag was set => reading settings.");
            #endif
            settings[SETTING0_METRIC] = EEPROM.read(SETTING0_METRIC);
            settings[SETTING1_BLINDMAXDISTANCE] = EEPROM.read(SETTING1_BLINDMAXDISTANCE);
            settings[SETTING2_SOCIALDISTANCE] = EEPROM.read(SETTING2_SOCIALDISTANCE);
        }
        else // First startup/init. Set all default settings.
        {
            #ifdef VERBOSE
            Serial.println("EEPROM: Init flag was NOT set => setting default settings and init flag.");
            #endif
            EEPROM.write(SETTING0_METRIC, settings[SETTING0_METRIC]);
            EEPROM.write(SETTING1_BLINDMAXDISTANCE, settings[SETTING1_BLINDMAXDISTANCE]);
            EEPROM.write(SETTING2_SOCIALDISTANCE, settings[SETTING2_SOCIALDISTANCE]);
            EEPROM.write(LASTADRESS, 'I');
        }
    }

    void updateSetting(int SettingAdress, byte value)
    {
        #ifdef VERBOSE
        Serial.println("EEPROM: updating setting.");
        #endif
        settings[SettingAdress] = value;
        EEPROM.update(SettingAdress, value);
    }

    byte getSetting(int SettingAdress)
    {
        return settings[SettingAdress];
    }

    void bubbleSort(int arr[], int n)
    {
        int i, j;
        for (i = 0; i < n-1; i++){
     
            for (j = 0; j < n-i-1; j++){
                if (arr[j] > arr[j+1])
                    swap(&arr[j], &arr[j+1]);
            }
        }
    }
    
    void swap(int *xp, int *yp)
    {
        int temp = *xp;
        *xp = *yp;
        *yp = temp;
    }
    void dropZeros(int arr[], int length)
    {
        
    }
};



#endif
