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

## Usage
```
Usage: ./build/tnt [options] [FILE [DIR]]

Positional arguments:
  FILE           Record moves to FILE if does not exist, else replay moves from FILE
  DIR            Save frames to DIR if replaying moves from FILE

Options:
  -h, --help     show this help message
  -v, --verbose  enable verbose output
  -n NUMPLAYERS  (default: 1)
  -o OPPONENT    (default: Off) 1=Easy 2=Medium 3=Hard 4=Very hard 5=Master
  -0 NAME        (default: 'PLAYER 0')
  -1 NAME        (default: 'PLAYER 1')
  -2 NAME        (default: 'PLAYER 2')
  -3 NAME        (default: 'PLAYER 3')
  -s SCREEN      (default: random) 0=Mayan 1=Greek 2=Egyptian 3=Celtic 4=African 5=Japanese 6=Russian 7=Finale
  -g GAMEID      (default: random) GAMEID modulo 0x0C000000

game mode:
  Choose one of these game modes.  (default: Marathon)

  --sprint
  --ultra

garbage mode:
  Choose one of these garbage modes.  (default: None)

  --hotpotato
  --directed
```
