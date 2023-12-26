if(cc == true && Reqmem[i][j - 1] != 0 && j - 1 == 0){
                j = j - 1;
            }
            if(cc == true && Reqmem[i][j - 1] == 0 && j - 1 == 0){
                cc = false;
            }
            if(Reqmem[i][j - 1] != false && j > 0){
                j = j - 1;
            }
            if(Reqmem[i][j] > 1 && j == 0){
                cc = true;
            }