/*. Escriba un programa en C que mida el tiempo
de reacción. Su programa debe medir el tiempo que tarda una persona en activar el
interruptor de la derecha (SW[0]) después de que todos los LEDs se enciendan. Usará la
función rand() de la librería stdlib.h para generar una cantidad aleatoria de tiempo de retardo
entre cada vez que el usuario intente probar su tiempo de reacción.*/

#include <stdlib.h>

#define GPIO_SWs    0x80001400
#define GPIO_LEDs   0x80001404
#define GPIO_INOUT  0x80001408


#define READ_GPIO(dir) (*(volatile unsigned int *)(dir))
#define WRITE_GPIO(dir, value) { (*(volatile unsigned int *)(dir)) = (value); }

void IOsetup();
void playGame();
void delay(__uint32_t num);

int main() {

    IOsetup();
   
    while (1)
    {
        if((READ_GPIO(GPIO_SWs) & 0x1) == 0x1){
            playGame();      
        };
    }

    return 0;
}

void playGame(){
    __uint32_t counter=0;
    __uint8_t fin = 0;
    
    //APAGO LOS LEDS
    WRITE_GPIO(GPIO_LEDs, 0x0);

    // esepero tiempo aleatorio no mayor a 3 seg
    delay(rand() % (3000000+1));
    
    //inicio un contador hasta detectar que baja el sw
    while (fin != 1)
    {
        fin = ((READ_GPIO(GPIO_SWs) & 0x1) == 0x0);
        counter ++;
    };

    //muestro el contador con los leds en binario y por serie
    WRITE_GPIO(GPIO_LEDs, counter);
    printfNexys("Tiempo de reaccion: %d\n", counter);

    return;
}

void IOsetup() {
    int En_value = 0x0000FFFF;
    WRITE_GPIO(GPIO_INOUT, En_value);
}

void delay(__uint32_t num){
    for (volatile int i = 0; i < num; i++)
    {
    }
}