#include "ecs36b_Common.h"
#include "Person.h"
#include "JvTime.h"
#include "GPS_DD.h"
#include "Thing.h"
#include "Record.h"
    Record::Record(){}

    Record::Record(Person person, Thing thing1){
        this->person1 = person;
        this->thing1 = thing1;
    }
    Record::Record(Person person, Person person2,Thing thing1, Thing thing2){
        this->person1 = person;
        this->person2 = person2;
        this->thing1 = thing1;
        this->thing2 = thing2;  
    }
    Record::Record(Person person, Person person2, GPS_DD location){
        this->person1 = person;
        this->person2 = person2;
        this->location = location;
    }

    Record::Record(Person person,GPS_DD location, Thing thing1, Thing thing2,Thing thing3){
        this->person1 = person;
        this->location = location;
        this->thing1 = thing1;
        this->thing2 = thing2;
        this->thing3 = thing3;
    }

    void Record::setTime(char * time)
    {
    this->time = JvTime(time);
    }

    void Record::setEventDescription(string event){
        this->eventDescription = event;
    }
    
    Json::Value Record::dump2JSON(){ // need to edit this

    Json::Value result { };
    Json::Value jv_result;
    
    result["Event description"] = this->eventDescription;

    jv_result = this->person1.dump2JSON();
    result["Person1"] = jv_result;

    if(this->person2.name!=""){
    jv_result = this->person2.dump2JSON();
    result["Person2"] = jv_result;
    }

    jv_result = (this->location).dump2JSON();
    result["Location"] = jv_result;

    if(thing1.thingName!=""){
    jv_result = (this->thing1).dump2JSON();
    result["Thing 1"] = jv_result;
    }
    
    if(thing2.thingName!=""){
    jv_result = (this->thing2).dump2JSON();
    result["Thing 2"] = jv_result;
    }

    if(thing3.thingName!=""){
    jv_result = (this->thing3).dump2JSON();
    result["Thing 3"] = jv_result;
    }

    
    jv_result = (this->time).dump2JSON();
    result["Time"] = jv_result;
    
  return result;
}

bool Record::JSON2Object(Json::Value jsonVal){
    /* string s = jsonVal.toStyledString();
    if(s.find("Person1:")>=0){
        
    }
    */

    Json::Value temp;
    temp = jsonVal["Person1"];
    this->person1.setName(temp["Name"].asString());

    temp = jsonVal["Person2"];
    this->person2.setName(temp["Name"].asString());

    temp = jsonVal["Event description"];
    this->eventDescription = temp.asString();

    temp = jsonVal["Location"];
    this->location.setLocationName(temp["Location Name"].asString());

    temp = jsonVal["Thing 1"];
    this->thing1.thingName = temp["Thing Name"].asString();

    temp = temp["Location"];
    this->thing1.location.setLocationName(temp["Location Name"].asString());


    temp = jsonVal["Thing 2"];
    this->thing2.thingName = temp["Thing Name"].asString();

    temp = temp["Location"];
    this->thing2.location.setLocationName(temp["Location Name"].asString());

    temp = jsonVal["Thing 3"];
    this->thing3.thingName = temp["Thing Name"].asString();

    temp = temp["Location"];
    this->thing3.location.setLocationName(temp["Location Name"].asString());

    temp = jsonVal["Time"];
    char * timeString = (char *) (temp["time"]).asCString();
   // char timeString[] = "0000-12-00T00:00:00+000".;
    this->setTime(timeString);

     return true;
}


