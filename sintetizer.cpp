/**
 * @Author: Rafael H. Tibaes <rafael>
 * @Date:   2017-06-01T10:35:43-03:00
 * @Email:  r@fael.nl
 * @Project: Biometrics Research
 * @Filename: sintetizer.cpp
 * @Last modified by:   rafael
 * @Last modified time: 2017-06-01T15:28:00-03:00
 * @License: MIT
 * @Copyright: Nandlands and Akiyama
 */

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <opencv2/core/ocl.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv) {
  const auto keys = "{help h usage ? | | Display this message}"
                    "{input i in | | input image}"
                    "{output o out | | output image}"
                    "{scale s | | scale factor in %}"
                    "{rotate90 r90 | | rotate in 90 degrees}"
                    "{rotate180 r180 | | rotate in 180 degrees}"
                    "{rotate270 r270 | | rotate in 270 degrees}"
                    "{crop1 c1 | | crop the first quadrant}"
                    "{crop2 c2 | | crop the second quadrant}"
                    "{crop3 c3 | | crop the third quadrant}"
                    "{crop4 c4 | | crop the fourth quadrant}"
                    "{crop0 c0 | | crop the center with half the size}"
                    "{nocl | | set to not use OpenCL}";
  auto cmd = CommandLineParser(argc, argv, keys);

  if (cmd.has("help") || !(cmd.has("input") && cmd.has("output"))) {
    cmd.printMessage();
    return 0;
  }

  ocl::setUseOpenCL((!cmd.has("nocl")));

  UMat input, output;
  imread(cmd.get<string>("input"), IMREAD_UNCHANGED).copyTo(input);
  input.copyTo(output);

  const auto halfHeight = input.size().height / 2;
  const auto halfWidth = input.size().width / 2;
  if (cmd.has("crop1"))
    input(Rect(0, 0, halfWidth, halfHeight)).copyTo(output); // first quadrant
  else if (cmd.has("crop2"))
    input(Rect(halfWidth, 0, halfWidth, halfHeight)).copyTo(output);
  else if (cmd.has("crop3"))
    input(Rect(halfWidth, halfHeight, halfWidth, halfHeight)).copyTo(output);
  else if (cmd.has("crop4"))
    input(Rect(0, halfHeight, halfWidth, halfHeight)).copyTo(output);
  else if (cmd.has("crop0"))
    input(Rect(halfWidth / 2, halfHeight / 2, halfWidth, halfHeight))
        .copyTo(output);
  output.copyTo(input);

  if (cmd.has("scale")) {
    double s = cmd.get<double>("scale");
    resize(input, output, Size(), s, s);
    output.copyTo(input);
  }

  if (cmd.has("rotate90"))
    rotate(input, output, ROTATE_90_CLOCKWISE);
  else if (cmd.has("rotate180"))
    rotate(input, output, ROTATE_180);
  else if (cmd.has("rotate270"))
    rotate(input, output, ROTATE_90_COUNTERCLOCKWISE);
  output.copyTo(input);

  imwrite(cmd.get<string>("output"), output);

  return 0;
}
