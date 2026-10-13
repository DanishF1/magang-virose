#ifndef PARSING_H
#define PARSING_H

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
        int checksum{Doc["checksum"]};
        int id{Doc["id"]};
        string name{Doc["name"]};
        int T_unit{Doc["total_unit"]};
        int M_unit_id{Doc["motion_unit"][0]["id"]};
        double M_unit_speed{Doc["motion_unit"][0]["speed"]};
        int M_unit_loop{Doc["motion_unit"][0]["loop"]};

        cout<<id<<endl;
        continueParsing(M_unit_id);
    }

    void continueParsing(int number){
        string Snumber = to_string(number);

    }
    

};




#endif