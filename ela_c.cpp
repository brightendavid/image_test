#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector> 
#include "ela.hpp"

// Control
int scale = 15,
    quality = 75;

// Image containers
cv::Mat input_image,
    compressed_image;

void processImage(int, void*)
{
   // Setting up parameters and JPEG compression
   std::vector<int> parameters;
   parameters.push_back(CV_IMWRITE_JPEG_QUALITY);
   parameters.push_back(quality);
   cv::imwrite("lena.jpeg", input_image, parameters);

   // Reading temp image from the disk
   compressed_image = cv::imread("lena.jpeg");

   if (compressed_image.empty())
   {
      std::cout << "> Error loading temp image" << std::endl;
      exit(EXIT_FAILURE);
   }

   cv::Mat output_image = cv::Mat::zeros(input_image.size(), CV_8UC3);

   // Compare values through matrices
   for (int row = 0; row < input_image.rows; ++row)
   {
    const uchar* ptr_input = input_image.ptr<uchar>(row);
    const uchar* ptr_compressed = compressed_image.ptr<uchar>(row);
    uchar* ptr_out = output_image.ptr<uchar>(row);

        for (int column = 0; column < input_image.cols; column++)
        {
            // Calc abs diff for each color channel multiplying by a scale factor
            ptr_out[0] = abs(ptr_input[0] - ptr_compressed[0]) * scale;
            ptr_out[1] = abs(ptr_input[1] - ptr_compressed[1]) * scale;
            ptr_out[2] = abs(ptr_input[2] - ptr_compressed[2]) * scale;

            ptr_input += 3;
            ptr_compressed += 3;
            ptr_out += 3;
        }
    }

    // Shows processed image
    cv::imshow("Error Level Analysis", output_image);
} 

void new_func (char* filename)
{

   // Read the image
   input_image = cv::imread(filename);

   
   // Set up window and trackbar
   cv::namedWindow("Error Level Analysis", CV_WINDOW_AUTOSIZE);
   cv::imshow("Error Level Analysis", input_image);
   cv::createTrackbar("Scale", "Error Level Analysis", &scale, 100, processImage);
   cv::createTrackbar("Quality", "Error Level Analysis", &quality, 100, processImage);

   // Press 'q' to quit
   while (char(cv::waitKey(0)) != 'q') {};

   
} 