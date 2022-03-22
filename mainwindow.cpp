#include "mainwindow.h"
#include "ui_mainwindow.h"

//General Declarations
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>

// Computer Vision
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

//Window Name Declarations
char const* ImageWin = "Image";

//Box & Circle Set Up Name Declarations
char const* ControlPanel = "Box SetUp Control";
char const* track_OnOff = "Set Box Position";
char const* track_val = "Gray Value";
char const* X_top_left = "X Top Left";
char const* Y_top_left = "Y Top Left";
char const* X_size = "Width";
char const* Y_size = "Height";
char const* Max_Rad = "Maximum Radius";

//Grey Threshold Declarations
int thresh_val = 75;
int thresh_type = 1;
int thresh_max_val = 100;
int thresh_max_type = 1;

//Circle Tracking Declarations
int CED = 1;
int Cent_D = 1;
int min_rad = 58;
int max_rad = 60;
int X_Point = 0;
int Y_Point = 0;
int Radius = 0;
int max_circ_rad = 100;
int X = 320;
int Y = 240;
int Width = 160;
int Height = 120;
int OnOff = 0;

Mat img;

string Filepath = "/home/four/Downloads/image.png";

//Timing Declarations
time_t iTime = 0;
time_t cTime = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Button2->setEnabled(false);
}

void MainWindow::on_Button1_clicked()
{
    hide();

    OnOff = 0;

    img = imread(Filepath, IMREAD_COLOR);
    if(img.empty())
    {
        cout << "Could not read the image: " << Filepath << endl;
    }
    else{
        cout << "Read image: " << Filepath << endl;
    }

    namedWindow(ImageWin, WINDOW_NORMAL);
    resizeWindow(ImageWin,640,480);
    moveWindow(ImageWin, 160, 0);

    namedWindow(ControlPanel, WINDOW_NORMAL);
    resizeWindow(ControlPanel,300,480);
    moveWindow(ControlPanel, 0, 0);

    time(&iTime);
    while(OnOff == 0 && difftime(cTime,iTime) < 5){

        createTrackbar(track_val, ControlPanel,&thresh_val,thresh_max_val); //binary gray value
        createTrackbar(track_OnOff, ControlPanel,&OnOff,1); //video window on and off
        createTrackbar(X_top_left, ControlPanel,&X,638); //bounding box top left X
        createTrackbar(Y_top_left, ControlPanel,&Y,478); //bounding box top left Y
        createTrackbar(X_size, ControlPanel,&Width,640); //bounding box width
        createTrackbar(Y_size, ControlPanel,&Height,480); //bounding box height
        createTrackbar(Max_Rad, ControlPanel,&max_rad,max_circ_rad); //Circle Size

        imshow(ImageWin, img);
        waitKey(1);

        time(&cTime);
    }
    destroyAllWindows();
    show();

    ui->Button2->setEnabled(true);
}

void MainWindow::on_Button2_clicked()
{
    hide();

    img = imread(Filepath, IMREAD_COLOR);
    if(img.empty())
    {
        cout << "Could not read the image: " << Filepath << endl;
    }
    else{
        cout << "Read image: " << Filepath << endl;
    }

    namedWindow(ImageWin, WINDOW_NORMAL);
    resizeWindow(ImageWin,800,480);
    moveWindow(ImageWin, 0, 0);

    time(&iTime);
    while(difftime(cTime,iTime) < 5){
        imshow(ImageWin, img);
        waitKey(1);

        time(&cTime);
    }
    destroyWindow(ImageWin);
    show();
}

MainWindow::~MainWindow()
{
    delete ui;
}





