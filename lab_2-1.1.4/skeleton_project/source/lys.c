// #include "lys.h"

// void floorupdate(int current_floor){
//     if(elevio_floorSensor() != -1){
//         current_floor = elevio_floorSensor();
//     }
// }

// void setlights(MotorDirection dirn, int floor, int ordersinside[], int ordersoutside[]){
//     elevio_floorIndicator(floor);
//     int targetfloor;
//     ButtonType btn;
//     for (int i = 0; i<=5; i++){
//         if(i == 0){targetfloor = 1;}
//         if(i == 1 || i == 2){targetfloor = 2;}
//         if(i == 3 || i == 4){targetfloor = 3;}
//         if(i == 5){targetfloor = 5;}
        
//         if(i == 0 || i == 2 || i == 4){btn = BUTTON_HALL_UP;}
//         if(i == 1 || i == 3 || i == 5){btn = BUTTON_HALL_DOWN;}
//         elevio_buttonLamp(targetfloor, btn, ordersoutside[i]);
//     }
//     for(int i = 0; i<=3; i++){
//         elevio_buttonLamp(i+1, BUTTON_CAB, ordersinside[i]);
//     }

//     if(dirn == 0 && elevio_floorSensor() != -1){
//         elevio_doorOpenLamp(1);
//     }
//     return;
// }


#include "lys.h"
#include "bestillinger.h"

void lights_set_order_lamps_from_orders(void){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            ButtonType btn = (ButtonType)b;

            // orders_get() returnerer false hvis ugyldig hall-knapp i etasjen,
            // så da slår vi bare av lampen.
            bool on = orders_get(f, btn);
            elevio_buttonLamp(f, btn, on ? 1 : 0);
        }
    }
}

void lights_set_floor_indicator(int floor){
    // elevio_floorIndicator forventer 0..N_FLOORS-1
    if(floor >= 0 && floor < N_FLOORS){
        elevio_floorIndicator(floor);
    }
}

void lights_set_stop_lamp(bool on){
    elevio_stopLamp(on ? 1 : 0);
}

void lights_set_door_open_lamp(bool on){
    elevio_doorOpenLamp(on ? 1 : 0);
}
