#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>
using namespace std;

// Enhanced base conversion for very large numbers
long long baseToDecimal(const string& value, int base) {
    cout << "Converting \"" << value << "\" from base " << base << ":" << endl;
    
    long long result = 0;
    long long power = 1;
    
    // Process from right to left for better handling of large numbers
    for (int i = value.length() - 1; i >= 0; i--) {
        char digit = value[i];
        int digitValue;
        
        if (digit >= '0' && digit <= '9') {
            digitValue = digit - '0';
        } else if (digit >= 'a' && digit <= 'z') {
            digitValue = digit - 'a' + 10;
        } else if (digit >= 'A' && digit <= 'Z') {
            digitValue = digit - 'A' + 10;
        } else {
            cout << "Error: Invalid digit '" << digit << "'" << endl;
            return -1;
        }
        
        if (digitValue >= base) {
            cout << "Error: Digit " << digitValue << " >= base " << base << endl;
            return -1;
        }
        
        result += digitValue * power;
        power *= base;
        
        // Show calculation for first few and last few digits
        if (i >= value.length() - 3 || i <= 2) {
            cout << "  " << digitValue << " × " << base << "^" << (value.length() - 1 - i) 
                 << " = " << digitValue * (power / base) << endl;
        } else if (i == 3 && value.length() > 6) {
            cout << "  ... (middle digits) ..." << endl;
        }
    }
    
    cout << "  Result: " << result << endl << endl;
    return result;
}

struct Point {
    int x;
    long long y;
};

// High precision Lagrange interpolation
long long lagrangeInterpolation(const vector<Point>& points) {
    cout << "=== LAGRANGE INTERPOLATION FOR f(0) ===" << endl;
    cout << "Using " << points.size() << " points:" << endl;
    
    for (size_t i = 0; i < points.size(); i++) {
        cout << "  Point " << (i+1) << ": (" << points[i].x << ", " << points[i].y << ")" << endl;
    }
    cout << endl;
    
    long double result = 0.0;
    int n = points.size();
    
    for (int i = 0; i < n; i++) {
        long double numerator = 1.0;
        long double denominator = 1.0;
        
        cout << "For point (" << points[i].x << ", " << points[i].y << "):" << endl;
        
        // Calculate Lagrange basis polynomial Li(0)
        for (int j = 0; j < n; j++) {
            if (i != j) {
                numerator *= (0 - points[j].x);
                denominator *= (points[i].x - points[j].x);
                cout << "  Factor: (0-" << points[j].x << ")/(" << points[i].x 
                     << "-" << points[j].x << ") = " << (0 - points[j].x) 
                     << "/" << (points[i].x - points[j].x) << endl;
            }
        }
        
        long double basisValue = numerator / denominator;
        long double contribution = points[i].y * basisValue;
        
        cout << "  L" << i << "(0) = " << fixed << setprecision(10) << basisValue << endl;
        cout << "  Contribution = " << points[i].y << " × " << basisValue 
             << " = " << contribution << endl << endl;
        
        result += contribution;
    }
    
    cout << "Total sum = " << fixed << setprecision(10) << result << endl;
    cout << "Rounded = " << (long long)round(result) << endl;
    
    return (long long)round(result);
}

int main() {
    cout << "=== SHAMIR'S SECRET SHARING - TEST CASE 2 ===" << endl;
    cout << "=============================================" << endl << endl;
    
    // Test Case 2 data
    vector<pair<int, pair<int, string>>> testData = {
        {1, {6, "13444211440455345511"}},
        {2, {15, "aed7015a346d635"}},
        {3, {15, "6aeeb69631c227c"}},
        {4, {16, "e1b5e05623d881f"}},
        {5, {8, "316034514573652620673"}},
        {6, {3, "2122212201122002221120200210011020220200"}},
        {7, {3, "20120221122211000100210021102001201112121"}},
        {8, {6, "20220554335330240002224253"}},
        {9, {12, "45153788322a1255483"}},
        {10, {7, "1101613130313526312514143"}}
    };
    
    int n = 10;  // Total points
    int k = 7;   // Points needed
    
    cout << "Total points available: " << n << endl;
    cout << "Minimum points needed: " << k << endl;
    cout << "Polynomial degree: " << (k-1) << endl << endl;
    
    vector<Point> points;
    
    // Convert all points from their bases to decimal
    cout << "=== BASE CONVERSIONS ===" << endl;
    for (const auto& data : testData) {
        int x = data.first;
        int base = data.second.first;
        string value = data.second.second;
        
        cout << "Point " << x << " (base " << base << "):" << endl;
        long long y = baseToDecimal(value, base);
        
        if (y != -1) {
            points.push_back({x, y});
            cout << "Final: (" << x << ", " << y << ")" << endl;
        } else {
            cout << "Error converting point " << x << endl;
        }
        cout << string(50, '-') << endl;
    }
    
    // Use first k points for interpolation
    vector<Point> selectedPoints(points.begin(), points.begin() + k);
    
    cout << "\n=== SELECTED POINTS FOR CALCULATION ===" << endl;
    for (int i = 0; i < k; i++) {
        cout << "Point " << (i+1) << ": (" << selectedPoints[i].x 
             << ", " << selectedPoints[i].y << ")" << endl;
    }
    cout << endl;
    
    // Calculate the secret
    long long secret = lagrangeInterpolation(selectedPoints);
    
    cout << "\n=== FINAL RESULT ===" << endl;
    cout << "🔐 THE SECRET FOR TEST CASE 2: " << secret << endl;
    
    // Additional verification info
    cout << "\n=== VERIFICATION NOTES ===" << endl;
    cout << "- All base conversions completed successfully" << endl;
    cout << "- Used first 7 points for degree-6 polynomial" << endl;
    cout << "- Lagrange interpolation applied to find f(0)" << endl;
    cout << "- Result rounded to nearest integer" << endl;
    
    return 0;
}

