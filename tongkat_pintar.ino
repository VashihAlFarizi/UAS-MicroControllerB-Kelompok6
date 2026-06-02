#define TRIG 5
#define ECHO 18
#define BUZZER 23
#define RELAY 19

long duration;
int distance;

// PWM ESP32
const int buzzerChannel = 0;
const int resolution = 8;

void setup() {

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Relay
  pinMode(RELAY, OUTPUT);

  Serial.begin(115200);

  // Setup PWM buzzer
  ledcSetup(buzzerChannel, 1000, resolution);
  ledcAttachPin(BUZZER, buzzerChannel);

  // Relay awal mati
  digitalWrite(RELAY, LOW);
}

void loop() {

  // Mengirim gelombang ultrasonik
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  // Membaca pantulan
  duration = pulseIn(ECHO, HIGH);

  // Menghitung jarak
  distance = duration * 0.034 / 2;

  // Menampilkan jarak
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Jika jarak sangat dekat
  if(distance <= 20 && distance > 0){

    // Buzzer
    ledcWriteTone(buzzerChannel, 2500);

    // Relay ON
    digitalWrite(RELAY, HIGH);

    delay(100);

    // Buzzer OFF
    ledcWriteTone(buzzerChannel, 0);

    // Relay OFF
    digitalWrite(RELAY, LOW);

    delay(100);
  }

  // Jika jarak dekat
  else if(distance <= 30){

    ledcWriteTone(buzzerChannel, 1800);

    digitalWrite(RELAY, HIGH);

    delay(300);

    ledcWriteTone(buzzerChannel, 0);

    digitalWrite(RELAY, LOW);

    delay(300);
  }

  // Jika jarak agak jauh
  else if(distance <= 60){

    ledcWriteTone(buzzerChannel, 1000);

    digitalWrite(RELAY, LOW);

    delay(600);

    ledcWriteTone(buzzerChannel, 0);

    digitalWrite(RELAY, LOW);

    delay(600);
  }

  // Jika tidak ada objek
  else{

    ledcWriteTone(buzzerChannel, 0);

    digitalWrite(RELAY, LOW);
  }

  delay(50);
}