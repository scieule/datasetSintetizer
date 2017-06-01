/**
 * @Author: Rafael H. Tibaes <rafael>
 * @Date:   2017-06-01T10:35:43-03:00
 * @Email:  r@fael.nl
 * @Project: Biometrics Research
 * @Filename: sintetizer.cpp
 * @Last modified by:   rafael
 * @Last modified time: 2017-06-01T11:11:05-03:00
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
  const auto keys =
      "{help h usage ? | | Display this message}"
      "{input i in | | input image}"
      "{output o out | | output image}"
      "{scale s | | scale factor in %}"
      "{rotation rot r | | rotation in degrees}"
      "{crop c | | size of the computed crops in % relative to input}"
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

  // TODO: computation

  imwrite(cmd.get<string>("output"), output);

  return 0;
}
