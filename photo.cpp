#include "photo.h"
#include<iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>


photo::photo()
{
    //Ainda não sei o que colocar no construtor da classe
}

void photo::convertToPx(){

    float pixel_size_x = 0.00261;
    float pixel_size_y = 0.00261;

    int imageColums = 4864, imageRows = 3648;

    float d_imgx = pixel_size_x * imageColums;
    float d_imgy = pixel_size_y * imageRows;

    for(int i = 0; i < (*this).points.size(); i++){

            float x_microns = std::stod((*this).points.at(i).at(1)) / 1000;
            float y_microns = std::stod((*this).points.at(i).at(2)) / 1000;

            int C = int((1/pixel_size_x) * ((d_imgx/2) + x_microns));
            int L = int((1/pixel_size_y) * ((d_imgy/2) - y_microns)) -1;

            (*this).points.at(i).at(1) = std::to_string(C);
            (*this).points.at(i).at(2) = std::to_string(L);
    }
}

std::vector< std::vector<std::string> > photo::loadPointsAndPhotos(){

    std::string filePath;

    std::cout << "Digite o caminho para o arquivo com os pontos de Tie: " << std::endl;
    getline(std::cin, filePath);


    std::ifstream infile(filePath, std::ifstream::in);
    std::vector< std::vector<std::string> > data;

    infile ? std::cout << "Arquivo lido com sucesso!" << std::endl : std::cout << "Leitura falhou!" << std::endl;

    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss;
        std::string aux;

        iss.str(line);

        std::vector<std::string> data_line;
        for(int i=0; i < 3; i++){
            iss >> aux;
            data_line.push_back(aux);
        }

        data.push_back(data_line);
    }

    std::cout << "File content loaded! " << data.size() << " lines readed!" << std::endl;

    return data;
}

void photo::loadExteriorOrientation(){


}

std::vector<std::string> photo::definePhotosToBeConverted()
{
    std::string photoPrefix = "DJI_", photoSufix = ".JPG", photoNumbers, aux;
    std::vector<std::string> userPhotosID;
    char delimiter = ' ';

    // ----------------- Separando as fotos que o usuário quer -----------------------------------#

    std::cout << "Digite os números das fotografias que você quer gravar separados por espaço \nDigite all para que todas sejam gravadas: " << std::endl;
    std::getline(std::cin, photoNumbers);



    if (photoNumbers != "all"){

        int nDelimiter = 0, nUserPhotos = 0;

        for(int i=0; i < photoNumbers.size(); i++){

            if (photoNumbers.at(i) == delimiter){
                nDelimiter = nDelimiter + 1;

            }

        }

        nUserPhotos = ++nDelimiter; // Número de fotos que o usuário digitou

        std::istringstream s;
        s.str(photoNumbers);

        for (int i=0; i < nUserPhotos; i++){
            s >> aux;
            userPhotosID.push_back(photoPrefix + aux + photoSufix);
        }

        return userPhotosID;

    } else {
        userPhotosID.push_back("all");
        return userPhotosID;
    }



}


void photo::convertToLPS(std::vector<std::string> photosToconvert, std::vector<photo> allPhotos){

    std::vector<photo> photosToWrite;
    photo newPhoto1, newPhoto2, nPhoto;


    for (int i=0; i < photosToconvert.size(); i++){
        for (int j=0; j < allPhotos.size(); j++){

            if (allPhotos.at(j).ID == photosToconvert.at(i)){
                photosToWrite.push_back(allPhotos.at(j));
            }
        }
    }


    std::cout << photosToWrite.size() << std::endl;

    nPhoto.ID = photosToWrite.at(0).ID;
    newPhoto1 = photosToWrite.at(0);
    newPhoto2.ID =  photosToWrite.at(1).ID;

    // Procurar por pontos com o mesmo identificador e colocá-los em um novo vetor

    int menor = newPhoto1.points.size();

    for (int i=1; i < photosToWrite.size(); i++ ){
        if(photosToWrite.at(i).points.size() < menor){
            menor = photosToWrite.at(i).points.size();
        }
    }



    for(int i=1; i < photosToWrite.size(); i++){
        for(int j=0; j < menor; j++){ //Vai percorrer a foto fixa
                for(int k=0; k < menor; k++ ){ //Vai percorrer as próximas fotos

                    if(newPhoto1.points.at(j).at(0) == photosToWrite.at(i).points.at(k).at(0)){

                            //std::cout << "Encontrei um homologo!" << std::endl;
                            newPhoto2.points.push_back(photosToWrite.at(i).points.at(k));
                            nPhoto.points.push_back(newPhoto1.points.at(j));
                    }
                }
            }
        }

        std::ofstream LPSFile;
        LPSFile.open("pointsLPS.txt");
        std::string tab = "\t";



        for (int i = 0; i < nPhoto.points.size(); i++){

            std::ostringstream ss1;

            ss1 << (i+1);

            nPhoto.points.at(i).at(0) = ss1.str();
            newPhoto2.points.at(i).at(0) = ss1.str();
            LPSFile << "1" + tab + nPhoto.points.at(i).at(0) + tab + nPhoto.points.at(i).at(1) + tab + nPhoto.points.at(i).at(2) + "\n";
            LPSFile << "2" + tab + newPhoto2.points.at(i).at(0) + tab + newPhoto2.points.at(i).at(1) + tab + newPhoto2.points.at(i).at(2) + "\n";


        }

        LPSFile.close();

        std::cout << "Aquivo gravado, " << nPhoto.points.size() << " gravados!" << std::endl;
}

void photo::convertToLPS(std::vector<photo> aPhotos){

    for (int i=0; i < aPhotos.size(); i++){



    }

}



 std::vector<photo> photo::separatePhotos(std::vector< std::vector<std::string> > myData){

    std::vector<photo> mySeparatedPhotos;
    std::string photoID = "DJI_";

    for(int i= 0; i < myData.size(); i++){

            photo fPhoto;
            bool isPopulated= false;

            if (myData.at(i).at(0).find(photoID) != std::string::npos){


                fPhoto.ID = myData.at(i).at(0);
                int cont = i+1;

                while (myData.at(cont).at(0).find("-99") == std::string::npos){

                        fPhoto.points.push_back(myData.at(cont));
                        isPopulated = true;
                        cont++;
                }
            }
            if (isPopulated)
                mySeparatedPhotos.push_back(fPhoto);

            }

            std::cout << mySeparatedPhotos.size() << " Photos separated!" << std::endl;

            return mySeparatedPhotos;

    }



int main(){

    std::cout << "Hello hell" << std::endl;

    photo myPhotos;

    std::vector< std::vector<std::string> > myPhotosData = myPhotos.loadPointsAndPhotos();
    std::vector<photo> separatedPhotos = myPhotos.separatePhotos(myPhotosData);

    std::vector<std::string> photosToBeConverted = photo::definePhotosToBeConverted();

    for (int i = 0; i < separatedPhotos.size(); i++){
        separatedPhotos.at(i).convertToPx();
    }

    if (photosToBeConverted.at(0) == "all"){
        std::cout << "Vou escrever todas as fotos, hein, arrombado!" << std::endl;
    }else{
        photo::convertToLPS(photosToBeConverted, separatedPhotos);
    }


    //for (int i = 0; i < separatedPhotos.size(); i++){
        //separatedPhotos.at(i).convertToLPS();
    //}


    return 0;
}
