/* Siconos-sample version 3.0.0, Copyright INRIA 2005-2008.
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
 * Contact: Vincent ACARY vincent.acary@inrialpes.fr
 */

/*!\file BallOnMovingPlane.cpp
  \brief \ref EMBallOnMovingPlane - C++ input file, Time-Stepping version -
  V. Acary

  A Ball bouncing on a moving plane.
  This example shows how some precribed boundary conditions can be imposed.
  Simulation with a Time-Stepping scheme.
*/

#include "SiconosKernel.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  try
  {

    // ================= Creation of the model =======================

    // User-defined main parameters
    unsigned int nDof = 3;           // degrees of freedom for the ball
    double t0 = 0;                   // initial computation time
    double T = 10.0;                  // final computation time
    double h = 0.005;                // time step
    double position_init = 1.0;      // initial position for lowest bead.
    double velocity_init = 0.0;      // initial velocity for lowest bead.
    double theta = 0.5;              // theta for Moreau integrator
    double R = 0.1; // Ball radius
    double m = 1; // Ball mass
    double g = 9.81; // Gravity
    // -------------------------
    // --- Dynamical systems ---
    // -------------------------

    cout << "====> Model loading ..." << endl << endl;

    SP::SiconosMatrix Mass(new SimpleMatrix(nDof, nDof));
    (*Mass)(0, 0) = m;
    (*Mass)(1, 1) = m;
    (*Mass)(2, 2) = 3. / 5 * m * R * R;

    // -- Initial positions and velocities --
    SP::SimpleVector q0(new SimpleVector(nDof));
    SP::SimpleVector v0(new SimpleVector(nDof));
    (*q0)(0) = position_init;
    (*v0)(0) = velocity_init;

    // -- The dynamical system --
    SP::LagrangianLinearTIDS ball(new LagrangianLinearTIDS(q0, v0, Mass));

    // -- Set external forces (weight) --
    SP::SimpleVector weight(new SimpleVector(nDof));
    (*weight)(0) = -m * g;
    ball->setFExtPtr(weight);

    // -- Moving Plane --


    // -- Initial positions and velocities --
    SP::SimpleVector q02(new SimpleVector(nDof));
    SP::SimpleVector v02(new SimpleVector(nDof));
    (*q02)(0) = 0.0;
    (*v02)(0) = velocity_init;

    // -- The dynamical system --
    SP::LagrangianLinearTIDS movingplane(new LagrangianLinearTIDS(q02, v02, Mass));

    // -- Set external forces (weight) --
    movingplane->setFExtPtr(weight);

    SP::IndexInt bdindex(new IndexInt(1));
    (*bdindex)[0] = 0;

    //    SP::SimpleVector bdPrescribedVelocity(new SimpleVector(1));
    //    bdPrescribedVelocity->setValue(0,0.5);
    //    SP::BoundaryCondition bd (new BoundaryCondition(&bdindex,bdPrescribedVelocity));


    SP::BoundaryCondition bd(new BoundaryCondition(bdindex));
    bd->setComputePrescribedVelocityFunction("BallOnMovingPlanePlugin.so", "prescribedvelocity");


    movingplane->setBoundaryConditions(bd);



    // --------------------
    // --- Interactions ---
    // --------------------

    // -- nslaw --
    double e = 0.9;

    // Interaction ball-plane
    //
    SP::SiconosMatrix H(new SimpleMatrix(1, 2 * nDof));
    (*H)(0, 0) = 1.0;
    (*H)(0, 3) = -1.0;

    SP::NonSmoothLaw nslaw(new NewtonImpactNSL(e));
    SP::Relation relation(new LagrangianLinearTIR(H));

    SP::Interaction inter(new Interaction(1, nslaw, relation));

    // -------------
    // --- Model ---
    // -------------
    SP::Model bouncingBall(new Model(t0, T));

    // add the dynamical system in the non smooth dynamical system
    bouncingBall->nonSmoothDynamicalSystem()->insertDynamicalSystem(ball);
    bouncingBall->nonSmoothDynamicalSystem()->insertDynamicalSystem(movingplane);

    // link the interaction and the dynamical system
    bouncingBall->nonSmoothDynamicalSystem()->link(inter, ball);
    bouncingBall->nonSmoothDynamicalSystem()->link(inter, movingplane);


    // ------------------
    // --- Simulation ---
    // ------------------

    // -- (1) OneStepIntegrators --
    SP::Moreau OSI(new Moreau(ball, theta));
    OSI->insertDynamicalSystem(movingplane);

    // -- (2) Time discretisation --
    SP::TimeDiscretisation t(new TimeDiscretisation(t0, h));

    // -- (3) one step non smooth problem
    SP::OneStepNSProblem osnspb(new LCP());

    // -- (4) Simulation setup with (1) (2) (3)
    SP::TimeStepping s(new TimeStepping(t, OSI, osnspb));

    // =========================== End of model definition ===========================

    // ================================= Computation =================================

    // --- Simulation initialization ---

    cout << "====> Initialisation ..." << endl << endl;
    bouncingBall->initialize(s);
    int N = ceil((T - t0) / h); // Number of time steps

    // --- Get the values to be plotted ---
    // -> saved in a matrix dataPlot
    unsigned int outputSize = 12;
    SimpleMatrix dataPlot(N, outputSize);

    SP::SiconosVector q = ball->q();
    SP::SiconosVector v = ball->velocity();
    SP::SiconosVector p = ball->p(2);
    SP::SiconosVector qplane = movingplane->q();
    SP::SiconosVector vplane = movingplane->velocity();
    SP::SiconosVector pplane = movingplane->p(2);
    SP::SiconosVector lambda = inter->lambda(1);
    SP::SiconosVector reaction = movingplane->reactionToBoundaryConditions();

    dataPlot(0, 0) = bouncingBall->t0();
    dataPlot(0, 1) = (*q)(0);
    dataPlot(0, 2) = (*v)(0);
    dataPlot(0, 3) = (*p)(0);
    dataPlot(0, 4) = (*lambda)(0);
    dataPlot(0, 5) = (*q)(0);
    dataPlot(0, 6) = (*v)(0);
    dataPlot(0, 7) = (*qplane)(0);
    dataPlot(0, 8) = (*vplane)(0);
    dataPlot(0, 9) = (*qplane)(1);
    dataPlot(0, 10) = (*vplane)(1);
    dataPlot(0, 11) = (*reaction)(0);
    // --- Time loop ---
    cout << "====> Start computation ... " << endl << endl;
    // ==== Simulation loop - Writing without explicit event handling =====
    int k = 1;
    boost::progress_display show_progress(N);

    boost::timer time;
    time.restart();

    while (s->nextTime() < T)
    {
      s->computeOneStep();

      // --- Get values to be plotted ---
      dataPlot(k, 0) =  s->nextTime();
      dataPlot(k, 1) = (*q)(0);
      dataPlot(k, 2) = (*v)(0);
      dataPlot(k, 3) = (*p)(0);
      dataPlot(k, 4) = (*lambda)(0);
      dataPlot(k, 5) = (*q)(1);
      dataPlot(k, 6) = (*v)(1);
      dataPlot(k, 7) = (*qplane)(0);
      dataPlot(k, 8) = (*vplane)(0);
      dataPlot(k, 9) = (*qplane)(1);
      dataPlot(k, 10) = (*vplane)(1);
      dataPlot(k, 11) = (*reaction)(0);

      s->nextStep();
      ++show_progress;
      k++;
    }
    cout << endl << "End of computation - Number of iterations done: " << k - 1 << endl;
    cout << "Computation Time " << time.elapsed()  << endl;

    // --- Output files ---
    cout << "====> Output file writing ..." << endl;
    ioMatrix io("result.dat", "ascii");
    io.write(dataPlot, "noDim");



  }

  catch (SiconosException e)
  {
    cout << e.report() << endl;
  }
  catch (...)
  {
    cout << "Exception caught in BallOnMovingPlane.cpp" << endl;
  }



}
