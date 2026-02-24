// #include "bestillinger.h"


// void outside_addtoorders(int outsideorders[], int floor, ButtonType btn){
//     if(btn == 0){
//         switch (floor)
//         {
//         case 1:
//             outsideorders[0] == 1;
//             break;
//         case 2:
//             outsideorders[2] == 1;
//             break;
//         case 3: 
//             outsideorders[4] == 1;
//         default:
//             break;
//         }}
//     if (btn == 1){
//         switch (floor)
//         {
//         case 1:
//             outsideorders[1] == 1;
//             break;
//         case 2:
//             outsideorders[3] == 1;
//             break;
//         case 3: 
//             outsideorders[5] == 1;
//         default:
//             break;
//         }
//     }
//     return;
// }

// void outside_ordercomplete(int outsideorders[], int floor, MotorDirection dir){
//     if(dir == -1){
//         switch (floor)
//         {
//         case 1:
//             outsideorders[0] == 0;
//             break;
//         case 2:
//             outsideorders[2] == 0;
//             break;
//         case 3: 
//             outsideorders[4] == 0;
//         default:
//             break;
//         }}
//     if (dir == -1){
//         switch (floor)
//         {
//         case 1:
//             outsideorders[1] == 0;
//             break;
//         case 2:
//             outsideorders[3] == 0;
//             break;
//         case 3: 
//             outsideorders[5] == 0;
//         default:
//             break;
//         }
//     }
//     return;
// }

// void inside_addtoorders(int insideorders[], int floor){
//     insideorders[floor] = 1;
// }

// int getnextfloor(MotorDirection motordir, int currentfloor, int outsideorders[], int insideorders[]){
//     int targetfloorout;
//     int nextfloorout, nextfloorin = 0;
//     int nextfloor = currentfloor;
//     int emptylistout[6];
//     int emptylistin[4];

//     // sjekk om listene er tomme
//     if(outsideorders == emptylistout && insideorders == emptylistin){return currentfloor;}

    
//     // finn neste etasje fra knapp som trykkes utenfor heisen
//     for(int i = 0 ; i<=5; i++) {
//         if(i == 0){targetfloorout = 1;}
//         if(i == 1 || i == 2){targetfloorout = 2;}
//         if(i == 3 || i == 4){targetfloorout = 3;}
//         if(i == 5){targetfloorout = 5;}
//         switch (motordir)
//         {
//         case -1: 
//             if(targetfloorout <= currentfloor){
//                 if ((outsideorders[i] == 1) && (targetfloorout > nextfloorout)){nextfloorout = targetfloorout;}
//             }                    
//             break;
//         case 0:
//             if(targetfloorout == currentfloor){return currentfloor}
//             if(outsideorders[i] == 1){
//                 if(abs(currentfloor - targetfloorout) <= abs(currentfloor - nextfloorout)){
//                     nextfloorout = targetfloor;
//                 }
//             };            
//             break;
//         case 1:
//             if(targetfloorout >= currentfloor){
//                 if ((outsideorders[i] == 1) && (targetfloorout < nextfloorout)){nextfloorout = targetfloorout;}
//             }            
//             break;
//         default:
//             break;
//         }      
//     }

//     //sjekker innsiden
//     for(int i = 1; i<=4; i++){
//     switch (motordir)
//     {
    
//     case 1: 
//         if((insideorders[i] == 1) && (i < nextfloorin) && (i >= currentfloor)){nextfloorin = i;}
//         break;
//     case 0:
//         if(i == currentfloor){return currentfloor}
//         if((insideorders[i] == 1 && nextfloorin != currentfloor)){
//             if(abs(currentfloor-i) <= abs(currentfloor - nextfloorin)){nextfloorin = i;}
//         break;
//     case -1:
//         if((insideorders[i] == 1) && (i > nextfloorin) && (i <= currentfloor)){nextfloorin = i;}
//         break;
    
//     default:
//         break;
//     }}


//     if(nextfloorout-nextfloorin <= 0){
//         nextfloor = nextfloorout;
//     }
//     if(nextfloorout - nextfloorin > 0){
//         nextfloor = nextfloorin;
//     }

//     return nextfloor;
// }

// void switch_dir_check(int outsideorders[], int insideorders[], int currentfloor, MotorDirection dir){
//     int onitswayto[4];
//     switch (dir)
//     {
//     case -1:
//         if(outsideorders[0] == 1 || insideorders[0] = 1){onitswayto[0] = 1}
//         if(outsideorders[2] == 1 || insideorders[1] = 1){onitswayto[1] = 1}
//         if(outsideorders[4] == 1 || insideorders[2] = 1){onitswayto[2] = 1}
//         for(int i = 0; i<=currentfloor-1; i++){
//             if(onitsway[i] == 1){return;}
//             dir = 1;
//             return;
//         }
//         break;
//     case 1:
//         if(outsideorders[1] == 1 || insideorders[1] = 1){onitswayto[1] = 1}
//         if(outsideorders[3] == 1 || insideorders[2] = 1){onitswayto[2] = 1}
//         if(outsideorders[5] == 1 || insideorders[3] = 1){onitswayto[3] = 1}
//         for(int i = 5; i>=currentfloor-1; i--){
//             if(onitsway[i] == 1){return;}
//             dir = -1;
//             return;
//         }
//     default:
//         break;
//     } 


// }


#include <stdbool.h>
#include <stdlib.h>     // abs
#include "bestillinger.h"

