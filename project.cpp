#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

typedef std::vector<double> data_t;

// Global variables
const double delta = 0.01;
const double xmin = 0.0;
const double xmax = 1.0;
const double ymin = 0.0;
const double ymax = 1.0;
const int nx = (xmax - xmin) / delta;
const int ny = (ymax - ymin) / delta;
const int r = nx / 3;
const int maxnsteps = 2000;

// Function declarations
void initial_conditions(data_t &data, int nx, int ny);
void boundary_conditions(data_t &data, int nx, int ny);
double relaxation_step(data_t &data, int nx, int ny);
void print_file(const data_t &data, int nx, int ny);
int evolve(data_t &data, int nx, int ny, int maxnsteps, double eps);
void start_gnuplot(void);
void print_gnuplot(const data_t &data, int nx, int ny);

// Main
int main() {

  data_t potential(nx * ny);
  double eps = 1.0e-4;

  initial_conditions(potential, nx, ny);
  boundary_conditions(potential, nx, ny);

  int actual_nsteps = evolve(potential, nx, ny, maxnsteps, eps);

  std::cout << "Se relajó con " << actual_nsteps << " iteraciones."
            << "\n";

  return 0;
}

// Function initializations
void initial_conditions(data_t &data, int nx, int ny) {
  for (int ix = 0; ix < nx; ++ix) {
    for (int iy = 0; iy < ny; ++iy) {
      data[ix * ny + iy] = 0.0;
    }
  }
}

void boundary_conditions(data_t &data, int nx, int ny) {
  int ix, iy;
  for (int ix = 0; ix < nx; ++ix) {
    for (int iy = 0; iy < ny; ++iy) {
      int x = iy - ny / 2;
      int y = nx / 2 - ix;
      int sumsq = x * x + y * y;
      if ((pow(r - 2, 2) < sumsq) && (sumsq < pow(r + 2, 2))) {
        data[ix * ny + iy] = 100.0;
      }
    }
  }
  // BORDER BOUNDARY CONDITIONS
  //  First Row
  // ix = 0;
  // for (int iy = 0; iy < ny; ++iy) {
  //   data[ix * ny + iy] = 100.0;
  // }
  // // Last Row
  // ix = nx - 1;
  // for (int iy = 0; iy < ny; ++iy) {
  //   data[ix * ny + iy] = 0.0;
  // }
  // // First Column
  // iy = 0;
  // for (int ix = 1; ix < nx; ++ix) {
  //   data[ix * ny + iy] = 0.0;
  // }
  // // Last Column
  // iy = ny - 1;
  // for (int ix = 1; ix < nx; ++ix) {
  //   data[ix * ny + iy] = 0.0;
  // }
  // // INNER BOUNDARY CONDITIONS
  // //  First Row
  // ix = nx / 5;
  // for (int iy = ny / 5; iy < 4 * ny / 5; ++iy) {
  //   data[ix * ny + iy] = 100.0;
  // }
  // // Last Row
  // ix = 4 * nx / 5;
  // for (int iy = ny / 5; iy < 4 * ny / 5; ++iy) {
  //   data[ix * ny + iy] = 100.0;
  // }
  // // First Column
  // iy = ny / 5;
  // for (int ix = nx / 5; ix < 4 * nx / 5; ++ix) {
  //   data[ix * ny + iy] = 100.0;
  // }
  // // Last Column
  // iy = 4 * ny / 5;
  // for (int ix = nx / 5; ix < 4 * nx / 5; ++ix) {
  //   data[ix * ny + iy] = 100.0;
  // }
}

double relaxation_step(data_t &data, int nx, int ny) {
  double maxDELTA = -1;
  for (int ix = 1; ix < nx - 1; ++ix) {
    for (int iy = 1; iy < ny - 1; ++iy) {
      // if ((nx / 5 <= ix) && (ix <= 4 * nx / 5) && (iy == ny / 5)) {
      //   continue;
      // }
      // if ((nx / 5 <= ix) && (ix <= 4 * nx / 5) && (iy == 4 * ny / 5)) {
      //   continue;
      // }
      // if ((ny / 5 <= iy) && (iy <= 4 * ny / 5) && (ix == nx / 5)) {
      //   continue;
      // }
      // if ((ny / 5 <= iy) && (iy <= 4 * ny / 5) && (ix == 4 * nx / 5)) {
      //   continue;
      // }
      int x = iy - ny / 2;
      int y = nx / 2 - ix;
      int sumsq = x * x + y * y;
      if ((pow(r - 2, 2) < sumsq) && (sumsq < pow(r + 2, 2))) {
        continue;
      }
      double newval = (data[(ix + 1) * ny + iy] + data[(ix - 1) * ny + iy] +
                       data[ix * ny + (iy + 1)] + data[ix * ny + (iy - 1)]) /
                      4.0;
      double newDELTA = std::fabs(1 - (newval / data[ix * ny + iy]));
      if (newDELTA > maxDELTA) {
        maxDELTA = newDELTA;
      }
      data[ix * ny + iy] = newval;
    }
  }
  return maxDELTA;
}

void print_file(const data_t &data, int nx, int ny) {
  std::ofstream file;
  file.open("datafile.txt");
  for (int ix = 0; ix < nx; ++ix) {
    double x = xmin + ix * delta;
    for (int iy = 0; iy < nx; ++iy) {
      double y = ymin + iy * delta;
      file << x << "  " << y << "  " << data[ix * ny + iy] << "\n";
    }
    file << "\n";
  }
  file << "\n";
  file.close();
}

int evolve(data_t &data, int nx, int ny, int maxnsteps, double eps) {
  int istep;
  // start_gnuplot();
  for (istep = 0; istep < maxnsteps; ++istep) {
    double maxDELTA = relaxation_step(data, nx, ny);
    if (maxDELTA <= eps) {
      break;
    }
    // print_gnuplot(data, nx, ny);
    print_file(data, nx, ny);
  }
  return istep;
}

// void print_gnuplot(const data_t &data, int nx, int ny) {
//   std::cout << "splot '-' w l lt 3 \n";
//   for (int ix = 0; ix < nx; ++ix) {
//     double x = xmin + ix * delta;
//     for (int iy = 0; iy < ny; ++iy) {
//       double y = ymin + iy * delta;
//       std::cout << x << "  " << y << "  " << data[ix * ny + iy] << "\n";
//     }
//     std::cout << "\n";
//   }
//   std::cout << "e\n";
// }

// void start_gnuplot(void) {
//   std::cout << "set terminal gif animate\n";
//   std::cout << "set output 'anim.gif'\n";
//   std::cout << "set pm3d\n";
//   std::cout << "set contour base\n";
//   std::cout << "set hidden3d\n";
// }
