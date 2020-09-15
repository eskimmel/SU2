﻿/*!
 * \file CNEMONSSolver.hpp
 * \brief Headers of the CNEMONSSolver class
 * \author S. R. Copeland, F. Palacios, W. Maier.
 * \version 7.0.6 "Blackbird"
 *
 * SU2 Project Website: https://su2code.github.io
 *
 * The SU2 Project is maintained by the SU2 Foundation
 * (http://su2foundation.org)
 *
 * Copyright 2012-2020, SU2 Contributors (cf. AUTHORS.md)
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <cmath>
#include <iostream>
#include <cstdlib>

#include "CNEMOEulerSolver.hpp"

/*!
 * \class CNEMONSSolver
 * \brief Main class for defining the NEMO Navier-Stokes flow solver.
 * \ingroup Navier_Stokes_Equations
 * \author S. R. Copeland, F. Palacios, W. Maier.
 * \version 6.1
 */
class CNEMONSSolver final : public CNEMOEulerSolver {
private:

  su2double Prandtl_Lam,   /*!< \brief Laminar Prandtl number. */
  Prandtl_Turb;            /*!< \brief Turbulent Prandtl number. */
 
  su2double StrainMag_Max, Omega_Max; /*!< \brief Maximum Strain Rate magnitude and Omega. */
  su2double *primitives_aux; /*!< \brief Primitive auxiliary variables (Y_s, T, Tve, ...) in compressible flows. */

public:

  /*!
   * \brief Constructor of the class.
   */
  CNEMONSSolver() = default;

  /*!
   * \overload
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  CNEMONSSolver(CGeometry *geometry, CConfig *config, unsigned short iMesh);

  /*!
   * \brief Destructor of the class.
   */
  ~CNEMONSSolver(void) override;

  /*!
   * \brief Restart residual and compute gradients.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] config - Definition of the particular problem.
   * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
   * \param[in] RunTime_EqSystem - System of equations which is going to be solved.
   * \param[in] Output - boolean to determine whether to print output.
   */
  void Preprocessing(CGeometry *geometry,
                    CSolver **solver_container,
                    CConfig *config,
                    unsigned short iMesh,
                    unsigned short iRKStep,
                    unsigned short RunTime_EqSystem,
                    bool Output) override;

  /*!
   * \brief Compute the gradient of the primitive variables using Green-Gauss method,
   *        and stores the result in the <i>Gradient_Primitive</i> variable.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] config - Definition of the particular problem.
   * \param[in] reconstruction - indicator that the gradient being computed is for upwind reconstruction.
   */
  void SetPrimitive_Gradient_GG(CGeometry *geometry,
                                const CConfig *config,
                                bool reconstruction = false) override;

  /*!
   * \brief Compute the gradient of the primitive variables using a Least-Squares method,
   *        and stores the result in the <i>Gradient_Primitive</i> variable.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] config - Definition of the particular problem.
   * \param[in] reconstruction - indicator that the gradient being computed is for upwind reconstruction.
   */
  void SetPrimitive_Gradient_LS(CGeometry *geometry,
                                const CConfig *config,
                                bool reconstruction = false) override;

  /*!
   * \brief Impose a constant heat-flux condition at the wall.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] conv_numerics - Description of the numerical method for convective terms.
   * \param[in] visc_numerics - Description of the numerical method for viscous terms.
   * \param[in] config - Definition of the particular problem.
   * \param[in] val_marker - Surface marker where the boundary condition is applied.
   */
  void BC_HeatFlux_Wall(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics,
                        CNumerics *visc_numerics, CConfig *config, unsigned short val_marker) override;

  /*!
   * \brief Impose a constant heat-flux condition at the wall.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] conv_numerics - Description of the numerical method for convective terms.
   * \param[in] visc_numerics - Description of the numerical method for viscous terms.
   * \param[in] config - Definition of the particular problem.
   * \param[in] val_marker - Surface marker where the boundary condition is applied.
   */
  void BC_HeatFluxCatalytic_Wall(CGeometry *geometry,
                                 CSolver **solver_container,
                                 CNumerics *conv_numerics,
                                 CNumerics *visc_numerics,
                                 CConfig *config, unsigned short val_marker);

  /*!
   * \brief Impose a constant heat-flux condition at the wall.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] conv_numerics - Description of the numerical method for convective terms.
   * \param[in] visc_numerics - Description of the numerical method for viscous terms.
   * \param[in] config - Definition of the particular problem.
   * \param[in] val_marker - Surface marker where the boundary condition is applied.
   */
  void BC_HeatFluxNonCatalytic_Wall(CGeometry *geometry,
                                    CSolver **solver_container,
                                    CNumerics *conv_numerics,
                                    CNumerics *visc_numerics,
                                    CConfig *config, unsigned short val_marker);

  /*!
   * \brief Generic implementation of the isothermal wall.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] conv_numerics - Description of the numerical method for convective terms.
   * \param[in] visc_numerics - Description of the numerical method for viscous terms.
   * \param[in] config - Definition of the particular problem.
   * \param[in] val_marker - Surface marker where the boundary condition is applied.
   */
  void BC_Isothermal_Wall(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics,
                          CNumerics *visc_numerics, CConfig *config, unsigned short val_marker) override;

  /*!
   * \brief Impose the Navier-Stokes boundary condition (strong).
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] conv_numerics - Description of the numerical method for convective terms.
   * \param[in] visc_numerics - Description of the numerical method for viscous terms.
   * \param[in] config - Definition of the particular problem.
   * \param[in] val_marker - Surface marker where the boundary condition is applied.
   */
  void BC_IsothermalNonCatalytic_Wall(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics,
                                      CNumerics *visc_numerics, CConfig *config, unsigned short val_marker);

  /*!
   * \brief Impose the Navier-Stokes boundary condition (strong).
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] conv_numerics - Description of the numerical method for convective terms.
   * \param[in] visc_numerics - Description of the numerical method for viscous terms.
   * \param[in] config - Definition of the particular problem.
   * \param[in] val_marker - Surface marker where the boundary condition is applied.
   */
  void BC_IsothermalCatalytic_Wall(CGeometry *geometry,
                                   CSolver **solver_container,
                                   CNumerics *conv_numerics,
                                   CNumerics *visc_numerics,
                                   CConfig *config, unsigned short val_marker);

  /*!
   * \brief Impose the Navier-Stokes boundary condition (strong).
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] conv_numerics - Description of the numerical method for convective terms.
   * \param[in] visc_numerics - Description of the numerical method for viscous terms.
   * \param[in] config - Definition of the particular problem.
   * \param[in] val_marker - Surface marker where the boundary condition is applied.
  */
  void BC_Smoluchowski_Maxwell(CGeometry *geometry,
                               CSolver **solver_container,
                               CNumerics *conv_numerics,
                               CNumerics *visc_numerics,
                               CConfig *config,
                               unsigned short val_marker) override;

  /*!
   * \brief Compute the viscous contribution for a particular edge.
   * \param[in] iEdge - Edge for which the flux and Jacobians are to be computed.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] numerics - Description of the numerical method.
   * \param[in] config - Definition of the particular problem.
   */
  void Viscous_Residual(unsigned long iEdge, CGeometry *geometry, CSolver **solver_container,
                        CNumerics *numerics, CConfig *config) override;


};