#include <iostream>
#include <fstream>
#include<sstream>
#include<iomanip>
#include<vector>
#include <string>

using namespace std;

struct DiseaseData {
    string diseaseCode;
    string diseaseName;
    int year;
    string county;
    string gender;
    int count;
    double rate=count*100000;
};

void viewCidDataByDisease(string diseaseDataFile, string diseaseInfoFile, string diseaseCode) {
vector<DiseaseData> data;
    ifstream diseaseData(diseaseDataFile);
    ifstream diseaseInfo(diseaseInfoFile);
    string line;
    getline(diseaseData, line); // skip header line
    while (getline(diseaseData, line)) {
        DiseaseData d;
        stringstream ss(line);
        getline(ss, d.county, ',');
        getline(ss, d.diseaseCode, ',');
        ss >> d.year;
        ss.ignore();
        getline(ss, d.gender, ',');
        ss >> d.count;
        ss.ignore();
        if (d.count > 0) {
            data.push_back(d);
        }
    }
    diseaseData.close();
    getline(diseaseInfo, line); // skip header line
    while (getline(diseaseInfo, line)) {
        stringstream ss(line);
        string code, name;
        double rate;
        getline(ss, code, ',');
        getline(ss, name, ',');
        ss >> rate;
        for (auto& d : data) {
            if (d.diseaseCode == code && d.diseaseCode == diseaseCode) {
                d.diseaseName = name;
                d.rate = rate;
            }
        }
    }
    diseaseInfo.close();
    // Display the summary header
    cout << "SUMMARY BY INFECTIOUS DISEASE" << endl;
    cout << "==============================================================" << endl;
    cout << "DIS-CODE   DIS-NAME   YEAR   COUNTY   GENDER  COUNT     RATE" << endl;
    cout << "==============================================================" << endl;
    // Display the matching data
    for (auto& d : data) {
        if (d.diseaseCode == diseaseCode) {
            cout << setw(6) << d.diseaseCode << " ";
            cout << setw(14) << d.diseaseName << " ";
            cout << setw(4) << d.year << " ";
            cout << setw(12) << d.county << " ";
            cout << setw(10) << d.gender << " ";
            cout << setw(5) << d.count << " ";
            cout << setw(8) << d.rate << endl;
        }
    }
    // Display the summary footer
    int totalCount = 0;
    double totalRate = 0.0;
    for (auto& d : data) {
        if (d.diseaseCode == diseaseCode) {
            totalCount += d.count;
            totalRate += d.rate;
        }
    }
    cout << "==============================================================" << endl;
    cout << "TOTALS  " << setw(40) << totalCount << " " << setw(8) << totalRate << endl;
    cout << "==============================================================" << endl;
}

int main() {
    viewCidDataByDisease("cid_data.txt", "disease_info.txt", "C0DE");// replace "CODE" with the desired disease code
    return 0;
}