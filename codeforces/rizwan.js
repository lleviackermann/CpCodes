/* RIZWAN  */
// Dubai Airport
function calculateRequiredStations(arrivals, departures, totalTrains) {
    const sortedArrivals = [...arrivals].sort((a, b) => a - b);
    const sortedDepartures = [...departures].sort((a, b) => a - b);

    let maxConcurrent = 0;
    let currentStations = 0;
    let arrivalIndex = 0;
    let departureIndex = 0;

    while (arrivalIndex < totalTrains && departureIndex < totalTrains) {
        if (sortedArrivals[arrivalIndex] <= sortedDepartures[departureIndex]) {
            currentStations++;
            arrivalIndex++;
        } else {
            currentStations--;
            departureIndex++;
        }

        maxConcurrent = Math.max(maxConcurrent, currentStations);
    }

    return maxConcurrent;
}

// BOOKS
function isPartitionValid(threshold, sequence, length, maxGroups) {
    let groupSum = 0;
    let groupCount = 0;
    let index = 0;

    while (index < length) {
        if (sequence[index] > threshold) return false;
        
        groupSum += sequence[index];
        
        if (groupSum > threshold) {
            groupCount++;
            groupSum = sequence[index];
        }
        index++;
    }
    groupCount++;

    return groupCount <= maxGroups;
}

function optimizePartition(sequence, length, maxGroups) {
    const maxElement = Math.max(...sequence);
    let lowerBound = maxElement;
    let upperBound = sequence.reduce((sum, num) => sum + num, 0);
    
    let optimalThreshold = upperBound;

    while (lowerBound <= upperBound) {
        const midpoint = Math.floor((lowerBound + upperBound) / 2);
        
        if (isPartitionValid(midpoint, sequence, length, maxGroups)) {
            optimalThreshold = midpoint;
            upperBound = midpoint - 1;
        } else {
            lowerBound = midpoint + 1;
        }
    }

    return optimalThreshold;
}


// String permutation
var checkInclusion = function (pattern, text) {
    if (pattern.length > text.length) return false;

    let charCount = {}; 

    for (let i = 0; i < pattern.length; i++) {
        charCount[pattern[i]] = (charCount[pattern[i]] || 0) + 1;
    }

    let left = 0,
        right = 0,
        requiredChars = pattern.length;

    while (right < text.length) {
        if (charCount[text[right]] > 0) requiredChars--;

        charCount[text[right]]--;
        right++;

        if (requiredChars === 0) return true;

        if (right - left === pattern.length) {
            if (charCount[text[left]] >= 0) requiredChars++;
            charCount[text[left]]++;
            left++;
        }
    }

    return false;
};


// MAJORITY
function findMajorityElement(array, n) {
    let candidate;
    let balance = 0;
    let index = 0;

    while (index < array.length) {
        const item = array[index];
        if (balance === 0) {
            candidate = item;
        }
        balance += (item === candidate) ? 1 : -1;
        index++;
    }

    return candidate;
}