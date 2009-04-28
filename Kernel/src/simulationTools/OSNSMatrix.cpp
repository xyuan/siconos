/* Siconos-Kernel version 3.0.0, Copyright INRIA 2005-2008.
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
#include <assert.h>
#include "OSNSMatrix.h"
#include "Tools.hpp"

using namespace std;

void OSNSMatrix::updateSizeAndPositions(unsigned int& dim,
                                        SP::UnitaryRelationsGraph indexSet)
{
  // === Description ===

  // For a unitaryBlock (diagonal or extra diagonal) corresponding to
  // a Unitary Relation, we need to know the position of its first
  // element in the full-matrix M. This position depends on the
  // previous unitaryBlocks sizes.
  //
  // positions are saved in a map<SP::UnitaryRelation, unsigned int>,
  // named unitaryBlocksPositions.
  //

  // Computes real size of the current matrix = sum of the dim. of all
  // UR in indexSet
  dim = 0;
  UnitaryRelationsGraph::VIterator vd, vdend;
  for (boost::tie(vd, vdend) = indexSet->vertices(); vd != vdend; ++vd)
  {
    assert(indexSet->descriptor(indexSet->bundle(*vd)) == *vd);

    (*unitaryBlocksPositions)[indexSet->bundle(*vd)] = dim;
    dim += (indexSet->bundle(*vd)->getNonSmoothLawSize());

    assert((*unitaryBlocksPositions)[indexSet->bundle(*vd)] < dim);
  }
}

void OSNSMatrix::updateSizeAndPositions(unsigned int& dim,
                                        SP::DynamicalSystemsSet DSSet)
{
  // === Description ===

  // For a DSBlock (diagonal or extra diagonal) corresponding to a
  // DynamicalSet, we need to know the position of its first element
  // in the full-matrix M. This position depends on the previous
  // DSBlocks sizes.
  //
  // positions are saved in a map<SP::DynamicalSystem, unsigned int>,
  // named DSBlocksPositions.
  //

  // Computes real size of the current matrix = sum of the dim. of all
  // UR in indexSet
  dim = 0;
  for (DSIterator it = DSSet->begin(); it != DSSet->end(); ++it)
  {
    (*DSBlocksPositions)[*it] = dim;
    dim += (*it)->getDim();
  }
}

void OSNSMatrix::updateSizeAndPositions(unsigned int& dim, SP::DynamicalSystemsSet DSSet, SP::UnitaryRelationsGraph indexSet)
{
  // === Description ===

  // positions are saved in a map<SP::UnitaryRelation, unsigned int>,
  // named unitaryBlocksPositions.  positions are saved in a
  // map<SP::DynamicalSystem, unsigned int>, named DSBlocksPositions.
  //

  // Computes real size of the current matrix = sum of the dim. of all
  // UR in indexSet
  dim = 0;
  for (DSIterator it = DSSet->begin(); it != DSSet->end(); ++it)
  {
    (*DSBlocksPositions)[*it] = dim;
    dim += (*it)->getDim();
  }
  UnitaryRelationsGraph::VIterator vd, vdend;
  for (boost::tie(vd, vdend) = indexSet->vertices(); vd != vdend; ++vd)
  {
    (*unitaryBlocksPositions)[indexSet->bundle(*vd)] = dim;
    dim += indexSet->bundle(*vd)->getNonSmoothLawSize();
  }
}

// Default constructor: empty matrix, default storage
// No allocation for M1 or M2
OSNSMatrix::OSNSMatrix():
  dimRow(0),  dimColumn(0), storageType(0)
{
  unitaryBlocksPositions.reset(new UR_int());
  DSBlocksPositions.reset(new DS_int());
  numericsMat.reset(new NumericsMatrix);
}

// Constructor with dimensions (one input: square matrix only)
OSNSMatrix::OSNSMatrix(unsigned int n, int stor):
  dimRow(n),  dimColumn(n), storageType(stor)
{
  // Note:

  // for storageType = 0 (dense) n represents the real dimRowension of
  // the matrix and for sparse storage (storageType == 1) the number
  // of unitaryBlocks in a row or column.

  if (storageType == 0)
  {
    // A zero matrix M of size nXn is built.  unitaryBlocksPositions
    // remains empty (=NULL) since we have no information concerning
    // the UR.
    M1.reset(new SimpleMatrix(n, n));
  }
  else // if(storageType == 1)
    M2.reset(new BlockCSRMatrix(n));
  unitaryBlocksPositions.reset(new UR_int());
  DSBlocksPositions.reset(new DS_int());
  numericsMat.reset(new NumericsMatrix);
}
OSNSMatrix::OSNSMatrix(unsigned int n, unsigned int m, int stor):
  dimRow(n),  dimColumn(m), storageType(stor)
{
  // Note:

  // for storageType = 0 (dense) n represents the real dimension of
  // the matrix and for sparse storage (storageType == 1) the number
  // of unitaryBlocks in a row or column.

  if (storageType == 0)
  {
    // A zero matrix M of size nXn is built.  unitaryBlocksPositions
    // remains empty (=NULL) since we have no information concerning
    // the UR.
    M1.reset(new SimpleMatrix(n, m));
  }
  else // if(storageType == 1)
    M2.reset(new BlockCSRMatrix(n));

  unitaryBlocksPositions.reset(new UR_int());
  DSBlocksPositions.reset(new DS_int());
  numericsMat.reset(new NumericsMatrix);
}

// Basic constructor
OSNSMatrix::OSNSMatrix(SP::UnitaryRelationsGraph indexSet, MapOfMapOfUnitaryMatrices& unitaryBlocks, int stor):
  dimRow(0), dimColumn(0), storageType(stor)
{
  unitaryBlocksPositions.reset(new UR_int());
  DSBlocksPositions.reset(new DS_int());
  numericsMat.reset(new NumericsMatrix);

  fill(indexSet, unitaryBlocks);
}

OSNSMatrix::OSNSMatrix(SP::DynamicalSystemsSet DSSet, MapOfDSMatrices& DSBlocks, int stor):
  dimRow(0), dimColumn(0), storageType(stor)
{
  unitaryBlocksPositions.reset(new UR_int());
  DSBlocksPositions.reset(new DS_int());
  numericsMat.reset(new NumericsMatrix);

  fill(DSSet, DSBlocks);
}
OSNSMatrix::OSNSMatrix(SP::DynamicalSystemsSet DSSet, SP::UnitaryRelationsGraph indexSet, MapOfDSMapOfUnitaryMatrices& DSUnitaryBlocks, int stor):
  dimRow(0), dimColumn(0), storageType(stor)
{
  unitaryBlocksPositions.reset(new UR_int());
  DSBlocksPositions.reset(new DS_int());
  numericsMat.reset(new NumericsMatrix);

  fill(DSSet, indexSet, DSUnitaryBlocks);
}

OSNSMatrix::OSNSMatrix(SP::UnitaryRelationsGraph indexSet, SP::DynamicalSystemsSet DSSet,  MapOfUnitaryMapOfDSMatrices& unitaryDSBlocks, int stor):
  dimRow(0), dimColumn(0), storageType(stor)
{
  unitaryBlocksPositions.reset(new UR_int());
  DSBlocksPositions.reset(new DS_int());
  numericsMat.reset(new NumericsMatrix);

  fill(indexSet, DSSet, unitaryDSBlocks);
}

OSNSMatrix::OSNSMatrix(SP::UnitaryRelationsGraph indexSet, SP::DynamicalSystemsSet DSSet, MapOfMapOfUnitaryMatrices& unitaryBlocks,   MapOfDSMatrices& DSBlocks, MapOfDSMapOfUnitaryMatrices& DSUnitaryBlocks, MapOfUnitaryMapOfDSMatrices& unitaryDSBlocks, int stor):
  dimRow(0), dimColumn(0), storageType(stor)
{
  unitaryBlocksPositions.reset(new UR_int());
  DSBlocksPositions.reset(new DS_int());
  numericsMat.reset(new NumericsMatrix);

  fill(indexSet, DSSet, unitaryBlocks, DSBlocks, DSUnitaryBlocks, unitaryDSBlocks);
}






// Copy of a SiconosMatrix (used when OSNS xml constructor is called with M input in XML file)
OSNSMatrix::OSNSMatrix(const SiconosMatrix& MSource):
  dimRow(MSource.size(0)), dimColumn(MSource.size(1)), storageType(0)
{
  unitaryBlocksPositions.reset(new UR_int());
  DSBlocksPositions.reset(new DS_int());
  numericsMat.reset(new NumericsMatrix);
  M1.reset(new SimpleMatrix(MSource));

  // Warning: unitaryBlocksPositions remains empty since we have no
  // information concerning indexSet and unitaryBlocks in MSource
}


// Destructor : pointers are smart
OSNSMatrix::~OSNSMatrix()
{
}

unsigned int OSNSMatrix::getPositionOfUnitaryBlock(SP::UnitaryRelation UR) const
{
  UR_int::const_iterator it = unitaryBlocksPositions->find(UR);
  if (it == unitaryBlocksPositions->end())
    RuntimeException::selfThrow
    ("OSNSMatrix::getPositionOfUnitaryBlock(UnitaryRelation ur), ur does not belong to the index set used to built the OSNS matrix.");
  return it->second;
}
unsigned int OSNSMatrix::getPositionOfDSBlock(SP::DynamicalSystem DS) const
{
  DS_int::const_iterator it = DSBlocksPositions->find(DS);
  if (it == DSBlocksPositions->end())
    RuntimeException::selfThrow
    ("OSNSMatrix::getPositionOfDSBlock(DynamicalSystems ds), ds does not belong to the DynamicalSet used to built the OSNS matrix.");
  return it->second;
}


// Fill the matrix
void OSNSMatrix::fill(SP::UnitaryRelationsGraph indexSet, MapOfMapOfUnitaryMatrices& unitaryBlocks, bool update)
{

  assert(indexSet);

  if (update)
  {
    // Computes dimRow and unitaryBlocksPositions according to indexSet
    updateSizeAndPositions(dimColumn, indexSet);
    dimRow = dimColumn;
  }

  if (storageType == 0)
  {

    // === Memory allocation, if required ===
    // Mem. is allocate only if !M or if its size has changed.
    if (update)
    {
      if (! M1)
        M1.reset(new SimpleMatrix(dimRow, dimColumn));
      else
      {
        if (M1->size(0) != dimRow || M1->size(1) != dimColumn)
          M1->resize(dimRow, dimColumn);
        M1->zero();
      }
    }

    // ======> Aim: find UR1 and UR2 both in indexSet and which have
    // common DynamicalSystems.  Then get the corresponding matrix
    // from map unitaryBlocks, and copy it into M

    unsigned int pos = 0, col = 0; // index position used for
    // unitaryBlock copy into M, see
    // below.
    // === Loop through "active" Unitary Relations (ie present in
    // indexSets[level]) ===
    UnitaryRelationsGraph::VIterator ui1, ui1end;
    for (boost::tie(ui1, ui1end) = indexSet->vertices();
         ui1 != ui1end; ++ui1)
    {
      SP::UnitaryRelation ur1 = indexSet->bundle(*ui1);
      pos = (*unitaryBlocksPositions)[ur1];
      boost::static_pointer_cast<SimpleMatrix>(M1)
      ->setBlock(pos, pos, *(unitaryBlocks[ur1][ur1]));
      UnitaryRelationsGraph::AVIterator ui2, ui2end;
      for (boost::tie(ui2, ui2end) = indexSet->adjacent_vertices(*ui1);
           ui2 != ui2end; ++ui2)
      {
        SP::UnitaryRelation ur2 = indexSet->bundle(*ui2);
        assert(indexSet->is_vertex(ur2));
        assert(ur2 != ur1);

        col = (*unitaryBlocksPositions)[ur2];


        assert(pos < dimRow);
        assert(col < dimColumn);
        boost::static_pointer_cast<SimpleMatrix>(M1)
        ->setBlock(pos, col, *(unitaryBlocks[ur1][ur2]));
      }
    }
  }

  else // if storageType == 1
  {
    if (! M2)
      M2.reset(new BlockCSRMatrix(indexSet, unitaryBlocks));
    else
      M2->fill(indexSet, unitaryBlocks);
  }
  if (update)
    convert();

}
void OSNSMatrix::fillDiagonal(SP::UnitaryRelationsGraph URSet, MapOfMapOfUnitaryMatrices& unitaryBlocks, bool update)
{

  assert(URSet);

  if (update)
  {
    // Computes dimRow and unitaryBlocksPositions according to indexSet
    updateSizeAndPositions(dimColumn, URSet);
    updateSizeAndPositions(dimRow, URSet);
  }

  if (storageType == 0)
  {
    // === Memory allocation, if required ===
    // Mem. is allocate only if !M or if its size has changed.
    if (update)
    {
      if (! M1)
        M1.reset(new SimpleMatrix(dimRow, dimColumn));
      else
      {
        if (M1->size(0) != dimRow || M1->size(1) != dimColumn)
          M1->resize(dimRow, dimColumn);
        M1->zero();
      }
    }

    // ======> Aim: find UR1 and UR2 both in indexSet and which have
    // common DynamicalSystems.  Then get the corresponding matrix
    // from map unitaryBlocks, and copy it into M

    unsigned int pos = 0, col = 0; // index position used for
    // unitaryBlock copy into M, see
    // below.
    // === Loop through "active" Unitary Relations (ie present in
    // indexSets[level]) ===

    UnitaryRelationsGraph::VIterator ui, uiend;
    for (boost::tie(ui, uiend) = URSet->vertices(); ui != uiend; ++ui)
    {
      SP::UnitaryRelation ur = URSet->bundle(*ui);
      pos = (*unitaryBlocksPositions)[ur];
      boost::static_pointer_cast<SimpleMatrix>(M1)->setBlock(pos, pos, *(unitaryBlocks[ur][ur]));
    }
  }
  else // if storageType == 1
  {
    if (! M2)
      M2.reset(new BlockCSRMatrix(URSet, unitaryBlocks));
    else
      M2->fill(URSet, unitaryBlocks);
  }

  if (update)
    convert();
}

void OSNSMatrix::fill(SP::DynamicalSystemsSet DSSet, MapOfDSMatrices& DSBlocks, bool update)
{

  assert(DSSet && "NULL pointer");

  if (update)
  {
    // Computes dimRow and unitaryBlocksPositions according to indexSet
    updateSizeAndPositions(dimRow, DSSet);
    updateSizeAndPositions(dimColumn, DSSet);
  }
  if (storageType == 0)
  {
    // === Memory allocation, if required ===
    // Mem. is allocate only if !M or if its size has changed.
    if (update)
    {
      if (! M1)
        M1.reset(new SimpleMatrix(dimRow, dimColumn));
      else
      {
        if (M1->size(0) != dimRow || M1->size(1) != dimColumn)
          M1->resize(dimRow, dimColumn);
        M1->zero();
      }
    }

    // get the corresponding matrix from map unitaryBlocks, and copy it into M

    unsigned int pos = 0, col = 0; // index position used for unitaryBlock copy into M, see below.
    // === Loop through "active" Unitary Relations (ie present in indexSets[level]) ===
    for (DSIterator itDS = DSSet->begin(); itDS != DSSet->end(); ++itDS)
    {
      // DS = *itDS
      // corresponding matrix = DSBlocks[*itDS]

      // Case 1: basic storage
      pos = (*DSBlocksPositions)[*itDS];
      boost::static_pointer_cast<SimpleMatrix>(M1)->setBlock(pos, pos, *(DSBlocks[*itDS]));
    }
  }
  else // if storageType == 1
  {
    if (! M2)
      M2.reset(new BlockCSRMatrix(DSSet, DSBlocks));
    else
      M2->fill(DSSet, DSBlocks);
  }
  if (update)
    convert();

}
void OSNSMatrix::fill(SP::DynamicalSystemsSet DSSet, SP::UnitaryRelationsGraph URSet, MapOfDSMapOfUnitaryMatrices& DSUnitaryBlocks, bool update)
{

  assert(URSet && "NULL pointer");
  assert(DSSet && "NULL pointer");

  if (update)
  {
    // Computes dimRow and unitaryBlocksPositions and  DSBlocksPositions according to indexSet
    updateSizeAndPositions(dimColumn, URSet);


    updateSizeAndPositions(dimRow, DSSet);
  }

  if (storageType == 0)
  {
    // === Memory allocation, if required ===
    // Mem. is allocate only if !M or if its size has changed.
    if (update)
    {
      if (! M1)
        M1.reset(new SimpleMatrix(dimRow, dimColumn));
      else
      {
        if (M1->size(0) != dimRow || M1->size(1) != dimColumn)
          M1->resize(dimRow, dimColumn);
        M1->zero();
      }
    }


    // Get the  matrix from map unitaryDSBlocks which corresponds to UR and DS, and copy it into M

    unsigned int pos = 0, col = 0; // index position used for unitaryBlock copy into M, see below.
    // === Loop through "active" Unitary Relations (ie present in indexSets[level]) ===


    for (DSIterator itCol = DSSet->begin(); itCol != DSSet->end(); ++itCol)
    {
      // Look for DS
      // The connection is checked thanks to unitaryBlocks map
      for (UnitaryMatrixColumnIterator itRow = DSUnitaryBlocks[*itCol].begin(); itRow != DSUnitaryBlocks[*itCol].end(); ++itRow)
      {
        // DS = *itCol
        // UR = *itRow
        // corresponding matrix = DSUnitaryBlocks[*itCol][(*itRow).first]

        // Case 1: basic storage
        pos = (*DSBlocksPositions)[*itCol];
        col = (*unitaryBlocksPositions)[(*itRow).first];
        boost::static_pointer_cast<SimpleMatrix>(M1)->setBlock(pos, col, *(DSUnitaryBlocks[*itCol][(*itRow).first]));
      }
    }

  }
  else // if storageType == 1
  {
    RuntimeException::selfThrow("Not yet Implemented case storageType == 1:OSNSMatrix::fill(DynamicalSystemsSet* DSSet, UnitaryRelationsGraph* URSet, MapOfDSMapOfUnitaryMatrices& DSUnitaryBlocks,bool update) ");

    //       if(M2==NULL)
    //  M2 = new BlockCSRMatrix(DSSet,URSet,DSUnitaryBlocks);
    //       else
    //  M2->fill(DSSet,URSet,DSUnitaryBlocks);
  }
  if (update)
    convert();

}




void OSNSMatrix::fill(SP::UnitaryRelationsGraph indexSet, SP::DynamicalSystemsSet DSSet,  MapOfUnitaryMapOfDSMatrices& unitaryDSBlocks, bool update)
{
  assert(false);
}
/*
  assert (indexSet && "NULL pointer");
  assert (DSSet && "NULL pointer");

  if (update){
    // Computes dimRow and unitaryBlocksPositions and  DSBlocksPositions according to indexSet
    updateSizeAndPositions(dimRow,indexSet);


    updateSizeAndPositions(dimColumn,DSSet);
  }

  if(storageType==0)
    {
      // === Memory allocation, if required ===
      // Mem. is allocate only if !M or if its size has changed.
      if (update){
  if(! M1)
    M1.reset(new SimpleMatrix(dimRow,dimColumn));
  else
    {
      if( M1->size(0) != dimRow || M1->size(1)!= dimColumn )
        M1->resize(dimRow,dimColumn);
      M1->zero();
    }
      }


      // Get the matrix from map unitaryDSBlocks which corresponds to
      // UR and DS, and copy it into M

      unsigned int pos = 0, col =0; // index position used for
                                    // unitaryBlock copy into M, see
                                    // below.
      // === Loop through "active" Unitary Relations (ie present in indexSets[level]) ===

      for (URGVIterator ui1 = boost::vertices(*indexSet).first;
           ui1 != boost::vertices(*indexSet).second; ++ui1)
        {
          SP::UnitaryRelation ur1 = URGVertices[*ui1];
          URGVIterator ui2beg, ui2end;
          boost::tie(ui2beg, ui2end) = boost::adjacent_vertices(*ui1, *indexSet);
          for (URGVIterator ui2 = ui2beg; ui2 != ui2end; ++ui2)
            {
              SP::UnitaryRelation ur2 = URGVertices[*ui2];
              pos = (*unitaryBlocksPositions)[ur1];
              col = (*unitaryBlocksPositions)[ur2];
              boost::static_pointer_cast<SimpleMatrix>(M1)->setBlock(pos,col,*(unitaryBlocks[ur1][ur2]));
            }
        }
      for(UnitaryRelationsIterator itRow=indexSet->begin(); itRow!=indexSet->end(); ++itRow)
  {
    // Look for UR
    // The connection is checked thanks to unitaryBlocks map
    for(MatIterator itCol = unitaryDSBlocks[*itRow].begin(); itCol!=unitaryDSBlocks[*itRow].end(); ++itCol)
      {
          // UR = *itRow
      // DS= *itCol
      // corresponding matrix = unitaryDSBlocks[*itUR][(*itCol).first]

      // Case 1: basic storage
      pos = (*unitaryBlocksPositions)[*itRow];
      col = (*DSBlocksPositions)[(*itCol).first];
                  boost::static_pointer_cast<SimpleMatrix>(M1)->setBlock(pos,col,*(unitaryDSBlocks[*itRow][(*itCol).first]));
      }
  }

    }
  else // if storageType == 1
    {
      if(! M2)
  M2.reset(new BlockCSRMatrix(indexSet,DSSet,unitaryDSBlocks));
      else
  M2->fill(indexSet,DSSet,unitaryDSBlocks);
    }
  if (update)
    convert();
}
*/
void OSNSMatrix::fill(SP::UnitaryRelationsGraph URSet, SP::DynamicalSystemsSet DSSet,  MapOfMapOfUnitaryMatrices& unitaryBlocks,  MapOfDSMatrices& DSBlocks, MapOfDSMapOfUnitaryMatrices& DSUnitaryBlocks ,  MapOfUnitaryMapOfDSMatrices& unitaryDSBlocks , bool update)
{
  assert(false);
}
/*
  updateSizeAndPositions(dimRow, DSSet, URSet);
  dimColumn = dimRow;
  if(! M1)
    M1.reset(new SimpleMatrix(dimRow,dimColumn));
  else
    {
      if( M1->size(0) != dimRow || M1->size(1)!= dimColumn )
  M1->resize(dimRow,dimColumn);
      M1->zero();
    }

  //Fill the diagonal of the DSs block
  fill(DSSet,DSBlocks,false);
  //Fill the diagonal of the URs block
  fillDiagonal(URSet,unitaryBlocks,false);
  //Fill DSxUR
  fill(DSSet, URSet, DSUnitaryBlocks,false);
  //Fill URxDS
  fill(URSet,DSSet, unitaryDSBlocks,false);
  convert();

  }*/


// convert current matrix to NumericsMatrix structure
void OSNSMatrix::convert()
{
  numericsMat->storageType = storageType;
  numericsMat->size0 = dimRow;
  numericsMat->size1 = dimColumn;
  if (storageType == 0)
  {
    numericsMat->matrix0 = M1->getArray(); // Pointer link
    // numericsMat->matrix1 = NULL; matrix1 is not set to NULL: we
    // keep previous allocation. May be usefull if we switch between
    // different storages during simu
  }
  else
  {
    M2->convert();
    numericsMat->matrix1 = &*M2->getNumericsMatSparse();
  }
}

// Display data
void OSNSMatrix::display() const
{
  if (storageType == 0)
  {
    cout << "----- OSNS Matrix using default storage type for Numerics structure (SiconosMatrix -> double*)" << endl;
    if (! M1)
      cout << " matrix = NULL pointer" << endl;
    else M1->display();
  }
  else
  {
    cout << "----- OSNS Matrix using Sparse UnitaryBlock storage type for Numerics (SparseBlockStructuredMatrix)" << endl;
    if (! M2)
      cout << " matrix = NULL pointer" << endl;
    else M2->display();
  }
}
