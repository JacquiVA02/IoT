//se demuestra el manejo del display de siete segmentos

//se declaran los pines a usar
//int LEDs[] = {8,9,7,6,4,3,2};        // for Arduino microcontroller
//int LEDs[] = {D2,D1,D3,D4,D6,D7,D8}; // for ESP8266 microcontroller
int LEDs[] = {22,23,33,25,19,32,12};    // for ESP32 microcontroller

//se declaran los arreglos que forman los dígitos
int zero[] = {1, 1, 1, 1, 1, 1, 0};   // cero
int one[] = {0, 0, 0, 0, 1, 1, 0};   // uno
int two[] = {1, 1, 0, 1, 1, 0, 1};   // dos
int three[] = {1, 1, 1, 1, 0, 0, 1};   // tres
int four[] = {0, 1, 1, 0, 0, 1, 1};   // cuatro 
int five[] = {1, 0, 1, 1, 0, 1, 1};   // cinco
int six[] = {1, 0, 1, 1, 1, 1, 1};   // seis
int seven[] = {1, 1, 1, 0, 0, 0, 0};   // siete
int eight[] = {1, 1, 1, 1, 1, 1, 1}; // ocho
int nine[] = {1, 1, 1, 1, 0, 1, 1};   // nueve
int ten[] = {1, 1, 1, 0, 1, 1, 1};   // diez, A
int eleven[] = {0, 0, 1, 1, 1, 1, 1};   // once, b
int twelve[] = {0, 0, 0, 1, 1, 0, 1};   // doce, C
int thirteen[] = {0, 1, 1, 1, 1, 0, 1};   // trece, d
int fourteen[] = {1, 0, 0, 1, 1, 1, 1};   // catorce, E
int fifteen[] = {1, 0, 0, 0, 1, 1, 1};   // quince, F

//se declara contador
unsigned char contador = 0;

//función que despliega del 0 al F
void segment_display(unsigned char valor)
{
    switch(valor)
    {
        case 0:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], zero[i]);
                    break;
        case 1:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], one[i]);
                    break;
        case 2:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], two[i]);
                    break;
        case 3:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], three[i]);
                    break;
        case 4:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], four[i]);
                    break;
        case 5:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], five[i]);
                    break;
        case 6:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], six[i]);
                    break;
        case 7:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], seven[i]);
                    break;
        case 8:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], eight[i]);
                    break;
        case 9:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], nine[i]);
                    break;
        case 10:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], ten[i]);
                    break;
        case 11:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], eleven[i]);
                    break;
        case 12:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], twelve[i]);
                    break;
        case 13:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], thirteen[i]);
                    break;
        case 14:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], fourteen[i]);
                    break;
        case 15:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], fifteen[i]);
                    break; 
        default:
                    for (int i = 0; i<7; i++) digitalWrite(LEDs[i], zero[i]);
                    break;          
    }
}

void setup() 
{
  //se inicializan los pines como salida
  for (int i = 0; i<7; i++) pinMode(LEDs[i], OUTPUT);
}

void loop() 
{
    //se muestra contador, retardo y se incrementa contador
    segment_display(contador);
    delay(1000);
    if(contador < 15) contador++;
    else contador = 0;
}
