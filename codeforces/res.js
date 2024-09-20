function findPlatform(landings, takeoffs, totalFlights) {
    function sortSchedule(schedule) {
        return [...schedule].sort((a, b) => a - b);
    }

    let sortedLandings = [...landings]
    let sortedTakeoffs = [...takeoffs]
    
    for(let i = 0; i < totalFlights; i++) {
        if(sortedTakeoffs[i] < sortedLandings[i]) sortedTakeoffs[i] = 2359;
    }

    sortedLandings = sortSchedule(sortedLandings);
    sortedTakeoffs = sortSchedule(sortedTakeoffs);

    let maxStations = 0;
    let activeStations = 0;
    console.log(sortedLandings);
    console.log(sortedTakeoffs);
    
    
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

const landings = [2200, 2300]
const takeoffs = [200, 300]
console.log(findPlatform(landings, takeoffs, 2));
