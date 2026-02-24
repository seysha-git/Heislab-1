// Lage et set som tar inn bestillinger fra knapper
// Dersom noen skal opp, legges dere etasje i et set
// Dersom noen skal ned, legges deres etasje * -1 i samme set

// Sender heis til nærmeste etasje i retning heisen er på vei hvor det er lagt inn bestilling

// Skal finne neste etasje som skal hente opp folk

// Om utfører bestilling: må først gjøre ferdig bestillingen (dra opp eller ned én etasje), deretter gå til neste etasje
// Må sjekke om etasjen er den man skal til i bestillingen

#include "bestillinger.h"

void outside_addtoorders(int outsideorders[], int floor, ButtonType btn){
    if(btn == 0){
        switch (floor)
        {
        case 1:
            outsideorders[0] == 1;
            break;
        case 2:
            outsideorders[2] == 1;
            break;
        case 3: 
            outsideorders[4] == 1;
        default:
            break;
        }}
    if (btn == 1){
        switch (floor)
        {
        case 1:
            outsideorders[1] == 1;
            break;
        case 2:
            outsideorders[3] == 1;
            break;
        case 3: 
            outsideorders[5] == 1;
        default:
            break;
        }
    }
    return;
}

void outside_ordercomplete(int outsideorders[], int floor, MotorDirection dir){
    if(dir == -1){
        switch (floor)
        {
        case 1:
            outsideorders[0] == 0;
            break;
        case 2:
            outsideorders[2] == 0;
            break;
        case 3: 
            outsideorders[4] == 0;
        default:
            break;
        }}
    if (dir == -1){
        switch (floor)
        {
        case 1:
            outsideorders[1] == 0;
            break;
        case 2:
            outsideorders[3] == 0;
            break;
        case 3: 
            outsideorders[5] == 0;
        default:
            break;
        }
    }
    return;
}

void inside_addtoorders(int insideorders[], int floor){
    insideorders[floor] = 1;
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

void switch_dir_check(int outsideorders[], int insideorders[], int currentfloor, MotorDirection dir){
    int onitswayto[4];
    switch (dir)
    {
    case -1:
        if(outsideorders[0] == 1 || insideorders[0] = 1){onitswayto[0] = 1}
        if(outsideorders[2] == 1 || insideorders[1] = 1){onitswayto[1] = 1}
        if(outsideorders[4] == 1 || insideorders[2] = 1){onitswayto[2] = 1}
        for(int i = 0; i<=currentfloor-1; i++){
            if(onitsway[i] == 1){return;}
            dir = 1;
            return;
        }
        break;
    case 1:
        if(outsideorders[1] == 1 || insideorders[1] = 1){onitswayto[1] = 1}
        if(outsideorders[3] == 1 || insideorders[2] = 1){onitswayto[2] = 1}
        if(outsideorders[5] == 1 || insideorders[3] = 1){onitswayto[3] = 1}
        for(int i = 5; i>=currentfloor-1; i--){
            if(onitsway[i] == 1){return;}
            dir = -1;
            return;
        }
    default:
        break;
    } 


}
