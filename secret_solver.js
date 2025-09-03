// Simple solution for Shamir's Secret Sharing
// Save as: secret_solver.js
// Run with: node secret_solver.js

// Step 1: Convert from any base to decimal
function convertToDecimal(value, base) {
    const digits = '0123456789abcdefghijklmnopqrstuvwxyz';
    let result = 0;
    
    for (let i = 0; i < value.length; i++) {
        const digit = digits.indexOf(value[i].toLowerCase());
        result = result * base + digit;
    }
    
    return result;
}

// Step 2: Find the secret using Lagrange interpolation
function findSecret(points) {
    let secret = 0;
    const n = points.length;
    
    // For each point, calculate its contribution to f(0)
    for (let i = 0; i < n; i++) {
        let contribution = points[i].y;
        
        // Lagrange basis polynomial at x=0
        for (let j = 0; j < n; j++) {
            if (i !== j) {
                contribution *= (0 - points[j].x) / (points[i].x - points[j].x);
            }
        }
        
        secret += contribution;
    }
    
    return Math.round(secret);
}

// Step 3: Main solving function
function solve(inputData) {
    console.log("Starting to solve...\n");
    
    const n = inputData.keys.n;
    const k = inputData.keys.k;
    
    console.log(`Total points available: ${n}`);
    console.log(`Points needed: ${k}\n`);
    
    // Step 4: Convert all points to decimal
    const points = [];
    
    for (let x = 1; x <= n; x++) {
        if (inputData[x.toString()]) {
            const base = parseInt(inputData[x.toString()].base);
            const value = inputData[x.toString()].value;
            const y = convertToDecimal(value, base);
            
            points.push({ x: x, y: y });
            console.log(`Point ${x}: (${x}, ${y}) from base ${base} value "${value}"`);
        }
    }
    
    // Step 5: Use only first k points (we only need k points)
    const neededPoints = points.slice(0, k);
    console.log(`\nUsing these ${k} points:`);
    neededPoints.forEach(p => console.log(`(${p.x}, ${p.y})`));
    
    // Step 6: Find the secret
    const secret = findSecret(neededPoints);
    console.log(`\nThe secret is: ${secret}`);
    
    return secret;
}

// Test Case 1
console.log("=" .repeat(40));
console.log("TEST CASE 1");
console.log("=" .repeat(40));

const test1 = {
    "keys": { "n": 4, "k": 3 },
    "1": { "base": "10", "value": "4" },
    "2": { "base": "2", "value": "111" },
    "3": { "base": "10", "value": "12" },
    "6": { "base": "4", "value": "213" }
};

const answer1 = solve(test1);

// Test Case 2
console.log("\n" + "=" .repeat(40));
console.log("TEST CASE 2");
console.log("=" .repeat(40));

const test2 = {
    "keys": { "n": 10, "k": 7 },
    "1": { "base": "6", "value": "13444211440455345511" },
    "2": { "base": "15", "value": "aed7015a346d635" },
    "3": { "base": "15", "value": "6aeeb69631c227c" },
    "4": { "base": "16", "value": "e1b5e05623d881f" },
    "5": { "base": "8", "value": "316034514573652620673" },
    "6": { "base": "3", "value": "2122212201122002221120200210011020220200" },
    "7": { "base": "3", "value": "20120221122211000100210021102001201112121" },
    "8": { "base": "6", "value": "20220554335330240002224253" },
    "9": { "base": "12", "value": "45153788322a1255483" },
    "10": { "base": "7", "value": "1101613130313526312514143" }
};

const answer2 = solve(test2);

console.log("\n" + "=" .repeat(40));
console.log("FINAL ANSWERS");
console.log("=" .repeat(40));
console.log(`Test Case 1: ${answer1}`);
console.log(`Test Case 2: ${answer2}`);

// To read from a file instead:
// const fs = require('fs');
// const data = JSON.parse(fs.readFileSync('input.json', 'utf8'));
// solve(data);