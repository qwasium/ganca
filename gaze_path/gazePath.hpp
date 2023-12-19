// depenndencies: opencv

# ifndef GAZEPTH_HPP
# define GAZEPTH_HPP

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <cmath>


def int plotGazePath(std::string bgFilePath, std::string outFilePath){
    try
    {
        cv::Mat bgImg = cv::imread(bgFilePath, cv::IMREAD_COLOR); // IMREAD_COLOR: If set, always convert image to the 3 channel BGR color image.
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    // int rad = 150;
    // auto clr = cv::Scalar(0, 0, 255);
    cv::circle(
        bgImg,
        cv::Point(bgImg.cols/2, bgImg.rows/2),
        int 150,
        cv::Scalar(0, 0, 255)
        int -1,
        cv::LineTypes LINE_AA
    );

// void cv::circle	(
//     InputOutputArray 	img,
//     Point 	center,
//     int 	radius,
//     const Scalar & 	color,
//     int 	thickness = 1,
//     int 	lineType = LINE_8,
//     int 	shift = 0
// )

    cv::imshow("Display window", bgImg);


    return 0;
    }

# endif