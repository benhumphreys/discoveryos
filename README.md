# Discovery OS

A toy operating system.

## Running the operating system (Bochs)

We can run the operating system inside the [Bochs x86 emulator](http://bochs.sourceforge.net/).
On an Ubuntu system it can be installed like so:
```
apt-get install bochs bochs-x
```

To run the operating system inside Bochs execute:
```
bochs
```
Then press 'c' to continue execution, as Bochs will started in a paused state.

## Running the operating system (QEMU)

We can also run the operating system inside [QEMU](https://www.qemu.org/).
On an Ubuntu system it can be installed like so:
```
apt-get install qemu
```

QEMU doesn't support reading config from file, so unlike Bochs command line parameters are
required. Two helper scripts are included:

To run DiscoveryOS in QEMU without debugging:
```
./discoveryos-run.sh
```

To run in QEMU with GDB:
```
./discoveryos-debug.sh
```
Then press 'c' to continue execution, as QEMU/GDB will started in a paused state.
