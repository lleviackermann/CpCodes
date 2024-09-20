/* MOTA  */
// DUBAI
function findPlatform(landings, takeoffs, totalFlights) {
    function sortSchedule(schedule) {
        return [...schedule].sort((a, b) => a - b);
    }

    const sortedLandings = sortSchedule(landings);
    const sortedTakeoffs = sortSchedule(takeoffs);

    let maxStations = 0;
    let activeStations = 0;

    // Use for loop instead of while
    for (let i = 0, j = 0; i < totalFlights || j < totalFlights;) {
        if (i < totalFlights && (j >= totalFlights || sortedLandings[i] <= sortedTakeoffs[j])) {
            activeStations++;
            i++;
        } else {
            activeStations--;
            j++;
        }

        maxStations = Math.max(maxStations, activeStations);
    }

    return maxStations;
}

/* BOOKS  */
function splitArray(arr, arrLength, maxSubarrays) {
    function canPartition(targetSum) {
        let currentSum = 0;
        let subarrayCount = 0;

        for (let i = 0; i < arrLength; i++) {
            if (arr[i] > targetSum) return false;

            currentSum += arr[i];

            if (currentSum > targetSum) {
                subarrayCount++;
                currentSum = arr[i];
            }
        }

        subarrayCount++;

        return subarrayCount <= maxSubarrays;
    }

    const maxVal = Math.max(...arr);
    let left = maxVal;
    let right = arr.reduce((sum, num) => sum + num, 0);

    let optimalSum = right;

    for (; left <= right;) {
        const mid = Math.floor((left + right) / 2);

        if (canPartition(mid)) {
            optimalSum = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return optimalSum;
}


// String permutation
function isAnagramSubstringPresent(needle, haystack) {
    function buildCharCountMap(str) {
        return [...str].reduce((acc, char) => {
            acc[char] = (acc[char] || 0) + 1;
            return acc;
        }, {});
    }

    const needleCharCount = buildCharCountMap(needle);

    let windowStart = 0;
    let windowCharCount = {};

    for (let windowEnd = 0; windowEnd < haystack.length; windowEnd++) {
        const incomingChar = haystack[windowEnd];
        windowCharCount[incomingChar] = (windowCharCount[incomingChar] || 0) + 1;

        while (windowCharCount[incomingChar] > (needleCharCount[incomingChar] || 0)) {
            windowCharCount[haystack[windowStart]]--;
            windowStart++;
        }

        if (windowEnd - windowStart + 1 === needle.length) {
            return true;
        }
    }

    return false;
}

// MAJORITY
function calcMajority(sequence, n) {
    if (sequence.length === 0) return undefined;
    if (sequence.length === 1) return sequence[0];

    const occurrences = {};
    const threshold = Math.floor(sequence.length / 2) + 1;

    for (const item of sequence) {
        occurrences[item] = (occurrences[item] || 0) + 1;
        
        if (occurrences[item] >= threshold) {
            return item;
        }
    }

    return undefined;
}