#include <cmath>
#include <iostream>
#include <vector>

typedef std::vector<double> data_t;

// Global variables
const double delta = 0.05;
const double xmin = 0.0;
const double xmax = 1.0;
const double ymin = 0.0;
const double ymax = 1.2;
const int nx = (xmax - xmin) / delta;
const int ny = (ymax - ymin) / delta;
const int nsteps = 200;

// Function declarations
void initial_conditions(data_t &data, int nx, int ny);
void boundary_conditions(data_t &data, int nx, int ny);
void relaxation_step(data_t &data, int nx, int ny);
void print_screen(const data_t &data, int nx, int ny);
void start_gnuplot(void);
void print_gnuplot(const data_t &data, int nx, int ny);
void evolve(data_t &data, int nx, int ny, int nsteps);
//

// Main
int main() {

  data_t potential(nx * ny);

  initial_conditions(potential, nx, ny);
  boundary_conditions(potential, nx, ny);

  evolve(potential, nx, ny, nsteps);

  return 0;
}
//

// Function initializations
void initial_conditions(data_t &data, int nx, int ny) {
  for (int ix = 0; ix < nx; ++ix) {
    for (int iy = 0; iy < ny; ++iy) {
      data[ix * ny + iy] = 1.0;
    }
  }
}

void boundary_conditions(data_t &data, int nx, int ny) {
  int ix, iy;
  // First Row
  ix = 0;
  for (int iy = 0; iy < ny; ++iy) {
    data[ix * ny + iy] = 100.0;
  }
  // Last Row
  ix = nx - 1;
  for (int iy = 0; iy < ny; ++iy) {
    data[ix * ny + iy] = 0.0;
  }
  // First Column
  iy = 0;
  for (int ix = 1; ix < nx; ++ix) {
    data[ix * ny + iy] = 0.0;
  }
  // Last Column
  iy = ny - 1;
  for (int ix = 1; ix < nx; ++ix) {
    data[ix * ny + iy] = 0.0;
  }
  // New boundary
  ix = nx / 2;
  for (int iy = ny / 3; iy < 2 * (ny / 3); ++iy) {
    data[ix * ny + iy] = -50.0;
  }
}

void relaxation_step(data_t &data, int nx, int ny) {
  // Recorre la matriz cuidando de no modificar las condiciones de frontera.
  for (int ix = 1; ix < nx - 1; ++ix) {
    for (int iy = 1; iy < ny - 1; ++iy) {
      // Revisar que la celda no es condición de frontera. if (si es condición)
      // {continue;}
      if ((ix == nx / 2) && ((ny / 3) <= iy) && (iy <= 2 * (ny / 3))) {
        continue;
      }
      data[ix * ny + iy] =
          (data[(ix + 1) * ny + iy] + data[(ix - 1) * ny + iy] +
           data[ix * ny + (iy + 1)] + data[ix * ny + (iy - 1)]) /
          4.0;
    }
  }
}

void print_screen(const data_t &data, int nx, int ny) {
  for (int ix = 0; ix < nx; ++ix) {
    for (int iy = 0; iy < ny; ++iy) {
      std::cout << data[ix * ny + iy] << "  ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void start_gnuplot(void) {
  std::cout << "set terminal gif animate\n";
  std::cout << "set output 'anim.gif'\n";
  std::cout << "set pm3d\n";
  std::cout << "set contour base\n";
}

void print_gnuplot(const data_t &data, int nx, int ny) {
  std::cout << "splot '-' w l lt 3 \n";
  for (int ix = 0; ix < nx; ++ix) {
    double x = xmin + ix * delta;
    for (int iy = 0; iy < ny; ++iy) {
      double y = ymin + iy * delta;
      std::cout << x << "  " << y << "  " << data[ix * ny + iy] << "\n";
    }
    std::cout << "\n";
  }
  std::cout << "e\n";
}

void evolve(data_t &data, int nx, int ny, int nsteps) {
  start_gnuplot();
  for (int istep = 0; istep < nsteps; ++istep) {
    relaxation_step(data, nx, ny);
    print_gnuplot(data, nx, ny);
  }
}
//
