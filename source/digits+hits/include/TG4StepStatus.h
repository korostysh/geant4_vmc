// $Id: TG4StepStatus.h,v 1.1 2002/06/20 11:53:25 hristov Exp $
// Category: digits+hits
//
// Author: I.Hrivnacova
//
// Enum TG4StepStatus
// ------------------
// In orded to take into account different stepping 
// mechanism in G3 and G4 three states of TG4StepManager
// are defined:
//  kVertex     - returns track properties in the vertex
//                position before particle started stepping
//  kBoundary   - returns track properties when particle
//                is crossing geometrical boundary
//                (the volume that preceeds the boundary is returned
//                 as current volume)
//  kNormalStep - returns track properties in a post step
//                point              

#ifndef TG4_STEP_STATUS_H
#define TG4_STEP_STATUS_H

enum TG4StepStatus { 
  kVertex,     // in track vertex
  kBoundary,   // when crossing geometrical boundary
  kNormalStep  // in post step point
};

#endif //TG4_STEP_STATUS_H
