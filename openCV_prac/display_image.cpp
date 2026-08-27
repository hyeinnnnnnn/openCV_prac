#include <opencv2/opencv.hpp>
#include <iostream>

int main() {

    // Display Image

    /*
    // Load an image
    cv::Mat img = cv::imread("image.jpg");

    // Check if image was loaded successfully
    if (img.empty()) {
        std::cout << "Could not read the image" << std::endl;
        return 1;
    }

    // Display the image
    cv::imshow("Display window", img);
    int k = cv::waitKey(0);

    // Save if 's' key is pressed
    if (k == 's') {
        cv::imwrite("output.png", img);
    }

    return 0;
    */

    // 기초 이미지 처리

    // Read the image
    cv::Mat img = cv::imread("image.jpg");
    cv::Mat gray, blurred, edges;

    // Convert to grayscale
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    // Apply Gaussian blur
    cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0);

    // Detect edges using Canny
    cv::Canny(blurred, edges, 50, 150);

    // Display all results
    cv::imshow("Original", img);
    cv::imshow("Grayscale", gray);
    cv::imshow("Edges", edges);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}