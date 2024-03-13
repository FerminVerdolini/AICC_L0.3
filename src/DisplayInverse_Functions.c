/*
    Escriba un programa en C que muestre el valor inverso de los interruptores en
    los LEDs. Por ejemplo, si los interruptores son (en binario): 0101010101010101, 
    entonces los LEDs deberian mostrar: 1010101010101010; si los interruptores son:
    1111000011110000, entonces en los LEDs deberian aparecer: 0000111100001111; y así
    sucesivamente.
*/

#define GPIO_SWs    0x80001400
#define GPIO_LEDs   0x80001404
#define GPIO_INOUT  0x80001408


#define READ_GPIO(dir) (*(volatile unsigned int *)(dir))
#define WRITE_GPIO(dir, value) { (*(volatile unsigned int *)(dir)) = (value); }

void IOsetup();
unsigned int getSwitchesInvert();

int main() {

    int switches_value;

    IOsetup();
    /* Constantemente lee el valor de los switches y desplaza
    ese valor, negado, las posiciones para los leds
    y hace un sleep para mostrar el valor
    */
    while (1)
    {
        switches_value = getSwitchesInvert();
        WRITE_GPIO(GPIO_LEDs, switches_value);
    }

    return 0;
}

unsigned int getSwitchesInvert() {
    return (~READ_GPIO(GPIO_SWs)) >> 16;
}

void IOsetup() {
    int En_value = 0x0000FFFF;
    WRITE_GPIO(GPIO_INOUT, En_value);
}