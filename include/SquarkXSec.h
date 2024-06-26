std::pair<double, double> GetSquarkXSec(double Squark_Mass) {
	int mass_round = std::round(Squark_Mass/25)*25;
	switch (mass_round) {
		case  200: return std::pair<double, double>(7.55E+02, 6.47);
		case  205: return std::pair<double, double>(6.70E+02, 6.48);
		case  210: return std::pair<double, double>(5.97E+02, 6.48);
		case  215: return std::pair<double, double>(5.33E+02, 6.49);
		case  220: return std::pair<double, double>(4.76E+02, 6.49);
		case  225: return std::pair<double, double>(4.27E+02, 6.50);
		case  230: return std::pair<double, double>(3.83E+02, 6.51);
		case  235: return std::pair<double, double>(3.44E+02, 6.52);
		case  240: return std::pair<double, double>(3.10E+02, 6.53);
		case  245: return std::pair<double, double>(2.80E+02, 6.53);
		case  250: return std::pair<double, double>(2.53E+02, 6.54);
		case  255: return std::pair<double, double>(2.29E+02, 6.55);
		case  260: return std::pair<double, double>(2.08E+02, 6.56);
		case  265: return std::pair<double, double>(1.89E+02, 6.57);
		case  270: return std::pair<double, double>(1.72E+02, 6.58);
		case  275: return std::pair<double, double>(1.57E+02, 6.59);
		case  280: return std::pair<double, double>(1.43E+02, 6.60);
		case  285: return std::pair<double, double>(1.31E+02, 6.61);
		case  290: return std::pair<double, double>(1.19E+02, 6.63);
		case  295: return std::pair<double, double>(1.09E+02, 6.64);
		case  300: return std::pair<double, double>(1.00E+02, 6.65);
		case  305: return std::pair<double, double>(9.20E+01, 6.66);
		case  310: return std::pair<double, double>(8.45E+01, 6.68);
		case  315: return std::pair<double, double>(7.77E+01, 6.69);
		case  320: return std::pair<double, double>(7.16E+01, 6.70);
		case  325: return std::pair<double, double>(6.60E+01, 6.72);
		case  330: return std::pair<double, double>(6.09E+01, 6.73);
		case  335: return std::pair<double, double>(5.63E+01, 6.75);
		case  340: return std::pair<double, double>(5.20E+01, 6.77);
		case  345: return std::pair<double, double>(4.81E+01, 6.78);
		case  350: return std::pair<double, double>(4.46E+01, 6.80);
		case  355: return std::pair<double, double>(4.13E+01, 6.82);
		case  360: return std::pair<double, double>(3.83E+01, 6.83);
		case  365: return std::pair<double, double>(3.56E+01, 6.85);
		case  370: return std::pair<double, double>(3.31E+01, 6.87);
		case  375: return std::pair<double, double>(3.07E+01, 6.89);
		case  380: return std::pair<double, double>(2.86E+01, 6.91);
		case  385: return std::pair<double, double>(2.66E+01, 6.93);
		case  390: return std::pair<double, double>(2.48E+01, 6.95);
		case  395: return std::pair<double, double>(2.31E+01, 6.97);
		case  400: return std::pair<double, double>(2.16E+01, 6.99);
		case  405: return std::pair<double, double>(2.02E+01, 7.01);
		case  410: return std::pair<double, double>(1.88E+01, 7.03);
		case  415: return std::pair<double, double>(1.76E+01, 7.05);
		case  420: return std::pair<double, double>(1.65E+01, 7.08);
		case  425: return std::pair<double, double>(1.54E+01, 7.10);
		case  430: return std::pair<double, double>(1.45E+01, 7.12);
		case  435: return std::pair<double, double>(1.35E+01, 7.15);
		case  440: return std::pair<double, double>(1.27E+01, 7.17);
		case  445: return std::pair<double, double>(1.19E+01, 7.20);
		case  450: return std::pair<double, double>(1.12E+01, 7.22);
		case  455: return std::pair<double, double>(1.05E+01, 7.25);
		case  460: return std::pair<double, double>(9.88E+00, 7.27);
		case  465: return std::pair<double, double>(9.29E+00, 7.30);
		case  470: return std::pair<double, double>(8.74E+00, 7.32);
		case  475: return std::pair<double, double>(8.23E+00, 7.34);
		case  480: return std::pair<double, double>(7.75E+00, 7.37);
		case  485: return std::pair<double, double>(7.30E+00, 7.39);
		case  490: return std::pair<double, double>(6.88E+00, 7.41);
		case  495: return std::pair<double, double>(6.48E+00, 7.43);
		case  500: return std::pair<double, double>(6.12E+00, 7.45);
		case  505: return std::pair<double, double>(5.77E+00, 7.47);
		case  510: return std::pair<double, double>(5.45E+00, 7.5);
		case  515: return std::pair<double, double>(5.15E+00, 7.53);
		case  520: return std::pair<double, double>(4.87E+00, 7.55);
		case  525: return std::pair<double, double>(4.60E+00, 7.58);
		case  530: return std::pair<double, double>(4.35E+00, 7.61);
		case  535: return std::pair<double, double>(4.11E+00, 7.64);
		case  540: return std::pair<double, double>(3.89E+00, 7.67);
		case  545: return std::pair<double, double>(3.69E+00, 7.7);
		case  550: return std::pair<double, double>(3.49E+00, 7.73);
		case  555: return std::pair<double, double>(3.31E+00, 7.76);
		case  560: return std::pair<double, double>(3.13E+00, 7.79);
		case  565: return std::pair<double, double>(2.97E+00, 7.82);
		case  570: return std::pair<double, double>(2.82E+00, 7.85);
		case  575: return std::pair<double, double>(2.67E+00, 7.88);
		case  580: return std::pair<double, double>(2.54E+00, 7.92);
		case  585: return std::pair<double, double>(2.41E+00, 7.95);
		case  590: return std::pair<double, double>(2.29E+00, 7.98);
		case  595: return std::pair<double, double>(2.17E+00, 8.01);
		case  600: return std::pair<double, double>(2.06E+00, 8.05);
		case  605: return std::pair<double, double>(1.96E+00, 8.08);
		case  610: return std::pair<double, double>(1.86E+00, 8.11);
		case  615: return std::pair<double, double>(1.77E+00, 8.14);
		case  620: return std::pair<double, double>(1.69E+00, 8.18);
		case  625: return std::pair<double, double>(1.60E+00, 8.21);
		case  630: return std::pair<double, double>(1.53E+00, 8.25);
		case  635: return std::pair<double, double>(1.45E+00, 8.28);
		case  640: return std::pair<double, double>(1.39E+00, 8.31);
		case  645: return std::pair<double, double>(1.32E+00, 8.35);
		case  650: return std::pair<double, double>(1.26E+00, 8.38);
		case  655: return std::pair<double, double>(1.20E+00, 8.42);
		case  660: return std::pair<double, double>(1.14E+00, 8.45);
		case  665: return std::pair<double, double>(1.09E+00, 8.49);
		case  670: return std::pair<double, double>(1.04E+00, 8.52);
		case  675: return std::pair<double, double>(9.92E-01, 8.56);
		case  680: return std::pair<double, double>(9.46E-01, 8.59);
		case  685: return std::pair<double, double>(9.03E-01, 8.63);
		case  690: return std::pair<double, double>(8.62E-01, 8.67);
		case  695: return std::pair<double, double>(8.24E-01, 8.7);
		case  700: return std::pair<double, double>(7.87E-01, 8.74);
		case  705: return std::pair<double, double>(7.52E-01, 8.77);
		case  710: return std::pair<double, double>(7.18E-01, 8.81);
		case  715: return std::pair<double, double>(6.86E-01, 8.84);
		case  720: return std::pair<double, double>(6.56E-01, 8.88);
		case  725: return std::pair<double, double>(6.27E-01, 8.91);
		case  730: return std::pair<double, double>(6.00E-01, 8.95);
		case  735: return std::pair<double, double>(5.74E-01, 8.98);
		case  740: return std::pair<double, double>(5.49E-01, 9.02);
		case  745: return std::pair<double, double>(5.25E-01, 9.06);
		case  750: return std::pair<double, double>(5.03E-01, 9.09);
		case  755: return std::pair<double, double>(4.81E-01, 9.13);
		case  760: return std::pair<double, double>(4.61E-01, 9.16);
		case  765: return std::pair<double, double>(4.41E-01, 9.2);
		case  770: return std::pair<double, double>(4.23E-01, 9.24);
		case  775: return std::pair<double, double>(4.05E-01, 9.27);
		case  780: return std::pair<double, double>(3.88E-01, 9.31);
		case  785: return std::pair<double, double>(3.72E-01, 9.35);
		case  790: return std::pair<double, double>(3.57E-01, 9.39);
		case  795: return std::pair<double, double>(3.42E-01, 9.42);
		case  800: return std::pair<double, double>(3.28E-01, 9.46);
		case  805: return std::pair<double, double>(3.14E-01, 9.5);
		case  810: return std::pair<double, double>(3.02E-01, 9.54);
		case  815: return std::pair<double, double>(2.89E-01, 9.58);
		case  820: return std::pair<double, double>(2.78E-01, 9.62);
		case  825: return std::pair<double, double>(2.66E-01, 9.66);
		case  830: return std::pair<double, double>(2.56E-01, 9.7);
		case  835: return std::pair<double, double>(2.45E-01, 9.74);
		case  840: return std::pair<double, double>(2.36E-01, 9.78);
		case  845: return std::pair<double, double>(2.26E-01, 9.82);
		case  850: return std::pair<double, double>(2.17E-01, 9.86);
		case  855: return std::pair<double, double>(2.09E-01, 9.9);
		case  860: return std::pair<double, double>(2.01E-01, 9.94);
		case  865: return std::pair<double, double>(1.93E-01, 9.98);
		case  870: return std::pair<double, double>(1.85E-01, 10.02);
		case  875: return std::pair<double, double>(1.78E-01, 10.06);
		case  880: return std::pair<double, double>(1.71E-01, 10.1);
		case  885: return std::pair<double, double>(1.64E-01, 10.14);
		case  890: return std::pair<double, double>(1.58E-01, 10.18);
		case  895: return std::pair<double, double>(1.52E-01, 10.22);
		case  900: return std::pair<double, double>(1.46E-01, 10.26);
		case  905: return std::pair<double, double>(1.41E-01, 10.3);
		case  910: return std::pair<double, double>(1.35E-01, 10.34);
		case  915: return std::pair<double, double>(1.30E-01, 10.38);
		case  920: return std::pair<double, double>(1.25E-01, 10.42);
		case  925: return std::pair<double, double>(1.21E-01, 10.47);
		case  930: return std::pair<double, double>(1.16E-01, 10.51);
		case  935: return std::pair<double, double>(1.12E-01, 10.55);
		case  940: return std::pair<double, double>(1.08E-01, 10.59);
		case  945: return std::pair<double, double>(1.04E-01, 10.63);
		case  950: return std::pair<double, double>(9.97E-02, 10.67);
		case  955: return std::pair<double, double>(9.60E-02, 10.71);
		case  960: return std::pair<double, double>(9.25E-02, 10.76);
		case  965: return std::pair<double, double>(8.91E-02, 10.8);
		case  970: return std::pair<double, double>(8.58E-02, 10.84);
		case  975: return std::pair<double, double>(8.27E-02, 10.88);
		case  980: return std::pair<double, double>(7.97E-02, 10.93);
		case  985: return std::pair<double, double>(7.68E-02, 10.97);
		case  990: return std::pair<double, double>(7.40E-02, 11.01);
		case  995: return std::pair<double, double>(7.13E-02, 11.06);
		case  1000: return std::pair<double, double>(6.88E-02, 11.1);
		case  1005: return std::pair<double, double>(6.63E-02, 11.14);
		case  1010: return std::pair<double, double>(6.39E-02, 11.19);
		case  1015: return std::pair<double, double>(6.16E-02, 11.23);
		case  1020: return std::pair<double, double>(5.94E-02, 11.28);
		case  1025: return std::pair<double, double>(5.73E-02, 11.32);
		case  1030: return std::pair<double, double>(5.53E-02, 11.37);
		case  1035: return std::pair<double, double>(5.34E-02, 11.41);
		case  1040: return std::pair<double, double>(5.15E-02, 11.46);
		case  1045: return std::pair<double, double>(4.97E-02, 11.51);
		case  1050: return std::pair<double, double>(4.79E-02, 11.55);
		case  1055: return std::pair<double, double>(4.63E-02, 11.6);
		case  1060: return std::pair<double, double>(4.47E-02, 11.64);
		case  1065: return std::pair<double, double>(4.31E-02, 11.69);
		case  1070: return std::pair<double, double>(4.16E-02, 11.74);
		case  1075: return std::pair<double, double>(4.02E-02, 11.79);
		case  1080: return std::pair<double, double>(3.88E-02, 11.83);
		case  1085: return std::pair<double, double>(3.75E-02, 11.88);
		case  1090: return std::pair<double, double>(3.62E-02, 11.93);
		case  1095: return std::pair<double, double>(3.49E-02, 11.98);
		case  1100: return std::pair<double, double>(3.37E-02, 12.02);
		case  1105: return std::pair<double, double>(3.26E-02, 12.07);
		case  1110: return std::pair<double, double>(3.15E-02, 12.12);
		case  1115: return std::pair<double, double>(3.04E-02, 12.17);
		case  1120: return std::pair<double, double>(2.94E-02, 12.22);
		case  1125: return std::pair<double, double>(2.84E-02, 12.27);
		case  1130: return std::pair<double, double>(2.74E-02, 12.32);
		case  1135: return std::pair<double, double>(2.65E-02, 12.36);
		case  1140: return std::pair<double, double>(2.56E-02, 12.41);
		case  1145: return std::pair<double, double>(2.48E-02, 12.46);
		case  1150: return std::pair<double, double>(2.39E-02, 12.51);
		case  1155: return std::pair<double, double>(2.31E-02, 12.56);
		case  1160: return std::pair<double, double>(2.24E-02, 12.61);
		case  1165: return std::pair<double, double>(2.16E-02, 12.66);
		case  1170: return std::pair<double, double>(2.09E-02, 12.71);
		case  1175: return std::pair<double, double>(2.02E-02, 12.76);
		case  1180: return std::pair<double, double>(1.96E-02, 12.82);
		case  1185: return std::pair<double, double>(1.89E-02, 12.87);
		case  1190: return std::pair<double, double>(1.83E-02, 12.92);
		case  1195: return std::pair<double, double>(1.77E-02, 12.97);
		case  1200: return std::pair<double, double>(1.71E-02, 13.02);
		case  1205: return std::pair<double, double>(1.66E-02, 13.07);
		case  1210: return std::pair<double, double>(1.60E-02, 13.12);
		case  1215: return std::pair<double, double>(1.55E-02, 13.18);
		case  1220: return std::pair<double, double>(1.50E-02, 13.23);
		case  1225: return std::pair<double, double>(1.45E-02, 13.28);
		case  1230: return std::pair<double, double>(1.41E-02, 13.33);
		case  1235: return std::pair<double, double>(1.36E-02, 13.38);
		case  1240: return std::pair<double, double>(1.32E-02, 13.44);
		case  1245: return std::pair<double, double>(1.27E-02, 13.49);
		case  1250: return std::pair<double, double>(1.23E-02, 13.54);
		case  1255: return std::pair<double, double>(1.19E-02, 13.59);
		case  1260: return std::pair<double, double>(1.16E-02, 13.65);
		case  1265: return std::pair<double, double>(1.12E-02, 13.7);
		case  1270: return std::pair<double, double>(1.08E-02, 13.76);
		case  1275: return std::pair<double, double>(1.05E-02, 13.81);
		case  1280: return std::pair<double, double>(1.02E-02, 13.86);
		case  1285: return std::pair<double, double>(9.84E-03, 13.92);
		case  1290: return std::pair<double, double>(9.53E-03, 13.97);
		case  1295: return std::pair<double, double>(9.23E-03, 14.03);
		case  1300: return std::pair<double, double>(8.94E-03, 14.08);
		case  1305: return std::pair<double, double>(8.66E-03, 14.14);
		case  1310: return std::pair<double, double>(8.39E-03, 14.19);
		case  1315: return std::pair<double, double>(8.13E-03, 14.25);
		case  1320: return std::pair<double, double>(7.87E-03, 14.3);
		case  1325: return std::pair<double, double>(7.63E-03, 14.36);
		case  1330: return std::pair<double, double>(7.39E-03, 14.41);
		case  1335: return std::pair<double, double>(7.16E-03, 14.47);
		case  1340: return std::pair<double, double>(6.94E-03, 14.52);
		case  1345: return std::pair<double, double>(6.72E-03, 14.58);
		case  1350: return std::pair<double, double>(6.52E-03, 14.64);
		case  1355: return std::pair<double, double>(6.31E-03, 14.69);
		case  1360: return std::pair<double, double>(6.12E-03, 14.75);
		case  1365: return std::pair<double, double>(5.93E-03, 14.81);
		case  1370: return std::pair<double, double>(5.75E-03, 14.86);
		case  1375: return std::pair<double, double>(5.57E-03, 14.92);
		case  1380: return std::pair<double, double>(5.40E-03, 14.98);
		case  1385: return std::pair<double, double>(5.24E-03, 15.04);
		case  1390: return std::pair<double, double>(5.08E-03, 15.1);
		case  1395: return std::pair<double, double>(4.92E-03, 15.16);
		case  1400: return std::pair<double, double>(4.77E-03, 15.22);
		case  1405: return std::pair<double, double>(4.63E-03, 15.28);
		case  1410: return std::pair<double, double>(4.49E-03, 15.34);
		case  1415: return std::pair<double, double>(4.35E-03, 15.4);
		case  1420: return std::pair<double, double>(4.22E-03, 15.46);
		case  1425: return std::pair<double, double>(4.09E-03, 15.52);
		case  1430: return std::pair<double, double>(3.97E-03, 15.58);
		case  1435: return std::pair<double, double>(3.85E-03, 15.64);
		case  1440: return std::pair<double, double>(3.74E-03, 15.7);
		case  1445: return std::pair<double, double>(3.62E-03, 15.76);
		case  1450: return std::pair<double, double>(3.51E-03, 15.83);
		case  1455: return std::pair<double, double>(3.41E-03, 15.89);
		case  1460: return std::pair<double, double>(3.31E-03, 15.95);
		case  1465: return std::pair<double, double>(3.21E-03, 16.01);
		case  1470: return std::pair<double, double>(3.11E-03, 16.08);
		case  1475: return std::pair<double, double>(3.02E-03, 16.14);
		case  1480: return std::pair<double, double>(2.93E-03, 16.21);
		case  1485: return std::pair<double, double>(2.84E-03, 16.27);
		case  1490: return std::pair<double, double>(2.76E-03, 16.33);
		case  1495: return std::pair<double, double>(2.68E-03, 16.4);
		case  1500: return std::pair<double, double>(2.60E-03, 16.46);
		case  1505: return std::pair<double, double>(2.52E-03, 16.53);
		case  1510: return std::pair<double, double>(2.45E-03, 16.59);
		case  1515: return std::pair<double, double>(2.38E-03, 16.65);
		case  1520: return std::pair<double, double>(2.31E-03, 16.72);
		case  1525: return std::pair<double, double>(2.24E-03, 16.78);
		case  1530: return std::pair<double, double>(2.17E-03, 16.85);
		case  1535: return std::pair<double, double>(2.11E-03, 16.91);
		case  1540: return std::pair<double, double>(2.05E-03, 16.98);
		case  1545: return std::pair<double, double>(1.99E-03, 17.05);
		case  1550: return std::pair<double, double>(1.93E-03, 17.11);
		case  1555: return std::pair<double, double>(1.87E-03, 17.18);
		case  1560: return std::pair<double, double>(1.82E-03, 17.25);
		case  1565: return std::pair<double, double>(1.76E-03, 17.31);
		case  1570: return std::pair<double, double>(1.71E-03, 17.38);
		case  1575: return std::pair<double, double>(1.66E-03, 17.45);
		case  1580: return std::pair<double, double>(1.62E-03, 17.51);
		case  1585: return std::pair<double, double>(1.57E-03, 17.58);
		case  1590: return std::pair<double, double>(1.52E-03, 17.65);
		case  1595: return std::pair<double, double>(1.48E-03, 17.72);
		case  1600: return std::pair<double, double>(1.44E-03, 17.79);
		case  1605: return std::pair<double, double>(1.40E-03, 17.86);
		case  1610: return std::pair<double, double>(1.36E-03, 17.93);
		case  1615: return std::pair<double, double>(1.32E-03, 18.0);
		case  1620: return std::pair<double, double>(1.28E-03, 18.07);
		case  1625: return std::pair<double, double>(1.24E-03, 18.14);
		case  1630: return std::pair<double, double>(1.21E-03, 18.21);
		case  1635: return std::pair<double, double>(1.17E-03, 18.28);
		case  1640: return std::pair<double, double>(1.14E-03, 18.35);
		case  1645: return std::pair<double, double>(1.11E-03, 18.43);
		case  1650: return std::pair<double, double>(1.07E-03, 18.5);
		case  1655: return std::pair<double, double>(1.04E-03, 18.57);
		case  1660: return std::pair<double, double>(1.01E-03, 18.64);
		case  1665: return std::pair<double, double>(9.85E-04, 18.72);
		case  1670: return std::pair<double, double>(9.57E-04, 18.79);
		case  1675: return std::pair<double, double>(9.30E-04, 18.86);
		case  1680: return std::pair<double, double>(9.03E-04, 18.94);
		case  1685: return std::pair<double, double>(8.78E-04, 19.01);
		case  1690: return std::pair<double, double>(8.53E-04, 19.08);
		case  1695: return std::pair<double, double>(8.29E-04, 19.16);
		case  1700: return std::pair<double, double>(8.05E-04, 19.23);
		case  1705: return std::pair<double, double>(7.82E-04, 19.31);
		case  1710: return std::pair<double, double>(7.60E-04, 19.38);
		case  1715: return std::pair<double, double>(7.39E-04, 19.45);
		case  1720: return std::pair<double, double>(7.18E-04, 19.53);
		case  1725: return std::pair<double, double>(6.98E-04, 19.6);
		case  1730: return std::pair<double, double>(6.78E-04, 19.68);
		case  1735: return std::pair<double, double>(6.59E-04, 19.76);
		case  1740: return std::pair<double, double>(6.41E-04, 19.83);
		case  1745: return std::pair<double, double>(6.23E-04, 19.91);
		case  1750: return std::pair<double, double>(6.05E-04, 19.98);
		case  1755: return std::pair<double, double>(5.88E-04, 20.06);
		case  1760: return std::pair<double, double>(5.72E-04, 20.14);
		case  1765: return std::pair<double, double>(5.56E-04, 20.21);
		case  1770: return std::pair<double, double>(5.40E-04, 20.29);
		case  1775: return std::pair<double, double>(5.25E-04, 20.37);
		case  1780: return std::pair<double, double>(5.11E-04, 20.45);
		case  1785: return std::pair<double, double>(4.96E-04, 20.53);
		case  1790: return std::pair<double, double>(4.83E-04, 20.6);
		case  1795: return std::pair<double, double>(4.69E-04, 20.68);
		case  1800: return std::pair<double, double>(4.56E-04, 20.76);
		case  1805: return std::pair<double, double>(4.43E-04, 20.84);
		case  1810: return std::pair<double, double>(4.31E-04, 20.92);
		case  1815: return std::pair<double, double>(4.19E-04, 21.0);
		case  1820: return std::pair<double, double>(4.08E-04, 21.08);
		case  1825: return std::pair<double, double>(3.96E-04, 21.17);
		case  1830: return std::pair<double, double>(3.85E-04, 21.25);
		case  1835: return std::pair<double, double>(3.75E-04, 21.33);
		case  1840: return std::pair<double, double>(3.64E-04, 21.41);
		case  1845: return std::pair<double, double>(3.54E-04, 21.49);
		case  1850: return std::pair<double, double>(3.44E-04, 21.58);
		case  1855: return std::pair<double, double>(3.35E-04, 21.66);
		case  1860: return std::pair<double, double>(3.26E-04, 21.74);
		case  1865: return std::pair<double, double>(3.17E-04, 21.83);
		case  1870: return std::pair<double, double>(3.08E-04, 21.91);
		case  1875: return std::pair<double, double>(3.00E-04, 21.99);
		case  1880: return std::pair<double, double>(2.91E-04, 22.08);
		case  1885: return std::pair<double, double>(2.83E-04, 22.16);
		case  1890: return std::pair<double, double>(2.76E-04, 22.25);
		case  1895: return std::pair<double, double>(2.68E-04, 22.33);
		case  1900: return std::pair<double, double>(2.61E-04, 22.42);
		case  1905: return std::pair<double, double>(2.54E-04, 22.51);
		case  1910: return std::pair<double, double>(2.47E-04, 22.59);
		case  1915: return std::pair<double, double>(2.40E-04, 22.68);
		case  1920: return std::pair<double, double>(2.33E-04, 22.77);
		case  1925: return std::pair<double, double>(2.27E-04, 22.85);
		case  1930: return std::pair<double, double>(2.21E-04, 22.94);
		case  1935: return std::pair<double, double>(2.15E-04, 23.03);
		case  1940: return std::pair<double, double>(2.09E-04, 23.12);
		case  1945: return std::pair<double, double>(2.03E-04, 23.2);
		case  1950: return std::pair<double, double>(1.98E-04, 23.29);
		case  1955: return std::pair<double, double>(1.92E-04, 23.38);
		case  1960: return std::pair<double, double>(1.87E-04, 23.47);
		case  1965: return std::pair<double, double>(1.82E-04, 23.56);
		case  1970: return std::pair<double, double>(1.77E-04, 23.65);
		case  1975: return std::pair<double, double>(1.72E-04, 23.74);
		case  1980: return std::pair<double, double>(1.68E-04, 23.83);
		case  1985: return std::pair<double, double>(1.63E-04, 23.92);
		case  1990: return std::pair<double, double>(1.59E-04, 24.01);
		case  1995: return std::pair<double, double>(1.54E-04, 24.11);
		case  2000: return std::pair<double, double>(1.50E-04, 24.2);
		case  2005: return std::pair<double, double>(1.46E-04, 24.29);
		case  2010: return std::pair<double, double>(1.42E-04, 24.38);
		case  2015: return std::pair<double, double>(1.38E-04, 24.48);
		case  2020: return std::pair<double, double>(1.35E-04, 24.57);
		case  2025: return std::pair<double, double>(1.31E-04, 24.67);
		case  2030: return std::pair<double, double>(1.27E-04, 24.76);
		case  2035: return std::pair<double, double>(1.24E-04, 24.86);
		case  2040: return std::pair<double, double>(1.21E-04, 24.95);
		case  2045: return std::pair<double, double>(1.17E-04, 25.05);
		case  2050: return std::pair<double, double>(1.14E-04, 25.14);
		case  2055: return std::pair<double, double>(1.11E-04, 25.24);
		case  2060: return std::pair<double, double>(1.08E-04, 25.34);
		case  2065: return std::pair<double, double>(1.05E-04, 25.43);
		case  2070: return std::pair<double, double>(1.02E-04, 25.53);
		case  2075: return std::pair<double, double>(9.96E-05, 25.63);
		case  2080: return std::pair<double, double>(9.70E-05, 25.73);
		case  2085: return std::pair<double, double>(9.44E-05, 25.83);
		case  2090: return std::pair<double, double>(9.18E-05, 25.93);
		case  2095: return std::pair<double, double>(8.94E-05, 26.03);
		case  2100: return std::pair<double, double>(8.70E-05, 26.13);
		case  2105: return std::pair<double, double>(8.46E-05, 26.23);
		case  2110: return std::pair<double, double>(8.24E-05, 26.33);
		case  2115: return std::pair<double, double>(8.02E-05, 26.43);
		case  2120: return std::pair<double, double>(7.80E-05, 26.53);
		case  2125: return std::pair<double, double>(7.59E-05, 26.63);
		case  2130: return std::pair<double, double>(7.39E-05, 26.73);
		case  2135: return std::pair<double, double>(7.19E-05, 26.84);
		case  2140: return std::pair<double, double>(7.00E-05, 26.94);
		case  2145: return std::pair<double, double>(6.81E-05, 27.04);
		case  2150: return std::pair<double, double>(6.63E-05, 27.15);
		case  2155: return std::pair<double, double>(6.45E-05, 27.25);
		case  2160: return std::pair<double, double>(6.28E-05, 27.35);
		case  2165: return std::pair<double, double>(6.12E-05, 27.46);
		case  2170: return std::pair<double, double>(5.95E-05, 27.57);
		case  2175: return std::pair<double, double>(5.79E-05, 27.67);
		case  2180: return std::pair<double, double>(5.64E-05, 27.78);
		case  2185: return std::pair<double, double>(5.49E-05, 27.89);
		case  2190: return std::pair<double, double>(5.34E-05, 27.99);
		case  2195: return std::pair<double, double>(5.20E-05, 28.1);
		case  2200: return std::pair<double, double>(5.06E-05, 28.21);
		case  2205: return std::pair<double, double>(4.93E-05, 28.32);
		case  2210: return std::pair<double, double>(4.80E-05, 28.43);
		case  2215: return std::pair<double, double>(4.67E-05, 28.54);
		case  2220: return std::pair<double, double>(4.55E-05, 28.65);
		case  2225: return std::pair<double, double>(4.42E-05, 28.76);
		case  2230: return std::pair<double, double>(4.31E-05, 28.87);
		case  2235: return std::pair<double, double>(4.19E-05, 28.99);
		case  2240: return std::pair<double, double>(4.08E-05, 29.1);
		case  2245: return std::pair<double, double>(3.97E-05, 29.21);
		case  2250: return std::pair<double, double>(3.87E-05, 29.33);
		case  2255: return std::pair<double, double>(3.77E-05, 29.44);
		case  2260: return std::pair<double, double>(3.67E-05, 29.56);
		case  2265: return std::pair<double, double>(3.57E-05, 29.67);
		case  2270: return std::pair<double, double>(3.47E-05, 29.79);
		case  2275: return std::pair<double, double>(3.38E-05, 29.91);
		case  2280: return std::pair<double, double>(3.29E-05, 30.02);
		case  2285: return std::pair<double, double>(3.21E-05, 30.14);
		case  2290: return std::pair<double, double>(3.12E-05, 30.26);
		case  2295: return std::pair<double, double>(3.04E-05, 30.38);
		case  2300: return std::pair<double, double>(2.96E-05, 30.5);
		case  2305: return std::pair<double, double>(2.88E-05, 30.62);
		case  2310: return std::pair<double, double>(2.80E-05, 30.74);
		case  2315: return std::pair<double, double>(2.73E-05, 30.86);
		case  2320: return std::pair<double, double>(2.66E-05, 30.98);
		case  2325: return std::pair<double, double>(2.59E-05, 31.1);
		case  2330: return std::pair<double, double>(2.52E-05, 31.22);
		case  2335: return std::pair<double, double>(2.45E-05, 31.35);
		case  2340: return std::pair<double, double>(2.39E-05, 31.47);
		case  2345: return std::pair<double, double>(2.33E-05, 31.59);
		case  2350: return std::pair<double, double>(2.26E-05, 31.72);
		case  2355: return std::pair<double, double>(2.20E-05, 31.84);
		case  2360: return std::pair<double, double>(2.15E-05, 31.97);
		case  2365: return std::pair<double, double>(2.09E-05, 32.09);
		case  2370: return std::pair<double, double>(2.03E-05, 32.22);
		case  2375: return std::pair<double, double>(1.98E-05, 32.35);
		case  2380: return std::pair<double, double>(1.93E-05, 32.48);
		case  2385: return std::pair<double, double>(1.88E-05, 32.6);
		case  2390: return std::pair<double, double>(1.83E-05, 32.73);
		case  2395: return std::pair<double, double>(1.78E-05, 32.86);
		case  2400: return std::pair<double, double>(1.73E-05, 32.99);
		case  2405: return std::pair<double, double>(1.69E-05, 33.12);
		case  2410: return std::pair<double, double>(1.64E-05, 33.26);
		case  2415: return std::pair<double, double>(1.60E-05, 33.39);
		case  2420: return std::pair<double, double>(1.56E-05, 33.52);
		case  2425: return std::pair<double, double>(1.52E-05, 33.65);
		case  2430: return std::pair<double, double>(1.48E-05, 33.79);
		case  2435: return std::pair<double, double>(1.44E-05, 33.92);
		case  2440: return std::pair<double, double>(1.40E-05, 34.06);
		case  2445: return std::pair<double, double>(1.36E-05, 34.19);
		case  2450: return std::pair<double, double>(1.33E-05, 34.33);
		case  2455: return std::pair<double, double>(1.29E-05, 34.47);
		case  2460: return std::pair<double, double>(1.26E-05, 34.61);
		case  2465: return std::pair<double, double>(1.23E-05, 34.75);
		case  2470: return std::pair<double, double>(1.19E-05, 34.89);
		case  2475: return std::pair<double, double>(1.16E-05, 35.03);
		case  2480: return std::pair<double, double>(1.13E-05, 35.17);
		case  2485: return std::pair<double, double>(1.10E-05, 35.31);
		case  2490: return std::pair<double, double>(1.07E-05, 35.46);
		case  2495: return std::pair<double, double>(1.05E-05, 35.6);
		case  2500: return std::pair<double, double>(1.02E-05, 35.75);
		case  2505: return std::pair<double, double>(9.91E-06, 35.89);
		case  2510: return std::pair<double, double>(9.65E-06, 36.04);
		case  2515: return std::pair<double, double>(9.40E-06, 36.19);
		case  2520: return std::pair<double, double>(9.15E-06, 36.34);
		case  2525: return std::pair<double, double>(8.91E-06, 36.49);
		case  2530: return std::pair<double, double>(8.68E-06, 36.64);
		case  2535: return std::pair<double, double>(8.45E-06, 36.8);
		case  2540: return std::pair<double, double>(8.23E-06, 36.95);
		case  2545: return std::pair<double, double>(8.01E-06, 37.1);
		case  2550: return std::pair<double, double>(7.80E-06, 37.26);
		case  2555: return std::pair<double, double>(7.60E-06, 37.42);
		case  2560: return std::pair<double, double>(7.40E-06, 37.57);
		case  2565: return std::pair<double, double>(7.21E-06, 37.73);
		case  2570: return std::pair<double, double>(7.02E-06, 37.89);
		case  2575: return std::pair<double, double>(6.83E-06, 38.06);
		case  2580: return std::pair<double, double>(6.65E-06, 38.22);
		case  2585: return std::pair<double, double>(6.48E-06, 38.38);
		case  2590: return std::pair<double, double>(6.31E-06, 38.55);
		case  2595: return std::pair<double, double>(6.14E-06, 38.71);
		case  2600: return std::pair<double, double>(5.98E-06, 38.88);
		case  2605: return std::pair<double, double>(5.83E-06, 39.05);
		case  2610: return std::pair<double, double>(5.67E-06, 39.22);
		case  2615: return std::pair<double, double>(5.53E-06, 39.39);
		case  2620: return std::pair<double, double>(5.38E-06, 39.56);
		case  2625: return std::pair<double, double>(5.24E-06, 39.74);
		case  2630: return std::pair<double, double>(5.10E-06, 39.91);
		case  2635: return std::pair<double, double>(4.97E-06, 40.09);
		case  2640: return std::pair<double, double>(4.84E-06, 40.27);
		case  2645: return std::pair<double, double>(4.71E-06, 40.45);
		case  2650: return std::pair<double, double>(4.59E-06, 40.63);
		case  2655: return std::pair<double, double>(4.47E-06, 40.81);
		case  2660: return std::pair<double, double>(4.35E-06, 40.99);
		case  2665: return std::pair<double, double>(4.24E-06, 41.17);
		case  2670: return std::pair<double, double>(4.13E-06, 41.35);
		case  2675: return std::pair<double, double>(4.02E-06, 41.53);
		case  2680: return std::pair<double, double>(3.91E-06, 41.72);
		case  2685: return std::pair<double, double>(3.81E-06, 41.9);
		case  2690: return std::pair<double, double>(3.71E-06, 42.09);
		case  2695: return std::pair<double, double>(3.61E-06, 42.28);
		case  2700: return std::pair<double, double>(3.52E-06, 42.46);
		case  2705: return std::pair<double, double>(3.43E-06, 42.65);
		case  2710: return std::pair<double, double>(3.34E-06, 42.84);
		case  2715: return std::pair<double, double>(3.25E-06, 43.03);
		case  2720: return std::pair<double, double>(3.16E-06, 43.22);
		case  2725: return std::pair<double, double>(3.08E-06, 43.41);
		case  2730: return std::pair<double, double>(3.00E-06, 43.6);
		case  2735: return std::pair<double, double>(2.92E-06, 43.79);
		case  2740: return std::pair<double, double>(2.85E-06, 43.98);
		case  2745: return std::pair<double, double>(2.77E-06, 44.17);
		case  2750: return std::pair<double, double>(2.70E-06, 44.36);
		case  2755: return std::pair<double, double>(2.63E-06, 44.56);
		case  2760: return std::pair<double, double>(2.56E-06, 44.75);
		case  2765: return std::pair<double, double>(2.49E-06, 44.95);
		case  2770: return std::pair<double, double>(2.43E-06, 45.14);
		case  2775: return std::pair<double, double>(2.36E-06, 45.33);
		case  2780: return std::pair<double, double>(2.30E-06, 45.53);
		case  2785: return std::pair<double, double>(2.24E-06, 45.73);
		case  2790: return std::pair<double, double>(2.18E-06, 45.92);
		case  2795: return std::pair<double, double>(2.13E-06, 46.12);
		case  2800: return std::pair<double, double>(2.07E-06, 46.31);
		case  2805: return std::pair<double, double>(2.02E-06, 46.51);
		case  2810: return std::pair<double, double>(1.96E-06, 46.7);
		case  2815: return std::pair<double, double>(1.91E-06, 46.89);
		case  2820: return std::pair<double, double>(1.86E-06, 47.09);
		case  2825: return std::pair<double, double>(1.81E-06, 47.28);
		case  2830: return std::pair<double, double>(1.77E-06, 47.47);
		case  2835: return std::pair<double, double>(1.72E-06, 47.67);
		case  2840: return std::pair<double, double>(1.68E-06, 47.86);
		case  2845: return std::pair<double, double>(1.63E-06, 48.06);
		case  2850: return std::pair<double, double>(1.59E-06, 48.26);
		case  2855: return std::pair<double, double>(1.55E-06, 48.45);
		case  2860: return std::pair<double, double>(1.51E-06, 48.65);
		case  2865: return std::pair<double, double>(1.47E-06, 48.85);
		case  2870: return std::pair<double, double>(1.43E-06, 49.05);
		case  2875: return std::pair<double, double>(1.39E-06, 49.25);
		case  2880: return std::pair<double, double>(1.36E-06, 49.46);
		case  2885: return std::pair<double, double>(1.32E-06, 49.66);
		case  2890: return std::pair<double, double>(1.29E-06, 49.86);
		case  2895: return std::pair<double, double>(1.25E-06, 50.07);
		case  2900: return std::pair<double, double>(1.22E-06, 50.28);
		case  2905: return std::pair<double, double>(1.19E-06, 50.48);
		case  2910: return std::pair<double, double>(1.16E-06, 50.69);
		case  2915: return std::pair<double, double>(1.13E-06, 50.9);
		case  2920: return std::pair<double, double>(1.10E-06, 51.12);
		case  2925: return std::pair<double, double>(1.07E-06, 51.33);
		case  2930: return std::pair<double, double>(1.04E-06, 51.55);
		case  2935: return std::pair<double, double>(1.01E-06, 51.76);
		case  2940: return std::pair<double, double>(9.88E-07, 51.98);
		case  2945: return std::pair<double, double>(9.62E-07, 52.2);
		case  2950: return std::pair<double, double>(9.37E-07, 52.42);
		case  2955: return std::pair<double, double>(9.13E-07, 52.65);
		case  2960: return std::pair<double, double>(8.89E-07, 52.87);
		case  2965: return std::pair<double, double>(8.66E-07, 53.1);
		case  2970: return std::pair<double, double>(8.43E-07, 53.33);
		case  2975: return std::pair<double, double>(8.21E-07, 53.56);
		case  2980: return std::pair<double, double>(8.00E-07, 53.79);
		case  2985: return std::pair<double, double>(7.79E-07, 54.03);
		case  2990: return std::pair<double, double>(7.59E-07, 54.26);
		case  2995: return std::pair<double, double>(7.39E-07, 54.5);
		case  3000: return std::pair<double, double>(7.20E-07, 54.75);
		default: return std::pair<double, double>(-9999,-9999);
	}
}