// Intern ordretilstand
static bool orders[N_FLOORS][N_BUTTONS];

static bool is_valid_hall_button(int floor, ButtonType btn){
    if(btn == BUTTON_HALL_UP)   return floor < (N_FLOORS - 1);
    if(btn == BUTTON_HALL_DOWN) return floor > 0;
    return true; // cab alltid gyldig
}

static bool any_above(int floor){
    for(int f = floor + 1; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            if(orders[f][b]) return true;
        }
    }
    return false;
}

static bool any_below(int floor){
    for(int f = 0; f < floor; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            if(orders[f][b]) return true;
        }
    }
    return false;
}

static bool any_here(int floor){
    for(int b = 0; b < N_BUTTONS; b++){
        if(orders[floor][b]) return true;
    }
    return false;
}

static int nearest_order_floor(int currentFloor){
    int bestFloor = -1;
    int bestDist  = 999;

    for(int f = 0; f < N_FLOORS; f++){
        if(!any_here(f)) continue;
        int d = abs(currentFloor - f);
        if(d < bestDist){
            bestDist = d;
            bestFloor = f;
        }
    }
    return bestFloor;
}

void orders_init(void){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            orders[f][b] = false;
        }
    }
}

void orders_clear_all(void){
    orders_init();
}

void orders_clear_at_floor(int floor){
    if(floor < 0 || floor >= N_FLOORS) return;
    for(int b = 0; b < N_BUTTONS; b++){
        orders[floor][b] = false;
    }
}

bool orders_add(int floor, ButtonType btn){
    if(floor < 0 || floor >= N_FLOORS) return false;
    if(btn < 0 || btn >= N_BUTTONS) return false;

    if(!is_valid_hall_button(floor, btn)) return false;

    orders[floor][btn] = true;
    return true;
}

void orders_poll_buttons(bool ignore){
    if(ignore) return;

    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            ButtonType btn = (ButtonType)b;
            if(!is_valid_hall_button(f, btn)) continue;

            if(elevio_callButton(f, btn)){
                orders[f][btn] = true;
            }
        }
    }
}

bool orders_any(void){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            if(orders[f][b]) return true;
        }
    }
    return false;
}

bool orders_get(int floor, ButtonType btn){
    if(floor < 0 || floor >= N_FLOORS) return false;
    if(btn < 0 || btn >= N_BUTTONS) return false;
    if(!is_valid_hall_button(floor, btn)) return false;
    return orders[floor][btn];
}

bool orders_should_stop(int floor, MotorDirection dir){
    if(floor < 0 || floor >= N_FLOORS) return false;

    // Cab: alltid stopp
    if(orders[floor][BUTTON_CAB]) return true;

    // Står stille -> stopp hvis noe i etasjen
    if(dir == DIRN_STOP){
        return orders[floor][BUTTON_HALL_UP] || orders[floor][BUTTON_HALL_DOWN];
    }

    if(dir == DIRN_UP){
        if(orders[floor][BUTTON_HALL_UP]) return true;
        if(orders[floor][BUTTON_HALL_DOWN] && !any_above(floor)) return true;
        return false;
    }

    if(dir == DIRN_DOWN){
        if(orders[floor][BUTTON_HALL_DOWN]) return true;
        if(orders[floor][BUTTON_HALL_UP] && !any_below(floor)) return true;
        return false;
    }

    return false;
}

MotorDirection orders_next_dir(int currentFloor, MotorDirection currentDir){
    if(!orders_any()) return DIRN_STOP;
    if(currentFloor < 0 || currentFloor >= N_FLOORS) return DIRN_STOP;

    if(currentDir == DIRN_UP){
        if(any_above(currentFloor)) return DIRN_UP;
        if(any_below(currentFloor)) return DIRN_DOWN;
        return DIRN_STOP;
    }

    if(currentDir == DIRN_DOWN){
        if(any_below(currentFloor)) return DIRN_DOWN;
        if(any_above(currentFloor)) return DIRN_UP;
        return DIRN_STOP;
    }

    // DIRN_STOP: velg retning mot nærmeste ordre
    int target = nearest_order_floor(currentFloor);
    if(target < 0) return DIRN_STOP;
    if(target > currentFloor) return DIRN_UP;
    if(target < currentFloor) return DIRN_DOWN;
    return DIRN_STOP;
}

int orders_next_stop_floor(int currentFloor, MotorDirection currentDir){
    if(!orders_any()) return -1;
    if(currentFloor < 0 || currentFloor >= N_FLOORS) return -1;

    if(orders_should_stop(currentFloor, currentDir)) return currentFloor;

    if(currentDir == DIRN_STOP){
        return nearest_order_floor(currentFloor);
    }

    if(currentDir == DIRN_UP){
        for(int f = currentFloor + 1; f < N_FLOORS; f++){
            if(orders_should_stop(f, DIRN_UP)) return f;
        }
        for(int f = currentFloor - 1; f >= 0; f--){
            if(orders_should_stop(f, DIRN_DOWN)) return f;
        }
        return -1;
    }

    if(currentDir == DIRN_DOWN){
        for(int f = currentFloor - 1; f >= 0; f--){
            if(orders_should_stop(f, DIRN_DOWN)) return f;
        }
        for(int f = currentFloor + 1; f < N_FLOORS; f++){
            if(orders_should_stop(f, DIRN_UP)) return f;
        }
        return -1;
    }

    return -1;
}
