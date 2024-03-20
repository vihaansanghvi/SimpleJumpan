#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define the number of columns and rows on the LCD
const int LCD_COLS = 16;
const int LCD_ROWS = 2;

// Button pin
const int buttonPin = 2;

// Game variables
int jumpmanPosition = 7; // Starting position of Jumpman
bool isJumping = false;
unsigned long jumpStartTime;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Set button pin as input with internal pullup resistor
  lcd.init();                      // Initialize the LCD
  lcd.backlight();                 // Turn on the backlight

  // Draw the ground on the bottom row
  for (int i = 0; i < LCD_COLS; i++) {
    lcd.setCursor(i, LCD_ROWS - 1);
    lcd.print("_");
  }
}

void loop() {
  // Read the state of the button
  bool buttonState = digitalRead(buttonPin);

  // If the button is pressed and Jumpman is not already jumping
  if (buttonState == LOW && !isJumping) {
    isJumping = true;
    jumpStartTime = millis();
  }

  // Handle the jumping logic
  if (isJumping) {
    unsigned long currentTime = millis();
    // Jump duration is half a second
    if (currentTime - jumpStartTime < 500) {
      // Jumpman is in the air
      drawJumpman(jumpmanPosition, 0); // Draw Jumpman in the top row
    } else {
      // Jump is over
      isJumping = false;
    }
  }

  if (!isJumping) {
    // If not jumping, ensure Jumpman is on the ground
    drawJumpman(jumpmanPosition, 1); // Draw Jumpman in the bottom row
  }

  delay(100); // Small delay to slow down the loop for button debouncing
}

void drawJumpman(int position, int row) {
  // Clear Jumpman's previous position by drawing a space
  lcd.setCursor(position, row == 0 ? 1 : 0);
  lcd.print(" ");

  // Draw Jumpman at the new position
  lcd.setCursor(position, row);
  lcd.print("A"); // Simple representation of Jumpman

  // Redraw the ground if Jumpman was on the bottom row
  if (row == 1) {
    lcd.setCursor(position, 0);
    lcd.print("_");
  }
}
