#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/startup.h"



int main(){
    elevio_init();

    orders_init();

    MotorDirection dir = DIRN_STOP;

    while(1){

        // 1️⃣ Les nye knapper og legg inn ordre
        orders_poll_buttons(false);

        // 2️⃣ Oppdater bestillingslys
        lights_set_order_lamps_from_orders();

        // 3️⃣ Les etasjesensor
        int floor = elevio_floorSensor();

        if(floor != -1){
            lights_set_floor_indicator(floor);

            // 4️⃣ Sjekk om vi skal stoppe her
            if(orders_should_stop(floor, dir)){
                elevio_motorDirection(DIRN_STOP);
                orders_clear_at_floor(floor);

                lights_set_door_open_lamp(true);
                // Her bør du egentlig ha en 3 sek timer
            }
        }

        // 5️⃣ Velg ny retning hvis vi ikke stopper
        dir = orders_next_dir(floor, dir);
        elevio_motorDirection(dir);
    }
    // printf("=== Example Program ===\n");
    // printf("Press the stop button on the elevator panel to exit\n");
    // while(startup()!=true){}

    // while(1){
    //     int floor = elevio_floorSensor();

    //     if(floor == 0){
    //         elevio_motorDirection(DIRN_UP);
    //     }

    //     if(floor == N_FLOORS-1){
    //         elevio_motorDirection(DIRN_DOWN);
    //     }


    //     for(int f = 0; f < N_FLOORS; f++){
    //         for(int b = 0; b < N_BUTTONS; b++){
    //             int btnPressed = elevio_callButton(f, b);
    //             elevio_buttonLamp(f, b, btnPressed);
    //         }
    //     }

    //     if(elevio_obstruction()){
    //         elevio_stopLamp(1);
    //     } else {
    //         elevio_stopLamp(0);
    //     }
        
    //     if(elevio_stopButton()){
    //         elevio_motorDirection(DIRN_STOP);
    //         break;
    //     }
        
    //     nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    // }

    return 0;
}
