/*
    RGBLED

        This library is created to simplify the steering of a colorful LED.
        The light emitted from the LED is set through the three color
        components, i.e. red, green and blue.
        The brightnesses of the three separate color channels of the LED
        are changed using PWM. The library itself uses analogWrite(...)
        to change the PWM pulse width.

    I.LICENSE

        Creative Commons Attribution-ShareAlike 3.0 License
        http://creativecommons.org/licenses/by-sa/3.0/

    II. USAGE

        Copy the RGBLED folder into your library folder
        and include it in your sketch. If you don't see the library
        immediately, then restart the arduino IDE.

        Create a RGBLED object.
        In order to create a RGBLED object, you must specify the pin
        numbers of the three separate color channels of the RGB LED
        as input parameters to the constructor.

        The first parameter is the pin number of the red color.
        The second parameter is the pin number of the green color.
        The third parameter is the pin number of the blue color.

        You can have more than one RGBLED objects in your sketch,
        but do not to use the same pin number for multiple RGBLED
        objects.

        Initially, the color is set to black, that is no light is emitted.

    III. EXAMPLE USAGE

        1. Import the lib into your sketch

            #import <RGBLED.h>

        2. Create an RGBLED object. As parameters provide the colors pin numbers.

            RGBLED myLed = RGBLED(pinRed, pinGreen, pinBlue);

        3. Set the color you wish

            myLed.setRed(0.1);
            myLed.setGreen(0.5);
            myLed.setBlue(1.0);

            // OR

            myLed.setRGB(0.1,0.5,1.0);

        4. You can brighten or darken the LED

           myLed.brighten(0.25);
           myLed.darken(1.0);

        5. You can override the color if you need to change the color for
           a short time.

            // set color to dim green
            myLed.setRGB(0.0,0.5,0.0);
            ...

            // Override the color with full red
            myLed.overrideRed();
            ...

            // Back to previously set color. (dim green in our case)
            myLed.stopOverride();
            ...

    IV. THE FULL API

        1. Constructor

            RGBLED(int redPin, int greenPin, int bluePin);

            The constructor changes the supplied pins modes to "OUTPUT".
            The initial color is black, that is no light.
            If you assign a pin to the RGBLED object, don't use the pin
            for other purposes.

        2. Setting a color

            setRed(float redValue);
            setGreen(float greenValue);
            setBlue(float blueValue);
            setRGB(float redValue, float greenValue, float blueValue);

            The input parameter should be in the range between 0.0 and 1.0
            Setting the value of one color does not change the value
            of the other colors. The LED output color is the mixture of
            the component colors, red green and blue.
            Internally "analogWrite(...)" is used.

        3. Get previously set color

            float getRed();
            float getGreen();
            float getBlue();

            The values returned from this functions are the color values
            from the inner buffer, not necessarily the real values of the
            PWM. The value of PWM can be different from the buffered colors
            values if "autoUpdate" is disabled and the user did'nt call
            "update()" after setting the color value.

        4. Brightening and darkening the light

            brighten(float amount);
            brightenRed(float amount);
            brightenGreen(float amount);
            brightenBlue(float amount);
            darken(float amount);
            darkenRed(float amount);
            darkenGreen(float amount);
            darkenBlue(flaot amount);

            The input parameter should be in the range of 0.0 to 1.0.
            The resulting color value is calculated to be between 0.0 and 1.0,
            so you can brighten the value even if it has the full brightness 
            already.

        5. Overriding a color

            overrideRed();
            overrideGreen();
            overrideBlue();
            overrideWhite();
            overrideBlack();
            overrideRGB(float redValue, float greenValue, float blueValue);
            stopOverride();

            The overriding of the colour does not influence the color
            value stored in the buffer. So after calling "stopOverride()"
            You always get the originally set color.

        6. Disable automatic color update

            The default behaviour is that the color changes immediately after
            setting the color with e.g. "setRGB(...)" or "overrideBlack()"
            However, sometimes you would like to buffer the color changes,
            and send the color value to the PWM later on.
            For that purpose you have the function:

                disableAutoUpdate();

            If you call it, then after setting the color you have to manualy
            do updates, like so:

                // Lets say the color was black.

                setRed(0.75);
                // still black
                setGreen(0.0);
                // still black
                setBlue(0.0);
                // still black
                update();
                // the colour is now 3/4 red

                overrideWhite();
                // the colour did not change
                update();
                // now the override kicks in.

            You can go back to automatic updates with this function:

                enableAutoUpdate();

            You can check if automatic update is on with:

                boolean isAutoUpdate();


    Created 24 August 2014
    By Marcin Drzymala

*/

#ifndef RGBLED_H
#define RGBLED_H

#include "Arduino.h"

class RGBLED {
public:
    RGBLED(const int redPin, const int greenPin, const int bluePin);
    void setRGB(const float redValue, const float greenValue, const float blueValue);
    void setRed(const float redValue);
    void setGreen(const float greenValue);
    void setBlue(const float blueValue);
    float getRed();
    float getGreen();
    float getBlue();
    void brighten(const float amount);
    void brightenRed(const float amount);
    void brightenGreen(const float amount);
    void brightenBlue(const float amount);
    void darken(const float amount);
    void darkenRed(const float amount);
    void darkenGreen(const float amount);
    void darkenBlue(const float amount);
    void overrideRGB(const float redValue, const float greenValue, const float blueValue);
    void overrideRed();
    void overrideGreen();
    void overrideBlue();
    void overrideWhite();
    void overrideBlack();
    bool isOverride();
    void stopOverride();
    void disableAutoUpdate();
    void enableAutoUpdate();
    bool isAutoUpdate();
    void update();
private:
    int pinR;
    int pinG;
    int pinB;
    float red_component;
    float green_component;
    float blue_component;
    float red_override;
    float green_override;
    float blue_override;
    bool auto_update;
    bool override_color;
    float sanitize(const float input);
    byte floatIntoByte(const float input);
    void autoUpdate();
};

#endif