#include "traitement.h"
#include <opencv2/aruco.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <QtDebug>
#include <vector>
#include "qjsondocument.h"
#include <qjsonobject.h>
#include <qjsonarray.h>

using namespace std;
using namespace cv;

traitement::traitement()
{

}


void rect(){

       for(int i = 0; i < 255; i++) {
           VideoCapture inputVideo(i);
           if(inputVideo.isOpened())
               qDebug() << "qzd" << i;
       }

        VideoCapture inputVideo(4);
        vector< vector< Point2f > > corners, rejected;
        vector< vector< Point2f > > corners_final, rejected_final;
        vector< Vec3d > rvecs_final, tvecs_final;
        cv::Mat imageCopy,circuit,idimage;
        vector< int > ids,ids_final;
        vector<int> v_x;
        vector<int> v_y;
        Mat image;

        while(true)
        {
            Mat cameraMatrix, distCoeffs;
            Ptr<aruco::DetectorParameters> detectorParams = aruco::DetectorParameters::create();
            cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

            //Decodes and returns the grabbed video frame.
            inputVideo.grab();
            inputVideo.retrieve(image);
            image.copyTo(imageCopy);
            // detecter et dessiner les marqueurs trouvés
            cv::aruco::detectMarkers(image, dictionary, corners, ids, detectorParams);

            // S'il y a au moins un marqueur de détecté
            if (ids.size() > 0)
            {
                // On dessine les marqueurs détectés sur l'image
                cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
            }

            //afficher la sortie
            cv::imshow("out", imageCopy);
            waitKey(20);//ms

            QJsonObject map;
               map.insert("mapWidth", QJsonValue::fromVariant(1000));
               map.insert("mapHeight", QJsonValue::fromVariant(1000));


               QJsonObject checkpoint ;
               checkpoint.insert("id", "");
               checkpoint.insert("x", "");
               checkpoint.insert("y", "");
               map.insert("checkpoint", checkpoint);

               QJsonObject obstacles;
               obstacles.insert("id", "");
               obstacles.insert("x", "");
               obstacles.insert("y", "");
               map.insert("obstacles", obstacles);

               QJsonDocument doc(map);
               qDebug() << doc.toJson();


               emit jmap(doc);
        }


}
