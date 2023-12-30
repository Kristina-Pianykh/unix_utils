# UNIX Utils

A playground to reimplement some UNIX utilities in a simplified way to get familiaried with the UNIX way of doing things.

A great deal of inspiration came from the book [Operating Systems: Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP/) by Remzi H. Arpaci-Dusseau and Andrea C. Arpaci-Dusseau written with wit and humour.

## Utilities

<details>
<summary>wcat</summary>
<br>

Usage: `wcat: file`

Takes a file name `file` as an input argument and prints its contents to STDOUT.
</details>

<details>
<summary>wgrep</summary>
<br>

Usage: `wgrep: searchterm [file ...]`

Takes a `searchterm` as 1st input argument and looks for it either in the file(s) provided after the search term or STDIN.
</details>

<details>
<summary>wzip and wunzip</summary>

Usage: `wzip: file1 [file2 ...]`

Takes file names as input arguments, compresses them using run-length encoding (RLE) and sends the result to STDOUT.


Usage: `wunzip: file1 [file2 ...]`

Takes file names of the files compressed with `wzip` as input arguments, decompresses them and sends the result to STDOUT.

Test with `make test_compression`.
</details>

<details>
<summary>reverse</summary>
<br>

Usage: `reverse`

Usage: `reverse file`

Usage: `reverse file1 file2`

Reads from STDIN or file and prints the lines in the reverse order either to `file2` or STDOUT.

Test with `make test_reverse`.
