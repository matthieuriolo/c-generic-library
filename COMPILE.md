#summary explanation how you have to compile c-generic-library


# How to Compile

Like the most linux tools you can compile the library by using following shell commands;

```
./configure
make
```


The compiled libraries should be found in the directory ./lib. By default there should be a static and a dynamic library.


# Optionals builds

The units and test files are optionally. This means that the command above won't compile them! If you wish to compile the test and unit cases you have to call configure with the enabling flag.

```
./configure --enable-tests=yes --enable-units=yes
make
```


The units are based on the library http://check.sourceforge.net/. If you want to build the unit tests then you have to install the *check* library.

#Trouble?

Make sure that 2.67 version of autotools or later is installed. They can be downloaded from this source http://lists.gnu.org/archive/html/autoconf/2010-08/msg00010.html.
Make sure that you run make clean.
Make sure that your system is using libtool 2.2.6b from http://www.gnu.org/software/libtool/.
If you have problem by using the commands above you can recreate the configure script. You must install the version 2.68 from http://en.wikipedia.org/wiki/GNU_build_system autotools. To create the configuration script run the commands:



```
autoreconf -i --force
automake --add-missing
```



# Mac OS X

On Mac OS X you have to install the autotools by hand! If you have already installed Xcode the existing autotools does not match the needed version and will fail. There are two ways to upgrade the building system.

1. Download and install the applications *autoconf*, *automake*, *m4* and *libtool*. If you do this version of "upgrading", please mind that Xcode may fails by trying to build stuff and you can only restore Xcode by downloading the whole package (something around 3GB) - don't choose this way!

2. Use [http://www.macports.org/ MacPort] to install the application above.

```
sudo port install autoconf automake m4 libtool
```

Create a copy of the existing build system

```
sudo cp /usr/bin/autoconf /usr/bin/autoconf-old
...
```

Create a symlink to the new building system

```
sudo ln -s /opt/local/bin/autoconf /usr/bin/autoconf
...
```

If Xcode fails you still have your old building system. Just rename it and you're fine.
