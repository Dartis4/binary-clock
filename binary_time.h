/*
 * binary_time.h
 *
 *  Created on: Mar 22, 2022
 *      Author: Danea
 */

#ifndef BINARY_TIME_H_
#define BINARY_TIME_H_

// Initialize to fill whole display
int hour[2] = { 15, 3 };  // all sets are in {ones, tens} order
int minute[2] = { 15, 7 };
int second[2] = { 15, 7 };

// little-endian
void convert_D_B(int x, int d[4])
{
    d[3] = x % 2; // LSB
    x = x >> 1;
    d[2] = x % 2;
    x = x >> 1;
    d[1] = x % 2;
    x = x >> 1;
    d[0] = x % 2; // MSB
    return;
}

// Reset
void reset_time(void)
{
    // 00:00:00
    hour[0] = 0;
    hour[1] = 0;
    minute[0] = 0;
    minute[1] = 0;
    second[0] = 0;
    second[1] = 0;
    return;
}

// Add hours
void addHour(void)
{
    hour[0]++;
    if (hour[0] > 9)
    {
        hour[0] = 0;
        hour[1]++;
    }
    if (hour[1] * 10 + hour[0] > 23)
        reset_time();
    return;
}

// Add minutes
void addMin(void)
{
    minute[0]++;
    if (minute[0] > 9)
    {
        minute[0] = 0;
        minute[1]++;
    }
    if (minute[1] > 5)
    {
        minute[0] = 0;
        minute[1] = 0;
        addHour();
    }
    return;
}

// Add seconds
void addSec(void)
{
    second[0]++;
    if (second[0] > 9)
    {
        second[0] = 0;
        second[1]++;
    }
    if (second[1] > 5)
    {
        second[0] = 0;
        second[1] = 0;
        addMin();
    }
    return;
}

// Assign val to column
void setHour(int tens, int val)
{
    if (tens && val > 2)
        val = 2;
    hour[tens] = val;
    return;
}

// Assign val to column
void setMinute(int tens, int val)
{
    if (tens && val > 5)
        val = 5;
    minute[tens] = val;
    return;
}

// Assign val to column
void setSecond(int tens, int val)
{
    if (tens && val > 5)
        val = 5;
    second[tens] = val;
    return;
}

// Return time
void time(int time_val[6][4])
{
    convert_D_B(hour[1], time_val[0]);
    convert_D_B(hour[0], time_val[1]);
    convert_D_B(minute[1], time_val[2]);
    convert_D_B(minute[0], time_val[3]);
    convert_D_B(second[1], time_val[4]);
    convert_D_B(second[0], time_val[5]);

    return;
}

#endif /* BINARY_TIME_H_ */
