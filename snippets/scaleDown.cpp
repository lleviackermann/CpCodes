void scaleDown(ll minimum, vl &arr) {
    vl temp = arr;
    sort(all(temp));
    uml another;
    another[temp[0]] = minimum;
    int n = arr.size();
    for(int i = 1; i < n; i++) {
        if(temp[i]!=temp[i-1]) another[temp[i]] = ++minimum;
    }
    for(int i = 0; i < n; i++) {
        arr[i] = another[arr[i]];
    }
}