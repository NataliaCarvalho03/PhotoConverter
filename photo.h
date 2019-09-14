#ifndef PHOTO_H
#define PHOTO_H

#include<vector>
#include<string>

class photo
{
    public:

        std::vector< std::vector<std::string> > points; //Each photo has many points
        std::string ID;
        float X0, Y0, Z0, om, phi, kappa; //Exterior Orientation Parameters

        photo();

        std::vector< std::vector<std::string> > loadPointsAndPhotos(); //This function organizes the photos, points and EOP
        std::vector<photo> separatePhotos(std::vector< std::vector<std::string> > myData);
        void loadExteriorOrientation(); // This function organizes the EOP
        void convertToPx();
        static void convertToLPS(std::vector<std::string> photosToconvert, std::vector<photo> allPhotos); //Write a file with tie points to LPS
        static std::vector<std::string> definePhotosToBeConverted();
};

#endif // PHOTO_H
