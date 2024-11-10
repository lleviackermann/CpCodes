vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        sort(products.begin(), products.end());
        deque<string> deq;
        for(int i =0;i<products.size();i++){
            deq.push_back(products[i]);
        }
        int n = searchWord.size();
        vector<vector<string>> results;
        for(int i =0;i<n;i++){
            while(deq.size()!=0 && searchWord[i]!=deq[0][i]){
                deq.pop_front();
            }
            for(int j =deq.size()-1;j>=0 && searchWord[i]!=deq[j][i];j--){
             
                deq.pop_back();
            }
            results.push_back({});
            for(int j =0;j<min(3ul, deq.size());j++){
                results[results.size()-1].push_back(deq[j]);
            }
        }
        return results;
    }