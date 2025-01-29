```
$ make
```

Record player's moves to file `./saved_moves` if it does not exist, else replay moves from that file.
```
$ ./build/tnt-allegro --sprint --seed 0x6dd7e5ea --name "GILLY" ./saved_moves
```

Game type is one of `--marathon`, `--sprint` (default), or `--ultra`.

Default seed is `0x00000000`.

Default name is `""`.

Arg1 (optional) is file name for recording or replaying moves.
