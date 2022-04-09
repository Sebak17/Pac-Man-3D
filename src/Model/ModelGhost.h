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



#ifndef MODEL_GHOST
#define MODEL_GHOST

extern ObjVerts GhostVerts;

#endif
