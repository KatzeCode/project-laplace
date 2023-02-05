// Librerías
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
// -------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------
typedef std::vector<double> data_t; // Definición del tipo de dato Vector
// -------------------------------------------------------------------------------------------

// Variables globales
const double delta = 0.03;            // Tamaño del paso
const double xmin = 0.0;              // Valor mínimo en x
const double xmax = 1.0;              // Valor máximo en x
const double ymin = 0.0;              // Valor mínimo en y
const double ymax = 1.0;              // Valor máximo en y
const int nx = (xmax - xmin) / delta; // Cantidad de pasos en x
const int ny = (ymax - ymin) / delta; // Cantidad de pasos en y
const int r = nx / 3;                 // Radio de la circunferencia
const int maxnsteps = 2000;           // Cantidad máxima de pasos a realizar
// -------------------------------------------------------------------------------------------

// Declaración de funciones
void initial_conditions(data_t &data, int nx, int ny);
void boundary_conditions(data_t &data, int nx, int ny);
void print_file(const data_t &data, int nx, int ny);
double relaxation_step(data_t &data, int nx, int ny);
int evolve(data_t &data, int nx, int ny, int maxnsteps, double eps);
// -------------------------------------------------------------------------------------------

// Función main
int main() {

  data_t potential(nx * ny);
  double eps = 1.0e-4; // Tolerancia

  initial_conditions(potential, nx, ny);
  boundary_conditions(potential, nx, ny);

  int actual_nsteps = evolve(potential, nx, ny, maxnsteps, eps);

  std::cout << "Se relajó con " << actual_nsteps << " iteraciones."
            << "\n";

  return 0;
}
// --------------------------------------------------------------------------------------------

// Inicialización de funciones
void initial_conditions(data_t &data, int nx, int ny) { // Condiciones iniciales
  for (int ix = 0; ix < nx; ++ix) {
    for (int iy = 0; iy < ny; ++iy) {
      data[ix * ny + iy] = 0.0;
    }
  }
}

void boundary_conditions(data_t &data, int nx,
                         int ny) { // Condiciones de frontera
  int ix, iy;
  for (int ix = 0; ix < nx; ++ix) {
    for (int iy = 0; iy < ny; ++iy) {
      // Zona rectangular ---------------------------------------
      ix = 0;
      for (int iy = 0; iy < ny; ++iy) {
        data[ix * ny + iy] = 100.0;
      }
      ix = nx - 1;
      for (int iy = 0; iy < ny; ++iy) {
        data[ix * ny + iy] = 0.0;
      }
      iy = 0;
      for (int ix = 1; ix < nx; ++ix) {
        data[ix * ny + iy] = 0.0;
      }
      iy = ny - 1;
      for (int ix = 1; ix < nx; ++ix) {
        data[ix * ny + iy] = 0.0;
      }
      //   // Barra central -----------------------------------------
      //   ix = nx / 2;
      //   for (int iy = ny / 3; iy < 2 * (ny / 3); ++iy) {
      //     data[ix * ny + iy] = 100.0;
      //   }
      //   // -------------------------------------------------------
      //   int x = iy - ny / 2;
      //   int y = nx / 2 - ix;
      //   int sumsq = x * x + y * y;
      //   if ((pow(r - 2, 2) < sumsq) && (sumsq < pow(r + 2, 2))) {
      //     data[ix * ny + iy] = 100.0;
      //   }
    }
  }
}

double relaxation_step(data_t &data, int nx,
                       int ny) { // Paso de relajación
  double maxDELTA = -1;
  for (int ix = 1; ix < nx - 1; ++ix) {
    for (int iy = 1; iy < ny - 1; ++iy) {
      // Saltarse la barra central
      // if ((ix == nx / 2) &&
      // ((ny / 3) <= iy) && (iy <= 2 * (ny / 3))) {
      //   continue;
      // }
      // -------------------------------------------------------------------------
      // Saltarse la circunferencia
      // int x = iy - ny / 2;
      // int y = nx / 2 - ix;
      // int sumsq = x * x + y * y;
      // if ((pow(r - 2, 2) < sumsq) && (sumsq < pow(r + 2, 2))) {
      //   continue;
      // }
      // -------------------------------------------------------------------------
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

void print_file(const data_t &data, int nx,
                int ny) { // Imprimir en archivo para graficar
  std::ofstream file;
  file.open("tosend.txt");
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

int evolve(data_t &data, int nx, int ny, int maxnsteps,
           double eps) { // Evolución tras cada iteración
  int istep;
  for (istep = 0; istep < maxnsteps; ++istep) {
    double maxDELTA = relaxation_step(data, nx, ny);
    if (maxDELTA <= eps) {
      break;
    }
    print_file(data, nx, ny);
  }
  return istep;
}
