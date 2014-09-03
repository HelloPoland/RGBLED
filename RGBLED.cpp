/*
    RGBLED

    I.LICENSE

        Creative Commons Attribution-ShareAlike 3.0 License
        http://creativecommons.org/licenses/by-sa/3.0/

    II. USAGE

        See the header file for the rest of the documentation.

    Created 24 August 2014
    By Marcin Drzymala

*/

#include "RGBLED.h"
#include "Arduino.h"

RGBLED::RGBLED(const int redPin, const int greenPin, const int bluePin){
    pinR = redPin;
    pinG = greenPin;
    pinB = bluePin;
    red_component = 0.0;
    green_component = 0.0;
    blue_component = 0.0;
    red_override = 0.0;
    green_override = 0.0;
    blue_override = 0.0;
    auto_update = true;
    override_color = false;
    pinMode(pinR, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinB, OUTPUT);
    update();
}


void RGBLED::setRGB(const float redValue, const float greenValue, const float blueValue){
    red_component = sanitize(redValue);
    green_component = sanitize(greenValue);
    blue_component = sanitize(blueValue);
    autoUpdate();
}


void RGBLED::setRed(const float redValue){
    red_component = sanitize(redValue);
    autoUpdate();
}


void RGBLED::setGreen(const float greenValue){
    green_component = sanitize(greenValue);
    autoUpdate();
}


void RGBLED::setBlue(const float blueValue){
    blue_component = sanitize(blueValue);
    autoUpdate();
}


float RGBLED::getRed(){
    return red_component;
}


float RGBLED::getGreen(){
    return green_component;
}


float RGBLED::getBlue(){
    return blue_component;
}


void RGBLED::brighten(const float amount){
    setRGB(red_component + amount,
           green_component + amount,
           blue_component + amount);
}


void RGBLED::brightenRed(const float amount){
    setRed(red_component + amount);
}


void RGBLED::brightenGreen(const float amount){
    setGreen(green_component + amount);
}


void RGBLED::brightenBlue(const float amount){
    setBlue(blue_component + amount);
}


void RGBLED::darken(const float amount){
    setRGB(red_component - amount,
           green_component - amount,
           blue_component - amount);
}


void RGBLED::darkenRed(const float amount){
    setRed(red_component - amount);
}


void RGBLED::darkenGreen(const float amount){
    setGreen(green_component - amount);
}


void RGBLED::darkenBlue(const float amount){
    setBlue(blue_component - amount);
}


void RGBLED::overrideRGB(const float redValue, const float greenValue, const float blueValue){
    red_override = sanitize(redValue);
    green_override = sanitize(greenValue);
    blue_override = sanitize(blueValue);
    override_color = true;
    autoUpdate();
}


void RGBLED::overrideRed(){
    overrideRGB(1.0,0.0,0.0);
}


void RGBLED::overrideGreen(){
    overrideRGB(0.0,1.0,0.0);
}


void RGBLED::overrideBlue(){
    overrideRGB(0.0,0.0,1.0);
}


void RGBLED::overrideWhite(){
    overrideRGB(1.0,1.0,1.0);
}


void RGBLED::overrideBlack(){
    overrideRGB(0.0,0.0,0.0);
}


bool RGBLED::isOverride(){
    return override_color;
}


void RGBLED::stopOverride(){
    override_color = false;
    autoUpdate();
}


void RGBLED::disableAutoUpdate(){
    auto_update = false;
}


void RGBLED::enableAutoUpdate(){
    auto_update = true;
}


bool RGBLED::isAutoUpdate(){
    return auto_update;
}

 
void RGBLED::update(){
    if (override_color){
        analogWrite(pinR, floatIntoByte(red_override));
        analogWrite(pinG, floatIntoByte(green_override));
        analogWrite(pinB, floatIntoByte(blue_override));
    } else {
        analogWrite(pinR, floatIntoByte(red_component));
        analogWrite(pinG, floatIntoByte(green_component));
        analogWrite(pinB, floatIntoByte(blue_component));
    }
}


float RGBLED::sanitize(const float input){
    if (input >= 1.0) return 1.0;
    if (input <= 0.0) return 0.0;
    return input;
}


byte RGBLED::floatIntoByte(const float input){
    if (input <= 0.001) return 0;
    if (input >= 0.999) return 255;
    return (byte)(255.0 * input);
}


void RGBLED::autoUpdate(){
    if (auto_update)
        update();
}