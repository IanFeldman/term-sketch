#include "touchscreen.h"

void TOUCH_Init() {
    // PB6 : SCL
    // PB7 : SDA

    // enable GPIO clock
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    // alternate function mode
    GPIOB->MODER &= ~(GPIO_MODER_MODE6_Msk | GPIO_MODER_MODE7_Msk);
    GPIOB->MODER |= (GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1);
    // open-drain
    GPIOB->OTYPER |= (GPIO_OTYPER_OT6 | GPIO_OTYPER_OT7);
    // high speed
    GPIOB->OSPEEDR |= (GPIO_OSPEEDR_OSPEED6_Msk | GPIO_OSPEEDR_OSPEED7_Msk);
    // pull up resistors
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD6_Msk | GPIO_PUPDR_PUPD7_Msk);
    GPIOB->PUPDR |= (GPIO_PUPDR_PUPD6_0 | GPIO_PUPDR_PUPD7_0);
    // set alternate function
    GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL6_Msk | GPIO_AFRL_AFSEL7_Msk);
    GPIOB->AFR[0] |= (4 << GPIO_AFRL_AFSEL6_Pos) | (4 << GPIO_AFRL_AFSEL7_Pos);
    // enable I2C clock
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN;
    // disable before start
    I2C1->CR1 &= ~I2C_CR1_PE;
    // configure I2C1 timing
    I2C1->TIMINGR = TIMING_FACTOR;
    // set up filters
    I2C1->CR1 &= ~I2C_CR1_ANFOFF;
    I2C1->CR1 &= ~I2C_CR1_DNF_Msk;
    // no stretch
    I2C1->CR1 &= ~I2C_CR1_NOSTRETCH;
    // re-enable
    I2C1->CR1 |= I2C_CR1_PE;
}

void TOUCH_Read(status_t *status) {
    // autoend
    I2C1->CR1 |= (I2C_CR2_AUTOEND);
    // 7 bit address
    I2C1->CR2 &= ~(I2C_CR2_ADD10);
    // set peripheral address
    I2C1->CR2 &= ~(I2C_CR2_SADD);
    I2C1->CR2 |= (DEVICE_ADDRESS << 1);
    // read
    I2C1->CR2 |= (I2C_CR2_RD_WRN);
    // read 9 bytes (register address)
    I2C1->CR2 &= ~(I2C_CR2_NBYTES);
    I2C1->CR2 |= (9 << I2C_CR2_NBYTES_Pos);
    // start
    I2C1->CR2 |= (1 << I2C_CR2_START_Pos);

    // wait for flag
    while(!(I2C1->ISR & I2C_ISR_RXNE));
    uint8_t data0 = I2C1->RXDR;
    while(!(I2C1->ISR & I2C_ISR_RXNE));
    uint8_t data1 = I2C1->RXDR;
    while(!(I2C1->ISR & I2C_ISR_RXNE));
    uint8_t data2 = I2C1->RXDR;
    while(!(I2C1->ISR & I2C_ISR_RXNE));
    uint8_t data3 = I2C1->RXDR;
    while(!(I2C1->ISR & I2C_ISR_RXNE));
    uint8_t data4 = I2C1->RXDR;
    while(!(I2C1->ISR & I2C_ISR_RXNE));
    uint8_t data5 = I2C1->RXDR;
    while(!(I2C1->ISR & I2C_ISR_RXNE));
    uint8_t data6 = I2C1->RXDR;
    while(!(I2C1->ISR & I2C_ISR_RXNE));
    uint8_t data7 = I2C1->RXDR;
    while(!(I2C1->ISR & I2C_ISR_RXNE));
    uint8_t data8 = I2C1->RXDR;

    // update status
    status->update = data2;
    status->pos_v  = data4;
    status->pos_h  = (data5 << 8) + data6;
}
