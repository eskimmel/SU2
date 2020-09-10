/*!
 * \file CFEMStandardVolumeQuadGrid.cpp
 * \brief Functions for the class CFEMStandardVolumeQuadGrid.
 * \author E. van der Weide
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

#include "../../include/fem/CFEMStandardVolumeQuadGrid.hpp"

/*----------------------------------------------------------------------------------*/
/*          Public member functions of CFEMStandardVolumeQuadGrid.                  */
/*----------------------------------------------------------------------------------*/

CFEMStandardVolumeQuadGrid::CFEMStandardVolumeQuadGrid(const unsigned short val_nPoly,
                                                       const unsigned short val_orderExact)
  : CFEMStandardQuad(val_nPoly, val_orderExact) {

}

void CFEMStandardVolumeQuadGrid::DataIntegrationPoints(const ColMajorMatrix<su2double>    &matB,
                                                       const unsigned short               ldb,
                                                       const unsigned short               ldc,
                                                       const unsigned short               n,
                                                       ColMajorMatrix<su2double>          *matC,
                                                       vector<ColMajorMatrix<su2double> > *matDerC,
                                                       const CConfig                      *config) const {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEMStandardVolumeQuadGrid::MinMaxJacobians(const bool                         LGLDistribution,
                                                 const ColMajorMatrix<su2double>    &matCoor,
                                                 const unsigned short               ldb,
                                                 const unsigned short               ldc,
                                                 vector<ColMajorMatrix<su2double> > &matMetricTerms,
                                                 su2activevector                    &Jacobians,
                                                 su2double                          &jacMin,
                                                 su2double                          &jacMax) const {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}