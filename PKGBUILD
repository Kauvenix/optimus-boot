# Maintainer: kauvenix <kauvenix@gmail.com>
pkgname=optimus-boot
pkgver=0.1
pkgrel=1
pkgdesc=""
licence='MIT'
arch=('x86_64')

build() {
  cmake -B build \
    -S .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/usr

  cmake --build build
}

package() {
  install -Dm755 "build/optimus-boot" \
    "$pkgdir/usr/bin/optimus-boot"

  install -Dm644 "optimus-boot.service" \
    "$pkgdir/usr/lib/systemd/system/optimus-boot.service"
}

post_install() {
  systemctl daemon-reload
}

post_upgrade() {
  systemctl daemon-reload
}

post_remove() {
  systemctl daemon-reload
}
