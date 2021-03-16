xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 80;
 13.60763;-3.39279;-4.33164;,
 9.25865;-2.54377;-5.39379;,
 8.27050;-5.61061;-7.02269;,
 12.23328;-6.73673;-5.69096;,
 14.29769;-0.31331;-2.40506;,
 9.97215;0.95128;-3.03720;,
 6.22672;3.65017;-3.31225;,
 4.97433;-0.48485;-6.54994;,
 4.08483;-6.30465;-9.16147;,
 14.44719;0.20936;1.12762;,
 10.10095;1.57323;1.01553;,
 6.25566;4.38061;1.06402;,
 4.43418;5.80437;1.26842;,
 3.23996;4.69919;-2.60281;,
 1.60925;0.39117;-7.02422;,
 2.08011;-5.53566;-9.69445;,
 13.89279;-1.81447;-5.92028;,
 12.52225;-5.79906;-7.61235;,
 8.87572;-4.80210;-8.89749;,
 9.87401;-0.94811;-6.89706;,
 14.57609;2.14271;-3.29029;,
 10.57822;3.45440;-3.84223;,
 5.56065;0.96877;-7.70022;,
 6.92333;5.96693;-4.21621;,
 4.65484;-5.41459;-10.98232;,
 14.66487;2.72800;1.66200;,
 10.67820;4.12285;1.54818;,
 7.04354;6.69277;1.60149;,
 3.91698;7.02518;-4.18350;,
 3.92578;8.06273;1.75178;,
 2.57583;-4.42211;-11.51135;,
 2.13209;1.98763;-8.30082;,
 0.80438;7.76228;-3.86232;,
 0.13572;5.51502;-2.87366;,
 0.36211;7.16624;1.53692;,
 1.11124;9.02137;1.96503;,
 0.40960;-3.69728;-12.08335;,
 0.01991;-4.86740;-10.25106;,
 -1.43637;1.19697;-7.57519;,
 -1.00086;2.80952;-8.98383;,
 13.25740;-5.24401;4.63737;,
 11.82212;-8.92365;4.55934;,
 7.80311;-8.11944;5.48066;,
 8.85913;-4.69358;5.28342;,
 14.04982;-1.62770;4.13732;,
 9.69036;-0.56776;4.49659;,
 4.50443;-2.99815;5.98202;,
 5.93165;2.06767;4.80720;,
 3.51735;-9.31983;6.09524;,
 14.44719;0.20936;1.12762;,
 10.10095;1.57323;1.01553;,
 6.25566;4.38061;1.06402;,
 2.98780;3.34240;4.29163;,
 4.43418;5.80437;1.26842;,
 1.47165;-8.78351;6.64337;,
 1.11829;-2.24340;6.48650;,
 13.40437;-4.40067;6.72048;,
 9.33976;-3.82616;7.35979;,
 8.25688;-8.12799;7.62768;,
 11.95065;-8.83616;6.68694;,
 14.23196;0.30923;5.94506;,
 10.20069;1.41684;6.24611;,
 6.52916;3.84835;6.63983;,
 4.99942;-2.03107;7.68586;,
 3.94747;-9.17522;8.20374;,
 3.58602;5.13025;6.50428;,
 2.05130;-1.35673;8.30972;,
 1.81788;-8.46880;8.77637;,
 -0.03916;4.46024;3.76636;,
 0.52710;6.15479;5.65122;,
 -1.62794;-0.56454;8.92592;,
 -1.94314;-1.52898;6.93053;,
 -0.61081;-8.24357;7.20745;,
 -0.36758;-7.85845;9.38531;,
 -1.94314;-1.52898;6.93053;,
 -0.03916;4.46024;3.76636;,
 0.36211;7.16624;1.53692;,
 0.36211;7.16624;1.53692;,
 0.13572;5.51502;-2.87366;,
 -1.43637;1.19697;-7.57519;;
 
 68;
 4;0,1,2,3;,
 4;4,5,1,0;,
 4;5,6,7,1;,
 4;2,1,7,8;,
 4;9,10,5,4;,
 4;10,11,6,5;,
 4;6,11,12,13;,
 4;8,7,14,15;,
 4;7,6,13,14;,
 4;16,17,18,19;,
 4;20,16,19,21;,
 4;21,19,22,23;,
 4;18,24,22,19;,
 4;25,20,21,26;,
 4;26,21,23,27;,
 4;23,28,29,27;,
 4;24,30,31,22;,
 4;22,31,28,23;,
 4;17,3,2,18;,
 4;18,2,8,24;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;24,8,15,30;,
 4;39,38,33,32;,
 4;40,41,42,43;,
 4;44,40,43,45;,
 4;45,43,46,47;,
 4;42,48,46,43;,
 4;49,44,45,50;,
 4;50,45,47,51;,
 4;47,52,53,51;,
 4;48,54,55,46;,
 4;46,55,52,47;,
 4;56,57,58,59;,
 4;60,61,57,56;,
 4;61,62,63,57;,
 4;58,57,63,64;,
 4;25,26,61,60;,
 4;26,27,62,61;,
 4;62,27,29,65;,
 4;64,63,66,67;,
 4;63,62,65,66;,
 4;58,42,41,59;,
 4;64,48,42,58;,
 4;35,34,68,69;,
 4;70,71,72,73;,
 4;67,54,48,64;,
 4;69,68,71,70;,
 4;73,72,54,67;,
 4;54,72,74,55;,
 4;55,74,75,52;,
 4;52,75,76,53;,
 4;12,77,78,13;,
 4;13,78,79,14;,
 4;14,79,37,15;,
 4;15,37,36,30;,
 4;30,36,39,31;,
 4;31,39,32,28;,
 4;28,32,35,29;,
 4;29,35,69,65;,
 4;66,65,69,70;,
 4;66,70,73,67;,
 4;56,59,41,40;,
 4;16,20,4,0;,
 4;3,17,16,0;,
 4;20,25,49,4;,
 4;25,60,44,49;,
 4;60,56,40,44;;
 
 MeshMaterialList {
  15;
  68;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.693600;0.618400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.400000;0.346800;0.309200;;
  }
  Material {
   0.144000;0.144000;0.144000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.545600;0.304000;0.244800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.265980;0.148200;0.119340;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.760000;0.760000;0.760000;;
   TextureFilename {
    "I2.png";
   }
  }
  Material {
   0.357600;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.032000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.109600;0.109600;0.109600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.648000;0.320000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.400000;0.400000;0.400000;;
   TextureFilename {
    "5471b3e10598046c28272a953d708f3f.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "5471b3e10598046c28272a953d708f3f.jpg";
   }
  }
  Material {
   0.414400;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.590000;0.590000;0.590000;;
  }
  Material {
   0.800000;0.648000;0.320000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "5471b3e10598046c28272a953d708f3f.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  95;
  0.314272;0.928195;0.199214;,
  0.476199;0.859190;0.187153;,
  0.447635;0.873114;0.193118;,
  -0.951791;0.304932;0.033317;,
  -0.288156;-0.936383;-0.200382;,
  -0.443265;-0.875149;-0.193985;,
  -0.523508;-0.831411;-0.186269;,
  -0.306398;-0.391586;0.867629;,
  -0.331375;-0.298523;0.895028;,
  -0.360144;-0.314054;0.878445;,
  -0.355518;-0.395365;0.846932;,
  -0.316395;-0.780055;0.539823;,
  -0.431917;-0.735633;0.521816;,
  -0.321205;-0.455252;0.830406;,
  -0.426611;-0.737358;0.523742;,
  -0.343139;-0.353195;0.870350;,
  -0.950089;0.311974;0.001367;,
  -0.948915;-0.075764;-0.306302;,
  -0.983972;0.115966;-0.135469;,
  0.317340;0.412292;-0.853997;,
  0.340033;0.418566;-0.842128;,
  0.342507;0.346490;-0.873289;,
  0.340093;0.316252;-0.885619;,
  0.339208;0.789741;-0.511124;,
  0.430693;0.747778;-0.505304;,
  0.423430;0.749591;-0.508744;,
  0.326059;0.450142;-0.831299;,
  0.341253;0.393956;-0.853431;,
  -0.157856;-0.045181;-0.986428;,
  -0.178756;0.043045;-0.982951;,
  -0.165521;0.020900;-0.985985;,
  -0.168344;-0.061847;-0.983786;,
  -0.207019;-0.519558;-0.828977;,
  -0.303794;-0.495110;-0.813987;,
  -0.163901;-0.109277;-0.980406;,
  -0.323337;-0.487474;-0.811062;,
  -0.178210;-0.003083;-0.983988;,
  -0.953463;0.296078;0.056978;,
  -0.992670;0.070826;0.097924;,
  0.173533;0.065257;0.982664;,
  0.155162;0.082824;0.984411;,
  0.151486;0.008968;0.988419;,
  0.197289;-0.028790;0.979922;,
  0.229049;0.540294;0.809703;,
  0.304881;0.511937;0.803099;,
  0.325266;0.507587;0.797846;,
  0.167021;0.107182;0.980110;,
  0.175049;0.045197;0.983522;,
  -0.968203;-0.169738;0.183769;,
  0.172836;0.163065;0.971359;,
  0.206551;0.565566;0.798418;,
  0.316874;0.927476;0.198444;,
  0.281079;0.813020;-0.509895;,
  0.277497;0.508568;-0.815079;,
  0.335709;0.430875;-0.837643;,
  -0.306424;-0.400884;0.863363;,
  -0.264577;-0.526342;0.808061;,
  -0.293249;-0.787685;0.541810;,
  -0.373691;-0.904259;-0.206566;,
  -0.201484;-0.521172;-0.829327;,
  -0.154683;-0.182966;-0.970874;,
  -0.209822;-0.030001;-0.977279;,
  0.238713;0.058555;0.969323;,
  -0.099956;-0.895015;-0.434691;,
  0.102065;-0.917296;-0.384904;,
  0.041429;-0.899233;-0.435503;,
  -0.173309;-0.827866;-0.533481;,
  0.034917;-0.999327;0.011263;,
  -0.182201;-0.982329;0.042800;,
  0.002980;-0.997840;0.065628;,
  -0.226384;-0.959811;0.165870;,
  -0.208027;-0.960638;0.184120;,
  -0.215385;-0.055079;-0.974975;,
  -0.160358;-0.225637;-0.960923;,
  -0.153569;-0.535059;-0.830740;,
  -0.202159;-0.664385;-0.719531;,
  -0.272130;-0.897927;0.345936;,
  -0.276074;-0.794278;0.541208;,
  -0.293779;-0.543445;0.786360;,
  -0.315658;-0.425142;0.848301;,
  -0.126107;-0.826961;-0.547935;,
  0.333435;0.450138;-0.828370;,
  0.265521;0.541577;-0.797617;,
  0.237764;0.831747;-0.501662;,
  0.256389;0.944047;0.207460;,
  0.143617;0.594117;0.791454;,
  0.147721;0.212135;0.966011;,
  0.233276;0.073618;0.969620;,
  0.964480;-0.262766;0.027057;,
  0.941333;-0.337362;0.008896;,
  0.967246;-0.247124;-0.058019;,
  0.990354;-0.135523;-0.028847;,
  0.942987;-0.324506;-0.073962;,
  0.993850;-0.109664;0.015387;,
  0.987385;-0.151532;0.045920;;
  68;
  4;7,10,9,8;,
  4;11,12,10,7;,
  4;12,14,13,10;,
  4;9,10,13,15;,
  4;4,5,12,11;,
  4;5,6,14,12;,
  4;14,6,58,57;,
  4;15,13,56,55;,
  4;13,14,57,56;,
  4;19,22,21,20;,
  4;23,19,20,24;,
  4;24,20,26,25;,
  4;21,27,26,20;,
  4;0,23,24,2;,
  4;2,24,25,1;,
  4;25,52,51,1;,
  4;27,54,53,26;,
  4;26,53,52,25;,
  4;63,63,64,64;,
  4;64,64,65,65;,
  4;16,16,3,3;,
  4;17,17,18,18;,
  4;65,65,66,66;,
  4;18,18,16,16;,
  4;28,29,30,31;,
  4;32,28,31,33;,
  4;33,31,34,35;,
  4;30,36,34,31;,
  4;4,32,33,5;,
  4;5,33,35,6;,
  4;35,59,58,6;,
  4;36,61,60,34;,
  4;34,60,59,35;,
  4;39,40,41,42;,
  4;43,44,40,39;,
  4;44,45,46,40;,
  4;41,40,46,47;,
  4;0,2,44,43;,
  4;2,1,45,44;,
  4;45,1,51,50;,
  4;47,46,49,62;,
  4;46,45,50,49;,
  4;67,67,68,68;,
  4;69,69,67,67;,
  4;3,3,37,37;,
  4;38,38,48,48;,
  4;70,70,69,69;,
  4;37,37,38,38;,
  4;71,71,70,70;,
  4;61,72,73,60;,
  4;60,73,74,59;,
  4;59,74,75,58;,
  4;58,76,77,57;,
  4;57,77,78,56;,
  4;56,78,79,55;,
  4;66,80,80,66;,
  4;54,81,82,53;,
  4;53,82,83,52;,
  4;52,83,84,51;,
  4;51,84,85,50;,
  4;49,50,85,86;,
  4;49,86,87,62;,
  4;88,89,89,88;,
  4;90,91,91,90;,
  4;92,92,90,90;,
  4;91,93,93,91;,
  4;93,94,94,93;,
  4;94,88,88,94;;
 }
 MeshTextureCoords {
  80;
  0.285500;0.693750;,
  0.236480;0.623460;,
  0.265740;0.586630;,
  0.314970;0.650050;,
  0.248760;0.726880;,
  0.195770;0.658550;,
  0.138070;0.610370;,
  0.179060;0.567770;,
  0.230110;0.528450;,
  0.213800;0.752990;,
  0.161270;0.691790;,
  0.102250;0.642370;,
  0.072650;0.617750;,
  0.098700;0.576080;,
  0.145450;0.523080;,
  0.212550;0.504400;,
  0.391760;0.603030;,
  0.335990;0.631600;,
  0.290070;0.571610;,
  0.338490;0.543680;,
  0.442060;0.560540;,
  0.387680;0.498300;,
  0.298060;0.479370;,
  0.347310;0.441790;,
  0.245110;0.520840;,
  0.493160;0.516440;,
  0.436470;0.455060;,
  0.388330;0.403630;,
  0.318750;0.406220;,
  0.356610;0.366540;,
  0.230090;0.495060;,
  0.265810;0.440360;,
  0.290750;0.370630;,
  0.270420;0.353740;,
  0.317150;0.319460;,
  0.330830;0.334660;,
  0.214070;0.472920;,
  0.195040;0.473910;,
  0.217600;0.403330;,
  0.235900;0.409710;,
  0.688340;0.325090;,
  0.641470;0.351090;,
  0.585110;0.295360;,
  0.624720;0.269040;,
  0.725380;0.290800;,
  0.664280;0.230820;,
  0.576090;0.205360;,
  0.623520;0.165480;,
  0.531600;0.254210;,
  0.755210;0.258480;,
  0.701260;0.197880;,
  0.658680;0.129660;,
  0.590640;0.123440;,
  0.634560;0.098430;,
  0.509100;0.234700;,
  0.533580;0.167360;,
  0.588570;0.422410;,
  0.535840;0.364810;,
  0.568570;0.319060;,
  0.621910;0.368610;,
  0.541770;0.469650;,
  0.485680;0.410470;,
  0.431470;0.366640;,
  0.474810;0.320050;,
  0.523110;0.269390;,
  0.397490;0.335470;,
  0.444680;0.288070;,
  0.498620;0.251060;,
  0.346790;0.282340;,
  0.361830;0.305200;,
  0.412340;0.249300;,
  0.406750;0.230730;,
  0.480260;0.214180;,
  0.477590;0.233060;,
  0.494980;0.133850;,
  0.553520;0.083840;,
  0.575260;0.049900;,
  0.023660;0.558620;,
  0.068040;0.531910;,
  0.116300;0.481530;;
 }
}