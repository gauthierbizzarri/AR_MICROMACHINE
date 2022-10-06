#include "traitement_image.h"




using namespace std;
using namespace cv;




Traitement_Image::Traitement_Image(QObject *parent)
    : QObject{parent}
{

}


void Traitement_Image::rect(){


    cv::VideoCapture cam1,cam2,cam3,cam4;


    vector< vector< Point2f > > corners, rejected;
    vector< vector< Point2f > > corners_final, rejected_final;
    vector< Vec3d > rvecs_final, tvecs_final;
    cv::Mat imageCopy1,imageCopy2,imageCopy3,imageCopy4,imageCopyf;
    vector< int > ids,ids_final;
    vector<int> v_x;
    vector<int> v_y;
    Mat fr1,fr2,fr3,fr4,pano;
    vector<Mat> imgs;



    int x ;
    int y ;
    float angle;
    float pi = M_PI;
    int width, height;

    QPolygon polygon1;
    QPoint pointf;
    QList<QPair<int,int>> listpoint;

    while(true)
    {
        Mat cameraMatrix, distCoeffs;
        Ptr<aruco::DetectorParameters> detectorParams = aruco::DetectorParameters::create();
        cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

        //Decodes and returns the grabbed video frame of the 4th camera.
        //Decodes and returns the grabbed video frame.
        cam1.grab();
        cam1.retrieve(fr1);
        fr1.copyTo(imageCopy1);

        //ajout de la deuxieme video
        cam2.grab();
        cam2.retrieve(fr2);
        fr2.copyTo(imageCopy2);

        cam3.grab();
        cam3.retrieve(fr3);
        fr3.copyTo(imageCopy3);

        cam4.grab();
        cam4.retrieve(fr4);
        fr4.copyTo(imageCopy4);




        imgs.push_back(imageCopy1);
        imgs.push_back(imageCopy2);
        imgs.push_back(imageCopy3);
        imgs.push_back(imageCopy4);

        Ptr<Stitcher> stitcher = Stitcher::create( Stitcher::Mode::PANORAMA);
        Stitcher::Status status = stitcher->stitch(imgs, pano);


        if (status != Stitcher::OK)
        {
            cout << "Error stitching - Code: " <<int(status)<<endl;
            break;
        }

        imshow("Stitched Image", pano);
        pano.copyTo(imageCopyf);

        // detecter et dessiner les marqueurs trouvés
        cv::aruco::detectMarkers(pano, dictionary, corners, ids, detectorParams);

        // On dessine les marqueurs détectés sur l'image
        cv::aruco::drawDetectedMarkers(imageCopyf, corners, ids);


        int numid = 0;

        for (std::vector<std::vector< cv::Point2f >>::iterator nCorner = corners.begin(); nCorner != corners.end(); nCorner++){
            //qDebug()<< "numid :"<<numid;
            x = 0;
            y = 0 ;
            QList<QPair<int,int>> clc;


            for (std::vector< cv::Point2f >::iterator nPoint = nCorner->begin(); nPoint != nCorner->end(); nPoint++) {
                //qDebug() << nPoint->x << ";" << nPoint->y;
                clc.append(QPair<int, int>(nPoint->x,nPoint->y));
                x += nPoint->x;
                y += nPoint->y;
            }

            x = x/4;
            y = y/4;
            pointf.setX(x);
            pointf.setY(y);


            if (ids[numid] >= 0 and ids[numid] <= 9 and !listpoint.contains(QPair<int, int>(x, y))){
                listpoint.append(QPair<int, int>(x, y));

            }

            if (ids[numid]  >= 200 and ids[numid] <= 249  ){

                angle= qAtan2(y-clc.at(0).second,x -clc.at(0).first) - pi/4;
            }

            for(int i=0; i < listpoint.count() ; i++){

                if(!listpoint.contains(QPair<int, int>(x, y))){
                    polygon1 <<  QPoint(listpoint.at(i).first,listpoint.at(i).second);

                }
            }

            QRect rect =  polygon1.boundingRect();


            width = rect.width();
            height = rect.height();


            if(rect.contains(pointf) /*and ids[numid] >9*/ ){

                constjson(ids[numid],x,y,angle,width,height);
            }else{
                qDebug()<<rect<<rect.contains(pointf)<<ids[numid]<<pointf;

            }
            numid++;
        }




        cv::imshow("out", imageCopy1);

        waitKey(2000);//ms

    }


}


void Traitement_Image::constjson(int id , int x, int y ,float angle,int width,int height){

    qDebug()<<id;
    map.insert("mapWidth",width);
    map.insert("mapHeight",height);

    if (id >= 100 and id <= 199){
        qDebug() << "checkpoint";



        // use initializer list to construct QJsonObject
        auto datacheckp = QJsonObject(
                    {
                        qMakePair(QString("id"), QJsonValue(id)),
                        qMakePair(QString("x"), QJsonValue(x)),
                        qMakePair(QString("y"), QJsonValue(y))
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

    if (id >= 200 and id<= 249  ){
        qDebug() << "obstacles";



        auto data_obs = QJsonObject(
                    {
                        qMakePair(QString("id"), QJsonValue(id)),
                        qMakePair(QString("angle"), QJsonValue(angle)),
                        qMakePair(QString("x"), QJsonValue(x)),
                        qMakePair(QString("y"), QJsonValue(y))
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

    map.insert("checkpoints",checkpoints);
    map.insert("obstacles",obstacles);

    QJsonDocument doc(map);
    qDebug() << doc.toJson();
    qDebug() << Qt::endl;

    //emit jsonmap(doc);

}
