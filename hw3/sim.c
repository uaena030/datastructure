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

            if (cc == true)
            {
                j = j - 1;
            }
            if (Reqmem[i][j] > 1 && cc == false)
            {              // 49 36 2
                cc = true; // same requirement
            }
            if (Reqmem[i][j] == 2)
            {
                cc = false;
            }