FROM archlinux/base
RUN pacman -Sy && pacman --noconfirm -S \
        git \
        boost \
        boost-libs \
        gmp \
        cmake \
        make \
        gcc \
        gcc-fortran \
        swig \
        openblas \
        lapacke \
        cblas \
        suitesparse \
        python3 \
        python-pytest \
        python-scipy \
        python-h5py \
        python-pip \
        python-lxml \
        python-packaging \
        cppunit \
        bullet \
        freetype2 \
        freeglut \
        glu
WORKDIR /home
ENV CI_PROJECT_DIR /home
COPY install_oce.sh /home/install_oce.sh
RUN sh /home/install_oce.sh

