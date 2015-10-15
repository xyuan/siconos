/* Siconos-Kernel, Copyright INRIA 2005-2012.
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
/*! \file NewtonImpactFrictionNSL.hpp
  Newton-Impact Non-Smooth Law
*/

#ifndef NEWTONIMPACTFRICTIONNSLAW_H
#define NEWTONIMPACTFRICTIONNSLAW_H

#include "NonSmoothLaw.hpp"

/** Newton Impact-Friction Non Smooth Law
 *
 *  \author SICONOS Development Team - copyright INRIA
 *  \version 3.0.0.
 *  \date (Creation) March 22, 2005
 *
 *
 */
class NewtonImpactFrictionNSL : public NonSmoothLaw
{

private:
  /** serialization hooks
  */
  ACCEPT_SERIALIZATION(NewtonImpactFrictionNSL);

  /** The Newton coefficient of restitution
   */
  double _en;
  double _et;
  /** friction coefficient */
  double _mu;

  /** default constructor
   */
  NewtonImpactFrictionNSL();

public:

  /** basic constructor
   *  \param size size of the ns law
   */
  NewtonImpactFrictionNSL(unsigned int size);

  /** constructor with the value of the NewtonImpactFrictionNSL attributes
   *  \param en double : normal e coefficient
   *  \param et double : tangent e coefficient
   *  \param mu double : friction coefficient
   *  \param size unsigned int: size of the ns law
   */
  NewtonImpactFrictionNSL(double en, double et, double mu, unsigned int size);

  /** Destructor */
  ~NewtonImpactFrictionNSL();

  /** check the ns law to see if it is verified
   *  \return a boolean value whioch determines if the NS Law is verified
   */
  bool isVerified(void) const;

  // GETTERS/SETTERS

  /** getter of en
   *  \return the value of en
   */
  inline double en() const
  {
    return _en;
  };

  /** setter of en
   *  \param newVal a double to set en
   */
  inline void setEn(double newVal)
  {
    _en = newVal;
  };

  /** getter of et
   *  \return the value of et
   */
  inline double et() const
  {
    return _et;
  };

  /** setter of et
   * \param newVal a double to set et
   */
  inline void setEt(double newVal)
  {
    _et = newVal;
  };

  /** getter of mu
   * \return the value of mu
   */
  inline double mu() const
  {
    return _mu;
  };

  /** setter of mu
   * \param newVal a double to set mu
   */
  inline void setMu(double newVal)
  {
    _mu = newVal;
  };

  // OTHER FUNCTIONS

  /** print the data to the screen
   */
  void display() const;

  /** Visitors hook
   */
  ACCEPT_STD_VISITORS();

};
DEFINE_SPTR(NewtonImpactFrictionNSL)
#endif // NewtonImpactFrictionNSL_H