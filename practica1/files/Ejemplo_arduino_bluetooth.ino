#include <Servo.h>        // Incluir la librería para controlar servos
#include <Wire.h>         // Incluir la librería para comunicación I2C (para la pantalla OLED)
#include <Adafruit_GFX.h> // Incluir la librería base de Adafruit para gráficos
#include <Adafruit_SSD1306.h> // Incluir la librería para manejar la pantalla OLED SSD1306

// Definir los pines donde están conectados los servos
#define SERVO_IZQUIERDO_PIN PB0   // Pin 0 para el servo izquierdo
#define SERVO_DERECHO_PIN PB1     // Pin 1 para el servo derecho

// Crear objetos para controlar los servos
Servo servoIzquierdo;  
Servo servoDerecho;

// Definir la configuración de la pantalla OLED
#define SCREEN_WIDTH 128  // Ancho de la pantalla OLED
#define SCREEN_HEIGHT 64  // Alto de la pantalla OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);  // Crear objeto para la pantalla OLED (usando I2C)

// Configuración inicial
void setup() {
  // Inicializar los servos en los pines definidos
  servoIzquierdo.attach(SERVO_IZQUIERDO_PIN);  // Asocia el servo izquierdo al pin PB0
  servoDerecho.attach(SERVO_DERECHO_PIN);  // Asocia el servo derecho al pin PB1

  // Inicializar la comunicación serial para recibir datos del Bluetooth
  Serial.begin(9600);  // Iniciar la comunicación serial a 9600 baudios

  // Inicializar la pantalla OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Comprobar si la pantalla se inicializa correctamente
    Serial.println(F("No se pudo inicializar la pantalla OLED"));
    while (true);  // Detener el código si no se puede inicializar la pantalla
  }

  display.display();  // Mostrar la pantalla (puede ser una imagen de inicio o vacío)
  delay(2000);  // Esperar 2 segundos para ver la pantalla de inicio
  display.clearDisplay();  // Limpiar la pantalla
}

// Bucle principal
void loop() {
  // Verificar si hay datos disponibles del módulo Bluetooth
  if (Serial.available() > 0) {
    char comando = Serial.read();  // Leer el comando enviado desde el Bluetooth

    // Comando '1' para mover hacia adelante
    if (comando == '1') {
      servoIzquierdo.write(180);  // Mover el servo izquierdo hacia adelante
      servoDerecho.write(0);  // Mover el servo derecho hacia adelante
      mostrarOjitos("adelante");  // Mostrar los ojitos mirando al frente
    }
    // Comando '2' para mover a la derecha
    else if (comando == '2') {
      servoIzquierdo.write(0);  // Girar el servo izquierdo a la derecha
      servoDerecho.write(0);  // Girar el servo derecho a la derecha
      mostrarOjitos("derecha");  // Mostrar los ojitos mirando a la derecha
    }
    // Comando '3' para mover a la izquierda
    else if (comando == '3') {
      servoIzquierdo.write(180);  // Girar el servo izquierdo a la izquierda
      servoDerecho.write(180);  // Girar el servo derecho a la izquierda
      mostrarOjitos("izquierda");  // Mostrar los ojitos mirando a la izquierda
    }
    // Comando '4' para detenerse
    else if (comando == '4') {
      servoIzquierdo.write(90);  // Posición de parada (neutral) para el servo izquierdo
      servoDerecho.write(90);  // Posición de parada (neutral) para el servo derecho
      mostrarOjitos("atras");  // Mostrar los ojitos cerrados (><)
    }
  }
}

// Función para dibujar los "ojitos" en la pantalla OLED
void mostrarOjitos(String direccion) {
  display.clearDisplay();  // Limpiar la pantalla antes de dibujar los ojitos
  display.setTextSize(1);  // Establecer tamaño de texto (1x1)
  display.setTextColor(SSD1306_WHITE);  // Establecer color del texto (blanco)

  // Dibujar los ojitos dependiendo de la dirección
  if (direccion == "adelante") {
    // Ojitos mirando al frente
    dibujarOjitos(40, 20, 60);  // Posiciones para los ojos
  }
  else if (direccion == "derecha") {
    // Ojitos mirando hacia la derecha
    dibujarOjitos(30, 20, 100);  // Posiciones para los ojos
  }
  else if (direccion == "izquierda") {
    // Ojitos mirando hacia la izquierda
    dibujarOjitos(30, 20, 20);  // Posiciones para los ojos
  }
  else if (direccion == "atras") {
    // Ojitos cerrados (><)
    display.setCursor(50, 20);  // Posición para los ojitos cerrados
    display.print("><");
  }

  display.display();  // Actualizar la pantalla para mostrar los ojitos
  delay(1000);  // Esperar 1 segundo antes de la siguiente acción
}

// Función para dibujar los ojitos (dos círculos y pupilas)
void dibujarOjitos(int x1, int y1, int x2) {
  display.fillCircle(x1, y1, 8, SSD1306_WHITE);  // Primer ojo
  display.fillCircle(x2, y1, 8, SSD1306_WHITE);  // Segundo ojo

  display.fillCircle(x1, y1, 3, SSD1306_BLACK);  // Pupila del primer ojo
  display.fillCircle(x2, y1, 3, SSD1306_BLACK);  // Pupila del segundo ojo
}