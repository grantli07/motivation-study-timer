#include <Arduino.h>
#include <LiquidCrystal.h>

// put function declarations here:
int myFunction(int, int);

// LCD setup
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// buzzer music
int music[] = {440, 494, 523, 587, 659};
const char* messages[] = {"--- FOCUSING ---", "--- GO GO GO ---", "--- IM BUSYY ---", "- YOU GOT THIS -", "-- DONT STOP! --"};
int numMessages = 5;

// variables
signed short minutes, seconds, rest;
char timeline[16];
char countf[16];
int selectButton = 7, leftButton = 8, rightButton = 9;
int buzzer = 10;
int menu = 0; // determines which selection is being hovered on a screen
int flag = 0; // 0 = mainMenu, 1 = customScreen, 2 = endScreen
int count = 0;
int hrs;
int mins;
int total;

// ---------- Main Menu ----------
void mainMenu() {
  menu = constrain(menu, 0, 1);
  lcd.clear();
  if (menu == 0) {
    lcd.print("---- OPTION ----");
    lcd.setCursor(1, 1);
    lcd.print("~AUTO");
    lcd.setCursor(9, 1);
    lcd.print("CUSTOM");
  } else {
    lcd.print("---- OPTION ----");
    lcd.setCursor(2, 1);
    lcd.print("AUTO");
    lcd.setCursor(8, 1);
    lcd.print("~CUSTOM");
  }
}

//---------- Custom Screen ----------
void customScreen() {
  menu = constrain(menu, 0, 5);
  lcd.clear();
  if (menu == 0) {
    lcd.print("---- OPTION ----");
    lcd.setCursor(1, 1);
    lcd.print("~1HR");
    lcd.setCursor(7, 1);
    lcd.print("2HR");
    lcd.setCursor(12, 1);
    lcd.print("3HR");
  } else if (menu == 1) {
    lcd.print("---- OPTION ----");
    lcd.setCursor(2, 1);
    lcd.print("1HR");
    lcd.setCursor(6, 1);
    lcd.print("~2HR");
    lcd.setCursor(12, 1);
    lcd.print("3HR");
  } else if (menu == 2) {
    lcd.print("---- OPTION ----");
    lcd.setCursor(2, 1);
    lcd.print("1HR");
    lcd.setCursor(7, 1);
    lcd.print("2HR");
    lcd.setCursor(11, 1);
    lcd.print("~3HR");
  } else if (menu == 3) {
    lcd.print("---- OPTION ----");
    lcd.setCursor(1, 1);
    lcd.print("~4HR");
    lcd.setCursor(7, 1);
    lcd.print("5HR");
    lcd.setCursor(12, 1);
    lcd.print("BCK");
  } else if (menu == 4) {
    lcd.print("---- OPTION ----");
    lcd.setCursor(2, 1);
    lcd.print("4HR");
    lcd.setCursor(6, 1);
    lcd.print("~5HR");
    lcd.setCursor(12, 1);
    lcd.print("BCK");
  } else {
    lcd.print("---- OPTION ----");
    lcd.setCursor(2, 1);
    lcd.print("4HR");
    lcd.setCursor(7, 1);
    lcd.print("5HR");
    lcd.setCursor(11, 1);
    lcd.print("~BCK");
  }
}

// ---------- Cycle End Screen ----------
void endScreen() {
  menu = constrain(menu, 0, 1);
  lcd.clear();
  if (menu == 0) {
    lcd.print("-- CONTINUE ? --");
    lcd.setCursor(2, 1);
    lcd.print("~YES");
    lcd.setCursor(11, 1);
    lcd.print("NO");
  } else {
    lcd.print("-- CONTINUE ? --");
    lcd.setCursor(3, 1);
    lcd.print("YES");
    lcd.setCursor(10, 1);
    lcd.print("~NO");
  }
}

