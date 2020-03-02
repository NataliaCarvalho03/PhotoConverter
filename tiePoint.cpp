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
