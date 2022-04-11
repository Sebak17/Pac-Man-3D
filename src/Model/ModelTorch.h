#ifndef OBJVERTS
#define OBJVERTS

typedef struct {
    int numFaces;
    int numVerts;
    float *vertCoords;
    float *normalCoords;
    float *texCoords;
} ObjVerts;

#endif



#ifndef MODEL_TORCH
#define MODEL_TORCH

extern ObjVerts TorchVerts;

#endif
