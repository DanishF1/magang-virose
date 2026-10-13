#ifndef PARSING_H
#define PARSING_H

//sumber: https://www.studyplan.dev/pro-cpp/json#parsing-json-documents
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "json.hpp"
using namespace std;

class parsing{
public:
    using json = nlohmann::json;

    void startParsing(int number){
        string Snumber = to_string(number);
        //string path = string(DATA_DIR) +"XL"+"/motion_movie/"+ Snumber + ".json";
        string path = "/home/dan-eksakdev/Documents/Magang_Vi-Rose/Pertemuan-2/XL/motion_movie/"+Snumber+".json";
        fstream File;
        File.open(path);

        json Doc = json::parse(File);
        long checksum{Doc["checksum"]};
        int id{Doc["id"]};
        string name{Doc["name"]};
        int T_unit{Doc["total_unit"]};
        int M_unit_id{Doc["motion_unit"][0]["id"]};
        double M_unit_speed{Doc["motion_unit"][0]["speed"]};
        int M_unit_loop{Doc["motion_unit"][0]["loop"]};

        cout<<endl;
        cout<<"DATA HASIL PARSING MOTION "<<Snumber + ".json"<<endl;
        cout<<"---------------------------"<<endl;
        cout<<"checksum: "<<checksum<<endl;
        cout<<"id: "<<id<<endl;
        cout<<"name: "<<name<<endl;
        cout<<"total unit: "<<T_unit<<endl;
        cout<<"motion unit id: "<<M_unit_id<<endl;
        cout<<"motion unit speed: "<<M_unit_speed<<endl;
        cout<<"motion unit speed: "<<M_unit_loop<<endl;
        cout<<"---------------------------"<<endl;


        continueParsing(M_unit_id);
    }

    void continueParsing(int number){
        string Snumber = to_string(number);
        //string path = string(DATA_DIR) +"XL"+"/motion_unit/"+ Snumber + ".json";
        string path = "/home/dan-eksakdev/Documents/Magang_Vi-Rose/Pertemuan-2/XL/motion_unit/"+Snumber+".json";
        fstream File;
        File.open(path);
        json Doc = json::parse(File);

        long checksum{Doc["checksum"]};
        int id{Doc["id"]};
        string name{Doc["name"]};
        int total_frame{Doc["total_frame"]};
        int time{Doc["time"]};
        int motion_frame[]{Doc["motion_frame"][0]};

        cout<<endl;
        cout<<"DATA HASIL PARSING UNIT "<<Snumber + ".json"<<endl;
        cout<<"---------------------------"<<endl;
        cout<<"checksum: "<<checksum<<endl;
        cout<<"id: "<<id<<endl;
        cout<<"name: "<<name<<endl;
        cout<<"total frame: "<<total_frame<<endl;
        cout<<"total time: "<<time<<endl;
        cout<<"motion frame: ";
        for(int i=0;i<sizeof(motion_frame);i++){
            cout<<motion_frame[i]<<" ";
        }
        cout<<"---------------------------"<<endl;

    }
    

};




#endif