#include "photo.h"
#include <iostream>
#include <fstream>
//#include "tiePoint.h"

int main(){

    std::cout << "Hello hell" << std::endl;

    photo myPhotos;

    std::vector< std::vector<std::string> > myPhotosData = myPhotos.loadPointsAndPhotos();
    std::vector<photo> separatedPhotos = myPhotos.separatePhotos(myPhotosData);

    std::vector<std::string> photosToBeConverted = photo::definePhotosToBeConverted();

    for (int i = 0; i < separatedPhotos.size(); i++){
        separatedPhotos.at(i).convertToPx();
    }

    std::vector<tiePoint> tiePoints;

    if (photosToBeConverted.at(0) == "all"){
        std::cout << "Vou escrever todas as fotos!" << std::endl;
        tiePoints = photo::organizePoints(separatedPhotos);

        /*std::ofstream LPSFile;
        LPSFile.open("tiePoints.txt");

        for (int i = 0; i < tiePoints.size(); i++){

            LPSFile << tiePoints.at(i).point_ID << std::endl;

            for (int j = 0; j < tiePoints.at(i).photo_ID.size(); j++){

                LPSFile << tiePoints.at(i).photo_ID.at(j) << std::endl;
            }

            LPSFile << std::endl;
            
        }*/
        photo::writeTiePoints(tiePoints, separatedPhotos);
    }else{
        photo::convertToLPS(photosToBeConverted, separatedPhotos);
    }


    //for (int i = 0; i < separatedPhotos.size(); i++){
        //separatedPhotos.at(i).convertToLPS();
    //}


    return 0;
}