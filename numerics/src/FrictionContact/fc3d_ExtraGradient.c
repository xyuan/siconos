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
#include "projectionOnCone.h"
#include "fc3d_Solvers.h"
#include "fc3d_compute_error.h"
#include "SiconosBlas.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* #define DEBUG_STDOUT */
/* #define DEBUG_MESSAGES */
#include "debug.h"

void fc3d_ExtraGradient(FrictionContactProblem* problem, double *reaction, double *velocity, int* info, SolverOptions* options)
{
  /* int and double parameters */
  int* iparam = options->iparam;
  double* dparam = options->dparam;
  /* Number of contacts */
  int nc = problem->numberOfContacts;
  double* q = problem->q;
  NumericsMatrix* M = problem->M;
  double* mu = problem->mu;
  /* Dimension of the problem */
  int n = 3 * nc;
  /* Maximum number of iterations */
  int itermax = iparam[0];
  /* Tolerance */
  double tolerance = dparam[0];





  /*****  Fixed point iterations *****/
  int iter = 0; /* Current iteration number */
  double error = 1.; /* Current error */
  int hasNotConverged = 1;
  int contact; /* Number of the current row of blocks in M */
  int nLocal = 3;
  dparam[0] = dparam[2]; // set the tolerance for the local solver


  double * velocitytmp = (double *)malloc(n * sizeof(double));
  double * reactiontmp = (double *)malloc(n * sizeof(double));

  double rho = 0.0, rho_k =0.0;
  int isVariable = 0;

  if (dparam[3] > 0.0)
  {    
    rho = dparam[3];
    if (verbose > 0)
    {
      printf("----------------------------------- FC3D - Extra Gradient (EG) - Fixed stepsize with  rho = %14.7e \n", rho); 
    }
  }
  else
  {
    /* Variable step in iterations*/
    isVariable = 1;  
    rho = -dparam[3];
    if (verbose > 0)
    {
      printf("----------------------------------- FC3D - Extra Gradient (EG) - Variable stepsize with starting rho = %14.7e \n", rho);
    }
     
  }

  double alpha = 1.0;
  double beta = 1.0;

  /* Variable for Line_search */
  int success =0;
  double error_k;
  int ls_iter = 0;
  int ls_itermax = 10;
  double tau=0.6, L= 0.9, Lmin =0.3, taumin=0.7;
  double a1=0.0, a2=0.0;
  double * reaction_k =0;
  double * velocity_k =0;

  if (isVariable)
  {
    reaction_k = (double *)malloc(n * sizeof(double));
    velocity_k = (double *)malloc(n * sizeof(double));
  }

  if (!isVariable)
  {
    /*   double minusrho  = -1.0*rho; */
    while ((iter < itermax) && (hasNotConverged > 0))
    {
      ++iter;

      /* reactiontmp <- reaction  */
      cblas_dcopy(n , reaction , 1 , reactiontmp, 1);

      /* velocitytmp <- q  */
      cblas_dcopy(n , q , 1 , velocitytmp, 1);


      prodNumericsMatrix(n, n, alpha, M, reactiontmp, beta, velocitytmp);
      // projection for each contact
      for (contact = 0 ; contact < nc ; ++contact)
      {
        int pos = contact * nLocal;
        double  normUT = sqrt(velocitytmp[pos + 1] * velocitytmp[pos + 1] + velocitytmp[pos + 2] * velocitytmp[pos + 2]);
        reactiontmp[pos] -= rho * (velocitytmp[pos] + mu[contact] * normUT);
        reactiontmp[pos + 1] -= rho * velocitytmp[pos + 1];
        reactiontmp[pos + 2] -= rho * velocitytmp[pos + 2];
        projectionOnCone(&reactiontmp[pos], mu[contact]);
      }
      cblas_dcopy(n , q , 1 , velocitytmp, 1);
      prodNumericsMatrix(n, n, alpha, M, reactiontmp, beta, velocitytmp);
      // projection for each contact
      for (contact = 0 ; contact < nc ; ++contact)
      {
        int pos = contact * nLocal;
        double  normUT = sqrt(velocitytmp[pos + 1] * velocitytmp[pos + 1] + velocitytmp[pos + 2] * velocitytmp[pos + 2]);
        reaction[pos] -= rho * (velocitytmp[pos] + mu[contact] * normUT);
        reaction[pos + 1] -= rho * velocitytmp[pos + 1];
        reaction[pos + 2] -= rho * velocitytmp[pos + 2];
        projectionOnCone(&reaction[pos], mu[contact]);
      }

      /* **** Criterium convergence **** */
      fc3d_compute_error(problem, reaction , velocity, tolerance, options, &error);

      if (options->callback)
      {
        options->callback->collectStatsIteration(options->callback->env, nc * 3, 
                                        reaction, velocity, 
                                        error, NULL);
      }

      if (verbose > 0)
      {
        printf("----------------------------------- FC3D - Extra Gradient (EG) - Iteration %i rho = %14.7e \tError = %14.7e\n", iter, rho, error);
      }
      if (error < tolerance) hasNotConverged = 0;
      *info = hasNotConverged;
    }
  }

  if (isVariable)
  {
    while ((iter < itermax) && (hasNotConverged > 0))
    {
      ++iter;


      /* Store the error */
      error_k = error;
      /* store the reaction at the beginning of the iteration */
      cblas_dcopy(n , reaction , 1 , reaction_k, 1);

      /* velocity_k <- q  */
      cblas_dcopy(n , q , 1 , velocity_k, 1);

      /* velocity_k <- q + M * reaction_k  */
      beta = 1.0;
      prodNumericsMatrix(n, n, alpha, M, reaction_k, beta, velocity_k);

      ls_iter = 0 ;
      success =0;

      while (!success && (ls_iter < ls_itermax))
      {

        rho_k = rho * pow(tau,ls_iter);

        /* projection for each contact */
        for (contact = 0 ; contact < nc ; ++contact)
        {
          int pos = contact * nLocal;
          double  normUT = sqrt(velocity_k[pos + 1] * velocity_k[pos + 1] + velocity_k[pos + 2] * velocity_k[pos + 2]);
          /* reaction[pos] = reaction_k[pos] -  rho_k * (velocity_k[pos] + mu[contact] * normUT); */
          /* reaction[pos + 1] = reaction_k[pos+1] - rho_k * velocity_k[pos + 1]; */
          /* reaction[pos + 2] = reaction_k[pos+2] - rho_k * velocity_k[pos + 2]; */

          reaction[pos] -= rho_k * (velocity_k[pos] + mu[contact] * normUT);
          reaction[pos + 1] -= rho_k * velocity_k[pos + 1];
          reaction[pos + 2] -= rho_k * velocity_k[pos + 2];
          projectionOnCone(&reaction[pos], mu[contact]);
        }


        /* velocity <- q + M * reaction  */
        beta = 1.0;
        cblas_dcopy(n , q , 1 , velocity, 1);
        prodNumericsMatrix(n, n, alpha, M, reaction, beta, velocity);


        /* velocitytmp <- velocity */

        DEBUG_EXPR_WE( for (int i =0; i< 5 ; i++)
                       {
                         printf("reaction[%i]=%12.8e\t",i,reaction[i]);    printf("velocity[%i]=F[%i]=%12.8e\n",i,i,velocity[i]);
                       }
          );
        cblas_dcopy(n, velocity, 1, velocitytmp , 1) ;
        /* velocitytmp <- modified velocity - velocity_k   */
        for (contact = 0 ; contact < nc ; ++contact)
        {
          int pos = contact * nLocal;
          double  normUT = sqrt(velocitytmp[pos + 1] * velocitytmp[pos + 1]
                                + velocitytmp[pos + 2] * velocitytmp[pos + 2]);
          double  normUT_k = sqrt(velocity_k[pos + 1] * velocity_k[pos + 1] + velocity_k[pos + 2] * velocity_k[pos + 2]);
          velocitytmp[pos] += mu[contact] * (normUT -normUT_k)  ;
        }

        /* for (contact = 0 ; contact < nc ; ++contact) */
        /* { */
        /*   int pos = contact * nLocal; */
        /*   double  normUT = sqrt(velocity_k[pos + 1] * velocity_k[pos + 1] + velocity_k[pos + 2] * velocity_k[pos + 2]); */
        /*   velocity_k[pos] += mu[contact] * normUT; */
        /* } */

        cblas_daxpy(n, -1.0, velocity_k , 1, velocitytmp , 1) ;

        a1 = cblas_dnrm2(n, velocitytmp, 1);
        DEBUG_PRINTF("a1 = %12.8e\n", a1);

        /* reactiontmp <- reaction */
        cblas_dcopy(n, reaction, 1, reactiontmp , 1) ;

        /* reactiontmp <- reaction - reaction_k   */
        cblas_daxpy(n, -1.0, reaction_k , 1, reactiontmp , 1) ;

        a2 = cblas_dnrm2(n, reactiontmp, 1) ;
        DEBUG_PRINTF("a2 = %12.8e\n", a2);

        success = (rho_k*a1 < L * a2)?1:0;

        /* printf("rho_k = %12.8e\t", rho_k); */
        /* printf("a1 = %12.8e\t", a1); */
        /* printf("a2 = %12.8e\t", a2); */
        /* printf("norm reaction = %12.8e\t",cblas_dnrm2(n, reaction, 1) ); */
        /* printf("success = %i\n", success); */

        ls_iter++;
      }
      /* velocitytmp <- M* reaction* q  */
      cblas_dcopy(n , q , 1 , velocitytmp, 1);
      prodNumericsMatrix(n, n, alpha, M, reaction, beta, velocitytmp);

      // projection for each contact
      for (contact = 0 ; contact < nc ; ++contact)
      {
        int pos = contact * nLocal;
        double  normUT = sqrt(velocitytmp[pos + 1] * velocitytmp[pos + 1] +
                              velocitytmp[pos + 2] * velocitytmp[pos + 2]);
        reaction[pos] -= rho_k * (velocitytmp[pos] + mu[contact] * normUT);
        reaction[pos + 1] -= rho_k * velocitytmp[pos + 1];
        reaction[pos + 2] -= rho_k * velocitytmp[pos + 2];
        /* reaction[pos] = reaction_k[pos] -  rho_k * (velocitytmp[pos] + mu[contact] * normUT); */
        /* reaction[pos + 1] = reaction_k[pos+1] - rho_k * velocitytmp[pos + 1]; */
        /* reaction[pos + 2] = reaction_k[pos+2] - rho_k * velocitytmp[pos + 2]; */
        projectionOnCone(&reaction[pos], mu[contact]);
      }
      DEBUG_EXPR_WE( for (int i =0; i< 5 ; i++)
                     {
                       printf("reaction[%i]=%12.8e\t",i,reaction[i]);    printf("velocity[%i]=F[%i]=%12.8e\n",i,i,velocity[i]);
                     }
        );

      /* **** Criterium convergence **** */
      fc3d_compute_error(problem, reaction , velocity, tolerance, options, &error);
      DEBUG_PRINTF("error = %12.8e\t error_k = %12.8e\n",error,error_k);
      /*Update rho*/
      if ((rho_k*a1 < Lmin * a2) && (error < error_k))
      {
        rho =rho_k/taumin;
      }
      else
        rho =rho_k;





      if (verbose > 0)
      {
        printf("----------------------------------- FC3D - Extra Gradient (EG) - Iteration %i rho = %14.7e \tError = %14.7e\n", iter, rho, error);
      }
      if (error < tolerance) hasNotConverged = 0;
      *info = hasNotConverged;
    }
  }


  if (verbose > 0)
  {
    printf("----------------------------------- FC3D -  Extra Gradient (EG) - #Iteration %i Final Residual = %14.7e\n", iter, error);
  }
  dparam[0] = tolerance;
  dparam[1] = error;
  iparam[7] = iter;
  free(velocitytmp);
  free(reactiontmp);
  if (isVariable)
  {
    free(reaction_k);
    free(velocity_k);
  }
}


int fc3d_ExtraGradient_setDefaultSolverOptions(SolverOptions* options)
{
  int i;
  if (verbose > 0)
  {
    printf("Set the Default SolverOptions for the ExtraGradient Solver\n");
  }

  /*strcpy(options->solverName,"DSFP");*/
  options->solverId = SICONOS_FRICTION_3D_EG;
  options->numberOfInternalSolvers = 0;
  options->isSet = 1;
  options->filterOn = 1;
  options->iSize = 8;
  options->dSize = 8;
  options->iparam = (int *)malloc(options->iSize * sizeof(int));
  options->dparam = (double *)malloc(options->dSize * sizeof(double));
  options->dWork = NULL;
  null_SolverOptions(options);
  for (i = 0; i < 8; i++)
  {
    options->iparam[i] = 0;
    options->dparam[i] = 0.0;
  }
  options->iparam[0] = 20000;
  options->dparam[0] = 1e-3;
  options->dparam[3] = 1e-3;
  options->dparam[3] = -1.0; // rho is variable by default

  options->internalSolvers = NULL;

  return 0;
}
