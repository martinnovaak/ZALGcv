# Knight Shortest Path Algorithm

This algorithm finds the shortest path for a knight on a chessboard from one square to another using breadth-first search.

## Input

- from_x, from_y: 2D coordinates of the source square
- to_x, to_y: 2D coordinates of the destination square
- n: the size of the chessboard (n x n)
- chessboard: an array representing the chessboard with 4 sentinel ranks and 2 sentinel files, where -1 means an invalid square (sentinel square) and 0 means an unvisited square
- knight_moves: an array of offsets for the possible knight moves

## Output
- prev: a vector of previous squares in the shortest path
- chessboard: an array with the distances from the source marked on each visited square

## Pseudocode

```pseudocode
FUNCTION knight_shortest_path(from_x, from_y, to_x, to_y)
    // convert the coordinates to squares using a formula
    from = (from_x + 2) * (n + 2) + (from_y + 1)
    to = (to_x + 2) * (n + 2) + (to_y + 1)

    // create a queue for breadth-first search
    CREATE queue q
    // create a vector to store the previous squares in the path
    CREATE vector prev with size (n + 4) * (n + 2) and value -1

    // add the source square to the queue and mark it as visited
    ENQUEUE from to q
    SET chessboard[from] = 1

    // repeat until the queue is empty or the destination is reached
    WHILE q is not empty
        // remove the front square from the queue
        curr = DEQUEUE q

        // Don't implement if you want to find shortest path to every square.
        IF curr == to THEN
            BREAK
        ENDIF

        // loop through the possible knight moves from the current square
        FOR each move in knight_moves
            // calculate the next square using the offset
            next = curr + move
            // check if the next square is valid and not visited
            IF chessboard[next] == 0 THEN
                // add the next square to the queue and mark it as visited and previous square
                ENQUEUE next to q
                SET chessboard[next] = chessboard[curr] + 1
                SET prev[next] = curr
            ENDIF
        ENDFOR
    ENDWHILE

    IF destination was reached
        PRINT length of path
        PRINT "The path is:"
        SET curr = to
        WHILE curr is not from
            // convert the square to coordinates
            SET x to (square / (size + 2)) - 2
            SET y to (square % (size + 2)) - 1
            PRINT "(" + x + ", " + y + ")  "
            // update the current square to the previous square in the path
            curr = prev[curr];
        ENDWHILE
    ELSE
        print "There is no path from [from_x][from_y] to [to_x][to_y]"
    ENDIF
    // OPTIONAL:
    PRINT BOARD