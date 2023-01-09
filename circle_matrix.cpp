#include <cmath>
#include <iostream>
#include <vector>

const double xmin = 0;
const double xmax = 24;
const double ymin = 0;
const double ymax = 24;
const double delta = 1.0;
const int nx = (xmax - xmin) / delta;
const int ny = (ymax - ymin) / delta;
const int r = nx / 3;

void initial_values(std::vector<double> &vectormatrix, int nx, int ny) {
  for (int ix = 0; ix < nx; ++ix) {
    for (int iy = 0; iy < ny; ++iy) {
      vectormatrix[ix * ny + iy] = 0.0;
    }
  }
}

void boundaries(std::vector<double> &vectormatrix, int nx, int ny) {
  for (int ix = 0; ix < nx; ++ix) {
    for (int iy = 0; iy < ny; ++iy) {
      int x = iy - ny / 2;
      int y = nx / 2 - ix;
      int sumsq = x * x + y * y;
      if ((pow(r - 2, 2) < sumsq) && (sumsq < pow(r + 2, 2))) {
        vectormatrix[ix * ny + iy] = 5.0;
      }
    }
  }
}

void print_values(const std::vector<double> &vectormatrix, int nx, int ny) {
  for (int ix = 0; ix < nx; ++ix) {
    for (int iy = 0; iy < ny; ++iy) {
      std::cout << vectormatrix[ix * ny + iy] << "  ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

int main() {

  std::vector<double> vectormatrix(nx * ny);

  initial_values(vectormatrix, nx, ny);
  boundaries(vectormatrix, nx, ny);
  print_values(vectormatrix, nx, ny);

  return 0;
}
