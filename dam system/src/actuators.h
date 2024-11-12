// the spillway and alarm

int spillwayrelay=6;
int alarmrelay=22;

void triggerSpillway(){
    digitalWrite(spillwayrelay,HIGH);
}

void triggeralarm(){
    digitalWrite(spillwayrelay,HIGH);
}