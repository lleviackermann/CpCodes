function isVowel(x) {
    let result;
    result = x == "a" || x == "e" || x == "i" || x == "o" || x == "u";
    return result;
}

function getWho(s) {
    let ans = []
    s.forEach((word) => {
        let cnt = 0;
        for (let char of word) {
            if (isVowel(char)) {
                cnt++;
            }
        }
        if(cnt == 0) ans.push("Chris");
        else ans.push("Alex");
    });
    return ans;
}

arr = ["ljis", "lhr", "gms"]
console.log(getWho(arr));