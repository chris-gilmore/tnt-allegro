## Build `tnt-allegro`

### Install dependencies
Redhat-based
```
$ sudo dnf install allegro5-devel allegro5-addon-image-devel libconfig-devel enet-devel
```
Debian-based
```
$ sudo apt-get install liballegro5-dev liballegro-image5-dev libconfig-dev libenet-dev
```

### Make `tnt-allegro`
```
$ mkdir ~/src
$ cd ~/src
$ git clone https://github.com/chris-gilmore/tnt-splat.git
$ git clone https://github.com/chris-gilmore/tnt-allegro.git
$ cd tnt-allegro
$ make
```

### Link to a default set of images
```
$ ln -snf images.default images
```

### Run
```
$ ./build/tnt
```

## Extract original images and anims from ROM

Place `tnt.z64` under `~/`.
```
$ crc32 tnt.z64
528a07fa

$ md5sum tnt.z64
7a28179b00734c9aa0f0609fafaafd5f

$ sha1sum tnt.z64
83fff25e82181a6993f28c91b9eeb8430396838b
```

### Install dependencies
Redhat-based
```
$ sudo dnf install lzo-devel python3-devel
$ pip3 install python-lzo
$ pip3 install pillow
```
Debian-based
```
$ sudo apt-get install python3-lzo python3-pil
```

### Download `n64tetristools`
```
$ cd ~/src
$ git clone https://github.com/chris-gilmore/n64tetristools.git
```

### Extract all non-anim images
```
$ cd ~/src/tnt-allegro
$ mkdir images.orig
$ cd images.orig
$ ~/src/n64tetristools/tnt-extract.py -v ~/tnt.z64 --all-images
```

### Extract all anim images
```
$ cd ~/src/tnt-allegro
$ mkdir anims.orig
$ cd anims.orig
$ ~/src/n64tetristools/tnt-extract.py -v ~/tnt.z64 --all-anims
```

### Link to original set of images and anims
```
$ cd ~/src/tnt-allegro
$ ln -snf images.orig images
$ ln -snf anims.orig anims
```

## Example usage

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
