// Find the smallest positive number missing from an unsorted array
// Refer: 
// https://www.geeksforgeeks.org/find-the-smallest-positive-number-missing-from-an-unsorted-array/

void swap(int *a, int *b){
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

int mntl(vector<int> &a) {
    int nc = 0;
    for(int i=0; i<a.size(); i++) {
        if(a[i] <=0) {
            swap(&a[i], &a[nc]);
            nc++;
        }
    }
    return nc;
}

int fmp(vector<int> &a) {
    int i=0;
    for(; i<a.size(); i++){
        if (abs(a[i]) - 1 < a.size() && a[abs(a[i]) - 1] > 0) {
            a[abs(a[i]) - 1] = - a[abs(a[i]) - 1];
        }
    }

    for(i=0; i<a.size(); i++) {
        if (a[i] > 0)
            return i+1;
    }
    return a.size() + 1;
}

int fm(vector<int> &a) {
    int nc = mntl(a);
    vector<int> sa(a.begin() + nc, a.begin() + a.size());
    return fmp(sa);
}

int solution(vector<int> &a) {
    return fm(a);
}
