#include "demo.hxx"

using namespace cv;
using namespace cv::utils;

#define STEREO_MATCHER_BM   0
#define STEREO_MATCHER_SGBM 1

String fileName(const String& absoluteName)
{
    auto separator = absoluteName.find_last_of('\\');

    return separator == String::npos ? absoluteName : absoluteName.substr(separator + 1);
}

int main(int argc, char* argv[])
{
    // Define command line arguments.
    const String keys =
        "{help h usage ? |      | Print this message. }"
        "{left_dir dl    |      | Directory that contains the images of the left camera. Images must have the .png ending. Corresponding images must have the same name. }"
        "{right_dir dr   |      | Directory that contains the images of the right camera. Images must have the .png ending. Corresponding images must have the same name. }"
        "{matcher m      | 0    | Stereo matcher algorithm: 0 - binary BM (default), 1 - binary SGBM. }"
        "{disparities d  | 16   | Number of disparity levels. }"
        "{block_size bs  | 9    | Size of a pixel kernel for comparison. }"
        "{cuda c         |      | Use CUDA version of the stereo matcher (only works with binary BM matcher). }"
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
    int blockSize = parser.get<int>("bs");
    int disparities = parser.get<int>("d");
    bool useCuda = parser.has("cuda");

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
    else if (matcher != STEREO_MATCHER_BM && matcher != STEREO_MATCHER_SGBM)
    {
        std::cerr << "Invalid matcher: " << matcher << ". Use `help` for more info." << std::endl;
        return 1;
    }

    if (useCuda && matcher == STEREO_MATCHER_SGBM)
        std::cout << "Warning: CUDA can only be used with the binary BM matcher. Matching will be performed at CPU." << std::endl;

    // Get all files from the left and right directory.
    std::vector<String> leftImages, rightImages;
    fs::glob(leftDir, "*.png", leftImages);
    fs::glob(rightDir, "*.png", rightImages);
    
    std::cout << "Found " << leftImages.size() << " images in left directory and " << rightImages.size() << " images in right directory." << std::endl;

    // Create stereo matcher instance.
    Ptr<stereo::StereoMatcher> stereoMatcher;

    switch (matcher)
    {
    case STEREO_MATCHER_BM:
        stereoMatcher = useCuda ?
            cuda::StereoBM::create(disparities, blockSize);
            stereo::StereoBinaryBM::create(disparities, blockSize);
        break;
    case STEREO_MATCHER_SGBM:
        stereoMatcher = stereo::StereoBinarySGBM::create(0, disparities, blockSize);
        break;
    }

    for (std::vector<String>::size_type i(0); i < leftImages.size(); ++i)
    {
        // Get the name of the last image.
        String leftImage = leftImages[i];
        String leftImageName = fileName(leftImage);
        
        // Find the corresponding right image.
        auto match = std::find_if(rightImages.begin(), rightImages.end(), [&](const String& s) { return fileName(s) == leftImageName; });

        if (match == rightImages.end())
        {
            std::cout << "Skipping image (no corresponding right image found): \"" << leftImage << "\"" << std::endl;
            continue;
        }

        String rightImage = *match;
        std::cout << "Interfering images \"" << leftImage << "\" and \"" << rightImage << "\"... ";

        // Load images and match them.
        Mat left = imread(leftImage, IMREAD_GRAYSCALE), right = imread(rightImage, IMREAD_GRAYSCALE);
        
        if (left.size() != right.size())
        {
            std::cout << std::endl << "Skipping image (image pair has not the same size): \"" << leftImage << "\"" << std::endl;
            continue;
        }

        Mat disparity = Mat(left.size(), CV_8UC1);

        auto start = std::chrono::high_resolution_clock::now();
        stereoMatcher->compute(left, right, disparity);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto time = end - start;

        std::cout << time / std::chrono::milliseconds(1) << "ms" << std::endl;
    }

    return 0;
}