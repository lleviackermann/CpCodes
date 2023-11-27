let url = "https://jsonmock.hackerrank.com/api/medical_records?page=";

let ans = 0;
let low = 120, high = 160;

const sum = (data) => {
    const val = data.vitals.bloodPressureDiastole;
    if(val >= low && val <= high) ans++;
}
const apiCall = async() => {

    for(let i = 1; i <= 10; i++){
        const tempUrl = url + i;
        const responseData = await fetch(tempUrl, {method: "GET"}).then(res => res.json());
        const data = responseData.data;
        data.forEach(sum);
    }
    console.log(ans);
}

apiCall();