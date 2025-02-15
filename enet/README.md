```
dnf: enet-devel
apt: libenet-dev
```

```
$ gcc -o enet_server enet_server.c -lenet
```

```
$ gcc -o enet_client enet_client.c -lenet -lallegro
```
