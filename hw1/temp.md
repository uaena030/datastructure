 if (first == 1){
        //printf("1\n");
        //printf("x = %d,y = %d\n", new_y, 10 - new_x);
        runtime ++;
        dijkstra(n - 1 - src1[1], src1[0], n - 1 - dst2[1], dst2[0], maze, n, new_x, new_y, n - 1 - dst2[1], dst2[0]);
        //printf("ball1 second success\n");
        //printf("x = %d,y = %d\n", new_x, new_y);
        check = 1;
        dijkstra(new_x, new_y, n - 1 - dst1[1], dst1[0], maze, n, n - 1 - src1[1], src1[0], -100, -100);
        return 0;
    }
    else if (first == 2){
        //printf("2\n");
        runtime++;
        dijkstra(n - 1 - src2[1], src2[0], n - 1 - dst1[1], dst1[0], maze, n, n - 1 - src1[1], src1[0], n - 1 - dst2[1], dst2[0]);
        check = 1;
        dijkstra(n - 1 - src1[1], src1[0], n - 1 - dst2[1], dst2[0], maze, n, n - 1 - src1[1], src1[0], -100, -100);
        return 0;
    }
    runtime++;
    check = 1;
    dijkstra(new_x, new_y, n - 1 - dst2[1], dst2[0], maze, n, n - 1 - src1[1], src1[0], -100, -100);
    //printf("src1_x = %d, src1_y = %d\n", new_x, new_y);
    //check = 1;
    //dijkstra(new_x, new_y, n - 1 - dst2[1], dst2[0], maze, n, src2[0], src2[1]);
    return 0;