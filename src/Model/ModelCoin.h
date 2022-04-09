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



#ifndef MODEL_COIN
#define MODEL_COIN

extern ObjVerts CoinVerts;

#endif
