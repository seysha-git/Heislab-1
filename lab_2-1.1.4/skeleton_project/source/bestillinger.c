// Lage et set som tar inn bestillinger fra knapper
// Dersom noen skal opp, legges dere etasje i et set
// Dersom noen skal ned, legges deres etasje * -1 i samme set

// Sender heis til nærmeste etasje i retning heisen er på vei hvor det er lagt inn bestilling

// Skal finne neste etasje som skal hente opp folk

// Om utfører bestilling: må først gjøre ferdig bestillingen (dra opp eller ned én etasje), deretter gå til neste etasje
// Må sjekke om etasjen er den man skal til i bestillingen

#include "bestillinger.h"

void outside_addtoorders(int outsideorders[], int floor, ButtonType btn){
    if(btn == 1){
        outsideorders[floor*2]
    }
    return;
}

void outside_ordercomplete(int outsideorders[], int floor){
    outsideorders[floor-1] = 0;
}

void inside_addtoorders(int insideorders[], int floor){

}

int getnextfloor(MotorDirection motordir, int currentfloor, int outsideorders[], int insideorders[]){
    int targetfloorout;
    int nextfloorout, nextfloorin = 0;
    int nextfloor = currentfloor;
    int emptylistout[6];
    int emptylistin[4];

    // sjekk om listene er tomme
    if(outsideorders == emptylistout && insideorders == emptylistin){return currentfloor;}

    
    // finn neste etasje fra knapp som trykkes utenfor heisen
    for(int i = 0 ; i<=5; i++) {
        if(i == 0){targetfloorout = 1;}
        if(i == 1 || i == 2){targetfloorout = 2;}
        if(i == 3 || i == 4){targetfloorout = 3;}
        if(i == 5){targetfloorout = 5;}
        switch (motordir)
        {
        case -1: 
            if(targetfloorout <= currentfloor){
                if ((outsideorders[i] == 1) && (targetfloorout > nextfloorout)){nextfloorout = targetfloorout;}
            }                    
            break;
        case 0:
            if(targetfloorout == currentfloor){return currentfloor}
            if(outsideorders[i] == 1){
                if(abs(currentfloor - targetfloorout) <= abs(currentfloor - nextfloorout)){
                    nextfloorout = targetfloor;
                }
            };            
            break;
        case 1:
            if(targetfloorout >= currentfloor){
                if ((outsideorders[i] == 1) && (targetfloorout < nextfloorout)){nextfloorout = targetfloorout;}
            }            
            break;
        default:
            break;
        }      
    }

    //sjekker innsiden
    for(int i = 1; i<=4; i++){
    switch (motordir)
    {
    
    case 1: 
        if((insideorders[i] == 1) && (i < nextfloorin) && (i >= currentfloor)){nextfloorin = i;}
        break;
    case 0:
        if(i == currentfloor){return currentfloor}
        if((insideorders[i] == 1 && nextfloorin != currentfloor)){
            if(abs(currentfloor-i) <= abs(currentfloor - nextfloorin)){nextfloorin = i;}
        break;
    case -1:
        if((insideorders[i] == 1) && (i > nextfloorin) && (i <= currentfloor)){nextfloorin = i;}
        break;
    
    default:
        break;
    }}


    if(nextfloorout-nextfloorin <= 0){
        nextfloor = nextfloorout;
    }
    if(nextfloorout - nextfloorin > 0){
        nextfloor = nextfloorin;
    }

    return nextfloor;
}

