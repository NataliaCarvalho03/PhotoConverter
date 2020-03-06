#ifndef TIEPOINT_H
#define TIEPOINT_H

#include<vector>
#include<string>
#include<iostream>

class tiePoint
{
    public:
        std::string point_ID; // Quem é este ponto
        std::vector<std::string> photo_ID; //Em quais fotos o ponto aparece
        std::vector<std::vector<std::string>> points; //As coordenadas deste ponto nestas fotos

        tiePoint(std::string p_ID, std::vector<std::string> ph_ID, std::vector<std::vector<std::string>> pts); //Construtor

};

#endif // TIEPOINT_H
