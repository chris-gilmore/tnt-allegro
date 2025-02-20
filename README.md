```
$ make
```

Record player's moves to file `./saved_moves_0x05261ec7.001` if it does not exist, else replay moves from that file.
```
$ ./build/tnt --sprint --gameid 0x05261ec7 --name "GILLY" ./saved_moves_0x05261ec7.001
```

Game type is one of `--marathon`, `--sprint` (default), or `--ultra`.

Default gameid is random.

Default name is `"Player 0"`.

Arg1 (optional) is file name for recording or replaying moves.
