pkgname=madagascar-api
arch=('x86_64')
url="http://www.ahay.org/wiki/Main_Page"
licence=('GPL')
pkgver='3.2'
pkgrel=3
makedepends=('meson' 'blas' 'cblas' 'gcc-fortran' 'gcc-libs')


build()
{
    cd ..
    meson --prefix /usr --buildtype=plain builddir
    meson compile -C builddir
}

package()
{
    cd ..
    DESTDIR="$pkgdir" meson install -C builddir
}
