#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include<sstream>

using namespace std;

void viewCidDataByDisease(string diseaseDataFile, string diseaseInfoFile, string diseaseCode) {
    ifstream diseaseData(diseaseDataFile);
    ifstream diseaseInfo(diseaseInfoFile);
    string line;
    getline(diseaseData, line); // skip header line
    getline(diseaseInfo, line); // skip header line
    // Display the summary header
    cout << "SUMMARY BY INFECTIOUS DISEASE" << endl;
    cout << "==============================================================" << endl;
    cout << "DIS-CODE DIS-NAME YEAR    COUNTY   GENDER  COUNT   RATE"    << endl;
    cout << "==============================================================" << endl;
    // Display the matching data
    while (getline(diseaseData, line)) {
        string county, code, gender;
        int year, count, population;
        double rate;
        istringstream ss(line);
        getline(ss, county, ',');
        getline(ss, code, ',');
        ss >> year;
        ss.ignore();
        getline(ss, gender, ',');
        ss >> count;
        ss.ignore();
        ss >> population;
        ss.ignore();
        if (code == diseaseCode && count > 0) {
            rate = static_cast<double>(count) / population * 100000;
            cout << setw(6) << code << " ";
            cout << setw(14) << "" << " ";
            cout << setw(4) << year << " ";
            cout << setw(12) << county << " ";
            cout << setw(10) << gender << " ";
            cout << setw(5) << count << " ";
            cout << setw(8) << fixed << setprecision(2) << rate << endl;
        }
    }
    // Display the summary footer
    int totalCount = 0;
    double totalRate = 0.0;
    diseaseInfo.clear();
    diseaseInfo.seekg(0, ios::beg); // reset the file pointer
    getline(diseaseInfo, line); // skip header line
    while (getline(diseaseInfo, line)) {
        string code, name;
        double rate;
        istringstream ss(line);
        getline(ss, code, ',');
        getline(ss, name, ',');
        ss >> rate;
        if (code == diseaseCode) {
            name = name.substr(1, name.length() - 2); // remove quotes from name
            cout << setw(6) << code << " ";
            cout << setw(14) << name << " ";
            cout << setw(4) << "" << " ";
            cout << setw(12) << "" << " ";
            cout << setw(10) << "" << " ";
            cout << setw(5) << "" << " ";
            cout << setw(8) << fixed << setprecision(2) << rate << endl;
            totalRate = rate;
        }
    }
    diseaseData.close();
    diseaseInfo.close();
    cout << "==============================================================" << endl;
    cout << "TOTALS  " << setw(5) << "" << " " << setw(8) << fixed << setprecision(2) << totalRate << endl;
    cout << "==============================================================" << endl;
}

int main() {
    viewCidDataByDisease("cid_data.txt", "disease_info.txt", "CODE"); // replace "CODE" with the desired disease code
    return 0;
}