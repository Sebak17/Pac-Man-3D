/*
 * auto created by obj2gl
 *
 * repo  : https://github.com/xiaozhuai/obj2gl
 * obj   : Ghost.obj
 * faces : 6196
 * verts : 18588
 *
 */

#ifndef OBJ2GL_OBJ2GLVERTS
#define OBJ2GL_OBJ2GLVERTS

typedef struct {
    int numFaces;
    int numVerts;
    float *vertCoords;
    float *normalCoords;
    float *texCoords;
} Obj2glVerts;

#endif



#ifndef OBJ2GL_GHOST
#define OBJ2GL_GHOST

extern Obj2glVerts GhostVerts;

#endif
