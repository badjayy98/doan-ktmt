#ifndef ChamTuDongQInt_H
#define ChamTuDongQInt_h
#endif

#include "QInt.h"
#include <fstream>
#include <sstream>

string convertToBase(QInt s, string base);

string ThucHienPhepTinh2QInt(QInt toantu1, QInt toantu2, string pheptoan, string base);

void XuLyPhepTinh(vector<string> calc, string fileoutput);

void ThucHienChamTuDong(string fileinput, string fileoutput);
