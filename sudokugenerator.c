bool sudokugenerator(int **arr, int len) {
    
    int size = (int)sqrt(len);

    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++) {
            if((j + 1) % size == 0) {
                j = 0;
                i++;
            }
        }
    }
}