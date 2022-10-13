#include "traitement_image.h"

using namespace std;
using namespace cv;


Traitement_Image::Traitement_Image(QObject *parent)
    : QObject{parent}
{

}

void Traitement_Image::CameraId()
{
    for(int i =0; i<100;i++)
    {
        VideoCapture inputVideo(i);
        Mat imageCopy,image;
        inputVideo.grab();
        inputVideo.retrieve(image);
        image.copyTo(imageCopy);
        if(imageCopy.empty()==false)
        {
            qDebug()<<"LE PORT eest "<<i;
        }
    }
}

void Traitement_Image::rect(){


    cv::VideoCapture cam1,cam2,cam3,cam4;

    cam1.open(1);
    cam2.open(0);
    cam3.open(8);
    cam4.open(10);

    cv::Mat imageCopy1,imageCopy2,imageCopy3,imageCopy4,imageCopyf;
    Mat fr1,fr2,fr3,fr4,panof;
    vector<Mat> imgs;



    while(true)
    {
        //Decodes and returns the grabbed video frame of the 4th camera.
        //Decodes and returns the grabbed video frame.
        qDebug() << "debut";
        cam1.grab();
        cam1.retrieve(fr1);
        fr1.copyTo(imageCopy1);

        //   qDebug() << "grab1";


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

        qDebug() << "affiche image ";


        cv::imshow("cam1", imageCopy1);
        cv::imshow("cam2", imageCopy2);
        cv::imshow("cam3", imageCopy3);
        cv::imshow("cam4", imageCopy4);



        imgs.clear();

        imgs.push_back(imageCopy1);
        imgs.push_back(imageCopy2);
        imgs.push_back(imageCopy3);
        imgs.push_back(imageCopy4);


        Ptr<Stitcher> stitcher = Stitcher::create( Stitcher::Mode::PANORAMA);
        Stitcher::Status status = stitcher->stitch(imgs, panof);

        //  stitcher->setWaveCorrection(false);
        //stitcher->estimateTransform(panof,noArray());

        if (status != Stitcher::OK)
        {
            //qDebug() << "stitch not ok";
            cout << "Error stitching - Code: " <<int(status)<<endl;
            // continue;
        }else{


            //  qDebug() << "stitch ok";
            panof.copyTo(imageCopyf);
            //imshow("Stitched Image", imageCopyf);
            Detectmarkers(imageCopyf);


        }

        qDebug() << "fin stitch ";

        waitKey(1000);

    }
    qDebug()<<"image recupere";


}





void Traitement_Image::Detectmarkers(cv::Mat image){

    // qDebug()<<"fontion traitement";

    vector< vector< Point2f > > corners, rejected;
    vector< vector< Point2f > > corners_final, rejected_final;
    vector< Vec3d > rvecs_final, tvecs_final;
    cv::Mat imageCopy;
    vector< int > ids,ids_final;
    vector<int> v_x;
    vector<int> v_y;

    int x ;
    int y ;
    int xmin = 10000;
    int ymin = 10000;
    int xmax = 0 ;
    int ymax = 0 ;
    float angle;
    float pi = M_PI;
    int width, height;


    Mat cameraMatrix, distCoeffs;
    Ptr<aruco::DetectorParameters> detectorParams = aruco::DetectorParameters::create();
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

    image.copyTo(imageCopy);

    // detecter et dessiner les marqueurs trouvés
    cv::aruco::detectMarkers(image, dictionary, corners, ids, detectorParams);

    // On dessine les marqueurs détectés sur l'image
    cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);


    int numid = 0;

    for (std::vector<std::vector< cv::Point2f >>::iterator nCorner = corners.begin(); nCorner != corners.end(); nCorner++){
        //qDebug()<< "numid :"<<numid;
        x = 0;
        y = 0 ;
        QList<QPair<int,int>> clc;

        qDebug()<<"fontion traitement2";
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

            xmin = listpoint.at(i).first < xmin ?listpoint.at(i).first : xmin;
            ymin = listpoint.at(i).second < ymin ?listpoint.at(i).second : ymin;

            xmax = listpoint.at(i).first > xmax ?listpoint.at(i).first : xmax;
            ymax = listpoint.at(i).second > ymax ?listpoint.at(i).second : ymax;

            if(!listpoint.contains(QPair<int, int>(x, y))){

                polygon1 <<  QPoint(listpoint.at(i).first,listpoint.at(i).second);

            }



        }


        QRect rect =  polygon1.boundingRect();


        width = 1000;
        height = 1000;

        // qDebug()<<maxw<<maxh;


        if(rect.contains(pointf) and ids[numid] >9 ){
            //qDebug()<<"fontion traitement3";
            x = (x - xmin)*1.0/(xmax-xmin)*1000 ;
            y = (y-ymin)*1.0/(ymax-ymin)*1000 ;



            constjson(ids[numid],x,y,angle,width,height);

        }else{

            // qDebug()<<rect<<rect.contains(pointf)<<ids[numid]<<pointf;

        }
        numid++;
    }
    //qDebug()<<"fin traitement";

    cv::imshow("out", imageCopy);


}



void Traitement_Image::constjson(int id , int x, int y ,float angle,int width,int height){

    // qDebug()<<"constjson";

    //qDebug()<<id;
    map.insert("mapWidth",width);
    map.insert("mapHeight",height);

    if (id >= 100 and id <= 199){
        //   qDebug() << "checkpoint";



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
                qDebug() << "chui la check ";
                presentcheck = true;

                datacheckp.insert("id", object["id"].toInt());
                datacheckp.insert(("x") ,object["x"].toInt());
                datacheckp.insert("y", object["y"].toInt());


            }

        }
        if(!presentcheck) checkpoints.push_back(QJsonValue(datacheckp));
    }

    if (id >= 200 and id<= 249  ){
        // qDebug() << "obstacles";



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

                qDebug() <<"obsid"  << data_obs.value("x");

                // data_obs.value().swap()


                data_obs.insert("id", object["id"].toInt());
                data_obs.insert(("angle") ,object["angle"]);
                data_obs.insert(("x") ,object["x"].toInt());
                data_obs.insert("y", object["y"].toInt());

                qDebug() <<   data_obs.value("x")<< object["x"].toInt();
            }
        }
        if(!presentobstacle ) obstacles.push_back(QJsonValue(data_obs));
    }

    map.insert("checkpoints",checkpoints);
    map.insert("obstacles",obstacles);

    QJsonDocument doc(map);
    //  qDebug() << doc.toJson();
    qDebug() << Qt::endl;

    emit jsonmap(doc);

}
