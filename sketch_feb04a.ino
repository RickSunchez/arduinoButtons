unsigned int noise = 10;
unsigned int doubleTimer = 500;
unsigned int holdTimer = 300;
unsigned int counter = 0;

bool prevClick = false;
bool onHoldAction = false;
bool _single = false;
bool _double = false;
bool _hold = false;

unsigned long globalTimer = 0;
unsigned long lastTimer = 0;
unsigned long diff = 0;

void setup(){
  Serial.begin(9600);
  pinMode(2, INPUT);
}

void loop(){
  bool onClick = digitalRead(2);
  
  if (onClick && !prevClick){
    globalTimer = millis();
  }

  if (onClick && prevClick) {
    diff = millis() - globalTimer;
    if (diff > holdTimer) {
      _hold = true;  
    }
  }
 
  if (!onClick && prevClick){
    diff = millis() - globalTimer;
    if (diff > noise && !_hold){
      diff = millis() - lastTimer;
      if (diff >= doubleTimer){
        lastTimer = millis();
        _single = true;
        counter=1;
      } else {
        counter++;
        lastTimer = millis();
        _single = false;
        _double = true;
      }
    }
    onHoldAction = false;
    _hold = false;
  }
  
  if (_hold && !onHoldAction) {
    _single = false;
    _double = false;
    _hold = false;
    onHoldAction = true;
    Serial.println("hold");
  }
  
  prevClick = onClick;

  diff = millis() - lastTimer;
  if (diff > doubleTimer) {
    if (_single){
      _double = false;
      _single = false;
      _hold = false;
      Serial.println(1);
    }
    if (_double){
      _single = false;
      _double = false;
      _hold = false;
      Serial.println(counter);
    }
  }
}
