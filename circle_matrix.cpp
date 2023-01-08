#include <cmath>
#include <iostream>
#include <vector>

const int nx = 9.0;
const int ny = 9.0;
const int a = nx / 2 * ny;
const int b = ny / 2;

void initial_values(std::vector<double> &vectormatrix, int nx, int ny) {
  for (int ix = 0; ix < nx; ++ix) {
    for (int iy = 0; iy < ny; ++iy) {
      vectormatrix[ix * ny + iy] = 0.0;
    }
  }
}

void boundaries(std::vector<double> &vectormatrix, int nx, int ny) {
  int ix, iy;
  vectormatrix[a + b] = 5.0;
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
