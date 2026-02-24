#pragma once
#include <stdbool.h>
#include "driver/elevio.h"

// Init/clear
void orders_init(void);
void orders_clear_all(void);
void orders_clear_at_floor(int floor);

// Innlegging
bool orders_add(int floor, ButtonType btn);
void orders_poll_buttons(bool ignore);

// Spørringer
bool orders_any(void);
bool orders_should_stop(int floor, MotorDirection dir);
MotorDirection orders_next_dir(int currentFloor, MotorDirection currentDir);
int orders_next_stop_floor(int currentFloor, MotorDirection currentDir);

// For lysmodulen (lese ordrestatus uten å kunne skrive):
bool orders_get(int floor, ButtonType btn);