# Sudoku Solver

Given a 9x9 Sudoku puzzle, solve it using only the "naked digit" technique without any brute force approach.

The solver identifies cells that have only one possible candidate and fills them automatically. The program uses binary representation to track possible candidates for each empty cell.

The Sudoku input uses the notation from sudoku.coach (81-character string) which can be used for debugging and testing different puzzles.

## Example Output
```
+---+---+---+
|4  | 6 |  1|
| 2 | 38|   |
|31 |  4| 5 |
+---+---+---+
|5  |   |   |
| 38|   |7 9|
|   |   |  3|
+---+---+---+
|   | 1 |875|
|  6|9 3|   |
|7  | 2 |   |
+---+---+---+
Row 7 - Col 6 - Value 6
Row 7 - Col 4 - Value 4
...

+---+---+---+
|489|567|321|
|625|138|497|
|317|294|658|
+---+---+---+
|574|389|162|
|138|652|749|
|962|741|583|
+---+---+---+
|293|416|875|
|856|973|214|
|741|825|936|
+---+---+---+

```
