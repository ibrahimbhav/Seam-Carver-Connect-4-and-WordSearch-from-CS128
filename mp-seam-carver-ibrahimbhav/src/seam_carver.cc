#include "seam_carver.hpp"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "image_ppm.hpp"
// implement the rest of SeamCarver's functions here
// do nothing functions
const ImagePPM& SeamCarver::GetImage() const { return image_; }
int SeamCarver::GetHeight() const { return height_; }
int SeamCarver::GetWidth() const { return width_; }
/* St
START OF ENERGY CELL FUNCTION AND HELPER FUNCTIONS
*/
int SeamCarver::GetEnergy(int row, int col) const {
  int x = 0;
  // corner pixels
  if ((row == 0 && col == 0) || (row == height_ - 1 && col == 0) ||
      (row == 0 && col == width_ - 1) ||
      (row == height_ - 1 && col == width_ - 1)) {
    x = CornerPixels(row, col);
  }
  // middle pixels
  if (row != 0 && row != (height_ - 1) && col != 0 && col != (width_ - 1)) {
    x = MiddlePixels(row, col);
  }
  // border of image  NON-corner pixels
  return x;
}
int SeamCarver::MiddlePixels(int row, int col) const {
  Pixel p_down = image_.GetPixel(row + 1, col);
  Pixel p_up = image_.GetPixel(row - 1, col);
  Pixel p_left = image_.GetPixel(row, col - 1);
  Pixel p_right = image_.GetPixel(row, col + 1);
  int vert_red =
      (p_down.GetRed() - p_up.GetRed()) * (p_down.GetRed() - p_up.GetRed());
  int vert_green = (p_down.GetGreen() - p_up.GetGreen()) *
                   (p_down.GetGreen() - p_up.GetGreen());
  int vert_blue =
      (p_down.GetBlue() - p_up.GetBlue()) * (p_down.GetBlue() - p_up.GetBlue());
  int horiz_red = (p_left.GetRed() - p_right.GetRed()) *
                  (p_left.GetRed() - p_right.GetRed());
  int horiz_green = (p_left.GetGreen() - p_right.GetGreen()) *
                    (p_left.GetGreen() - p_right.GetGreen());
  int horiz_blue = (p_left.GetBlue() - p_right.GetBlue()) *
                   (p_left.GetBlue() - p_right.GetBlue());
  return vert_red + vert_green + vert_blue + horiz_red + horiz_green +
         horiz_blue;
}
// Border Pixels of the image excluding the corners
int SeamCarver::BorderPixels(int row, int col) const {
  Pixel p_down, p_up, p_left, p_right;
  if (row == 0 && col != 0 && col != width_ - 1) {
    p_up = image_.GetPixel(height_ - 1, col);
    p_down = image_.GetPixel(row + 1, col);
    p_left = image_.GetPixel(row, col - 1);
    p_right = image_.GetPixel(row, col + 1);
  } else if (row == height_ - 1 && col != 0 && col != width_ - 1) {
    p_up = image_.GetPixel(row - 1, col);
    p_down = image_.GetPixel(0, col);
    p_left = image_.GetPixel(row, col - 1);
    p_right = image_.GetPixel(row, col + 1);
  } else if (col == 0 && row != 0 && row != height_ - 1) {
    p_up = image_.GetPixel(row - 1, col);
    p_down = image_.GetPixel(row + 1, col);
    p_left = image_.GetPixel(row, width_ - 1);
    p_right = image_.GetPixel(row, col + 1);
  } else if (col == width_ - 1 && row != 0 && row != height_ - 1) {
    p_up = image_.GetPixel(row - 1, col);
    p_down = image_.GetPixel(row + 1, col);
    p_left = image_.GetPixel(row, col - 1);
    p_right = image_.GetPixel(row, 0);
  }
  int vert_red =
      (p_down.GetRed() - p_up.GetRed()) * (p_down.GetRed() - p_up.GetRed());
  int vert_green = (p_down.GetGreen() - p_up.GetGreen()) *
                   (p_down.GetGreen() - p_up.GetGreen());
  int vert_blue =
      (p_down.GetBlue() - p_up.GetBlue()) * (p_down.GetBlue() - p_up.GetBlue());
  int horiz_red = (p_left.GetRed() - p_right.GetRed()) *
                  (p_left.GetRed() - p_right.GetRed());
  int horiz_green = (p_left.GetGreen() - p_right.GetGreen()) *
                    (p_left.GetGreen() - p_right.GetGreen());
  int horiz_blue = (p_left.GetBlue() - p_right.GetBlue()) *
                   (p_left.GetBlue() - p_right.GetBlue());
  return vert_red + vert_green + vert_blue + horiz_red + horiz_green +
         horiz_blue;
}
// corner pixels
int SeamCarver::CornerPixels(int row, int col) const {
  Pixel p_up, p_down, p_left, p_right;
  if (row == 0 && col == 0) { 
    p_up = image_.GetPixel(height_ - 1, 0); 
    p_down = image_.GetPixel(1, 0);
    p_left = image_.GetPixel(0, width_ - 1);
    p_right = image_.GetPixel(row, col + 1);
  } else if (row == height_ - 1 && col == 0) {
  } else if (row == 0 && col == width_ - 1) {
  } else if(row == height_ - 1 && col == width_ - 1) {
  }
    return 0;
}
/**
 * END OF ENERGY CELL FUNCTIONS
 *
 */
int* SeamCarver::GetHorizontalSeam() const {
  int* r = new int[width_];
  for (int i = 0; i < width_; i++) {
    r[i] = 0;
  }
  return r;
}
int* SeamCarver::GetVerticalSeam() const {
  int* a = new int[height_];
  for (int i = 0; i < height_; i++) {
    a[i] = 0;
  }
  return a;
}
void SeamCarver::RemoveHorizontalSeam() {}
void SeamCarver::RemoveVerticalSeam() {}
// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}
