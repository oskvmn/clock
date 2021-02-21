
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int modeButtonPin = 10;
const int selectButtonPin = 9;
const int increaseButtonPin = 8;
const int buzzer = 6;
int second = 1, minutes = 0, hours = 0, decisecond = 0, alarmHours = 0, alarmMinutes = 0, mode = 0, digitSelect = 0, indicator = 0, alarmIndicator = 0, alarmState = 0, alarmTimer = 0;
int modeButtonState = 0;
int selectButtonState = 0;
int increaseButtonState = 0;


void setup() {
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    pinMode(buzzer, OUTPUT);
}

void loop() {
    decisecond++; //Perform the time-tracking step
    if (decisecond >= 10)
    {
        decisecond = 0;
        second++;
    }
    if (second >= 60)
    {
        second = 0;
        minutes++;
    }
    if (minutes >= 60)
    {
        minutes = minutes - 60;
        hours++;
    }
    if (hours >= 13)
    {
        hours = hours - 12;
        indicator = (indicator - 1) * -1;
    }

    if (alarmMinutes >= 60)
    {
        alarmMinutes = alarmMinutes - 60;
        alarmHours++;
    }
    if (alarmHours >= 13)
    {
        alarmHours = alarmHours - 12;
        alarmIndicator = (alarmIndicator - 1) * -1;
    }


    modeButtonState = digitalRead(modeButtonPin); //Read button to change mode
    selectButtonState = digitalRead(selectButtonPin);
    increaseButtonState = digitalRead(increaseButtonPin);

    if (mode == 0) { //Normal Time Mode
        lcd.setCursor(0, 0); //Write to display
        if (hours < 10) { lcd.print("0"); }
        lcd.print(hours);
        lcd.print(":");
        if (minutes < 10) { lcd.print("0"); }
        lcd.print(minutes);
        lcd.print(" ");
        if (indicator == 0) { lcd.print("AM"); }
        else if (indicator == 1) { lcd.print("PM"); }
        lcd.print(" ");
        lcd.print("TIME ");
        lcd.setCursor(0, 1);
        lcd.print("     ");
        if (modeButtonState == HIGH) { mode = 1; } //Set mode to Time Set Mode

        if (increaseButtonState == HIGH) { //Cut off alarm

            alarmState = 0;
            alarmTimer = 0;

        }
        if (alarmHours == hours && alarmMinutes == minutes && second == 0 && alarmState == 0) {
            alarmState = 1;
            alarmTimer = 650;
        }

        if (alarmState == 1) {
            tone(buzzer, 1000);
            alarmTimer--;

        }
        if (alarmTimer <= 0) {

            noTone(buzzer);
            alarmState = 0;
        }
    }
    else if (mode == 1) { //Time Set Mode

        lcd.setCursor(0, 0);

        if (hours < 10) { lcd.print("0"); }
        lcd.print(hours);
        lcd.print(":");

        if (minutes < 10) { lcd.print("0"); }
        lcd.print(minutes);
        lcd.print(" ");

        if (indicator == 0) { lcd.print("AM"); }
        else if (indicator == 1) { lcd.print("PM"); }

        lcd.print(" ");
        lcd.print("SET  ");

        if (digitSelect == 0) {
            lcd.setCursor(0, 1);
            lcd.print("    ^");
        }
        else if (digitSelect == 1) {
            lcd.setCursor(0, 1);
            lcd.print("   ^ ");
        }
        else if (digitSelect == 2) {
            lcd.setCursor(0, 1);
            lcd.print(" ^   ");
        }
        else if (digitSelect == 3) {
            lcd.setCursor(0, 1);
            lcd.print("^    ");
        }

        if (modeButtonState == HIGH) { mode = 2; } //Mode 2= Alarm set mode

        if (digitSelect == 0) {
            if (selectButtonState == HIGH) { digitSelect++; }

            if (increaseButtonState == HIGH) { minutes++; }
        }
        else if (digitSelect == 1) {
            if (selectButtonState == HIGH) { digitSelect++; }

            if (increaseButtonState == HIGH) { minutes = minutes + 10; }
        }
        else if (digitSelect == 2) {
            if (selectButtonState == HIGH) { digitSelect++; }

            if (increaseButtonState == HIGH) { hours++; }
        }
        else if (digitSelect == 3) {
            if (selectButtonState == HIGH) { digitSelect = 0; }

            if (increaseButtonState == HIGH) { hours = hours + 12; }
        }
    }
    else if (mode == 2) {

        lcd.setCursor(0, 0);

        if (alarmHours < 10) { lcd.print("0"); }
        lcd.print(alarmHours);
        lcd.print(":");

        if (alarmMinutes < 10) { lcd.print("0"); }
        lcd.print(alarmMinutes);
        lcd.print(" ");

        if (alarmIndicator == 0) { lcd.print("AM"); }
        else if (alarmIndicator == 1) { lcd.print("PM"); }

        lcd.print(" ");
        lcd.print("ALARM");

        if (digitSelect == 0) {
            lcd.setCursor(0, 1);
            lcd.print("    ^");
        }
        else if (digitSelect == 1) {
            lcd.setCursor(0, 1);
            lcd.print("   ^ ");
        }
        else if (digitSelect == 2) {
            lcd.setCursor(0, 1);
            lcd.print(" ^   ");
        }
        else if (digitSelect == 3) {
            lcd.setCursor(0, 1);
            lcd.print("^    ");
        }

        if (digitSelect == 0) {
            if (selectButtonState == HIGH) { digitSelect++; }

            if (increaseButtonState == HIGH) { alarmMinutes++; }
        }
        else if (digitSelect == 1) {
            if (selectButtonState == HIGH) { digitSelect++; }

            if (increaseButtonState == HIGH) { alarmMinutes = alarmMinutes + 10; }
        }
        else if (digitSelect == 2) {
            if (selectButtonState == HIGH) { digitSelect++; }

            if (increaseButtonState == HIGH) { alarmHours++; }
        }
        else if (digitSelect == 3) {
            if (selectButtonState == HIGH) { digitSelect = 0; }

            if (increaseButtonState == HIGH) { alarmHours = alarmHours + 12; }
        }

        if (modeButtonState == HIGH) { mode = 0; } //Mode 0= Normal display mode
    }


    delay(87);


}
