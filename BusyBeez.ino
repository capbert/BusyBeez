#include <MIDI.h>
// #include <midi_Defs.h>
// #include <midi_Namespace.h>
// #include <midi_Settings.h>

#include "SimpleTimer.h"

#include "BBConstants.h"
#include "BBsample.h"
#include "BBSensor.h"
#include "BBFlower.h"







RoomState roomState = ROOM_STATE_INACTIVE;

int roomSensePin = 2;                                                   //motion sensor digital pin def
int proxSensePin1 = 1;                                                  //proximity sensor analog pin def
static const int NUM_FLOWER_SAMPLES = 7;
static const int NUM_FLOWERS = 2;
static const int NUM_AMBIENCE_SAMPLES = 2;
// Samples
static BBSample g_flowerSamples[] = {
  BBSample(1, 12, "Red Wing Blackbird"),
  BBSample(2, 13, "Mourning Dove"),
  BBSample(3, 14, "Black Throated Green Warbler"),
  BBSample(4, 15, "Bluebird"),
  BBSample(5, 16, "Robin"),
  BBSample(6, 17, "Catbird"),
  BBSample(7, 18, "GoldFinch"),
  BBSample(8, 19, "White Throated Sparrow"),
  BBSample(9, 20, "Yellow Throated Warbler"),
  BBSample(10, 21, "Black Throated Blue Warbler"),
  BBSample(11, 22, "Nashville Warbler"),
  BBSample(12, 23, "Phoebe")
};

static BBSample g_ambienceSamples[] = {
  BBSample(15, 24, "Field"),
  BBSample(16, 25, "Bees")
};




// Sensors
BBSensor roomMotionSensor(BBSensor::DIGITAL);


BBSensor proxSensor0(BBSensor::ANALOG);
BBSensor proxSensor1(BBSensor::ANALOG);
BBSensor proxSensor2(BBSensor::ANALOG);
BBSensor proxSensor3(BBSensor::ANALOG);
BBSensor proxSensor4(BBSensor::ANALOG);
BBSensor proxSensor5(BBSensor::ANALOG);


// Flowers

BBFlower g_flowers[NUM_FLOWERS] = {
  BBFlower(g_flowerSamples, NUM_FLOWER_SAMPLES),
  BBFlower(g_flowerSamples, NUM_FLOWER_SAMPLES),
  // BBFlower(g_flowerSamples, NUM_FLOWERS),
  // BBFlower(g_flowerSamples, NUM_FLOWERS),
  // BBFlower(g_flowerSamples, NUM_FLOWERS),
  // BBFlower(g_flowerSamples, NUM_FLOWERS)
  };



void setup(){
  // timer.setInterval(500, testFn);

  MIDI.begin(115200);
  Serial.begin(115200);


  roomMotionSensor.setPin(roomSensePin);
  roomMotionSensor.setInputRange(0,1);
  roomMotionSensor.setOutputRange(0,1);



  proxSensor0.setPin(0);
  proxSensor1.setPin(1);
  // proxSensor2.setPin(2);
  // proxSensor3.setPin(3);
  // proxSensor4.setPin(4);
  // proxSensor5.setPin(5);



  g_flowers[0].setSensor(&proxSensor0);
  g_flowers[1].setSensor(&proxSensor1);
  // g_flowers[2].setSensor(&proxSensor2);
  // g_flowers[3].setSensor(&proxSensor3);
  // g_flowers[4].setSensor(&proxSensor4);
  // g_flowers[5].setSensor(&proxSensor5);


}

void loop(){


  checkRoomState();

  if(roomState == ROOM_STATE_ACTIVE){
    updateFlowers();
  }

  delay(1000);
}


void updateFlowers(){
  for( int i = 0; i<NUM_FLOWERS; i++){

    // Serial.print("Updating flower at index: ");
    // Serial.println(i);

    g_flowers[i].update();
  }
}

void checkRoomState(){
  // poll room sensors... only one right now
  int sensorVal = roomMotionSensor.read();
  // Serial.println(F("read room sensor"));
  // Serial.println(sensorVal);
  // Serial.println(roomState == ROOM_STATE_ACTIVE);



  if (roomState == ROOM_STATE_ACTIVE){
    // sensor is off and room is active so turn it off
    if (sensorVal == -1){
      // Serial.println(F("room is active and sensor is off"));
      deactivateRoom();
    }
  }else if (roomState == ROOM_STATE_INACTIVE){
    // sensor is on and room is inactive
    if(sensorVal == 1)
      activateRoom();
  }

}

void activateFlowers(){
  for(int i = 0; i< NUM_FLOWERS; i++){
    g_flowers[i].enable();
  }
}

void deactivateFlowers(){
  for(int i = 0; i< NUM_FLOWERS; i++){
    g_flowers[i].disable();
  }
}

void deactivateRoom(){
  Serial.println(F("--- deactivate room\n ---"));
  setRoomState(ROOM_STATE_INACTIVE);

  deactivateFlowers();
  triggerRoomAmbienceOff();
}

void activateRoom(){
  Serial.println(F("--- activate room\n ---"));
  setRoomState(ROOM_STATE_ACTIVE);
  activateFlowers();
  triggerRoomAmbienceOn();

}

void setRoomState(RoomState state){
  // Not sure if more needs to happen to set room state --- so I abstracted it.
  roomState = state;
}

void triggerRoomAmbienceOn(){
  // trigger midi on
  for(int i = 0; i < NUM_AMBIENCE_SAMPLES; i++){
    g_ambienceSamples[i].triggerOn(); 
  }
}

void triggerRoomAmbienceOff(){
  // trigger midi off
  for(int i = 0; i < NUM_AMBIENCE_SAMPLES; i++){
    g_ambienceSamples[i].triggerOff(); 
  }
}




/*

Chris' orininal code for reference



*/



  // int val1 = digitalRead(roomSensePin);                                 //initialize variables to hold the read each time through loop
  // int val2 = analogRead(proxSensePin1);

  // if( roomState == 1 ){                                                 //if the room is full
  //     if(val1 == LOW){                                                  //if the motion sensor sees nothing
  //         roomState = 0;                                                //set state to empty
  //         MIDI.sendNoteOn(20, 0, 9);                                    //turn off motion sensor sound: really should send an ALL OFF here.
  //      }

  //      if ( (val2 >= 300) && (proxSenseState1 !=1) ){                   //if prox sensor sees useful value (really should be 50ish, not 300)
  //         proxSenseState1 = 1;                                          //set prox sensor state to engaged
  //         MIDI.sendNoteOn(14, 75, 9);                                   //play sound for this prox sensor
  //      }
       
  //      if( (val2 < 300) && (proxSenseState1 == 1) ){                    //if prox sensor was engaged, but now value too low
  //         MIDI.sendNoteOn(14, 0, 9);                                    //stop sound from playing
  //         proxSenseState1 = 0;                                          //set prox sensor state to NOT engaged
  //      }
  // }
  // else{                                                                 //else, room is empty, let's check to see if full                                                                 
  //     if(val1 == HIGH){                                                 //if room full
  //         roomState = 1;                                                //set room state to full
  //         MIDI.sendNoteOn(20, 75, 9);                                   //play the room ambience sounds
  //     }
  // }


/*

END REFERENCE

*/