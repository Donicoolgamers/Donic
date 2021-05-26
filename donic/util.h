#ifndef util_h
#define util_h

#include <EEPROM.h>



class Util
{
    private:

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
};



#endif
