/*==========================================================
  4-Way Traffic Light Control System (SEQUENTIAL, ONE DIRECTION AT A TIME)
  MCU: PIC16F877A | COMPILER: mikroC PRO | CLOCK: 4 MHz

  PORTB (RB0-RB6) = shared 7-seg bus (a..g)
  PORTD (RD0-RD7) = digit-select, 2 per direction
     RD0/RD1 = North tens/ones   RD2/RD3 = East tens/ones
     RD4/RD5 = South tens/ones   RD6/RD7 = West tens/ones
  RE0 = tied LOW, feeds unused D1/D2 mux pins on all 4 displays

  LEDs:
     North RC0/RC1/RC2   East RC3/RC4/RC5
     South RC6/RC7/RA0   West RA1/RA2/RA3

  Sequence: N green->yellow, E green->yellow, S green->yellow,
  W green->yellow, repeat. Only one direction green/yellow at
  a time; the other three stay red and count down to their turn.
==========================================================*/

#define T_GREEN_N   20
#define T_GREEN_E   20
#define T_GREEN_S   20
#define T_GREEN_W   20
#define T_YELLOW     3

#define D_N_TENS  0
#define D_N_ONES  1
#define D_E_TENS  2
#define D_E_ONES  3
#define D_S_TENS  4
#define D_S_ONES  5
#define D_W_TENS  6
#define D_W_ONES  7

#define DIR_N 0
#define DIR_E 1
#define DIR_S 2
#define DIR_W 3

sbit N_RED at RC0_bit;
sbit N_YEL at RC1_bit;
sbit N_GRN at RC2_bit;

sbit E_RED at RC3_bit;
sbit E_YEL at RC4_bit;
sbit E_GRN at RC5_bit;

sbit S_RED at RC6_bit;
sbit S_YEL at RC7_bit;
sbit S_GRN at RA0_bit;

sbit W_RED at RA1_bit;
sbit W_YEL at RA2_bit;
sbit W_GRN at RA3_bit;

sbit TIE_LOW at RE0_bit;

const unsigned short seg_table[10] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

unsigned short digit_values[8];
int remaining[4];
unsigned short green_time[4] = { T_GREEN_N, T_GREEN_E, T_GREEN_S, T_GREEN_W };
unsigned short cycle_total;
unsigned short cur_dir;
unsigned short cur_state;   // 0 = GREEN, 1 = YELLOW

void Display_Digit(unsigned short index) {
    PORTD = 0;
    PORTB = seg_table[digit_values[index]] & 0x7F;
    PORTD = (1 << index);
    Delay_ms(1);
    PORTD = 0;
}

void Show_1Sec() {
    unsigned short loop, d;
    for (loop = 0; loop < 125; loop++) {
        for (d = 0; d < 8; d++) {
            Display_Digit(d);
        }
    }
}

void Update_Digits() {
    digit_values[D_N_TENS] = remaining[DIR_N] / 10;
    digit_values[D_N_ONES] = remaining[DIR_N] % 10;
    digit_values[D_E_TENS] = remaining[DIR_E] / 10;
    digit_values[D_E_ONES] = remaining[DIR_E] % 10;
    digit_values[D_S_TENS] = remaining[DIR_S] / 10;
    digit_values[D_S_ONES] = remaining[DIR_S] % 10;
    digit_values[D_W_TENS] = remaining[DIR_W] / 10;
    digit_values[D_W_ONES] = remaining[DIR_W] % 10;
}

void Set_Lights(unsigned short dir, unsigned short state) {
    N_RED = 1; N_YEL = 0; N_GRN = 0;
    E_RED = 1; E_YEL = 0; E_GRN = 0;
    S_RED = 1; S_YEL = 0; S_GRN = 0;
    W_RED = 1; W_YEL = 0; W_GRN = 0;

    switch (dir) {
        case DIR_N:
            if (state == 0) { N_RED = 0; N_GRN = 1; }
            else            { N_RED = 0; N_YEL = 1; }
            break;
        case DIR_E:
            if (state == 0) { E_RED = 0; E_GRN = 1; }
            else            { E_RED = 0; E_YEL = 1; }
            break;
        case DIR_S:
            if (state == 0) { S_RED = 0; S_GRN = 1; }
            else            { S_RED = 0; S_YEL = 1; }
            break;
        case DIR_W:
            if (state == 0) { W_RED = 0; W_GRN = 1; }
            else            { W_RED = 0; W_YEL = 1; }
            break;
    }
}

void main() {
    unsigned short i;

    ADCON1 = 0x06;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISA = 0x00;
    TRISE = 0x00;

    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTA = 0;
    TIE_LOW = 0;

    cycle_total = T_GREEN_N + T_GREEN_E + T_GREEN_S + T_GREEN_W + 4 * T_YELLOW;

    cur_dir   = DIR_N;
    cur_state = 0;
    remaining[DIR_N] = T_GREEN_N;
    remaining[DIR_E] = T_GREEN_N + T_YELLOW;
    remaining[DIR_S] = remaining[DIR_E] + T_GREEN_E + T_YELLOW;
    remaining[DIR_W] = remaining[DIR_S] + T_GREEN_S + T_YELLOW;

    while (1) {
        Set_Lights(cur_dir, cur_state);
        Update_Digits();
        Show_1Sec();

        for (i = 0; i < 4; i++) {
            remaining[i]--;
        }

        if (remaining[cur_dir] <= 0) {
            if (cur_state == 0) {
                cur_state = 1;
                remaining[cur_dir] = T_YELLOW;
            } else {
                remaining[cur_dir] = cycle_total - green_time[cur_dir] - T_YELLOW;
                cur_dir   = (cur_dir + 1) % 4;
                cur_state = 0;
                remaining[cur_dir] = green_time[cur_dir];
            }
        }
    }
}