#include "traitement_image.h"


using namespace std;
using namespace cv;




Traitement_Image::Traitement_Image(QObject *parent)
    : QObject{parent}
{

}


void Traitement_Image::rect(){



    VideoCapture inputVideo(6);
    vector< vector< Point2f > > corners, rejected;
    vector< vector< Point2f > > corners_final, rejected_final;
    vector< Vec3d > rvecs_final, tvecs_final;
    cv::Mat imageCopy,circuit,idimage;
    vector< int > ids,ids_final;
    vector<int> v_x;
    vector<int> v_y;
    Mat image;

    QJsonArray checkpoints;
    QJsonArray obstacles;
    QJsonObject map;


    int x ;
    int y ;
    int width;
    int height;
    int angle ;

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

        // On dessine les marqueurs détectés sur l'image
        cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);







        int numid = 0;
        for (std::vector<std::vector< cv::Point2f >>::iterator nCorner = corners.begin(); nCorner != corners.end(); nCorner++) {
            //qDebug()<< "numid :"<<numid;
            x = 0;
            y = 0 ;


            for (std::vector< cv::Point2f >::iterator nPoint = nCorner->begin(); nPoint != nCorner->end(); nPoint++) {
                //qDebug() << nPoint->x << ";" << nPoint->y;
                x += nPoint->x;
                y += nPoint->y;


                if (ids[numid] >= 0 and ids[numid] <= 9 ){
                   int widthmx  = -1;
                   int heightmx = -1;

                   int widthmn= 0;
                   int heightmn= 0;

                    if (nPoint->x > heightmx  ) heightmx = nPoint->x;


                    if (nPoint->y > widthmx ) widthmx = nPoint->y;


                    if (nPoint->x < heightmn  ) heightmn = nPoint->x;


                    if (nPoint->y < widthmn ) {widthmn = nPoint->y;}

                    width = widthmx - widthmn ;
                    height = heightmx - heightmn;

                }



                if (ids[numid] >= 200 and ids[numid]<= 249  ){


                }


            }
            // dessine l'axe pour chaque marqueur

            int xf = x/4;
            int yf = y/4;



            if (ids[numid] >= 100 and ids[numid] <= 199 and  xf > height and yf < width){




                // use initializer list to construct QJsonObject
                auto datacheckp = QJsonObject(
                            {
                                qMakePair(QString("id"), QJsonValue(ids[numid])),
                                qMakePair(QString("x"), QJsonValue(xf)),
                                qMakePair(QString("y"), QJsonValue(yf))
                            });
                bool presentcheck = false;
                for (int i = 0; i < checkpoints.size() ; ++i)
                {
                    QJsonObject object = checkpoints[i].toObject();

                    if (object["id"].toInt() == datacheckp.value("id").toInt()){
                        presentcheck = true;

                        object["id"] = datacheckp.value("id");
                        object["x"] = datacheckp.value("x");
                        object["y"] = datacheckp.value("y");


                    }

                }
                if(!presentcheck) checkpoints.push_back(QJsonValue(datacheckp));
            }
            if (ids[numid] >= 200 and ids[numid]<= 249 and xf > height and yf <  width ){




                auto data_obs = QJsonObject(
                            {
                                qMakePair(QString("id"), QJsonValue(ids[numid])),
                                qMakePair(QString("angle"), QJsonValue(35)),
                                qMakePair(QString("x"), QJsonValue(xf)),
                                qMakePair(QString("y"), QJsonValue(yf))
                            });

                bool presentobstacle = false;
                for (int i = 0; i < obstacles.size() ; ++i)
                {
                    QJsonObject object = obstacles[i].toObject();

                    if (object["id"].toInt() == data_obs.value("id").toInt()){
                        presentobstacle = true;

                        object["id"] = data_obs.value("id");
                        object["angle"] = data_obs.value("angle");
                        object["x"] = data_obs.value("x");
                        object["y"] = data_obs.value("y");

                    }
                }
                if(!presentobstacle ) obstacles.push_back(QJsonValue(data_obs));
            }



            numid++;

        }





        map.insert("mapWidth", QJsonValue::fromVariant(1000));
        map.insert("mapHeight", QJsonValue::fromVariant(1000));


        map.insert("checkpoints",checkpoints);
        map.insert("obstacles",obstacles);



        QJsonDocument doc(map);
        qDebug() << doc.toJson();




        qDebug() << Qt::endl;
        qDebug() << Qt::endl;

        emit jsonmap(doc);

        //afficher la sortie
        cv::imshow("out", imageCopy);

        waitKey(1000);//ms


    }


}
