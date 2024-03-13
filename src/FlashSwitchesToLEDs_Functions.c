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
#define DELAY       0x1000000

#define READ_GPIO(dir) (*(volatile unsigned int *)(dir))
#define WRITE_GPIO(dir, value) { (*(volatile unsigned int *)(dir)) = (value); }

void delay(int num);
void IOsetup();

int main() {

    int switches_value;

    IOsetup();
    while(1){
        switches_value = READ_GPIO(GPIO_SWs);
        switches_value = switches_value >> 16;

        WRITE_GPIO(GPIO_LEDs, switches_value);
        delay(DELAY);
    }

}


void IOsetup(){
    int En_Value = 0xFFFF;
    WRITE_GPIO(GPIO_INOUT, En_Value);
}

void delay (int num){
    for (int i = 0; i < num; i++);
}
