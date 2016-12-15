AC_PREREQ(2.59)
AC_INIT(openredalert, 0.1, damien.carol@gmail.com)
AM_INIT_AUTOMAKE([foreign subdir-objects dist-xz])

AC_PROG_CXX
AC_PROG_MAKE_SET

# Check for SDL
PKG_CHECK_MODULES([SDL], [sdl])
# Check for SDL_mixer library
PKG_CHECK_MODULES([SDL_mixer], [SDL_mixer])

AC_CONFIG_FILES([
    Makefile
])

AC_OUTPUT
