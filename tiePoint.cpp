#include "tiePoint.h"
#include "photo.h"
#include<fstream>
#include <iostream>

tiePoint::tiePoint(std::string p_ID, std::vector<std::string> ph_ID, std::vector<std::vector<std::string>> pts)
{
    point_ID = p_ID;
    photo_ID = ph_ID;
    points = pts;
}

void tiePoint::showTies(){

    std::cout << "============== Point ID ==================" << std::endl;

    std::cout << (*this).point_ID << std::endl;

    std::cout << "============== Photos ==================" << std::endl;

    for (int i = 0; i < (*this).photo_ID.size(); i++){
        std::cout << (*this).photo_ID.at(i) << std::endl;
    }
}
