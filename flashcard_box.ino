#include <LiquidCrystal.h>

// LCD pin setup: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Flashcard content
String questions[] = {
  "What is 2+2?",
  "Capital France?",
  "Largest planet?"
};

String answers[] = {
  "4",
  "Paris",
  "Jupiter"
};

int totalCards = 3;
int index = 0;
bool showingAnswer = false;
int buttonPin = 2;

unsigned long lastSwitch = 0;
unsigned long switchInterval = 10000; // auto-switch every 10 sec
bool needUpdate = true;

void setup() {
  lcd.begin(16, 2);                  // 16 columns, 2 rows
  pinMode(buttonPin, INPUT_PULLUP); // internal pull-up resistor
  lcd.print("Flashcards Ready");    
  delay(2000);
  lcd.clear();
  lcd.print(questions[index]);       // show first question
}

void loop() {
  // If button is pressed, toggle between question and answer
  if (digitalRead(buttonPin) == LOW) {
    showingAnswer = !showingAnswer;
    needUpdate = true;
    delay(300); // debounce
  }

  // Every 10 seconds, move to the next flashcard
  if (millis() - lastSwitch > switchInterval) {
    index = (index + 1) % totalCards;
    showingAnswer = false;
    needUpdate = true;
    lastSwitch = millis();
  }

  // Update the LCD only when needed
  if (needUpdate) {
    lcd.clear();
    if (showingAnswer) {
      lcd.print(answers[index]);
    } else {
      lcd.print(questions[index]);
    }
    needUpdate = false;
  }
}
