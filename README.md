```
$ make
```

Record player's moves to file `./saved_moves_0x05261ec7.001` if it does not exist, else replay moves from that file.
```
$ ./build/tnt --sprint --screen 7 --gameid 0x05261ec7 --name "GILLY" ./saved_moves_0x05261ec7.001
```

Game type is one of `--marathon`, `--sprint` (default), or `--ultra`.

Default screen is random.

Default gameid is random.

Default name is `"PLAYER 0"`.

Arg1 (optional) is file name for recording or replaying moves.

Arg2 (optional) is dir name for saving frames as png files.

```
# Link
$ ln -s images.default images

# or Rename
$ mv images.default images
```
