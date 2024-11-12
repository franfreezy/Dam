
long int damvolumestatus=0;
int tiltsensordata=5;
void damvolume(){
    if((millis()-damvolumestatus)>=5000){
        damvolumestatus=millis();
        int damvolumestate= digitalRead(tiltsensordata);
        Serial.println(damvolumestate);
    }
}