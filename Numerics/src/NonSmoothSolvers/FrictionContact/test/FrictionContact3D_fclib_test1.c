/* Siconos-Numerics, Copyright INRIA 2005-2012.
 * Siconos is a program dedicated to modeling, simulation and control
 * of non smooth dynamical systems.
 * Siconos is a free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * Siconos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Siconos; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Contact: Vincent ACARY, siconos-team@lists.gforge.inria.fr
 */
#include <stdio.h>
#include <stdlib.h>
#include "NonSmoothDrivers.h"
#include "frictionContact_test_function.h"


int main(void)
{
  int info = 0 ;
  printf("Test on ./data/Capsules-i125-1213.hdf5\n");

  SolverOptions * options = (SolverOptions *) malloc(sizeof(SolverOptions));
  info = frictionContact3D_setDefaultSolverOptions(options, SICONOS_FRICTION_3D_LOCALFB);
  options->dparam[0] = 1e-08;
  options->iparam[0] = 10000;

  info = frictionContact_test_function_hdf5("./data/Capsules-i125-1213.hdf5", options);

  deleteSolverOptions(options);
  free(options);
  printf("\nEnd of test on ./data/Capsules-i125-1213.hdf5\n");
  return info;
}