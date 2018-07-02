xof 0303txt 0032
template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}


Material Material__25 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "1x1-blue.png";
 }
}

Frame default {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.202210,0.000000,0.217542,1.000000;;
 }

 Mesh  {
  13;
  0.998385;0.000000;0.000000;,
  -0.001741;0.499821;0.000000;,
  -0.001615;0.000000;0.000000;,
  0.998385;0.000000;-1.000000;,
  -0.001741;0.499821;-1.000000;,
  -0.001615;0.000000;-1.000000;,
  -0.001615;0.000000;-1.000000;,
  -0.001615;0.000000;0.000000;,
  -0.001741;0.499821;-1.000000;,
  0.998385;0.000000;0.000000;,
  0.998385;0.000000;-1.000000;,
  -0.001741;0.499821;0.000000;,
  -0.001615;0.000000;0.000000;;
  8;
  3;3,5,4;,
  3;3,2,6;,
  3;2,3,0;,
  3;5,1,4;,
  3;1,5,7;,
  3;8,9,10;,
  3;9,8,11;,
  3;11,12,0;;

  MeshNormals  {
   6;
   0.818882;-0.193228;-0.540458;,
   -0.577271;-0.577416;-0.577364;,
   -0.436852;0.706489;-0.556806;,
   -0.577271;-0.577416;0.577364;,
   0.818882;-0.193228;0.540458;,
   -0.436852;0.706489;0.556806;;
   8;
   3;0,1,2;,
   3;0,3,1;,
   3;3,0,4;,
   3;1,5,2;,
   3;5,1,3;,
   3;2,4,0;,
   3;4,2,5;,
   3;5,3,4;;
  }

  MeshMaterialList  {
   1;
   8;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;
   { Material__25 }
  }

  MeshTextureCoords  {
   13;
   1.000000;2.000000;,
   1.000000;2.000000;,
   0.000000;2.000000;,
   1.000000;2.000000;,
   1.000000;2.000000;,
   0.500000;1.000000;,
   0.000000;2.000000;,
   0.500000;1.000000;,
   0.000000;2.000000;,
   0.500000;1.000000;,
   0.500000;1.000000;,
   0.000000;2.000000;,
   1.000000;1.000000;;
  }
 }
}