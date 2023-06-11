#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct DiseaseData {
    string county;
    string disease;
    string sex;
    int year;
    int cases;
    int count;
    double rate;
};

void viewCidDataByDisease(string diseaseDataFile, string diseaseInfoFile, string diseaseCode) {
    // Open the disease data file
    ifstream diseaseData(diseaseDataFile);
    string diseaseDataLine;
    // Open the disease info file
    ifstream diseaseInfo(diseaseInfoFile);
    string diseaseInfoLine;
    // Initialize variables for totals
    int totalCount = 0;
    double totalRate = count*100000;
    // Display the summary header
    cout << "SUMMARY BY INFECTIOUS DISEASE" << endl;
    cout << "==============================================================" << endl;
    cout << "DIS-CODE DIS-NAME YEAR COUNTY GENDER COUNT RATE" << endl;
    cout << "==============================================================" << endl;
    // Loop through the disease data file
    while (getline(diseaseData, diseaseDataLine)) {
        // Split the line into fields
        string county, disease, sex;
        int year, cases;
        stringstream ss(diseaseDataLine);
        getline(ss, county, ',');
        getline(ss, disease, ',');
        getline(ss, sex, ',');
        ss >> year;
        ss.ignore();
       // if (d.count > 0) {
       //     data.push_back(d);
       //}
        ss >> cases;
        // Check if the disease code matches and the count is not zero
        if (disease == diseaseCode && cases > 0) {
            // Loop through the disease info file
            while (getline(diseaseInfo, diseaseInfoLine)) {
                // Split the line into fields
                string infoDisease;
                double rate;
                stringstream ss2(diseaseInfoLine);
                getline(ss2, infoDisease, ',');
                ss2 >> rate;
                // Check if the disease code matches
                if (infoDisease == diseaseCode) {
                    // Display the matching data
                    cout << diseaseCode << " " << disease << " " << year << " " << county << " " << sex << " " << cases << " " << rate << endl;
                    // Update the totals
                    totalCount += cases;
                    totalRate += rate;
                }
            }
            // Reset the disease info file pointer
            diseaseInfo.clear();
            diseaseInfo.seekg(0, ios::beg);
        }
    }
    // Close the files
    diseaseData.close();
    diseaseInfo.close();
    // Display the summary footer
    cout << "==============================================================" << endl;
    cout << "TOTALS " << totalCount << " " << totalRate << endl;
    cout << "==============================================================" << endl;
}

int main() {
    viewCidDataByDisease("cid_data.txt", "disease_info.txt", "DiseaseCODE");
    return 0;
}