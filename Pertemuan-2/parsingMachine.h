#ifndef PARSING_H
#define PARSING_H

//sumber: https://www.studyplan.dev/pro-cpp/json#parsing-json-documents
#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"
using namespace std;

class parsing{
public:
    using json = nlohmann::json;

    void startParsing(int number){
        string Snumber = to_string(number);
        string path = string(DATA_DIR) +"XL"+"/motion_movie/"+ Snumber + ".json";
        fstream File;
        File.open(path);
        if(!File.is_open()){
            cout<<"Err, motion_movie file won't open!"<<endl;
            return;
        }
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
        string path = string(DATA_DIR) +"XL"+"/motion_unit/"+ Snumber + ".json";
        fstream File;
        File.open(path);
        json Doc = json::parse(File);
        if(!File.is_open()){
            cout<<"Err, motion_unit file won't open!"<<endl;
            return;
        }
        long checksum{Doc["checksum"]};
        int id{Doc["id"]};
        string name{Doc["name"]};
        int total_frame{Doc["total_frame"]};
        vector<int> times = Doc["time"].get<vector<int>>();
        vector<vector<int>> motion_frame = Doc["motion_frame"].get<vector<vector<int>>>();

        size_t rows = motion_frame.size();
        size_t cols = (rows > 0 && !motion_frame[0].empty()) ? motion_frame[0].size() : 1;

        cout<<endl;
        cout<<"DATA HASIL PARSING UNIT "<<Snumber + ".json"<<endl;
        cout<<"---------------------------"<<endl;
        cout<<"checksum: "<<checksum<<endl;
        cout<<"id: "<<id<<endl;
        cout<<"name: "<<name<<endl;
        cout<<"total frame: "<<total_frame;
        cout<<"time(s): ";
        for (int i = 0;i<times.size();i++){
            cout<<times[i]<<" ";
        }
        cout<<endl;
        cout<<"motion frame(s): Matriks "<<cols<<" X "<<rows<<endl;;
        for (int i = 0;i<motion_frame.size();i++){
            for (int j = 0;j<motion_frame[i].size();j++){
                cout<<motion_frame[i][j]<<" ";
            }
            cout<<endl;
        }
            cout<<"---------------------------"<<endl;
        }

    };

#endif