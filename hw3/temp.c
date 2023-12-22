int* BFS(int src, int end, int **maze, int size){
    node queue[size * size + 1];
    int head = 0, tail = 1;
    queue[0].x = src;
    queue[0].y = src;//(src, src) is starting point
    int node_x, node_y;
    int visited[size], ancient[1000000];
    for(int i = 0; i < size; i++){
        visited[i] = false;
    }
    visited[0] = true;
    // bfs
    while (head != tail){
        node_x = queue[head].x;
        node_y = queue[head].y;
        if (node_x == end && node_y == end){
            break;
        }
        for(int i = 0; i < size; i++){
            if(maze[node_y][i] == 1 && visited[i] == false){
                //node_x = 0 0
                queue[tail].x = node_y;//0 1
                queue[tail].y = i;//1
                visited[i] = true;
                node_x = node_y;
                node_y = i;
                tail++;
            }
        }
        head++;
        ancient[head] = queue[head].x;
        //printf("node_x = %d, node_y = %d\n", node_x, node_y);
    }
}