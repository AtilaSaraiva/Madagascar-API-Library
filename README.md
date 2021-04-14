---
title: Madagascar API fork
author: Átila Saraiva Quintela Soares
---

# Intro

This repo offers the [Madagascar API library](http://www.ahay.org/wiki/Main_Page) for development of seismic processing tools. I've been conflicted by the idea of having to ask the user of my projects to download and install the Madagascar as a requirement to build it. I managed to also port it to a far superior build helper called [meson](https://mesonbuild.com/index.html).

# Dependencies

+ meson
+ fortran, c and c++ compiler
+ c math library
+ blas and cblas

# How to build

Just run:

```
meson setup builddir
meson compile -C builddir
```

If you are fortunate enough to use an Arch Linux distribution, you'll need only to run:

```
makepkg
```

and hopefully all of the dependencies will be pulled (or so it should, I still have to improve my PKGBUILD skills).

There are some sample codes for the three different languages so you can attest that it works.

# How to install on your system

It is really advised to just use this repo as a subproject on your build. Another good option is to create a package for your distribution. For those brave enough, the command is this:

```
meson install
```

Or for Arch Linux:

```
makepkg -i
```

A pkg-config file will be generated, so that you can use this library on your Cmake projects without worry.

Cheers!
