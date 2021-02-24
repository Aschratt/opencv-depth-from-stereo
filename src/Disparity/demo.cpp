#include "demo.hxx"
#include <iostream>

using namespace cv;
using namespace cv::utils;

int main(int argc, char* argv[])
{
    // Define command line arguments.
    const String keys =
        "{help h usage ? |      | Print this message. }"
        "{left_dir dl    |      | Directory that contains the images of the left camera. Images must have the .png ending. }"
        "{right_dir dr   |      | Directory that contains the images of the right camera. Images must have the .png ending. }"
        "{matcher m      | 0    | Stereo matcher algorithm: 0 - binary BM (default), 1 - binary SGBM, 2 - quasi dense. }"
    ;

    // Parse command line arguments.
    CommandLineParser parser(argc, argv, keys);
    parser.about("Disparity");

    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }

    String leftDir = fs::canonical(parser.get<String>("dl"));
    String rightDir = fs::canonical(parser.get<String>("dr"));
    int matcher = parser.get<int>("m");

    if (!parser.check())
    {
        parser.printErrors();
        return 1;
    }

    // Validate arguments.
    if (!fs::exists(leftDir))
    {
        std::cerr << "Directory does not exist: " << leftDir << std::endl;
        return 1;
    }
    else if (!fs::exists(rightDir))
    {
        std::cerr << "Directory does not exist: " << rightDir << std::endl;
        return 1;
    }
    else if (matcher < 0 || matcher > 2)
    {
        std::cerr << "Invalid matcher: " << matcher << ". Must be a value between 0 and 2. Use `help` for more info." << std::endl;
        return 1;
    }

    // Get all files from the left and right directory.
    std::vector<String> leftImages, rightImages;
    fs::glob(leftDir, "*.png", leftImages);
    fs::glob(rightDir, "*.png", rightImages);
    
    std::cout << "Found " << leftImages.size() << " images in left directory and " << rightImages.size() << " images in right directory." << std::cout;

    return 0;
}