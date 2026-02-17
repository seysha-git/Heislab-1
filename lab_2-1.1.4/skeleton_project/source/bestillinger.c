// Lage et set som tar inn bestillinger fra knapper
// Dersom noen skal opp, legges dere etasje i et set
// Dersom noen skal ned, legges deres etasje * -1 i samme set

// Sender heis til nærmeste etasje i retning heisen er på vei hvor det er lagt inn bestilling

// Skal finne neste etasje som skal hente opp folk

// Om utfører bestilling: må først gjøre ferdig bestillingen (dra opp eller ned én etasje), deretter gå til neste etasje
// Må sjekke om etasjen er den man skal til i bestillingen

#include "bestillinger.h"

void outside_addtoorders(int outsideorders[], int floor){
    outsideorders[floor-1] = 1;
}

void outside_ordercomplete(int outsideorders[], int floor){
    outsideorders[floor-1] = 0;
}

void inside_addtoorders(int insideorders[], int floor){

}

int getnextfloor(MotorDirection motordir, int currentfloor, int outsideorders[], int insideorders[]){
    if(motordir = 1){}
    int targetfloor;
    int nextfloor;

    for(int i = 0 ; i<=5; i++) {
        if(i == 0){targetfloor = 1;}
        if(i == 1 || i == 2){targetfloor = 2;}
        if(i == 3 || i == 4){targetfloor = 3;}
        if(i == 5){targetfloor = 5;}

        if((motordir == 1 && targetfloor <= currentfloor) || (motordir == -1 && targetfloor >= currentfloor)){
            continue;
        if((motordir == 1 && targetfloor > currentfloor) || (motordir == -1 && targetfloor < currentfloor)){
                if (outsideorders[i] == 1){nextfloor = targetfloor;}
            } 
        }       
    }
    if(motordir == 1){
        for(int i = 0; i <= 4, i++){
            if((i > currentfloor) && (insideorders[i] == 1) && (i < nextfloor)){i = nextfloor;}
        }
    }
}