// ---------- Pomodoro timer (standard 30 mins) ----------
void timer() {
  lcd.clear();
  lcd.print(messages[0]);

  minutes = 25;
  seconds = 0;

  int msgIndex = 0;
  unsigned long lastMsgSwitch = millis();
  const unsigned long msgDuration = 60000;
  
  while (minutes != 0 || seconds != 0) {
    if (millis() - lastMsgSwitch >= msgDuration) {
      msgIndex = (msgIndex + 1) % numMessages;
      lcd.setCursor(0, 0);
      lcd.print(messages[msgIndex]);
      lastMsgSwitch = millis();
    }

    lcd.setCursor(0,1);
    sprintf(timeline,"    %0.2d    %02d  ", minutes, seconds);
    lcd.print(timeline);
    delay(300);
    lcd.setCursor(7,1);
    lcd.print(":");
    lcd.setCursor(8,1);
    lcd.print(":");
    lcd.setCursor(7,1);
    lcd.print("");
    lcd.setCursor(8,1);
    lcd.print("");
    delay(700);
    if (seconds == 0) {
      seconds = 59;
      minutes--;
    } else {
      seconds--;
    }
  }
  lcd.setCursor(0,1);
  sprintf(timeline,"    %0.2d    %02d  ", minutes, seconds);
  lcd.print(timeline);
  delay(1000);
  lcd.clear();
  lcd.print("-- COMPLETED! --");
  for (int i = 0; i < 5; i++) {
    tone(buzzer, music[i], 500);
    delay(500);
    lcd.setCursor(3, 1);
    lcd.print("REST  TIME");
  }
  delay(2000);

  rest = 5;
  seconds = 0;
  
  lcd.clear();
  lcd.print("----- REST -----");
  while (rest != 0 || seconds != 0) {
    lcd.setCursor(0, 1);
    sprintf(timeline,"    %0.2d    %02d  ", rest, seconds);
    lcd.print(timeline);
    delay(300);
    lcd.setCursor(7,1);
    lcd.print(":");
    lcd.setCursor(8,1);
    lcd.print(":");
    lcd.setCursor(7,1);
    lcd.print("");
    lcd.setCursor(8,1);
    lcd.print("");
    delay(700);
    if (seconds == 0) {
      seconds = 59;
      rest--;
    } else {
      seconds--;
    }
  }
  lcd.setCursor(0,1);
  sprintf(timeline,"    %0.2d    %02d  ", rest, seconds);
  lcd.print(timeline);
  delay(1000);
  
  count++;
  total = count * 30;
  if (total >= 60) {
    hrs = total / 60;
    mins = total % 60;
  } else {
    hrs = 0;
    mins = total;
  }
  lcd.clear();
  lcd.print("-- CHECKPOINT --");
  tone(buzzer, 500, 500);
  lcd.setCursor(0, 1);
  sprintf(countf, "COUNT:%02d   %02d:%02d", count, hrs, mins);
  lcd.print(countf);
  delay(1000);

  if (flag == 0) {
    flag = 2;
    endScreen();
  }
}

// ---------- Start timer ----------
void start() {
  lcd.clear();
  lcd.print("---- ALERT! ----");
  tone(buzzer, 500, 500);
  for (int i = 5; i > 0; i--) {
    lcd.setCursor(1, 1);
    lcd.print("GET READY IN ");
    lcd.setCursor(14, 1);
    lcd.print(i);
    delay(1000);
  }

  timer();
  delay(2000);
}

// ---------- Main menu function execution ----------
void mainMenuFunction() {
  if (menu == 0) {
    flag = 0;
    delay(100);
    start();
  } else {
    menu = 0;
    flag = 1;
    delay(100);
    customScreen();
  }
}

// ---------- Custom menu function execution ----------
void customMenuFunction() {
  if (menu == 5) {
    menu = 0;
    flag = 0;
    mainMenu();
    return;
  }

  int cycles = 2 * (menu + 1);
  for (int i = 0; i < cycles; i++) {
    start();
  }

  tone(buzzer, 500, 500);
  delay(500);

  delay(1000);
  menu = 0;
  flag = 0;
  count = 0;
  mainMenu();
}

// ---------- endScreen function ----------
void confirm() {
  if (menu == 0) {
    delay(100);
    flag = 0;
    start();
  } else {
    delay(100);
    flag = 0;
    menu = 0;
    
    total = count * 30;
    if (total >= 60) {
      hrs = total / 60;
      mins = total % 60;
    } else {
      hrs = 0;
      mins = total;
    }
    lcd.clear();
    lcd.print("--- SUMMARY: ---");
    lcd.setCursor(0,1);
    sprintf(countf, "COUNT:%02d   %02d:%02d", count, hrs, mins);
    lcd.print(countf);
    delay(2000);
    count = 0;
    mainMenu();
  }
}

void updateCurrentMenu() {
    if (flag == 0) mainMenu();
    else if (flag == 1) customScreen();
    else if (flag == 2) endScreen();
}

void executeCurrentAction() {
    if (flag == 0) mainMenuFunction();
    else if (flag == 1) customMenuFunction();
    else if (flag == 2) confirm();
}

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(selectButton, INPUT_PULLUP);
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  lcd.setCursor(3, 0);
  lcd.print("WELCOME TO");
  for (int i = 0; i < 5; i++) {
    tone(buzzer, music[i], 500);
    delay(500);
    lcd.setCursor(4, 1);
    lcd.print("POMODORO");
  }
  mainMenu();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!digitalRead(leftButton)) {
    tone(buzzer, music[0], 50);
    menu--;
    updateCurrentMenu();
    delay(100);
    while (!digitalRead(leftButton));
  }

  if (!digitalRead(rightButton)) {
    tone(buzzer, music[0], 50);
    menu++;
    updateCurrentMenu();
    delay(100);
    while (!digitalRead(rightButton));
  }

  if (!digitalRead(selectButton)) {
    tone(buzzer, music[3], 50);
    executeCurrentAction();
    delay(100);
    while (!digitalRead(selectButton));
  }
}