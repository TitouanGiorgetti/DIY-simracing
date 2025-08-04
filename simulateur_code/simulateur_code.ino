#include <Joystick.h>
#include <Encoder.h>

// *** Définition des potentiomètres ***
const int potPin1 = A0;   // Potentiomètre 1
const int potPin2 = A1;   // Potentiomètre 2
const int potPin3 = A2;   // Potentiomètre 3

// Variables pour stocker les valeurs des potentiomètres
int potValue1 = 0;
int potValue2 = 0;
int potValue3 = 0;

// Seuil pour activer les boutons via les potentiomètres
int threshold = 512;

// *** Définition des boutons poussoirs ***
const int buttonPinUp = 4;      // Bouton Haut
const int buttonPinLeft = 5;    // Bouton Gauche
const int buttonPinRight = 6;   // Bouton Droite
const int buttonPinY = 7;       // Bouton Y
const int buttonPinDown = 8;    // Bouton Bas
const int buttonPinEsc = 9;     // Bouton Échap/Menu

// Variables pour l'état des boutons
int buttonStateUp = 0;
int buttonStateLeft = 0;
int buttonStateRight = 0;
int buttonStateY = 0;
int buttonStateDown = 0;
int buttonStateEsc = 0;

// *** Définition de l'encodeur ***
#define ENCODER_PIN_A 2
#define ENCODER_PIN_B 3
Encoder myEnc(ENCODER_PIN_A, ENCODER_PIN_B);
long lastEncoderPosition = 0;

// *** Initialisation du Joystick ***
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
                   16, 0,                   // 16 boutons, 0 chapeaux
                   true, true, false);      // Axes X et Y activés

void setup() {
  // Initialisation des broches des boutons poussoirs comme entrées
  pinMode(buttonPinUp, INPUT_PULLUP);
  pinMode(buttonPinLeft, INPUT_PULLUP);
  pinMode(buttonPinRight, INPUT_PULLUP);
  pinMode(buttonPinY, INPUT_PULLUP);
  pinMode(buttonPinDown, INPUT_PULLUP);
  pinMode(buttonPinEsc, INPUT_PULLUP);

  // Initialisation du Joystick
  Joystick.begin();
}

void loop() {
  // *** Gestion des potentiomètres ***
  potValue1 = analogRead(potPin1);
  potValue2 = analogRead(potPin2);
  potValue3 = analogRead(potPin3);

  if (potValue1 > threshold) Joystick.pressButton(0); else Joystick.releaseButton(0);
  if (potValue2 > threshold) Joystick.pressButton(1); else Joystick.releaseButton(1);
  if (potValue3 > threshold) Joystick.pressButton(2); else Joystick.releaseButton(2);

  // *** Gestion des boutons poussoirs ***
  buttonStateUp = digitalRead(buttonPinUp);
  buttonStateLeft = digitalRead(buttonPinLeft);
  buttonStateRight = digitalRead(buttonPinRight);
  buttonStateY = digitalRead(buttonPinY);
  buttonStateDown = digitalRead(buttonPinDown);
  buttonStateEsc = digitalRead(buttonPinEsc);

  if (buttonStateUp == LOW) Joystick.pressButton(3); else Joystick.releaseButton(3);
  if (buttonStateLeft == LOW) Joystick.pressButton(4); else Joystick.releaseButton(4);
  if (buttonStateRight == LOW) Joystick.pressButton(5); else Joystick.releaseButton(5);
  if (buttonStateY == LOW) Joystick.pressButton(6); else Joystick.releaseButton(6);
  if (buttonStateDown == LOW) Joystick.pressButton(7); else Joystick.releaseButton(7);
  if (buttonStateEsc == LOW) Joystick.pressButton(8); else Joystick.releaseButton(8);

  // *** Gestion de l'encodeur ***
  long currentEncoderPosition = myEnc.read();
  if (currentEncoderPosition != lastEncoderPosition) {
    int mappedX = map(currentEncoderPosition, -500, 500, -127, 127);
    Joystick.setXAxis(mappedX);
    lastEncoderPosition = currentEncoderPosition;
  }

  // Petite pause pour éviter les rebonds et réduire l'utilisation du CPU
  delay(10);
}
